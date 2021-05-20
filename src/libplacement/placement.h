/*
    placement.h
    By: Ammar Ratnani

    This header defines utility macros for placing variables in particular
    sections of memory.
*/

#ifndef PLACEMENT_H
#define PLACEMENT_H


#define IWRAM_DATA(var) var __attribute__((section(".iwram_data." #var)))
#define IWRAM_BSS(var)  var __attribute__((section(".iwram_bss."  #var)))

#define EWRAM_DATA(var) var __attribute__((section(".ewram_data." #var)))
#define EWRAM_BSS(var)  var __attribute__((section(".ewram_bss."  #var)))


#endif // ndef PLACEMENT_H
