# CloudSeed AudioUnit & VST3 (for Mac)

![screenshot](https://github.com/HolyBimBam/CloudSeed_AU_VST3/blob/master/exports/screenshot.png)


## Table of contents
* [General info](#general-info)
* [Download](https://github.com/HolyBimBam/CloudSeed_AU_VST3/releases)
* [Documentation](#documentation)
* [How to Build](#how-to-build)
* [ToDo](#to-do)
* [Credits](#credits)


## General Info

CloudSeed is a artificial reverbation plugin based on the reverbation algorithm written by Valdemar Erlingsson who also implemented a VST Version for Windows [CloudSeed VST](https://github.com/ValdemarOrn/CloudSeed) 

I was studying the algorithm and tried to get it to work on my different Apple machines when I stumbled upon [xunil-cloud's changes](https://github.com/xunil-cloud/CloudReverb) to use it with the JUCE Framework. 

Since it was only a bare implementation without a Graphical User Interface I tried my best in recreating Valdemars Windows Version.



## Download

Download the latest version of Cloud Seed for Mac from the [Releases Page](https://github.com/HolyBimBam/CloudSeed_AU_VST3/releases)



## Documentation
For the Documentation head over to the [original Documentation Page](https://github.com/ValdemarOrn/CloudSeed/tree/master/Documentation) to get an overview of the user interface and an explanation of the reverberation kernel.




## How to Build

The Build did not work for me. I used XCode for that but i'll leave it here, maybe it will help somebody.


##### 1. clone the repository



`git clone --recursive https://github.com/xunil-cloud/CloudSeed_AU_VST3.git`

##### 2. change directory into project folder and create build folder

`cd CloudSeedAUVST3 `

`mkdir build`

##### 3. run cmake command inside build folder

`cd build`

`cmake ../ -B .` (-B option specify a build directory)

`make`




## To Do

* Make it work with Logic

* Show Correct Scale for nonlinear Parameter

* Fix Loading Error when Preset it already selected

* Add Icons to Dials or a graphical Representation of what the individual Paramtere does

* Buy JUCE Licence and Remove Popup





## Credits

[CloudSeed VST](https://github.com/ValdemarOrn/CloudSeed) by Valdemar Erlingsson

[CloudReverb Juce Implementation](https://github.com/xunil-cloud/CloudReverb) by xunil-cloud

