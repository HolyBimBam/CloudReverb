#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "../audio_engine/ReverbController.h"

//==============================================================================
class AudioPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    CloudSeed::ReverbController reverb;
	
    juce::AudioParameterFloat* inputMix;
    juce::AudioParameterFloat* lowPass;
    juce::AudioParameterFloat* highPass;
    juce::AudioParameterFloat* preDelay;

    juce::AudioParameterFloat* dryOutGain;
    juce::AudioParameterFloat* predelayOutGain;
    juce::AudioParameterFloat* earlyOutGain;
    juce::AudioParameterFloat* mainOutGain;
    
    
    juce::AudioParameterFloat* tapCount;
    juce::AudioParameterFloat* tapLength;
    juce::AudioParameterFloat* tapGain;
    juce::AudioParameterFloat* tapDecay;

    juce::AudioParameterFloat* lateDiffusionEnabled;
    juce::AudioParameterFloat* diffusionEnabled;
    juce::AudioParameterFloat* diffusionStages;
    juce::AudioParameterFloat* diffusionDelay;
    juce::AudioParameterFloat* diffusionFeedback;
    juce::AudioParameterFloat* earlyDiffusionModAmount;
    juce::AudioParameterFloat* earlyDiffusionModRate;
    
    juce::AudioParameterFloat* lineCount;
    juce::AudioParameterFloat* lineDelay;
    juce::AudioParameterFloat* lineDecay;
    juce::AudioParameterFloat* lineModAmount;
    juce::AudioParameterFloat* lineModRate;
    
    
    juce::AudioParameterFloat* lateDiffusionStages;
    juce::AudioParameterFloat* lateDiffusionDelay;
    juce::AudioParameterFloat* lateDiffusionFeedback;
    juce::AudioParameterFloat* lateDiffusionModAmount;
    juce::AudioParameterFloat* lateDiffusionModRate;
    
    juce::AudioParameterFloat* postLowShelfGain;
    juce::AudioParameterFloat* postLowShelfFrequency;
    juce::AudioParameterFloat* postHighShelfGain;
    juce::AudioParameterFloat* postHighShelfFrequency;
    juce::AudioParameterFloat* postCutoffFrequency;

    juce::AudioParameterFloat* tapSeed;
    juce::AudioParameterFloat* diffusionSeed;
    juce::AudioParameterFloat* delaySeed;
    juce::AudioParameterFloat* postDiffusionSeed;
    juce::AudioParameterFloat* crossSeed;    
    
    juce::AudioParameterFloat* hiPassEnabled;
    juce::AudioParameterFloat* lowPassEnabled;
    juce::AudioParameterFloat* lowShelfEnabled;
    juce::AudioParameterFloat* highShelfEnabled;
    juce::AudioParameterFloat* cutoffEnabled;
    juce::AudioParameterFloat* lateStageTap;
    juce::AudioParameterFloat* interpolation;
	
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
