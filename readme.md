
# ![Logo](https://raw.githubusercontent.com/kapigames/NoiseExtensionResources/master/Icon.png) Noise Object

Noise object is Clickteam Fusion extension that allows you to use most of [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) library funtionality in Clickteam Fusion and adds some other fancy stuff.


## Screenshot

![Screenshot](https://raw.githubusercontent.com/kapigames/NoiseExtensionResources/master/ss.png)

(Noise sandbox.mfa example)


## Examples

There are some [included examples](Examples/Noise/), you can also find them in your Clickteam Fusion 2.5/Examples/Noise/ folder after you installed Noise.


## Wiki

I recently finaly created Noise Object [wiki on github](https://github.com/kapigames/NoiseExtension/wiki). There you can find more info about what each ACEs and properties do and some nice screenshots.


## Help file

I wanted to automaticaly convert github wiki to help file, but in the end it was too complicated and buggy so i scrapped it. Currently help button Noise object about properties just redirects you to github wiki.


## Installing

To install Noise Object, just download [latest release](https://github.com/kapigames/NoiseExtension/releases/latest), unzip it and copy all files to correct directories in your Fusion install (Often: "C:\Program Files (x86)\Steam\steamapps\common\Clickteam Fusion 2.5\"). Also this extension uses dark edif update checker, this means you will receive notifications about updates in Fusion. Updating extension is the same as installing it, just override old files.


## Building

To build Noise Object yourself you need Visual Studio 2022 with C/C++ toolkit and Android toolkit, if you want to compile for Android.

You can open Noise.sln solution in Visual Studio and compile it from VS or if you don't like VS like me, use build.bat script.

Using this command will build entire Noise Object and install it onto your Fusion installation (It should find it automaticaly using fusionpath.exe tool).
```cmd
build.bat --install --full --release
```

Other *usefull* build.bat flags:

- `--full` Build all targets (Windows and Android) (only Windows is built by default).
- `--release` Build using release configurations (Debug configurations are used by default).
- `--clean` Clean the build directory before building.
- `--bundle` Bundle Noise Object, help file and examples into single zip file.
- `--sdkconfig` Create "FusionSDKConfig.ini" file with default settings inside, in parent directory.
- `--verbose` Enables more msbuild logging
