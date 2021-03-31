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

// filename_parser.cpp
//
// Demonstrates howto:
// - Load a list of files;
// - In a loop,
// -- Read data from file;
// -- Parse file name and extension;
// -- Save file;
//
//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on

#include "cttl/cttl.h"
#include "utils/fileio.h"
#include "utils/pipe_input.h"

#include "example/filename_parser.h"

using namespace cttl;

int main(int argc, char* argv[])
{
    //////////////// Load input files //////////////////////////////
    std::vector< std::string > vect_input_files;

    if ( argc == 2 ) {
        // assume one input file was specified as input argument
        vect_input_files.push_back( argv[ 1 ] );
    } else {
        // assume list of input files was specified as pipe input
        pipe_input_2_vector( vect_input_files );
    }

    assert( vect_input_files.size() );

    std::string fname_inp;
    typedef const_edge<> fname_input_T;
    fname_input_T fname_substr( fname_inp );
    file_name_parser<> fname_parser( fname_substr );

    // for each file:
    for ( size_t file_cnt = 0; file_cnt < vect_input_files.size(); ++file_cnt ) {
        // read data from file:
        //file2string( vect_input_files[ file_cnt ], inp );

        fname_inp = vect_input_files[ file_cnt ];
        assert( fname_inp.length() );

        if ( fname_parser.grammar() ) {
            std::cout
                // Includes last slash or backslash in the path:
                << "PATH=\'" << fname_parser.edge_file_path.text() << '\''
                << '\t'
                << "NAMEXT=\'" << fname_parser.edge_file_name_ext.text() << '\''
                << '\t'
                << "NAME=\'" << fname_parser.edge_file_name.text() << '\''
                << '\t'
                << "EXT=\'" << fname_parser.edge_file_ext.text() << '\''
                << std::endl
                ;
        } else {
            std::cout << "*** FAILED TO PARSE FILE NAME ***" << std::endl;
            return 1;
        }

        // save file:
        //string2file( argv[ 2 ], inp );
    }


    return 0;
}
