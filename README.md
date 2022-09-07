# Elden Mod Loader
A mod loader for Elden Ring which simply loads all DLLs found in the "mods" folder when the game starts.

You can find the mods I've made for the mod loader in this repo: https://github.com/techiew/EldenRingMods

## Mod framework
If you want to develop a DLL mod, I recommend checking out [ModUtils.h](https://github.com/techiew/EldenRingMods/blob/master/ModUtils.h) in the mods repo. This header-only library contains various helpful tools such as a signature scanner, safe memory manipulation functions and a logger for troubleshooting.

## Load ordering
To specify a load order for a mod, create a folder with the same name as your DLL inside the "mods" folder. Inside the folder create "load.txt" and enter the load order number, which must go from 0 and up. Mods will load in order from lowest to highest number with an interval of 1 second. 

Alternatively, just add the dll name under the loadorder section of the ini  
```
[loadorder]
ErdTools = 1
```

Mods with a load order of 0 will be loaded instantly, even ignoring the load delay set inside "mod_loader_config.ini". I recommend not using 0 unless the mod is absolutely required to have an immediate effect, as race conditions may occur for some types of mods if they load too quickly.

If a load order is not specified for a mod, it will automatically receive a load order after the highest specified load order. Mods can have the same load order number, in which case they will load at the same time.

## Compilation
You will get an error. Remove the post-build event for the project: Project Properties -> Build Events -> Post-Build Event -> Command Line.

## Download
Download the mod loader: https://www.nexusmods.com/eldenring/mods/117

## Possible future features
~~- Runtime merging of multiple regulation.bin mods.~~

Mod Engine 2 handles this: https://github.com/soulsmods/ModEngine2 (not officially released yet, but a version is available on the ?ServerName? discord).
