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


# Get command line arguments
GAME_NAME =   argv[1].upper() if len(argv) >= 2                       else ""
GAME_CODE =   argv[2].upper() if len(argv) >= 3                       else ""
MAKER_CODE =  argv[3]         if len(argv) >= 4 and argv[3].isdigit() else ""
VERSION_NUM = int(argv[4])    if len(argv) >= 5 and argv[4].isdigit() else 0


# Array we will use in computing the checksum
compute_array = [0] * 29

# Copies exactly `length` characters of `string` into `compute_array` starting
#   at `offset`, truncating or padding with nulls if needed
def populate_compute_array(string, length, offset):
    for i in range(length):
        try:
            compute_array[offset + i] = ord(string[i])
        except IndexError:
            compute_array[offset + i] = 0


# Populate the array
populate_compute_array(GAME_NAME, 12, 0)
populate_compute_array(GAME_CODE, 4, 12)
populate_compute_array(MAKER_CODE, 2, 16)

compute_array[18] = 0x96  # Fixed value
compute_array[19] = 0x00  # Main unit code
compute_array[20] = 0x00  # Device type

compute_array[21:28] = [0x00]*7  # Reserved space

compute_array[28] = VERSION_NUM % 0x100


# Compute as described on GBATek and in devKit's `gbafix`
# Note that doing `& 0xff` is equivalent to `% 0x100`
checksum = 0
for n in compute_array:
    checksum = checksum - n
checksum = (checksum - 0x19) % 0x100


print(f"Header Bytes: {compute_array}")
print(f"Checksum    : {hex(checksum)}")
