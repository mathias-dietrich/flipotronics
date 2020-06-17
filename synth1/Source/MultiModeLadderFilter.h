//
//  MultiModeLadderFilter.h
//  synth1
//
//  Created by Mathias Dietrich on 15.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//
// http://www.willpirkle.com/Downloads/

#ifndef MultiModeLadderFilter_h
#define MultiModeLadderFilter_h

#include <stdio.h>
#include <JuceHeader.h>

#include <complex>
#include <iostream>
#include <valarray>
#include <cmath>


#include "Enum.h"
#include "Lowpass1.h"

class MultiModeLadderFilter{
public:
    MultiModeLadderFilter(){
        setCutoff(1000.0);
        setResonance(0.0);
        setFilterType(LPF4);
        setBoost(false);
        setSampleRate(44100.0);
    }
    inline float process(float x){
        if(m_filterType==OFF) return x;
        if(m_boost==true)x=x*(m_k+1.0);
        const float filterOutput = calculateCoefficients(x);
        return filterOutput;
    }
    inline void setCutoff(const float cutoff){
        m_f1.setCutoff(cutoff);
        m_f2.setCutoff(cutoff);
        m_f3.setCutoff(cutoff);
        m_f4.setCutoff(cutoff);
        m_cutoff = cutoff;
        setCoefficients();
    }
    inline void setResonance(const float res){
        m_k = res*4.0;
        m_alpha = 1.0/(1.0 + m_k*m_GAMMA);
    }
    inline void setBoost(const bool boost){
        m_boost = boost;
    }
    void setFilterType(const int filterType){
        m_filterType = filterType;
        switch (m_filterType) {
            case LPF1:
                m_a0 = 0.0;m_a1 = 1.0;m_a2 = 0.0;m_a3 = 0.0;m_a4 = 0.0;
                break;
            case LPF2:
                m_a0 = 0.0;m_a1 = 0.0;m_a2 = 1.0;m_a3 = 0.0;m_a4 = 0.0;
                break;
            case LPF3:
                m_a0 = 0.0;m_a1 = 0.0;m_a2 = 0.0;m_a3 = 1.0;m_a4 = 0.0;
                break;
            case LPF4:
                m_a0 = 0.0;m_a1 = 0.0;m_a2 = 0.0;m_a3 = 0.0;m_a4 = 1.0;
                break;
            case HPF1:
                m_a0 = 1.0; m_a1 = -1.0;m_a2 = 0.0;m_a3 = 0.0;m_a4 = 0.0;
                break;
            case HPF2:
                m_a0 = 1.0; m_a1 = -2.0;m_a2 = 1.0;m_a3 = 0.0;m_a4 = 0.0;
                break;
            case HPF3:
                m_a0 = 1.0; m_a1 = -3.0;m_a2 = 3.0;m_a3 = -1.0;m_a4 = 0.0;
                break;
            case HPF4:
                m_a0 = 1.0;m_a1 = -4.0;m_a2 = 6.0;m_a3 = -4.0;m_a4 = 1.0;
                break;
            case BPF2:
                m_a0 = 0.0;m_a1 = 2.0;m_a2 = -2.0;m_a3 = 0.0;m_a4 = 0.0;
                break;
            case BPF4:
                m_a0 = 0.0;m_a1 = 0.0;m_a2 = 4.0;m_a3 = -8.0;m_a4 = 4.0;
                break;
            case NF2:
                m_a0 = 1.0; m_a1 = -2.0;m_a2 = 2.0;m_a3 = 0.0;m_a4 = 0.0;
                break;
            case NF4:
                m_a0 = 1.0; m_a1 = -4.0;m_a2 = 8.0;m_a3 = -8.0;m_a4 = 4.0;
                break;
            case PF2:
                m_a0 = 1.0; m_a1 = -1.0;m_a2 = 1.0;m_a3 = 0.0;m_a4 = 0.0;
                break;
            case PF4:
                m_a0 = 1.0; m_a1 = -2.0;m_a2 = 3.0;m_a3 = -2.0;m_a4 = 1.0;
                break;
            default:
                break;
        }
    }
    
    inline void setSampleRate(const float sampleRate){
        m_f1.setSampleRate(sampleRate);
        m_f2.setSampleRate(sampleRate);
        m_f3.setSampleRate(sampleRate);
        m_f4.setSampleRate(sampleRate);
        m_sampleRate = sampleRate;
        setCoefficients();
    }
    inline float getSampleRate(){
        return m_sampleRate;
    }
    //based on transfer functions
    inline float magnitudePlot(float x){
        const float w = x/m_cutoff;
        const std::complex<float> j =  std::complex<float>(0.0,1.0);
        const std::complex<float> s = w*j;
        const std::complex<float> c = std::complex<float>(1.0,0.0);
        const std::complex<float> n = m_a0*(s+c)*(s+c)*(s+c)*(s+c)+m_a1*(s+c)*(s+c)*(s+c)
                                    +m_a2*(s+c)*(s+c)+m_a3*(s+c)+m_a4;
        const std::complex<float> d = (s+c)*(s+c)*(s+c)*(s+c)+m_k;
        const std::complex<float> N = n.real()*n.real()+n.imag()*n.imag();
        const std::complex<float> D = d.real()*d.real()+d.imag()*d.imag();
        const std::complex<float> H = sqrt(N/D);
        
        if(m_boost==true){
            return 20.0*log10f((1.0+m_k)*H.real());
        }
        
        return 20.0*log10f(H.real());
    }
    inline void reset(){
        m_f1.reset();
        m_f2.reset();
        m_f3.reset();
        m_f4.reset();
    }
    
private:
    inline void setCoefficients(){
        const float g = m_f1.getInstantaneousResponseGain();
        const float G = g/(1+g);
        m_GAMMA = G*G*G*G;
        m_beta1 = G*G*G/(1.0+g);
        m_beta2 = G*G/(1.0+g);
        m_beta3 = G/(1.0+g);
        m_beta4 = 1.0/(1.0+g);
    }
    float calculateCoefficients(const float x){
        const float s1 = m_f1.getFilterState()*m_beta1;
        const float s2 = m_f2.getFilterState()*m_beta2;
        const float s3 = m_f3.getFilterState()*m_beta3;
        const float s4 = m_f4.getFilterState()*m_beta4;
        const float SIGMA = s1 + s2 + s3 + s4;
        const float u = (x - m_k*SIGMA)*m_alpha;
        const float f1 = m_f1.process(u);
        const float f2 = m_f2.process(f1);
        const float f3 = m_f3.process(f2);
        const float f4 = m_f4.process(f3);
        return m_a0*u + m_a1*f1 + m_a2*f2 + m_a3*f3 + m_a4*f4;
    }
    int m_filterType;
    float m_cutoff;
    float m_k;
    float m_sampleRate;
    bool m_boost;
    
    float m_GAMMA;
    float m_beta1;
    float m_beta2;
    float m_beta3;
    float m_beta4;
    
    float m_alpha;
    
    float m_a0;
    float m_a1;
    float m_a2;
    float m_a3;
    float m_a4;
    
    Lowpass1 m_f1;
    Lowpass1 m_f2;
    Lowpass1 m_f3;
    Lowpass1 m_f4;
    
    typedef std::complex<double> Complex;
    typedef std::valarray<Complex> CArray;
    // Cooley–Tukey FFT (in-place)
    void fft2(CArray& x)
    {
        const size_t N = x.size();
        if (N <= 1) return;
        
        // divide
        CArray even = x[std::slice(0, N/2, 2)];
        CArray odd = x[std::slice(1, N/2, 2)];
        
        // conquer
        fft2(even);
        fft2(odd);
        
        // combine
        for (size_t k = 0; k < N/2; ++k)
        {
            Complex t = std::polar(1.0, -2.0 * M_PI * k / N) * odd[k];
            x[k] = even[k] + t;
            x[k+N/2] = even[k] - t;
        }
    }

    float fftMagnitudePlot(MultiModeLadderFilter filter,const int N){
        CArray x;
        x.resize(N);
        for (int i=0; i<N; i++) {
            x[i] = Complex(filter.process(i==0 ? 1 : 0),0);
        }
        fft2(x);
        float *buf = new float[N/2];
        float* normalizeBuf = new float[N/2];
        for (int i = 1; i<N/2; i++) {
            buf[i] = 20.0*log10f(sqrt(x[i].real()*x[i].real()+x[i].imag()*x[i].imag()));
            normalizeBuf[i] = filter.magnitudePlot(i*filter.getSampleRate()/N)/buf[i];
        }
        
        for (int i = 1; i<N/2; i++) {
            printf("%f  %f\n",((float)i*filter.getSampleRate()/N),normalizeBuf[i]*buf[i]);
        }
        float testPoint = (N/2-1)*filter.getSampleRate()/N;
        delete [] buf;
        delete [] normalizeBuf;
        return testPoint;
    }
};

/*int main(int argc, const char * argv[]) {
    MultiModeLadderFilter f;
    f.setCutoff(1000);
    f.setResonance(1.0);
    f.setFilterType(LPF4);
    f.setSampleRate(44100.0);
    f.setBoost(true);
    // FFT Plot will match magnitude of evaluations of transfer functions bode Plot
    printf("% f\n",f.magnitudePlot(fftMagnitudePlot(f, 1024)));
    return 0;
}
 */
#endif /* MultiModeLadderFilter_h */
