#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../audio_engine/FastSin.h"
#include "../audio_engine/AudioLib/ValueTables.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), reverb(44100)
{
    AudioLib::ValueTables::Init();
	CloudSeed::FastSin::Init();
    reverb.ClearBuffers(); // clear buffers before we start do dsp stuff.
  
	     
	     
	     
    // Add Juce Paramter for all Reverb Parameters (used Chorus Delay Preset)
    // https://github.com/ValdemarOrn/CloudSeed/blob/master/Factory%20Programs/Chorus%20Delay.json

    
    
    addParameter (inputMix = new juce::AudioParameterFloat ("inputMix", // parameter ID
                                                              "InputMix", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));
    addParameter (preDelay = new juce::AudioParameterFloat ("preDelay", // parameter ID
                                                              "PreDelay", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.07f));
    addParameter (lowPass = new juce::AudioParameterFloat ("lowPass", // parameter ID
                                                              "LowPass", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.29000008106231689f));
    addParameter (highPass = new juce::AudioParameterFloat ("highPass", // parameter ID
                                                              "HighPass", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));

    
    
    addParameter (tapCount = new juce::AudioParameterFloat ("tapCount", // parameter ID
                                                              "TapCount", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.36499997973442078f));
    addParameter (tapLength = new juce::AudioParameterFloat ("tapLength", // parameter ID
                                                              "TapLength", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              1.0f));
    addParameter (tapGain = new juce::AudioParameterFloat ("tapGain", // parameter ID
                                                              "TapGain", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              1.0f));
    addParameter (tapDecay = new juce::AudioParameterFloat ("tapDecay", // parameter ID
                                                              "TapDecay", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.86500012874603271));
    
    
    
    addParameter (diffusionEnabled = new juce::AudioParameterFloat ("diffusionEnabled", // parameter ID
                                                              "DiffusionEnabled", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              1.0f));
    addParameter (diffusionStages = new juce::AudioParameterFloat ("diffusionStages", // parameter ID
                                                              "DiffusionStages", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.4285714328289032f));
    addParameter (diffusionDelay = new juce::AudioParameterFloat ("diffusionDelay", // parameter ID
                                                              "DiffusionDelay", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.43500006198883057f));
    addParameter (diffusionFeedback = new juce::AudioParameterFloat ("diffusionFeedback", // parameter ID
                                                              "DiffusionFeedback", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.725000262260437f));
    addParameter (earlyDiffusionModAmount = new juce::AudioParameterFloat ("earlyDiffusionModAmount", // parameter ID
                                                              "EarlyDiffusionModAmount", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.50000005960464478f));
    addParameter (earlyDiffusionModRate = new juce::AudioParameterFloat ("earlyDiffusionModRate", // parameter ID
                                                              "EarlyDiffusionModRate", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.42500010132789612f));
    
    
    
    
    addParameter (lineCount = new juce::AudioParameterFloat ("lineCount", // parameter ID
                                                              "LineCount", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              1.0f));
    addParameter (lineDelay = new juce::AudioParameterFloat ("lineDelay", // parameter ID
                                                              "LineDelay", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.68499988317489624f));
    addParameter (lineDecay = new juce::AudioParameterFloat ("lineDecay", // parameter ID
                                                              "LineDecay", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.68000012636184692f));
    addParameter (lineModAmount = new juce::AudioParameterFloat ("lineModAmount", // parameter ID
                                                              "LineModAmount", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.59000003337860107f));
    addParameter (lineModRate = new juce::AudioParameterFloat ("lineModRate", // parameter ID
                                                              "LineModRate", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.46999993920326233f));

    
    addParameter (lateDiffusionEnabled = new juce::AudioParameterFloat ("lateDiffusionEnabled", // parameter ID
                                                              "LateDiffusionEnabled", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              1.0f));
    addParameter (lateDiffusionStages = new juce::AudioParameterFloat ("lateDiffusionStages", // parameter ID
                                                              "LateDiffusionStages", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.28571429848670959f));
    addParameter (lateDiffusionDelay = new juce::AudioParameterFloat ("lateDiffusionDelay", // parameter ID
                                                              "LateDiffusionDelay", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.54499995708465576f));
    addParameter (lateDiffusionFeedback = new juce::AudioParameterFloat ("lateDiffusionFeedback", // parameter ID
                                                              "LateDiffusionFeedback", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.65999996662139893f));
    addParameter (lateDiffusionModAmount = new juce::AudioParameterFloat ("lateDiffusionModAmount", // parameter ID
                                                              "LateDiffusionModAmount", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.619999885559082f));
    addParameter (lateDiffusionModRate = new juce::AudioParameterFloat ("lateDiffusionModRate", // parameter ID
                                                              "LateDiffusionModRate", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.42500019073486328f));


    
    
    
    
    addParameter (postLowShelfGain = new juce::AudioParameterFloat ("postLowShelfGain", // parameter ID
                                                              "PostLowShelfGain", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.5199999213218689f));
    addParameter (postLowShelfFrequency = new juce::AudioParameterFloat ("postLowShelfFrequency", // parameter ID
                                                              "PostLowShelfFrequency", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.31499990820884705f));
    addParameter (postHighShelfGain = new juce::AudioParameterFloat ("postHighShelfGain", // parameter ID
                                                              "PostHighShelfGain", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.83500003814697266f));
    addParameter (postHighShelfFrequency = new juce::AudioParameterFloat ("postHighShelfFrequency", // parameter ID
                                                              "PostHighShelfFrequency", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.73000013828277588f));
    addParameter (postCutoffFrequency = new juce::AudioParameterFloat ("postCutoffFrequency", // parameter ID
                                                              "PostCutoffFrequency", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.73499983549118042f));

 
    
 
    
        
    addParameter (tapSeed = new juce::AudioParameterFloat ("tapSeed", // parameter ID
                                                              "TapSeed", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0011500000255182385f));
    addParameter (diffusionSeed = new juce::AudioParameterFloat ("diffusionSeed", // parameter ID
                                                              "DiffusionSeed", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.00018899999849963933f));
    addParameter (delaySeed = new juce::AudioParameterFloat ("delaySeed", // parameter ID
                                                              "DelaySeed", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.00034699999378062785f));
    addParameter (postDiffusionSeed = new juce::AudioParameterFloat ("postDiffusionSeed", // parameter ID
                                                              "PostDiffusionSeed", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.00050099997315555811f));
    addParameter (crossSeed = new juce::AudioParameterFloat ("crossSeed", // parameter ID
                                                              "CrossSeed", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));
    
    
    
     
     
     
     addParameter (dryOutGain = new juce::AudioParameterFloat ("dryOut", // parameter ID
                                                               "DryOut", // parameter name
                                                               juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                               0.0f));
     addParameter (predelayOutGain = new juce::AudioParameterFloat ("predelayOut", // parameter ID
                                                               "PredelayOut", // parameter name
                                                               juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                               0.0f));
     addParameter (earlyOutGain = new juce::AudioParameterFloat ("earlyOut", // parameter ID
                                                               "EarlyOut", // parameter name
                                                               juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                               0.77999997138977051f));
     addParameter (mainOutGain = new juce::AudioParameterFloat ("mainOut", // parameter ID
                                                               "MainOut", // parameter name
                                                               juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                               0.74500006437301636f));


    
    
    
    addParameter (hiPassEnabled = new juce::AudioParameterFloat ("hiPassEnabled", // parameter ID
                                                              "HiPassEnabled", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));
    addParameter (lowPassEnabled = new juce::AudioParameterFloat ("lowPassEnabled", // parameter ID
                                                              "LowPassEnabled", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));
    addParameter (lowShelfEnabled = new juce::AudioParameterFloat ("lowShelfEnabled", // parameter ID
                                                              "LowShelfEnabled", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));
    addParameter (highShelfEnabled = new juce::AudioParameterFloat ("highShelfEnabled", // parameter ID
                                                              "HighShelfEnabled", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));
    addParameter (cutoffEnabled = new juce::AudioParameterFloat ("cutoffEnabled", // parameter ID
                                                              "CutoffEnabled", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              1.0f));
    addParameter (lateStageTap = new juce::AudioParameterFloat ("lateStageTap", // parameter ID
                                                              "LateStageTap", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              1.0f));
    addParameter (interpolation = new juce::AudioParameterFloat ("interpolation", // parameter ID
                                                              "Interpolation", // parameter name
                                                              juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                              0.0f));


    
    
    
    

	     
    // https://github.com/ValdemarOrn/CloudSeed/blob/master/Factory%20Programs/Hyperplane.json

    reverb.SetParameter(Parameter::InputMix, 0.1549999862909317);
    reverb.SetParameter(Parameter::PreDelay, 0.0);
    reverb.SetParameter(Parameter::HighPass, 0.57999998331069946);
    reverb.SetParameter(Parameter::LowPass, 0.9100000262260437);
    reverb.SetParameter(Parameter::TapCount, 0.41499990224838257);
    reverb.SetParameter(Parameter::TapLength, 0.43999996781349182);
    reverb.SetParameter(Parameter::TapGain, 1.0);
    reverb.SetParameter(Parameter::TapDecay, 1.0);
    reverb.SetParameter(Parameter::DiffusionEnabled, 1.0);
    reverb.SetParameter(Parameter::DiffusionStages, 0.4285714328289032);
    reverb.SetParameter(Parameter::DiffusionDelay, 0.27500024437904358);
    reverb.SetParameter(Parameter::DiffusionFeedback, 0.660000205039978);
    reverb.SetParameter(Parameter::LineCount, 0.72727274894714355);
    reverb.SetParameter(Parameter::LineDelay, 0.22500017285346985);
    reverb.SetParameter(Parameter::LineDecay, 0.794999897480011);
    reverb.SetParameter(Parameter::LateDiffusionEnabled, 1.0);
    reverb.SetParameter(Parameter::LateDiffusionStages, 1.0);
    reverb.SetParameter(Parameter::LateDiffusionDelay, 0.22999951243400574);
    reverb.SetParameter(Parameter::LateDiffusionFeedback, 0.59499990940093994);
    reverb.SetParameter(Parameter::PostLowShelfGain, 0.95999979972839355);
    reverb.SetParameter(Parameter::PostLowShelfFrequency, 0.23999994993209839);
    reverb.SetParameter(Parameter::PostHighShelfGain, 0.97500002384185791);
    reverb.SetParameter(Parameter::PostHighShelfFrequency, 0.78499996662139893);
    reverb.SetParameter(Parameter::PostCutoffFrequency, 0.87999981641769409);
    reverb.SetParameter(Parameter::EarlyDiffusionModAmount, 0.13499999046325684);
    reverb.SetParameter(Parameter::EarlyDiffusionModRate, 0.29000008106231689);
    reverb.SetParameter(Parameter::LineModAmount, 0.53999996185302734);
    reverb.SetParameter(Parameter::LineModRate, 0.44999989867210388);
    reverb.SetParameter(Parameter::LateDiffusionModAmount, 0.15999998152256012);
    reverb.SetParameter(Parameter::LateDiffusionModRate, 0.56000012159347534);
    reverb.SetParameter(Parameter::TapSeed, 0.00048499999684281647);
    reverb.SetParameter(Parameter::DiffusionSeed, 0.00020799999765586108);
    reverb.SetParameter(Parameter::DelaySeed, 0.00034699999378062785);
    reverb.SetParameter(Parameter::PostDiffusionSeed, 0.00037200000951997936);
    reverb.SetParameter(Parameter::CrossSeed, 0.800000011920929);
    reverb.SetParameter(Parameter::DryOut, 0.86500018835067749);
    reverb.SetParameter(Parameter::PredelayOut, 0.0);
    reverb.SetParameter(Parameter::EarlyOut, 0.8200000524520874);
    reverb.SetParameter(Parameter::MainOut, 0.79500007629394531);
    reverb.SetParameter(Parameter::HiPassEnabled, 1.0);
    reverb.SetParameter(Parameter::LowPassEnabled, 1.0);
    reverb.SetParameter(Parameter::LowShelfEnabled, 1.0);
    reverb.SetParameter(Parameter::HighShelfEnabled, 1.0);
    reverb.SetParameter(Parameter::CutoffEnabled, 1.0);
    reverb.SetParameter(Parameter::LateStageTap, 1.0);
    reverb.SetParameter(Parameter::Interpolation, 0.0);
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
	
	
    reverb.SetParameter(Parameter::InputMix, *inputMix);
    reverb.SetParameter(Parameter::HighPass, *highPass);
    reverb.SetParameter(Parameter::LowPass, *lowPass);
    reverb.SetParameter(Parameter::PreDelay, *preDelay);

    reverb.SetParameter(Parameter::DryOut, *dryOutGain);
    reverb.SetParameter(Parameter::PredelayOut, *predelayOutGain);
    reverb.SetParameter(Parameter::EarlyOut, *earlyOutGain);
    reverb.SetParameter(Parameter::MainOut, *mainOutGain);
    
    reverb.SetParameter(Parameter::TapCount, *tapCount);
    reverb.SetParameter(Parameter::TapLength, *tapLength);
    reverb.SetParameter(Parameter::TapGain, *tapGain);
    reverb.SetParameter(Parameter::TapDecay, *tapDecay);
  
    reverb.SetParameter(Parameter::DiffusionStages, *diffusionEnabled);
    reverb.SetParameter(Parameter::DiffusionStages, *diffusionStages);
    reverb.SetParameter(Parameter::DiffusionDelay, *diffusionDelay);
    reverb.SetParameter(Parameter::DiffusionFeedback, *diffusionFeedback);
    reverb.SetParameter(Parameter::EarlyDiffusionModAmount, *earlyDiffusionModAmount);
    reverb.SetParameter(Parameter::EarlyDiffusionModRate, *earlyDiffusionModRate);
    
    reverb.SetParameter(Parameter::LineCount, *lineCount);
    reverb.SetParameter(Parameter::LineDelay, *lineDelay);
    reverb.SetParameter(Parameter::LineDecay, *lineDecay);
    reverb.SetParameter(Parameter::LineModAmount, *lineModAmount);
    reverb.SetParameter(Parameter::LineModRate, *lineModRate);
    
    reverb.SetParameter(Parameter::LateDiffusionEnabled, *lateDiffusionEnabled);
    reverb.SetParameter(Parameter::LateDiffusionStages, *lateDiffusionStages);
    reverb.SetParameter(Parameter::LateDiffusionDelay, *lateDiffusionDelay);
    reverb.SetParameter(Parameter::LateDiffusionFeedback, *lateDiffusionFeedback);
    reverb.SetParameter(Parameter::LateDiffusionModAmount, *lateDiffusionModAmount);
    reverb.SetParameter(Parameter::LateDiffusionModRate, *lateDiffusionModRate);
    
    reverb.SetParameter(Parameter::PostLowShelfGain, *postLowShelfGain);
    reverb.SetParameter(Parameter::PostLowShelfFrequency, *postLowShelfFrequency);
    reverb.SetParameter(Parameter::PostHighShelfGain, *postHighShelfGain);
    reverb.SetParameter(Parameter::PostHighShelfFrequency, *postHighShelfFrequency);
    reverb.SetParameter(Parameter::PostCutoffFrequency, *postCutoffFrequency);
    
    reverb.SetParameter(Parameter::TapSeed,*tapSeed);
    reverb.SetParameter(Parameter::DiffusionSeed, *diffusionSeed);
    reverb.SetParameter(Parameter::DelaySeed, *delaySeed);
    reverb.SetParameter(Parameter::PostDiffusionSeed, *postDiffusionSeed);
    reverb.SetParameter(Parameter::CrossSeed, *crossSeed);

    reverb.SetParameter(Parameter::HiPassEnabled, *hiPassEnabled);
    reverb.SetParameter(Parameter::LowPassEnabled, *lowPassEnabled);
    reverb.SetParameter(Parameter::LowShelfEnabled, *lowShelfEnabled);
    reverb.SetParameter(Parameter::HighShelfEnabled, *highShelfEnabled);
    reverb.SetParameter(Parameter::CutoffEnabled, *cutoffEnabled);
    reverb.SetParameter(Parameter::LateStageTap, *lateStageTap);
    reverb.SetParameter(Parameter::Interpolation, *interpolation);
	
	
	
	
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // we only process stero signal, so we clear unused output buffers.
    for (auto i = 2; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // real dsp
    const float** in_sig =  buffer.getArrayOfReadPointers();
    float** out_sig =  buffer.getArrayOfWritePointers();
    reverb.Process(in_sig,out_sig, buffer.getNumSamples());
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
