/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
UsingFFTAudioProcessorEditor::UsingFFTAudioProcessorEditor (UsingFFTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 800);
    setLookAndFeel(&customLook);
}

UsingFFTAudioProcessorEditor::~UsingFFTAudioProcessorEditor()
{
}

//==============================================================================
void UsingFFTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
}

void UsingFFTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void UsingFFTAudioProcessorEditor::drawFFT(juce::Graphics &g , FFT& fftToDraw, juce::Rectangle<int> bounds)
{
    //Function for drawing the FFT
    //using the bounds of the rectangle and jmap function to decide where to draw the lines 
}
