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

// Sample csv2xml.cpp

///////////////////////////////////////////////////////////////////////
// Converts input file in comma separated value (CSV) format into
// its XML equivalent, assuming the first line contains column headers.
// Usage: >csv2xml file.csv
// Output is sent to standard output.
///////////////////////////////////////////////////////////////////////

// Must appear before assert.h to stop assertions from being compiled:
//#define NDEBUG

#include "cttl/cttl.h"
#include "utils/fileio.h"

using namespace cttl;

int main(int argc, char* argv[])
{
    assert( argc > 1 );
    std::string inp;
    file2string( argv[ 1 ], inp );
    assert( inp.length() );

    const_edge<> substring( inp );
    const_edge<> line = substring;
    const_edge<> cell = substring;

    std::vector< std::string > vect_columns;
    while (
        substring.length()
        &&
        lookbehind(
            line( entity() ),
            '\n' | end()
            ).match( substring ) != std::string::npos
        )
    {
        size_t line_count = line.first.line();
        int column_count = 0;

        if ( line_count != 1 )
            std::cout
                << "<line count="
                << line_count
                << '>'
                << std::endl
                ;

        while (
            line.length()
            &&
            ((
                (
                    ansi_double_quote( cell( entity() ) )
                    +
                    ( ',' | end() )
                )
                |
                (
                    cell.first( begin( true ) )
                    +
                    !cell.second( ',' | end() )
                )
            ).match( line ) != std::string::npos )
        )
        {
            if ( line_count == 1 ) {
                vect_columns.push_back( cell.text() );

            } else {

                std::cout
                    << '\t'
                    << '<'
                    << vect_columns[ column_count ]
                    << '>'
                    << cell.text()
                    << "</"
                    << vect_columns[ column_count ]
                    << '>'
                    << std::endl
                    ;
            }

            ++column_count;

        }

        if ( line_count != 1 )
            std::cout
                << "</line>"
                << std::endl
                ;
    }

    assert( !substring.length() );
    return 0;
}
