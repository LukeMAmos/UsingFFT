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
class UsingFFTAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    UsingFFTAudioProcessorEditor (UsingFFTAudioProcessor&);
    ~UsingFFTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    UsingFFTAudioProcessor& audioProcessor;
    //Custom look and feel
    CustomLookAndFeel customLook;
    
    void drawFFT(juce::Graphics &g , FFT& fftToDraw, juce::Rectangle<int> bounds);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UsingFFTAudioProcessorEditor)
};
