![Elden Mod Loader](https://github.com/techiew/EldenRingModLoader/blob/master/header.jpg)
A mod loader for Elden Ring which simply loads all .dlls found in the "mods" folder when the game starts. You can find the mods I've made for the mod loader in this repo: https://github.com/techiew/EldenRingMods

### Mod framework
If you want to develop a mod, I recommend checking out [ModUtils.h](https://github.com/techiew/EldenRingMods/blob/master/ModUtils.h) in the mods repo. This header-only library contains various helpful tools such as a signature scanner and a logger which logs to both std::out and log.txt inside your mods allocated folder (the logger automatically creates a folder for your mod which is based on the name of the .dll).

### Download
Download the mod loader: https://www.nexusmods.com/eldenring/mods/117

### Possible future features
~~- Runtime merging of multiple regulation.bin mods.~~
Mod Engine 2 handles this: https://github.com/soulsmods/ModEngine2 (not officially released yet, but a version is available on the ?ServerName? discord).