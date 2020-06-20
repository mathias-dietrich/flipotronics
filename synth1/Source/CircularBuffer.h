//
//  CircularBuffer.h
//  synth1
//
//  Created by Mathias Dietrich on 20.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef CircularBuffer_h
#define CircularBuffer_h


#include <stdio.h>
#include <JuceHeader.h>

#include <vector>
#include <type_traits>
#include <assert.h>
#include <algorithm>
#include <type_traits>

template <class T>
class CircularBuffer
{
 public:
    CircularBuffer ()
        : bufferLength (0),
          writeHead (0),
          readHead (0){

          };

    ~CircularBuffer (){};

    void init (size_t length, T initialValue)
    {
        bufferLength = length;
        buffer.resize (bufferLength, initialValue);
    }

    inline void insertOne (const T val)
    {
        buffer[writeHead] = val;
        if (++writeHead >= bufferLength)
        {
            writeHead = 0;
        }
    }

    inline void insertMany (const T* values, size_t length)
    {
        for (int i = 0; i < length; i++)
        {
            buffer[writeHead] = values[i];
            if (++writeHead >= bufferLength)
            {
                writeHead = 0;
            }
        }
    }

    inline T getOne (size_t nFrom)
    {
        assert (nFrom <= bufferLength);
        long int offset = writeHead - nFrom;

        readHead = ((offset % bufferLength) + bufferLength) % bufferLength;
        T output = buffer[readHead];
        return output;
    }

    inline T getInterpolatedOne (float nFrom)
    {
        static_assert (std::is_arithmetic<T> (),
                       "must be float (or double) to get interpolated value");
    }

    inline std::vector<T> getMany (size_t nFrom)
    {
        assert (nFrom < bufferLength);
        std::vector<T> output (nFrom, NULL);
        readHead = writeHead;
        for (size_t i = 0; i < nFrom; i++)
        {
            output[i] = buffer[readHead];
            if (++writeHead >= bufferLength)
            {
                writeHead = 0;
            }
        }
        return output;
    }

    inline std::vector<T> getUnwrapped ()
    {
        std::vector<T>                    unwrapped;
        typename std::vector<T>::iterator oldestElement =
            buffer.begin () + writeHead;
        unwrapped.insert (unwrapped.begin (), oldestElement, buffer.end ());
        unwrapped.insert (unwrapped.end (), buffer.begin (),
                          buffer.begin () + (writeHead));

        return unwrapped;
    }

    size_t getLength () { return bufferLength; };
    void   flush ()
    {
        if (bufferLength > 0)
        {
            std::fill (buffer.begin (), buffer.end (), 0.);
            buffer.clear ();
        }
    }

 private:
    std::vector<T>  buffer;
    signed long int bufferLength;
    size_t          writeHead;
    size_t          readHead;
};

#endif /* CircularBuffer_h */
