//
//  AudioSampleFifo.h
//  synth1
//
//  Created by Mathias Dietrich on 17.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AudioSampleFifo_h
#define AudioSampleFifo_h

#pragma once

template <typename FloatType>
class AudioSampleFifo
{
public:
    AudioSampleFifo (int ch=2, int size=1024) :
        abstractFifo (size),
        channels (ch)
    {
        jassert (size > 0);
        jassert (channels > 0);

        fifoBuffer.setSize (channels, abstractFifo.getTotalSize(), false, false, true);
        fifoBuffer.clear();
    }

    int writeSamplesToFifo (const AudioBuffer<FloatType>& buffer)
    {
        jassert (buffer.getNumChannels ()== channels);

        if (buffer.getNumSamples() > abstractFifo.getFreeSpace())
            return 0;

        int start1, size1, start2, size2;
        abstractFifo.prepareToWrite (buffer.getNumSamples(), start1, size1, start2, size2);

        if (size1 > 0)
            for (int ch = 0; ch < channels; ++ch)
                fifoBuffer.copyFrom (ch, start1, buffer, ch, 0, size1);

        if (size2 > 0)
            for (int ch = 0; ch < channels; ++ch)
                fifoBuffer.copyFrom (ch, start2, buffer, ch, size1, size2);

        abstractFifo.finishedWrite (size1 + size2);
        return size1 + size2;
    }

    int readSamplesFromFifo (AudioBuffer<FloatType>& buffer)
    {
        jassert (buffer.getNumChannels() == channels);

        if (abstractFifo.getNumReady() < buffer.getNumSamples())
            return 0;

        int start1, size1, start2, size2;
        abstractFifo.prepareToRead (buffer.getNumSamples(), start1, size1, start2, size2);

        if (size1 > 0)
            for (int ch = 0; ch < channels; ++ch)
                buffer.copyFrom (ch, 0, fifoBuffer, ch, start1, size1);

        if (size2 > 0)
            for (int ch = 0; ch < channels; ++ch)
                buffer.copyFrom (ch, size1, fifoBuffer, ch, start2, size2);

        abstractFifo.finishedRead (size1 + size2);
        return size1 + size2;
    }

    void setFifoSize (int newSize)
    {
        jassert (newSize > 0);
        abstractFifo.setTotalSize (newSize);
        fifoBuffer.setSize (channels, abstractFifo.getTotalSize(), false, false, true);
    }

    int getFifoSize() const noexcept
    {
        return abstractFifo.getTotalSize();
    }

    void setNumOfChannels (int newNumOfChannels)
    {
        jassert (newNumOfChannels > 0);
        channels = newNumOfChannels;
        fifoBuffer.setSize (channels, abstractFifo.getTotalSize(), false, false, true);
    }

    int getNumOfChannels() const noexcept
    {
        return channels;
    }

    int getFreeSpace() const noexcept
    {
        return abstractFifo.getFreeSpace();
    }

    int getNumReady() const noexcept
    {
        return abstractFifo.getNumReady();
    }

    void reset()
    {
        fifoBuffer.clear();
        abstractFifo.reset();
    }

    void copyWholeBuffer (AudioBuffer<FloatType>& buffer)
    {
        jassert (buffer.getNumChannels() == channels);
        jassert (buffer.getNumSamples() >= abstractFifo.getNumReady());

        int start1, size1, start2, size2;
        abstractFifo.prepareToRead (buffer.getNumSamples(), start1, size1, start2, size2);

        if (size1 > 0)
            for (int ch = 0; ch < channels; ++ch)
                buffer.copyFrom (ch, 0, fifoBuffer, ch, start1, size1);

        if (size2 > 0)
            for (int ch = 0; ch < channels; ++ch)
                buffer.copyFrom (ch, size1, fifoBuffer, ch, start2, size2);

        abstractFifo.finishedRead (0);
    }

private:
    AbstractFifo abstractFifo;
    AudioBuffer<FloatType> fifoBuffer;

    int channels;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSampleFifo)
};

#endif /* AudioSampleFifo_h */
