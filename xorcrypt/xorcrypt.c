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
    Binary XOR [eXclusive OR] obfuscation tool.

    Author  : White Guy That Don't Smile
    Date    : 2022/08/17, Wednesday, August 17th; 2049 HOURS
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main( int argc, char *argv[] )
{
    if ( argc != 4 ) {
        puts( "Usage: xorcrypt [infile] [outfile] [password]" );
        return 1;
    }
    else {
        FILE *ifile = (FILE *)0;
        FILE *ofile = (FILE *)0;
        const char *s = (const char *)argv[3];
        size_t pass_length = strlen( s );
        size_t i = 0;
        int c;
        int j = 0;
        int q;
        int r;

        ifile = fopen( argv[1], "rb" );
        assert( ifile != (FILE *)0 );
        ofile = fopen( argv[2], "wb" );
        assert( ofile != (FILE *)0 );
        assert( pass_length >= 16 );

        while ( 1 ) {
            c = fgetc( ifile );

            if ( c == EOF ) {
                break;
            }
            else {
            /*----------------------------------------------*/
            /*                 bit rotation                 */
            /*----------------------------------------------*/
            /* password glyph @ index has a negative value? */
            /*    rotate left; otherwise, rotate right.     */
            /*----------------------------------------------*/
                q = s[i] < 0 ? 1 : 7;
                q += s[i] < 0 ? j : -j;
                q = s[i] << q;
                i++;
                i %= pass_length;
                r = q & 0xFF;
                q &= 0x100;
                q >>= 8;
                r |= q;
                r = ~r; /* complement resulting bits. */
                r &= 0xFF; /* mask result to 8 bits. */
                j++;
            /*----------------------------------------------*/
            /*   modulo 6 considering a value of 7 would    */
            /*   defeat the purpose of this functionality.  */
            /*----------------------------------------------*/
                j %= 6;
                c ^= r;
                c += 128; /* Caesar.. */
                c &= 255; /* ..Cipher */
                fputc( c, ofile );
            }
        }

        fclose( ofile );
        fclose( ifile );
        return 0;
    }
}
