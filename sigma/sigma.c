/****************************************************************************
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
 ***************************************************************************/
/*---------------------------------------------------------------------------
    Sigma - Dynamic Data Summation Utility

    Author  : White Guy That Don't Smile
    Date    : 2023/05/13, Saturday, May 13th; 1215 HOURS
---------------------------------------------------------------------------*/
#include "sigma.h"

/*---------------------------------------------------------------------------
    const  unsigned     segment:    DATA_INPUT or DATA_OUTPUT macro.
    register size_t     amount:     Number of bytes to register.
---------------------------------------------------------------------------*/
void _updateSum(const unsigned segment, register size_t amount)
{
    register unsigned short *a = NULL, *z = NULL, *t = NULL;

    a = **&expSI[(segment == DATA_INPUT)];
    z = a + frame;
    t = a;

    while (amount--) {
        do {
            if (*a == 1000U) {
                *a++ %= 999U;
            }
            else {
                ++(*a);
                break;
            }
        } while (a < z);

        a = t;
    }

    return;
}

void _displaySum(void)
{
    const char *message[2] = { " bytes produced.", " bytes processed," };
    unsigned i;

    for (i = 2; i != 0; i--) {
        unsigned short *z = **&expSI[(i / 2)] + frame, *a = z - frame, *Q;

        for (Q = z; (*&Q[-1] == 0) && (Q > a); Q--);

        while (z > a) {
            if (&z[-1] < Q) {
                printf("%.3u,", *&z[-1]);
            }

            --z;
        }

        printf("%s\n", message[(i / 2)]);
    }

    return;
}
