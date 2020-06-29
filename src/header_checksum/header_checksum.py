#!/usr/bin/env python

# header_checksum.py
# By: Ammar Ratnani
#
# Computes the header checksum of a GBA game. Takes in exactly four command 
# line parameters - the game name, the game code, the maker code, and the 
# version number. The maker code and version are expected to be numbers. The 
# name, game code, and maker code are trucated to 12, 4, and 2 characters 
# respectively. The version number is taken modulo 256 to fit it into one byte.

from sys import argv
from itertools import islice, chain, repeat


# Get command line arguments
GAME_NAME =   argv[1].upper() if len(argv) >= 2                       else ""
GAME_CODE =   argv[2].upper() if len(argv) >= 3                       else ""
MAKER_CODE =  argv[3]         if len(argv) >= 4 and argv[3].isdigit() else ""
VERSION_NUM = int(argv[4])    if len(argv) >= 5 and argv[4].isdigit() else 0


# Array we will use in computing the checksum
compute_array = [0] * 29

# Returns an iterator of length exactly `l` with elements taken from `it`
# It either truncates or pads with `pad` if needed
def take_exactly(it, l, pad=None):
    return islice(
        chain(it, repeat(pad)),
        0, l
    )

# Populate the array
compute_array[0:12]  = take_exactly( map(ord,GAME_NAME), 12, pad=0)
compute_array[12:16] = take_exactly( map(ord,GAME_CODE),  4, pad=0)
compute_array[16:18] = take_exactly( map(ord,MAKER_CODE), 2, pad=0)

compute_array[18] = 0x96  # Fixed value
compute_array[19] = 0x00  # Main unit code
compute_array[20] = 0x00  # Device type

compute_array[21:28] = [0x00]*7  # Reserved space

compute_array[28] = VERSION_NUM % 0x100


# Compute as described on GBATek and in devKit's `gbafix`
# Note that doing `& 0xff` is equivalent to `% 0x100`
checksum = -sum(compute_array, 0x19) % 0x100


print(f"Header Bytes: {compute_array}")
print(f"Checksum    : {hex(checksum)}")
