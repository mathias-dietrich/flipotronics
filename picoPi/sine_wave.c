/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * minicom -D /dev/tty.usbmodem0000000000001  -b 11500
 * https://github.com/raspberrypi/pico-examples/blob/master/flash/program/flash_program.c
 */

#include <stdio.h>
#include <math.h>

#include <sys/stat.h>
#include <fcntl.h>

#if PICO_ON_DEVICE
    #include "hardware/clocks.h"
    #include "hardware/structs/clocks.h"
#endif

#include "pico/stdlib.h"
#include "pico/audio_i2s.h"
#include "bsp/board.h"
#include "tusb.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/flash.h"

const uint LED_PIN = 25;

#define SYNTH_VERSION 2

#define UART_ID uart1
#define BAUD_RATE 31250

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define PARITY    UART_PARITY_NONE
#define DATA_BITS 8
#define STOP_BITS 1

#define SINE_WAVE_TABLE_LEN 2048
#define SAMPLES_PER_BUFFER 256
static float sine_wave_table[SINE_WAVE_TABLE_LEN];
static float saw_wave_table[SINE_WAVE_TABLE_LEN];

absolute_time_t taken;
int lastNote;

#define SAMPLERATE 96000

#define FLASH_TARGET_OFFSET (256 * 1024)
  
 #define FLASH_PAGE_SIZE (1u << 8)
 #define FLASH_SECTOR_SIZE (1u << 12)
 #define FLASH_BLOCK_SIZE (1u << 16)
const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
}

void checkFlash(){
    uint8_t random_data[FLASH_PAGE_SIZE];
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i)
        random_data[i] = rand() >> 16;

    printf("Generated random data:\n");
    print_buf(random_data, FLASH_PAGE_SIZE);

    // Note that a whole number of sectors must be erased at a time.
    printf("\nErasing target region...\n");
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    printf("Done. Read back target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    printf("\nProgramming target region...\n");
    flash_range_program(FLASH_TARGET_OFFSET, random_data, FLASH_PAGE_SIZE);
    printf("Done. Read back target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    bool mismatch = false;
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
        if (random_data[i] != flash_target_contents[i])
            mismatch = true;
    }
    if (mismatch)
        printf("Programming failed!\n");
    else
        printf("Programming successful!\n");
}

bool audioOk = false;

struct audio_buffer_pool *init_audio() {
    static audio_format_t audio_format = {
            .format = AUDIO_BUFFER_FORMAT_PCM_S16,
            .sample_freq = SAMPLERATE, 
            .channel_count = 1,
    };

    static struct audio_buffer_format producer_format = {
            .format = &audio_format,
            .sample_stride = 2
    };

    struct audio_buffer_pool *producer_pool = audio_new_producer_pool(&producer_format, 3,SAMPLES_PER_BUFFER); // todo correct size
    bool __unused ok;
    
    struct audio_i2s_config config = {
            .data_pin = 9,
            .clock_pin_base = 10,
            .dma_channel = 0,
            .pio_sm = 0,
    };

    const struct audio_format *output_format;
    output_format = audio_i2s_setup(&audio_format, &config);
    if (!output_format) {
        printf("Audio setup failed");
        panic("PicoAudio: Unable to open audio device.\n");
    }

    ok = audio_i2s_connect(producer_pool);
    assert(ok);
    printf("Audio setup ok");
    audioOk = true;
    audio_i2s_set_enabled(true);
    return producer_pool;
}

uint32_t step ;
const int multi = 1 << 16;
float tuning = 440.0;

uint32_t calcStep(float freq){
    int multi = 1 << 16;
    return ( multi * freq * (float)SINE_WAVE_TABLE_LEN / (float)SAMPLERATE);
}


void tud_mount_cb(void)
{
  printf("tud_mount_cb");
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    printf("tud_umount_cb");
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  printf("tud_suspend_cb");

}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  printf("tud_resume_cb");
}

int bcount = 0;
uint8_t b0;
uint8_t b1;
uint8_t b2;
// RX interrupt handler
static int chars_rxed = 0;

bool isOn;

float freqFromNoteNumber(uint8_t number, float tuning){
    float d = (number-69) / 12.0;
    return pow(2, d) * tuning;
}

void noteOn(uint8_t midiNote, uint8_t velocity){
    
    printf("note On %i %i  \n",midiNote, velocity);
    float freq = freqFromNoteNumber(midiNote, 440.0);
    step = calcStep(freq);
    isOn = true;
    lastNote = midiNote;
}

void noteOff(uint8_t midiNote){
    if(midiNote==lastNote){
        isOn = false;
    }
    printf("note Off %i  \n",midiNote);
}

void on_uart_rx() {
    chars_rxed++;
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        if(ch==144){
            bcount = 1;
            b0 = ch;
             continue;
        }
        if(ch==128){
            bcount = 1;
            b0 = ch;
            continue;
        }
        if(bcount==1){
            b1 = ch;
            bcount = 2;
             continue;
        }

         if(bcount==2){
            b2 = ch;
            bcount = 0;
            if(b0==144){
                noteOn(b1,b2);
                continue;
            }
            if(b0==128){
                noteOff(b1);
                 continue;
            }
        }
        chars_rxed++;
    }
}


int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
   
    // Midi UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ID, false);
     // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

    step = calcStep(440);
    stdio_init_all();

    //tusb_init();

    for (int i = 0; i < SINE_WAVE_TABLE_LEN; i++) {
        sine_wave_table[i] = 32767.0 * cosf(i * 2.0 * (float) (M_PI / SINE_WAVE_TABLE_LEN));
        saw_wave_table[i] = -32767.0 + i * 32767 / SINE_WAVE_TABLE_LEN;
    }

    int multi = 1 << 16;
    int pos = 0;
    uint32_t pos_max = 0x10000 * SINE_WAVE_TABLE_LEN;
    uint vol = 64;
    int lastNote = 0;
    bool isMidiMounted = false;

    // Init Audio
    struct audio_buffer_pool *ap = init_audio();
    printf("audio instance %i", ap);
    // LED on
    gpio_put(LED_PIN, 1);

// Main Loop ===========================================================================================
    while (true) {
        absolute_time_t tStart = get_absolute_time();

        //tud_task(); // tinyusb device task
        isMidiMounted =  tud_mounted();
        int c = getchar_timeout_us(0);
        if (c >= 0) {
            if (c == '1' ) lastNote = 1;
            if (c == '2' ) lastNote = 2;
            if (c == '3' ) lastNote = 3;
            if (c == '4' ) lastNote = 4;
            if (c == '5' ) lastNote = 5;
            if (c == '6' ) lastNote = 6;
            if (c == '7' ) lastNote = 7;
            if (c == '8' ) lastNote = 8;
            if (c == '9' ) lastNote = 9;
            if (c == '-' && vol) vol -= 1;
            if ((c == '=' || c == '+') && vol < 127) vol += 1;
            if (c == 'a' && step > 0x10000) step -= 0x10000;
            if (c == 's' && step < (SINE_WAVE_TABLE_LEN / 16) * 0x20000) step += 0x10000;
            if (c == 'q') {
                gpio_put(LED_PIN, 0);
                break;
            }

             if (c == 't') {
                printf("ÜREP FLash Test T\n");
                checkFlash();
                continue;
            }
            
            if (c == 'f') {
               struct stat sb;
               int Result = stat("/test.txt", &sb);
               printf("File Test   = %i \n", Result);
               if((Result != 0 ) || (sb.st_mode & S_IFDIR )) {
                    printf("File Test  does not exist \n");
               }
               continue;
            }
             if (c == 'd') {
                printf("==========================================\n");
                printf("Version: %i \n", SYNTH_VERSION );
                printf("Audio Setup %d \n", audioOk);
                printf("vol = %d, step = %i  \n", vol, step);
                printf("Midi Mounted = %i \n", isMidiMounted);
                printf("UART Received = %i \n", chars_rxed);
                printf("Time taken  = %u \n", us_to_ms(taken));
            }
           
        }else{
            // lastNote = -1;
        }

        uint8_t packet[4];
        // int status = tud_midi_receive( packet);

        struct audio_buffer *buffer = take_audio_buffer(ap, true);
        int16_t *samples = (int16_t *) buffer->buffer->bytes;
        for (uint i = 0; i < buffer->max_sample_count; i++) {
            if(isOn){
                samples[i] = (vol * ((int)sine_wave_table[pos >> 16u])) >> 7u; // 
                samples[i] += (vol * ((int)saw_wave_table[pos >> 16u])) >> 7u; //
            }else{
                samples[i] = 0;
            }
            pos += step;
            if (pos >= pos_max) pos -= pos_max;
        }
        buffer->sample_count = buffer->max_sample_count;
        give_audio_buffer(ap, buffer);
        absolute_time_t tEnd = get_absolute_time();
        taken = tEnd - tStart;
       // if(taken > 0){
           // printf("Time taken  = %u \n", us_to_ms(taken));
         //}

    }
    puts("\n");
    return 0;
}
