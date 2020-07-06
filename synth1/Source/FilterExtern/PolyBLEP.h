//
//  PolyBLEP.h
//  synth1
//
//  Created by Mathias Dietrich on 06.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef PolyBLEP_h
#define PolyBLEP_h

class PolyBLEP {
public:
    enum Waveform {
        SINE,
        COSINE,
        TRIANGLE,
        SQUARE,
        RECTANGLE,
        SAWTOOTH,
        RAMP,
        MODIFIED_TRIANGLE,
        MODIFIED_SQUARE,
        HALF_WAVE_RECTIFIED_SINE,
        FULL_WAVE_RECTIFIED_SINE,
        TRIANGULAR_PULSE,
        TRAPEZOID_FIXED,
        TRAPEZOID_VARIABLE
    };

    PolyBLEP(double sampleRate, Waveform waveform = SINE, double initialFrequency = 440.0);

    virtual ~PolyBLEP();

    void setFrequency(double freqInHz);

    void setSampleRate(double sampleRate);

    void setWaveform(Waveform waveform);

    void setPulseWidth(double pw);

    double get() const;

    void inc();

    double getAndInc();

    double getFreqInHz() const;

    void sync(double phase);

protected:
    Waveform waveform;
    double sampleRate;
    double freqInSecondsPerSample;
    double amplitude; // Frequency dependent gain [0.0..1.0]
    double pulseWidth; // [0.0..1.0]
    double t; // The current phase [0.0..1.0) of the oscillator.

    void setdt(double time);

    double sin() const;

    double cos() const;

    double half() const;

    double full() const;

    double tri() const;

    double tri2() const;

    double trip() const;

    double trap() const;

    double trap2() const;

    double sqr() const;

    double sqr2() const;

    double rect() const;

    double saw() const;

    double ramp() const;
};


#endif /* PolyBLEP_h */
