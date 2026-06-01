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
    // editor's size to whatever you need it to be
    setSize (800, 800);
    setLookAndFeel(&customLook);
    
    
    //Start the repaint timer
    startTimerHz(45);
}

UsingFFTAudioProcessorEditor::~UsingFFTAudioProcessorEditor()
{
}

//==============================================================================
void UsingFFTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    
    juce::Rectangle<int> bounds;
    bounds.setBounds(50, 50, 400, 400);
    
    drawFFT(g, audioProcessor.fourierTrans, bounds , juce::Colours::white);
}

void UsingFFTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void UsingFFTAudioProcessorEditor::drawFFT(juce::Graphics &g , FFT& fftToDraw, juce::Rectangle<int> bounds , juce::Colour colour)
{
    //Function for drawing the FFT
    //using the bounds of the rectangle and jmap function to decide where to draw the lines
    g.setColour(colour);
    
    //Drawing the Lines
    int Xwidth = bounds.getWidth() / (fftToDraw.getFFTSize() / 2);
    for(int i = 0 ; i < fftToDraw.getFFTSize() / 2 ; i++){
    
        int barTopY = jmap(fftToDraw.getMagnitudeDb(i), -100.0f, 0.0f, (float)bounds.getBottom(), (float)bounds.getY());
        
        g.fillRect(i*Xwidth, barTopY , Xwidth, bounds.getBottom() - barTopY);
    }
    
    //Draw a box around the lines
    
    //Label the axis 
}

void UsingFFTAudioProcessorEditor::timerCallback()
{
    repaint();
}
