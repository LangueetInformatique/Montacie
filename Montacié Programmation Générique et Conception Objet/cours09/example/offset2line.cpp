////////////////////////////////////////////////////////////////////////
//
// This file is part of Common Text Transformation Library.
// Copyright (C) 1997-2009 by Igor Kholodov. 
//
// Common Text Transformation Library is free software: you can
// redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Common Text Transformation Library is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Common Text Transformation Library.
// If not, see <http://www.gnu.org/licenses/>.
//
// mailto:cttl@users.sourceforge.net
// http://cttl.sourceforge.net/
// http://sourceforge.net/projects/cttl/
//
////////////////////////////////////////////////////////////////////////

// offset2line.cpp
// args: path\file offset
// prints line number of the specified offset

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on
//#define CTTL_TRACE_TRIVIAL

#include <iostream>
#include "cttl/cttl.h"

#include "utils/fileio.h"
#include "utils/itos.h"

using namespace cttl;

int main(int argc, char* argv[])
{
    if ( argc != 3 ) {
        std::cout
            << "Usage: "
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " sourcefile.ext N"
            << std::endl
            << "\t where N is the character offset inside the text file."
            << std::endl
            << "-or-"
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " sourcefile.ext LN"
            << std::endl
            << "\t where N is the line number inside the text file."
            << std::endl
            ;
        return 1;
    }

    std::string inp;

    file2string( argv[ 1 ], inp );
    assert( inp.length() );
    const_edge<> substring( inp );

    size_t requested_offset = 0;
    if ( argv[ 2 ][ 0 ] == 'L' ) {
        requested_offset = atoi( argv[ 2 ] + 1 );
        assert( requested_offset );
        requested_offset = substring.first.go_line( requested_offset );
    
    } else {
        requested_offset = atoi( argv[ 2 ] );
        assert( requested_offset );
    }

    assert( requested_offset < inp.length() );


    std::cout
        << "File "
        << argv[ 1 ]
        << "; total lines: "
        << substring.second.line()
        << ", ("
        << substring.second.offset()
        << " characters)"
        << std::endl
        ;

    substring.first.offset( requested_offset );
    substring.first.go_line_home();
    substring.second.offset( requested_offset );
    substring.second.go_line_end();

    std::cout
        << "Line# "
        << substring.first.line()
        << ", (characters "
        << substring.first.offset()
        << '-'
        << substring.second.offset()
        << "):"
        << std::endl
//      << substring.text()
//      << std::endl
        ;

    std::string line_extract( substring.text() );

    std::cout
        // replace \r\n with dots, tabs with spaces:
        << xtl_trace_grammar::whitespace2monospace( line_extract )
        << std::endl
        ;

    size_t display_offset = requested_offset - substring.first.offset();
    for ( size_t pad = 0; pad < display_offset; ++pad )
        std::cout << ' ';

    std::cout
        << "^--offset="
        << requested_offset
        << "; character=/"
        << substring.first[ display_offset ]
        << "/ code=" << int( substring.first[ display_offset ] )
        << std::endl
        ;

    return 0;
}
