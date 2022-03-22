![Elden Mod Loader](https://github.com/techiew/EldenRingModLoader/blob/master/header.jpg)
A mod loader for Elden Ring which simply loads all .dlls found in the "mods" folder when the game starts. You can find the mods I've made for the mod loader in this repo: https://github.com/techiew/EldenRingMods

### Mod utilities
If you want to develop a mod, I recommend checking out [ModUtils.h](https://github.com/techiew/EldenRingMods/blob/master/ModUtils.h) in the mods repo. This header contains various helpful tools such as a signature scanner and a logger which logs to both std::out and log.txt inside your mods allocated folder (the logger automatically creates a folder for your mod which is based on the name of the .dll).

Download the mod loader: https://www.nexusmods.com/eldenring/mods/117

### Planned features:
- Runtime merging of multiple regulation.bin mods.
- File injection/redirection of individual loose files, removing the need to unpack the game.

If you want to work on any of these features, please reach out so we can coordinate our efforts. Also feel free to come with suggestions or code contributions to any repo that I have.
