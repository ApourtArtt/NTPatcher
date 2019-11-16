# NTPatcher
It is coded in C++ with Qt on Qt Creator.
Simple soft allowing you to enable some forbiddden functionnalities on the MMORPG NosTale.

## Available functionnalities
- Zoomhack : you can dezoom as you want. You can also do some tricks by setting the camera right above your character, or even under the map.
- CTRL+Z : due to a recent update, using the CTRL+Z combinaison to cancel the animation is impossible. Using it makes it doable.

## For developers
- You need to get the address you want to change (thanks to OllyDbg, for example).
- You need to find which operation you want to replace by.
- Once done, you have to build the file (still through OllyDbg) as exe.
- You must put those files in Qt Creator's build folder and debug it.
- Save those value in the std::vector<s_patch>.
- Enjoy.

This is extremely boring, but a good exercice for RE, which was this project's goal.

## For players
- Download a release.
- Enjoy.

### How to improve this soft
- Set an offset for the address.
- Using pattern can probably help a lot.
