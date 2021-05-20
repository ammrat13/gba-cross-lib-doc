# LibPlacement

This library exists to make it easier to place variables in certain sections of
memory. The linker script allows users to place symbols in IWRAM and EWRAM with
the `.iwram_{data,bss}*` and `.ewram_{data,bss}*` sections respectively. For
convinience, we define a header with macros to put variables in these sections.
