/*
    str_macro.h
    By: Ammar Ratnani

    This header simply provides a macro to convert bare words into string
    literals. It's useful, for instance, to convert an macro integer literal
    into a corresponding string literal.

    See: https://stackoverflow.com/questions/5459868/concatenate-int-to-string-using-c-preprocessor/5459929
*/

#ifndef STR_MACRO_H
#define STR_MACRO_H


#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)


#endif // ndef STR_MACRO_H
