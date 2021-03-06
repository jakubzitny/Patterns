#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <string>
#include "DrumTrack.h"
#include <vector>
#include <random>

//==============================================================================
/**
*/
class PatternsAudioProcessor  : public AudioProcessor
{
public:
    std::vector<DrumTrack*> mTracks;
    std::string debugText;

    //==============================================================================
    PatternsAudioProcessor();
    ~PatternsAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setMidiThrough(bool val) { mMidiThrough = val; }

private:
    std::random_device mRandomDevice;
    std::mt19937_64 mEngine;
    std::uniform_real_distribution<float> mDistribution;
    
    bool mMidiThrough;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatternsAudioProcessor)
};
