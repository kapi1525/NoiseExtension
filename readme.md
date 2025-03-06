
# ![Icon](https://raw.githubusercontent.com/kapi1525/NoiseExtensionResources/master/Icon.png) Noise Object

Noise object is Clickteam Fusion extension that allows you to use all of [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) library funtionality in Clickteam Fusion and adds some other fancy stuff.


## Screenshot

![Screenshot](https://raw.githubusercontent.com/kapi1525/NoiseExtensionResources/master/ss.png)

(Noise sandbox.mfa example)


## Examples

There are some [included examples](Examples/Noise/), you can also find them in your Clickteam Fusion 2.5/Examples/Noise/ folder after you installed Noise.
Noise sandbox.mfa is great for experimenting with different settings.


## Wiki

I recently finaly created Noise Object [wiki on github](https://github.com/kapi1525/NoiseExtension/wiki). There you can find more info about what each ACEs and properties do and some nice screenshots.


## Help file

Github wiki is converted automaticaly to a help file and is bundled with noise, so you can read it offline.


## Installing

You can find Noise object in Clickteam Fusion's extension manager, or install it manualy by following install instructions below.

To install Noise Object, just download [latest release](https://github.com/kapi1525/NoiseExtension/releases/latest), unzip it and copy all files to correct directories in your Fusion install (Often: "C:\Program Files (x86)\Steam\steamapps\common\Clickteam Fusion 2.5\"). Also this extension uses dark edif update checker, this means you will receive notifications about updates in Fusion. Updating extension is the same as installing it, just override old files.


## Building

### Why no msbuild?

This is probably the first extension thats not built with msbuild (or visual studio) but with [mesonbuild](https://mesonbuild.com/) instead.
While porting to html/webassembly i didnt know if it would be easily posible to use a custom compiler with msbuild, so i switched to something i knew, and something i could use on linux.

### Build dependencies

- all platforms:
  - mesonbuild
  - ninja
- windows
  - visual studio c++ build tools
- android
  - android ndk
  - 7zip (optional, used with meson install)
- html/webassembly
  - wasi-sdk
  - npm (node.js)

### Actualy building

#### Configure the build directory:

Run `meson setup bin` with correct flags depending on target platform:
- For windows add `-Deditor_build=<true or false>` to select if you want to build for runtime or editor.
- For other platforms first, update a cross file in 'sdk/cross/' directory with correct paths to compilers on your system and then add `--cross-file <file path>`.

You can also use `--prefix <path>` to select where files should be installed if you're using `meson install`.

#### Compile:

`meson compile -C bin`

#### Compile and install:

`meson install -C bin`

This will install the files to correct directories, if you didn't specify a path with `--prefix` during setup, it will by default create a ./MFX/ folder and install everything there.