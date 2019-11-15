# NTPatcher
Simple soft allowing you to enable some functionnalities (for the moment : Zoomhack and Ctrl+Z).

It is coded in C++ with Qt on Qt Creator.

## For developers :
- You need to get the address you want to change (thanks to OllyDbg, for example).
- You need to find which operation you want to replace by.
- Once done, you have to build the file (still through OllyDbg) as exe.
- You must put those files in Qt Creator's build folder and debug it.
- Save those value in the std::vector<s_patch>.
- Enjoy.
(This is extremely boring, but a good exercice for RE)

## For players :
- Download a release.
- Enjoy.

### How to improve this soft :
- Set an offset for the address.
- Nake a link between ASM op-code and hex/unicode value
