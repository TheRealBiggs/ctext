# Chrono Trigger Extender

<br>

## What is this?

CTExt is a replacement sqlite3.dll for the PC port of Chrono Trigger. Its main goals are to fix bugs and allow easy modding of the game.

## What does it do?

As of the time of writing, CTExt fixes one bug (diagonal movement stutter) and allows modding via loose files or by loading CTP files.

## What is planned for the future?

There are still bugs with music not pausing when entering a battle and diagonal movement stutter with the Epoch. There are also plans to implement a modding API to allow for mods that can achieve what simple file replacements can't.

## Where can I download it?

You can either compile CTExt yourself using Visual Studio 2022, or find pre-built releases on the Moogles & Mods Discord server.

## How do I install it?

If you are using a pre-built release of CText, just extract the .7z archive directly into the folder where Chrono Trigger is installed.

If you choose to compile CTExt yourself, you will need to rename Chrono Trigger's existing `sqlite3.dll` to `sqlite3.orig.dll`, then copy over the compiled `sqlite3.dll`, `ctext.dll`, `ctext.json`, and `loader.cfg` files to your Chrono Trigger installation folder.

## How do I uninstall it?

Delete `sqlite3.dll` from your Chrono Trigger installation folder and rename `sqlite3.orig.dll` to `sqlite3.dll`, or remove the `ctext.dll` entry in `loader.cfg`.

## What are all these files?

* `sqlite3.dll` is a proxy DLL for the original SQLite library that is used by Cocos2d, the game engine used by the PC port of Chrono Trigger. By using a local DLL file with the same name, we can force Chrono Trigger.exe to load our code, allowing us to inject hooks into the game. These hooks change how the code in the game works so that we can do things like redirecting file loading. `sqlite3.dll` itself does not apply any hooks and is simply a loader for other DLLs.
* `ctext.dll` is the main part of CTExt and contains all of the code and hooks.
* `ctext.json` is the configuration file for CText. With it, you can choose which built-in mods to apply, configure said mods, and set the load order of mods in the `\mods\` directory.
* `loader.cfg` is a line-separated file that tells `sqlite3.dll` which DLLs to load. By default, this file only includes `ctext.dll`, but other DLLs (like SpecialK) can be added to this list.

## How can I help?

You can contribute to CTExt in many ways!

* Tackle any of the current [issues](https://github.com/TheRealBiggs/ctext/issues).
* Contribute to the reverse-engineering effort that makes this work possible.
* Help test development releases and report any issues you may find.
* Show your support by sharing a link to this repo with your friends!
* Support me on [Ko-fi](https://ko-fi.com/therealbiggs)
