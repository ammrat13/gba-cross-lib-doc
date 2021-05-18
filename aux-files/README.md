# Auxilary Files

These files exist to provide defaults for compiling and linking. Right now,
there is a GCC specs file and a linker script.


## Specs

The specs provide sensible default options for cross compiling to the GBA. In
particular it:
* Includes the headers, start files, and libraries required to cross compile
* Compiles for the GBA's `-mcpu=arm7tdmi`
* Turns on `-ffreestanding`
* Turns on `-mthumb-interwork`
* Errors out on orphaned sections during linking
* Disables C++ exceptions and run-time type information


## Linker Script

The linker script allows GBA games to be linked and mapped to ROM. It will place
`crt0.o`'s `.text.bootstrap` section first. Then, it will place all the other
code sections, any interworking code, the initialization and finalization
arrays, and any variables.

It also provides some symbols for the program loader. For `.data`:
* `__data_vma_stt`: The desired starting address of the section in *RAM*
* `__data_vma_end`: The desired address just past the end of the section in
  *RAM*
* `__data_lma`: The address of the `.data` section in *ROM*

For `.bss`:
* `__bss_vma_stt`: Its desired starting address in *RAM*
* `__bss_vma_end`: Its desired address just past the end in *RAM*

For `.init_array` and `.fini_array`:
* `__init_arr_stt`: The address of the first element
* `__init_arr_end`: The address just past the end
* `__fini_arr_stt`: The address of the first element
* `__fini_arr_end`: The address just past the end
