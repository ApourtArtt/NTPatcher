# NTPatcher (Outdated)
It is coded in C++ with Qt on Qt Creator.
Simple soft allowing you to enable some forbiddden functionnalities on the MMORPG NosTale.

## Available functionnalities
- Zoomhack : you can dezoom as you want. You can also do some tricks by setting the camera right above your character, or even under the map. This is done by adding a jump to bypass their operations.
- CTRL+Z : due to a recent update, using the CTRL+Z combinaison to cancel the animation is impossible. Using it makes it doable. It is really easy to do : NOP two bytes.
- GfSkipper : starting NostaleClientX.exe with "gf" args isn't allowed. With this change, it is, but you will need a customed client (incoming) to make usage of it. A long jump was needed to achieve it.

## For developers
- Find manually (OllyDbg, Ghidra, Cheat engine are your best friends) OPs you want to modify, and by what.
- Save OPs pattern¹ and change every byte with \xXX (EB, for a short jump will become \xeb, or \xEB)
- Every value apt to change can be replaced by '?'.
- Do the same with the corrected pattern².

¹ Imagine OllyDbg gives you something like
```asm
006DC518   . C600 00        MOV BYTE PTR DS:[EAX],0
006DC51B   . 8D45 CC        LEA EAX,DWORD PTR SS:[EBP-34]
006DC51E   . 50             PUSH EAX
006DC51F   . 8D55 C8        LEA EDX,DWORD PTR SS:[EBP-38]
006DC522   . B8 01000000    MOV EAX,1
```
pattern would be `QByteArray pMyPattern"\xc6\x00\x00\x8d\x45\xcc\x50\x8d\x55\xc8\xb8\x01\x00\x00\x00"`.

² if you want to change the last line, `MOV EAX,1` by a NOP, the new pattern would become `QByteArray nMyPattern"\xc6\x00\x00\x8d\x45\xcc\x50\x8d\x55\xc8\x90\x90\x90\x90\x90"`

*Please, note that \x00 will be considered as a "end of string" character. If you really want to use it, you will need to use QByteArray::append('\0'); (see example in MainWindow.cpp) to handle it. If this is not necessary, just remove '\x00' by '?'.*

## For players
- Download a [release](https://github.com/ApourtArtt/NTPatcher/releases).
- Enjoy.



NOT UPDATED - Don't use it
