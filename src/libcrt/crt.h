/*
    crt.h
    By: Ammar Ratnani

    Defines symbols used during program startup. I don't know why you'd call
    any of these manually (maybe for resetting), but they're there.
*/

#ifndef CRT_H
#define CRT_H

#ifdef __cplusplus
extern "C" {
#endif


__attribute__((target("arm"))) _Noreturn void _start(void);
__attribute__((target("thumb"))) _Noreturn void _end(int errCode);
__attribute__((target("thumb"))) void _init(void);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef CRT_H