#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
                                         ,private juce::Slider::Listener
                                         ,private juce::Button::Listener
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override;
    void buttonClicked (juce::Button* button) override;
//    void toggleDiffusion ();
    void callFactoryPreset(int index);
    void reloadState();
    
    void toggleDiffusionEnabled(bool on);
    void toggleLateDiffusionEnabled(bool on);
    void toggleHighPassEnabled(bool on);
    void toggleLowPassEnabled(bool on);
    void toggleLowShelfEnabled(bool on);
    void toggleHighShelfEnabled(bool on);
    void toggleCutoffEnabled(bool on);
    void toggleLateStageTap(bool on);
    void toggleInterpolation(bool on);

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    
    juce::Slider inputMixSlider;
    juce::Slider predelaySlider;
    juce::Slider lowCutSlider;
    juce::Slider highCutSlider;
    
    juce::Slider dryOutSlider;
    juce::Slider predelayOutSlider;
    juce::Slider earlyOutSlider;
    juce::Slider mainOutSlider;
    
    
    juce::Slider tapCountSlider;
    juce::Slider tapLengthSlider;
    juce::Slider diffusionDelaySlider;
    juce::Slider earlyDiffusionModAmountSlider;
    
    juce::Slider tapGainSlider;
    juce::Slider tapDecaySlider;
    juce::Slider diffusionFeedbackSlider;
    juce::Slider earlyDiffusionModRateSlider;


    juce::Slider lineDelaySlider;
    juce::Slider lineModAmountSlider;
    juce::Slider lateDiffusionDelaySlider;
    juce::Slider lateDiffusionModAmountSlider;
    
    juce::Slider lineDecaySlider;
    juce::Slider lineModRateSlider;
    juce::Slider lateDiffusionFeedbackSlider;
    juce::Slider lateDiffusionModRateSlider;

    
    juce::Slider postLowShelfFrequencySlider;
    juce::Slider postHighShelfFrequencySlider;
    juce::Slider postCutoffFrequencySlider;
    
    juce::Slider postLowShelfGainSlider;
    juce::Slider postHighShelfGainSlider;
    juce::Slider crossSeedSlider;
    
    
    juce::Slider lineCountSlider;
    juce::Slider diffusionStagesSlider;
    juce::Slider lateDiffusionStagesSlider;
    
    
    juce::Slider tapSeedSlider;
    juce::Slider diffusionSeedSlider;
    juce::Slider delaySeedSlider;
    juce::Slider postDiffusionSeedSlider;
    
    
    //ToggleButton
    juce::TextButton diffusionEnabledButton {"On"};
    juce::TextButton lateDiffusionEnabledButton {"On"};
    juce::TextButton hiPassEnabledButton {"Off"};
    juce::TextButton lowPassEnabledButton {"Off"};
    juce::TextButton lowShelfEnabledButton {"Off"};
    juce::TextButton highShelfEnabledButton {"Off"};
    juce::TextButton cutoffEnabledButton {"On"};
    juce::TextButton lateStageTapButton {"Post"};
    juce::TextButton interpolationButton {"Off"};
    
    juce::ComboBox presetSelector;
    int selectedPreset = {-1};

    
    int firstRow, firstCol, secondRow, potSize, firstRowFont, secondRowFont, secondCol, thirdCol, fourthCol, thirdRowFont;

public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> inputMixSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> predelaySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lowCutSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> highCutSliderAttach;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> dryOutSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> predelayOutSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> earlyOutSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mainOutSliderAttach;
 
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> tapCountSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> tapLengthSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> diffusionDelaySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> earlyDiffusionModAmountSliderAttach;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> tapGainSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> tapDecaySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> diffusionFeedbackSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> earlyDiffusionModRateSliderAttach;
    
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lineDelaySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lineModAmountSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lateDiffusionDelaySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lateDiffusionModAmountSliderAttach;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lineDecaySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lineModRateSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lateDiffusionFeedbackSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lateDiffusionModRateSliderAttach;
    
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> postLowShelfFrequencySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> postHighShelfFrequencySliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> postCutoffFrequencySliderAttach;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> postLowShelfGainSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> postHighShelfGainSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> crossSeedSliderAttach;
    
    
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  lineCountSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  diffusionStagesSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  lateDiffusionStagesSliderAttach;
    
    //
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  tapSeedSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  diffusionSeedSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  delaySeedSliderAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment>  postDiffusionSeedSliderAttach;
    
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  diffusionEnabledButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  lateDiffusionEnabledButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  hiPassEnabledButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  lowPassEnabledButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  lowShelfEnabledButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  highShelfEnabledButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  cutoffEnabledButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  lateStageTapButtonAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment>  interpolationButtonAttach;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
