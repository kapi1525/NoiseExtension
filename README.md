
## ![Logo](Noise/Icon.png) Noise Object

Noise object is Clickteam Fusion extension that allows you to use most of [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) library funtionality in Clickteam Fusion and add some fancy noise stuff.


### Examples

There are some [included examples](Examples/Noise/), you can also find them in your Clickteam Fusion 2.5/Examples/Noise/ folder after you installed Noise.


### Wiki / Help file

I recently finaly created noise object wiki on github, its also automaticaly converted to help file that you can read offline.
Note: currently this wiki/help file is very much work in progress, not everythings is documented yet.


### Installing

To install Noise Object, just download [latest release](https://github.com/kapigames/NoiseExtension/releases/latest), unzip it and copy all files to correct directories in your Fusion install (Often: "C:\Program Files (x86)\Steam\steamapps\common\Clickteam Fusion 2.5\"), also this extension uses dark edif update checker this means you will receive notifications about updates in Fusion, updating extension is the same as installing it, just override old files.


### Building

To build noise yourself you need Visual Studio 2022 with C/C++ toolkit and Android toolkit it you want to compile for Android.

You can open Noise.sln solution in Visual Studio and compile from VS or if you dont like VS like me use build.bat script.

Useing this command you will build entire noise object and install it to you CTF install (by default "C:\Program Files (x86)\Steam\steamapps\common\Clickteam Fusion 2.5\" change it if you need, don't commit that change of course.)
```cmd
build.bat --install
```

Other build.bat flags:

- `--fast` Build only Windows Edittime and Runtime.
- `--debug` Build useing debug configuration.
- `--clean` Clean the build directory and build.
- `--bundle` Bundle noise object, help file and example into single zip file.
- `--sdkconfig` Create "FusionSDKConfig.ini" file with default settings in parent directory.