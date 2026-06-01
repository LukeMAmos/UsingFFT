/*
  ==============================================================================

    FourierTransformation.h
    Created: 1 Jun 2026 9:22:10am
    Author:  Luke Amos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class CircBuff{
    
public:
    
    void prepare(double sampleRateIn, int bufferSamples , int channelIn ){
        
        sampleRate = sampleRateIn;
        buffer.resize(bufferSamples, 0);
        writePosition = 0;
        channel = channelIn;
        
    }

    void processSample(juce::AudioBuffer<float> &inputSamples){
        
        //Take the input samples and write over the oldest samples in the buffer
        
        auto samplesIn = inputSamples.getReadPointer(channel);
        
        for(int i = 0; i < inputSamples.getNumSamples() ; i++ ){
            
            buffer[(writePosition + i ) % buffer.size()] = samplesIn[i];

        }
        writePosition = (writePosition + inputSamples.getNumSamples()) % buffer.size();
    }
    
    float bufferValue(int samplePos){
        
        return buffer[samplePos];
    }
    
private:
    
    std::vector<float> buffer;
    int writePosition;
    double sampleRate;
    int channel;
    
};


class DFT{
    
public:
    
    void prepare();
    
    void setParameters();
    
    void process();

    
private:
    
};



class FFT{
    
public:
    
    void prepare();
    
    void setParameters();
    
    void process();

    
private:
    
};
