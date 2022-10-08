'''----------------------------------------------------------------------------
   This is free and unencumbered software released into the public domain.

   Anyone is free to copy, modify, publish, use, compile, sell, or
   distribute this software, either in source code form or as a compiled
   binary, for any purpose, commercial or non-commercial, and by any
   means.

   In jurisdictions that recognize copyright laws, the author or authors
   of this software dedicate any and all copyright interest in the
   software to the public domain. We make this dedication for the benefit
   of the public at large and to the detriment of our heirs and
   successors. We intend this dedication to be an overt act of
   relinquishment in perpetuity of all present and future rights to this
   software under copyright law.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.

   For more information, please refer to <https://unlicense.org>
----------------------------------------------------------------------------'''
'''----------------------------------------------------------------------------
	Binary to C code generation script.

	Author  : White Guy That Don't Smile
	Date    : 2022/08/19, Friday, August 19th; 1955 HOURS
----------------------------------------------------------------------------'''
import sys

def bin2c():
	global ofile, ct, n

	z = 0
	buf = [''] * 8
	i = 0
	ofile.write( 'const unsigned char data[%lu] = {' % n )

	while ( z != n ):
		i &= 7
		buf[i] = ct[z]
		z += 1
		i += 1

		if ( (i == 8) or (z == n) ):
			ofile.write( '\n\t' )

			j = 0
			while ( j < i ):
				ofile.write( '0x%.2X, ' % buf[j] )
				j += 1

	ofile.write( '\n};' )

def main( argv ):
	global ofile, ct, n

	if ( len( argv ) != 2 ):
		print( 'Usage: bin2c [infile] [outfile]' )
		sys.exit( 1 )
	else:
		try:
			ifile = open( argv[0], 'rb' )
		except IOError:
			print( ('Unable to open: \"%s\"\n' % argv[0]) )
			sys.exit( 1 )

		ct = ifile.read()
		n = len( ct )

		if ( n == 0 ):
			print( ('Unable to work with a file size of: %ld\n' % n) )
			sys.exit( 1 )

		try:
			ofile = open( argv[1], 'w' )
		except IOError:
			print( ('Unable to create: \"%s\"\n' % argv[1]) )
			sys.exit( 1 )

		ifile.close()
		bin2c()
		ofile.close()
		sys.exit( 0 )

if __name__ == '__main__':
	main( sys.argv[1:] )
