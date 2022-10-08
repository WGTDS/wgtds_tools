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
    Binary to C code generation tool.

    Author  : White Guy That Don't Smile
    Date    : 2022/08/16, Tuesday, August 16th; 1815 HOURS
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
    s : destination file pointer.
    t : data buffer.
    n : number of data elements.
*/
void bin2c_buf2file( FILE *s, const unsigned char *t, size_t n )
{
    const unsigned char *ct = t;
    unsigned char *z = (unsigned char *)((size_t)ct + n);
    unsigned char buf[8] = { 0x00 };
    FILE *ss = s;
    int i = 0;
    int j;

    fprintf( ss, "const unsigned char data[%lu] = {", (unsigned long)n );

    while ( ct != z ) {
        i &= 7;
        buf[i++] = *ct++;

        if ( (i == 8) || (ct == z) ) {
            fprintf( ss, "\n\t" );

            for ( j = 0; j < i; j++ ) {
                fprintf( ss, "0x%.2X, ", buf[j] );
            }
        }
    }

    fprintf( ss, "\n};" );

    return;
}

int main( int argc, char *argv[] )
{
    if ( argc != 3 ) {
        puts( "Usage: bin2c [infile] [outfile]" );
        return 1;
    }
    else {
        FILE *ifile = (FILE *)0;
        FILE *ofile = (FILE *)0;
        unsigned char *buf = (unsigned char *)0;
        long n;

        ifile = fopen( argv[1], "rb" );
        assert( ifile != (FILE *)0 );
        ofile = fopen( argv[2], "wb" );
        assert( ofile != (FILE *)0 );
        fseek( ifile, 0L, SEEK_END );
        n = ftell( ifile );
        assert( n != EOF );
        rewind( ifile );
        buf = (unsigned char *)malloc( sizeof(unsigned char) * n );
        assert( buf != (unsigned char *)0 );
        assert( fread( buf, sizeof(unsigned char), n, ifile ) == (size_t)n );
        fclose( ifile );
        bin2c_buf2file( ofile, buf, n );
        fflush( ofile );
        fclose( ofile );
        free( buf );

        return 0;
    }
}
