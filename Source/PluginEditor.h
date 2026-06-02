/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
*/
class UsingFFTAudioProcessorEditor  : public juce::AudioProcessorEditor , public juce::Timer
{
public:
    UsingFFTAudioProcessorEditor (UsingFFTAudioProcessor&);
    ~UsingFFTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //==============================================================================
    void timerCallback() override; 
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    UsingFFTAudioProcessor& audioProcessor;
    //Custom look and feel
    CustomLookAndFeel customLook;
    
    std::vector<Complex> snapshot;
    
    float minFreq = 20.0f;
    float maxFreq = 20000.0f;
    
    void drawFFT(juce::Graphics &g , FFT& fftToDraw, juce::Rectangle<int> bounds, juce::Colour colour);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UsingFFTAudioProcessorEditor)
};
