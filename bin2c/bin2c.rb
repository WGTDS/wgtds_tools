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
#   Binary to C code generation script.
#
#   Author  : White Guy That Don't Smile
#   Date    : 2022/08/20, Saturday, August 20th; 1911 HOURS
#------------------------------------------------------------------------------

def bin2c( ofile, ct, n )
	z = 0
	buf = []
	i = 0
	ofile << "const unsigned char data[" << n << "] = {"

	while ( z != n )
		i &= 7
		buf[i] = ct[z]
		i += 1
		z += 1

		if ( (i == 8) || (z == n) )
			ofile << "\n\t"

			j = 0
			while ( j < i )
				ofile.write( sprintf( "0x%.2X, ", buf[j] ) )
				j += 1
			end
		end
	end

	ofile << "\n};"
end

if ( ARGV.count != 2 )
	puts( "Usage: bin2c [infile] [outfile]\n" )
	exit
else
	argv = ARGV.each { |v| }
	ifile = File.open( argv[0], "rb" )

	if ( File.readable?( argv[0] ) == false )
		print( "Unable to open: \"%s\"\n", argv[0] )
		exit
	end

	n = File.size?( argv[0] )

	if ( n == nil )
		puts( "Unable to work with a file size of: %ld\n", n )
		exit
	end

	ct = []
	c = 0
	while ( c < n )
		ct[c] = ifile.readbyte()
		c += 1
	end

	ifile.close()
	ofile = File.open( argv[1], "wb" )

	if ( File.writable?( argv[1] ) == false )
		print( "Unable to create: \"%s\"\n", argv[1] )
		exit
	end

	bin2c( ofile, ct, n )
	ofile.close()

	exit
end
