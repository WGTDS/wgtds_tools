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
	Binary XOR [eXclusive OR] obfuscation tool.

	Author  : White Guy That Don't Smile
	Date    : 2022/08/19, Friday, August 19th; 2152 HOURS
----------------------------------------------------------------------------'''
import sys

def main( argv ):

	if ( len( argv ) != 3 ):
		print( 'Usage: xorcrypt [infile] [outfile] [password]' )
		sys.exit( 1 )
	else:
		try:
			ifile = open( argv[0], 'rb' )
		except:
			print( ('Unable to open: \"%s\"\n' % argv[0]) )
			sys.exit( 1 )

		try:
			ofile = open( argv[1], 'wb' )
		except:
			print( ('Unable to create: \"%s\"\n' % argv[1]) )
			sys.exit( 1 )

		s = argv[2].encode( 'latin-1' )
		pass_length = len( s )

		if ( pass_length < 16 ):
			print( 'Expecting a password length >= 16!\n' )
			sys.exit( 1 )

		i = 0
		j = 0

		while ( True ):
			try:
				c = ord( ifile.read( 1 ) )
			except:
				break;

			'''----------------------------------------------\
			|                  bit rotation                  |
			|------------------------------------------------|
			|  password glyph @ index uses the eighth bit?   |
			|     rotate left; otherwise, rotate right.      |
			\----------------------------------------------'''
			b = ((s[i] & 0x80) == 0x80)
			q = 1 if (b == True) else 7
			q += j if (b == True) else -j
			q = s[i] << q
			i += 1
			i %= pass_length
			r = q & 0xFF
			q &= 0x100
			q >>= 8
			r |= q
			r = ~r # complement resulting bits.
			r &= 0xFF # mask result to 8 bits.
			j += 1
			'''----------------------------------------------\
			|    modulo 6 considering a value of 7 would     |
			|    defeat the purpose of this functionality.   |
			\----------------------------------------------'''
			j %= 6
			c ^= r
			c += 128 # Caesar..
			c &= 255 # ..Cipher
			ofile.write( bytes( chr( c ).encode( 'latin-1' ) ) )

		ifile.close()
		ofile.close()
		sys.exit( 0 )

if __name__ == '__main__':
	main( sys.argv[1:] )
