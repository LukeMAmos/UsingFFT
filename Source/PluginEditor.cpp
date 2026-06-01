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
    //For each xPos pixel inside the bar decide what binIndex they should represent , which means larger rectangles have a higehr resolution
    for(int xPos = bounds.getX() ; xPos < bounds.getTopRight().x ; xPos++){
        
        int binIndex = jmap(xPos, bounds.getX(), bounds.getTopRight().x ,0, (fftToDraw.getFFTSize() / 2));
        
        //Using the magnitude value to calculate where the line should start at
        int yStart = (int)jmap(fftToDraw.getMagnitudeDb(binIndex), -100.0f, 0.0f, (float)bounds.getTopRight().y , (float)bounds.getBottom());
        
        g.drawRect(xPos, yStart, 1, bounds.getBottom() - yStart);
    }
    
    //Draw a box around the lines
    
    //Label the axis
}

void UsingFFTAudioProcessorEditor::timerCallback()
{
    repaint();
}
