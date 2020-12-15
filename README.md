# CloudSeed AudioUnit & VST3 

CloudSeed is an algorithmic reverbation plugin. 

The reverbation algorithm is written by Valdemar Erlingsson who also implemented a VST Version for Windows [CloudSeed VST](https://github.com/ValdemarOrn/CloudSeed) 

I was studying the algorithm and tried to get it to work on my different Apple machines when I stumbled upon xunil-cloud's changes to use it with the JUCE Framework. 

Since it was only a bare implementation without a Graphical User Interface I tried my best in recreating Valdemars Windows Version.



The Build did not work for me but i'll leave it it, maybe it will help..


#####You can Download Prebuilt Versions here:

[VST3](https://github.com/HolyBimBam/CloudSeed_AU_VST3/raw/master/exports/CloudSeed.vst3.zip)

[AudioUnit](https://github.com/HolyBimBam/CloudSeed_AU_VST3/raw/master/exports/CloudSeed.component.zip)



## How to Build
##### 1. clone the repository

`git clone --recursive https://github.com/xunil-cloud/CloudSeed_AU_VST3.git`

##### 2. change directory into project folder and create build folder

`cd CloudSeedAUVST3 `

`mkdir build`

##### 3. run cmake command inside build folder

`cd build`

`cmake ../ -B .` (-B option specify a build directory)

`make`

## Credit

[CloudSeed VST](https://github.com/ValdemarOrn/CloudSeed) by Valdemar Erlingsson

[CloudReverb Juce Implementation](https://github.com/xunil-cloud/CloudReverb) by xunil-cloud

