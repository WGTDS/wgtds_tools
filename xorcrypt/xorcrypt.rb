#------------------------------------------------------------------------------
#  This is free and unencumbered software released into the public domain.
#
#  Anyone is free to copy, modify, publish, use, compile, sell, or
#  distribute this software, either in source code form or as a compiled
#  binary, for any purpose, commercial or non-commercial, and by any
#  means.
#
#  In jurisdictions that recognize copyright laws, the author or authors
#  of this software dedicate any and all copyright interest in the
#  software to the public domain. We make this dedication for the benefit
#  of the public at large and to the detriment of our heirs and
#  successors. We intend this dedication to be an overt act of
#  relinquishment in perpetuity of all present and future rights to this
#  software under copyright law.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
#  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
#  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
#  OTHER DEALINGS IN THE SOFTWARE.
#
#  For more information, please refer to <https://unlicense.org>
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#   Binary XOR [eXclusive OR] obfuscation tool.
#
#   Author  : White Guy That Don't Smile
#   Date    : 2022/08/20, Saturday, August 20th; 2217 HOURS
#------------------------------------------------------------------------------

if ( ARGV.count != 3 )
	puts( "Usage: xorcrypt [infile] [outfile] [password]\n" )
	exit
else
	argv = ARGV.each { |v| }
	ifile = File.open( argv[0], "rb" )

	if ( File.readable?( argv[0] ) == false )
		print( "Unable to open: \"%s\"\n", argv[0] )
		exit
	end

	ofile = File.open( argv[1], "wb" )

	if ( File.writable?( argv[1] ) == false )
		print( "Unable to create: \"%s\"\n", argv[1] )
		exit
	end

	s = argv[2]
	pass_length = s.size

	if ( pass_length < 16 )
		puts( "Expecting a password length >= 16!\n" )
		exit
	end

	i = 0
	j = 0

	while ( true )
		if ( ifile.eof? == true )
			break
		else
			c = ifile.readbyte()
			#------------------------------------------------#
			#                  bit rotation                  #
			#------------------------------------------------#
			#  password glyph @ index uses the eighth bit?   #
			#     rotate left; otherwise, rotate right.      #
			#------------------------------------------------#
			t = s[i].ord
			q = ((t & 0x80) == 0x80) ? 1 : 7
			q += ((t & 0x80) == 0x80) ? j : -j
			q = t << q
			i += 1
			i %= pass_length
			r = q & 0xFF
			q &= 0x100
			q >>= 8
			r |= q
			r = ~r # complement resulting bits.
			r &= 0xFF # mask result to 8 bits.
			j += 1
			#------------------------------------------------#
			#    modulo 6 considering a value of 7 would     #
			#    defeat the purpose of this functionality.   #
			#------------------------------------------------#
			j %= 6
			c ^= r
			c += 128 # Caesar..
			c &= 255 # ..Cipher
			ofile.putc( c )
		end
	end

	ifile.close()
	ofile.close()
	exit
end
