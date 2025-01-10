
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
  - 7zip (optional)
- html/webassembly
  - wasi-sdk
  - wasm-bindgen
  - npm (node.js)

### Actualy building

Configure:
- windows
  ```console
  meson setup bin -Deditor_build=<true or false>
  ```
- any other platform

  First update the cross file you will use in `cross` folder with correct paths to compilers on your system.
  ```console
  meson setup bin --cross-file cross/<cross file>
  ```
note: You can add `--buildtype release`, to make optimized release builds.
another note: wasm builds dont behave correctly in release builds, so compile them with `--buildtype plain` for now instead.

Compile:
```console
meson compile bin
```