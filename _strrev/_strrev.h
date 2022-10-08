/******************************************************************************
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <https://unlicense.org>
 *****************************************************************************/
/*-----------------------------------------------------------------------------
    String Reversal Function.

    Author  : White Guy That Don't Smile
    Date    : 2022/09/28, Wednesday, September 28th; 2110 HOURS
-----------------------------------------------------------------------------*/
#ifndef _STRREV_H_INCLUDED
#define _STRREV_H_INCLUDED

/*-----------------------------------------------------------------------------
    void       *data_pointer:   Pointer to the string to be reversed.
    unsigned    num_bytes:      Number of bytes that can be dereferenced.

    Examples:

        [ usage for byte swapping ]
            unsigned short i = 0xBEEF;
            _strrev(&i, sizeof(unsigned short));    result is: 0xEFBE

        [ usage for string reversal ]
            char *str = (char *)calloc(40, sizeof(char));
            char *dst = "The brown fox jumped over the lazy dog.";
            strcpy(str, dst);
            _strrev(str, strlen(str));
                result is: ".god yzal eht revo depmuj xof nworb ehT"
            free(str);
-----------------------------------------------------------------------------*/
void _strrev( void *data_pointer, unsigned num_bytes );

#endif
