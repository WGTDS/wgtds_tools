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
    Bit Rotation Functions for little-endian applications.

    Author  : White Guy That Don't Smile
    Date    : 2022/10/03, Monday, October 3rd; 2259 HOURS
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    void       *data_pointer:   Pointer to the string to be rotated.
    unsigned    num_bytes:      Number of bytes that can be dereferenced.

    This function rotates a string of data to the right by 1 bit.
-----------------------------------------------------------------------------*/
void _ror( void *data_pointer, unsigned num_bytes )
{
    unsigned remaining = num_bytes;
    unsigned char *footer = (unsigned char *)data_pointer;
    unsigned char *header = footer + num_bytes - 1;
    unsigned char sigbit = (*footer & 1) << 7;

    while ( remaining-- ) {
        *footer >>= 1;
        *footer |= ((*(footer + 1) & 1) << 7);
        footer++;
    }

    *header |= sigbit;
    return;
}

/*-----------------------------------------------------------------------------
    void       *data_pointer:   Pointer to the string to be rotated.
    unsigned    num_bytes:      Number of bytes that can be dereferenced.

    This function rotates a string of data to the left by 1 bit.
-----------------------------------------------------------------------------*/
void _rol( void *data_pointer, unsigned num_bytes )
{
    unsigned remaining = num_bytes;
    unsigned char *footer = (unsigned char *)data_pointer;
    unsigned char *header = footer + num_bytes - 1;
    unsigned char sigbit = (*header & 128) >> 7;

    while ( remaining-- ) {
        *header <<= 1;
        *header |= ((*(header - 1) & 128) >> 7);
        header--;
    }

    *footer |= sigbit;
    return;
}
