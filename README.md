# Chrono Trigger Extender

<br>

## What is this?

CTExt is an extension framework for the PC port of Chrono Trigger. Its main goals are to fix bugs and allow easy modding of the game.

## What does it do?

* Fixes the diagonal movement stutter bug by reverting to the original behaviour.
* Fixes the bug with music not resuming after a battle.
* Adds modding capabilities via loose files or by loading CTP files.
* Allows users to disable linear filtering on text and sprites to achieve a pixelated look.
* Enables font replacement and forcing a fixed font size for all text.
* Adds the ability to play audio during character dialogue. This feature was developed for [Echo-S CT](https://www.youtube.com/watch?v=hBHh6A83HHc) to enable voice acting.

## What is planned for the future?

Check out the current [issues](https://github.com/TheRealBiggs/ctext/issues) to see what work is planned.

## Where can I download it?

You can compile CTExt yourself using Visual Studio 2022 or use a [pre-built release](https://github.com/TheRealBiggs/ctext/releases).

## How do I install it?

If you are using a pre-built release of CText, just extract the .7z archive directly into the folder where Chrono Trigger is installed.

If you choose to compile CTExt yourself, copy the compiled `winmm.dll`, `ctext.dll`, `ctext.json`, and `ChronoType.ttf` files to your Chrono Trigger installation folder.

## How do I uninstall it?

Delete `winmm.dll`, `ctext.dll`, `ctext.json`, and `ChronoType.ttf` from your Chrono Trigger installation folder.

## What are all these files?

* `winmm.dll` is a proxy for the Windows multimedia library. By placing it next to the game executable, Chrono Trigger loads the proxy, which forwards the game's multimedia calls to the system `winmm.dll` and loads `ctext.dll`.
* `ctext.dll` is the main part of CTExt and contains all of the code and hooks.
* `ctext.json` is the configuration file for CText. With it, you can choose which built-in mods to apply, configure said mods, and set the load order of mods in the `\mods\` directory.
* `ChronoType.ttf` is the font used by CTExt's text replacement features.

## How can I help?

You can contribute to CTExt in many ways!

* Tackle any of the current [issues](https://github.com/TheRealBiggs/ctext/issues).
* Contribute to the reverse-engineering effort that makes this work possible.
* Help test development releases and report any issues you may find.
* Show your support by sharing a link to this repo with your friends!
* Support me on [Ko-fi](https://ko-fi.com/therealbiggs).
