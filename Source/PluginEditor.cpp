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
    setSize (1000, 850);
    setLookAndFeel(&customLook);
    
    
    //Start the repaint timer
    startTimerHz(45);
}

UsingFFTAudioProcessorEditor::~UsingFFTAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void UsingFFTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    
    juce::Rectangle<int> bounds;
    bounds.setBounds(25, 25, 950, 800);
    
    drawFFT(g, audioProcessor.fourierTrans, bounds , juce::Colours::white);
    DBG("Drawing FFT");
}

void UsingFFTAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void UsingFFTAudioProcessorEditor::drawFFT(juce::Graphics &g , FFT& fftToDraw, juce::Rectangle<int> bounds , juce::Colour colour)
{
    float dBPoints[5]{0.0f , -5.0f , -20.0f , -60.0f , -100.0f};
    float freqHzPoints[12]{0.0f , 20.0f , 40.0f , 80.0f , 160.0f , 320.0f , 640.0f , 1280.0f , 2560.0f , 5120.0f , 10240.0f , 20000.0f };
    //Function for drawing the FFT
    //using the bounds of the rectangle and jmap function to decide where to draw the lines
    g.setColour(colour);
    
    {
        juce::ScopedLock lock(audioProcessor.criticalSection);
        snapshot = fftToDraw.getComplexOut();
    }
    
    //Drawing the Lines
    //For each xPos pixel inside the bar decide what binIndex they should represent , which means larger rectangles have a higehr resolution
    auto plotArea = bounds.reduced(10);
    for(int xPos = plotArea.getX() ; xPos < plotArea.getTopRight().x ; xPos++){
        
        int binIndex = jmap(xPos, plotArea.getX(), plotArea.getRight(), 0, fftToDraw.getFFTSize() / 2);
        
        float snapShotMag = std::sqrt( std::pow(snapshot[binIndex].real, 2) + std::pow(snapshot[binIndex].imaginary, 2));
        float snapShotValDB = 20.0f * std::log10( std::max(snapShotMag, 0.0000001f) );
        //Using the magnitude value to calculate where the line should start at
        float magnitudeDB = jlimit(-100.0f, 0.0f,snapShotValDB);
        
        int yStart = (int)jmap(magnitudeDB, -100.0f, 0.0f , (float)plotArea.getBottom(), (float)plotArea.getY());
        
        
        g.fillRect(xPos, yStart, 1, plotArea.getBottom() - yStart);
    }
    
    //Draw a box around the lines
    g.drawRect(bounds); 
    //Label the axis
}

void UsingFFTAudioProcessorEditor::timerCallback()
{
    repaint();
}
