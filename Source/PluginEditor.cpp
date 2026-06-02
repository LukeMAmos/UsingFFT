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
    juce::Rectangle<int> boxBounds;
    boxBounds.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
    
    float dBPoints[5]{0.0f , -5.0f , -10.0f , -20.0f , -40.0f};
    float freqHzPoints[11]{ 20.0f , 40.0f , 80.0f , 160.0f , 320.0f , 640.0f , 1280.0f , 2560.0f , 5120.0f , 10240.0f , 20000.0f };
    //Function for drawing the FFT
    //using the bounds of the rectangle and jmap function to decide where to draw the lines
    g.setColour(colour);
    
    {
        juce::ScopedLock lock(audioProcessor.criticalSection);
        snapshot = fftToDraw.getComplexOut();
    }
    
    //Drawing the Lines
    //For each xPos pixel inside the bar decide what binIndex they should represent , which means larger rectangles have a higehr resolution
    auto labelArea = bounds.removeFromLeft(40); //Pre removing area for the labels
    auto freqLabelArea = bounds.removeFromBottom(20).removeFromRight(20);
    
    auto plotArea = bounds.reduced(5);

    auto fftSize = fftToDraw.getFFTSize();
    auto sampleRate = audioProcessor.getSampleRate();
    
    for(int xPos = plotArea.getX() ; xPos < plotArea.getTopRight().x ; xPos++){
        
        float t = (float)(xPos - plotArea.getX()) / (float)plotArea.getWidth();
        float freq = minFreq * std::pow(maxFreq / minFreq , t);

        int binIndex = (int)(freq * fftSize/sampleRate);
        binIndex = jlimit(0, fftSize/2 -1 , binIndex);
        
        float snapShotMag = std::sqrt( std::pow(snapshot[binIndex].real, 2) + std::pow(snapshot[binIndex].imaginary, 2));
        float snapShotValDB = 20.0f * std::log10( std::max(snapShotMag, 0.0000001f) );
        //Using the magnitude value to calculate where the line should start at
        float magnitudeDB = jlimit(-40.0f, 0.0f,snapShotValDB);
        
        int yStart = (int)jmap(magnitudeDB, -40.0f, 0.0f , (float)plotArea.getBottom(), (float)plotArea.getY());
        
        
        g.fillRect(xPos, yStart, 1, plotArea.getBottom() - yStart);
    }
    
    //Draw a box around the lines
    g.drawRect(boxBounds);
    
    //Draw the label
    for(auto db : dBPoints){
        
        int xpos = labelArea.getX();
        int ypos = jmap(db, -40.0f, 0.0f, (float)plotArea.getBottom(), (float)plotArea.getY());
        
        g.drawText(juce::String(db, 0), xpos, ypos - 6, 40, 12, juce::Justification::right);
        g.drawHorizontalLine(ypos, plotArea.getX(), plotArea.getRight());
    }
    
    //Draw the freq label
    
    for (auto freq : freqHzPoints){
        
        float t = std::log(freq / minFreq) / std::log(maxFreq / minFreq);
        int xpos = (int)(plotArea.getX() + t * plotArea.getWidth());
        int ypos = freqLabelArea.getBottom();
        
        g.drawText(juce::String(freq, 0), xpos, ypos - 6, 40, 12, juce::Justification::bottomLeft);
        g.drawVerticalLine(xpos, plotArea.getY(), plotArea.getBottom());
    }
}

void UsingFFTAudioProcessorEditor::timerCallback()
{
    repaint();
}
