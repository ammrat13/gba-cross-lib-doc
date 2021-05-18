# Header Checksum

Computes the header checksum of a GBA game. Takes in exactly four command line
parameters - the game name, the game code, the maker code, and the version
number. The maker code and version are expected to be numbers. The name, game
code, and maker code are trucated to 12, 4, and 2 characters respectively. The
version number is taken modulo 256 to fit it into one byte.

See [GBATek](https://mgba-emu.github.io/gbatek/#gbacartridgeheader) for more
details on the header and checksum.

Usage:
```
$ header_checksum.py game_name game_code maker_code version
```
Example:
```
$ header_checksum.py "CS2110ROCKS" "BCSE" "00" 0
```
