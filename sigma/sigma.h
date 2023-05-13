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
#ifndef _SIGMA_H_INCLUDED_
#define _SIGMA_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>

#define DATA_INPUT 1
#define DATA_OUTPUT 0
struct {
    /* Output Sums */
    unsigned short oB, oK, oM, oG, oT, oP, oE, oZ, oY;
    /* Input Sums */
    unsigned short iB, iK, iM, iG, iT, iP, iE, iZ, iY;
} _expSI_;
#define frame (sizeof(_expSI_) / 4)
unsigned short *expSI_ = (unsigned short *)&_expSI_,
               *_expSI = (unsigned short *)&_expSI_ + frame;
unsigned short **expSI[2] = { &expSI_, &_expSI };

/*---------------------------------------------------------------------------
    const  unsigned     segment:    DATA_INPUT or DATA_OUTPUT macro.
    register size_t     amount:     Number of bytes to register.
---------------------------------------------------------------------------*/
void _updateSum(const unsigned segment, register size_t amount);

void _displaySum(void);

#endif
