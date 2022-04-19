# Elden Mod Loader
A mod loader for Elden Ring which simply loads all .dlls found in the "mods" folder when the game starts. Has support for load order customization which is required for some types of mods to work. 

You can find the mods I've made for the mod loader in this repo: https://github.com/techiew/EldenRingMods

## Mod framework
If you want to develop a mod of this type, I recommend checking out [ModUtils.h](https://github.com/techiew/EldenRingMods/blob/master/ModUtils.h) in the mods repo. This header-only library contains various helpful tools such as a signature scanner, safe memory manipulation functions and a logger which logs to both std::out and a log file simultaneously.

## Load ordering
To specify a load order for a mod, first create a folder inside the "mods" folder with the same name as the DLL. Inside this folder, create "load.txt" and enter a number. Mods are loaded in order from the lowest to the highest number (smallest possible number is 0). Mods with a load order of 0 will be loaded instantly, ignoring the load delay inside "mod_loader_config.ini". I recommend not using 0 unless the mod is absolutely required to have an immediate effect, as race conditions may occur (which in addition will differ from computer to computer).

## Compilation
You will get an error. Remove the post-build event for the project: Project Properties -> Build Events -> Post-Build Event -> Command Line.

## Download
Download the mod loader: https://www.nexusmods.com/eldenring/mods/117

## Possible future features
~~- Runtime merging of multiple regulation.bin mods.~~

Mod Engine 2 handles this: https://github.com/soulsmods/ModEngine2 (not officially released yet, but a version is available on the ?ServerName? discord).
