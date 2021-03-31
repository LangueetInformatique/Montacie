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

// java_lexer.cpp

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on

// Suppress microsoft deprecation warnings:
#ifdef _WIN32
    // suppress windows platform deprecation warnings:
#   ifndef _CRT_SECURE_NO_DEPRECATE
#   define _CRT_SECURE_NO_DEPRECATE
#   endif // _CRT_SECURE_NO_DEPRECATE
#endif // _WIN32

#include <iostream>
#include "cttl/cttl.h"

#include "utils/fileio.h"
#include "utils/itos.h"
#include "utils/timeutils.h"

#include "utils/pipe_input.h"
#include "example/java_lexer/java_alphabet.cpp"
#include "example/java_lexer/java_lexer.h"

using namespace cttl;

int main(int argc, char* argv[])
{
    std::vector< std::string > vect_java_files;

    if ( argc == 2 ) {
        // assume one java file was specified as input argument
        vect_java_files.push_back( argv[1] );
    } else {
        // assume list of java input files was specified as pipe input
        pipe_input_2_vector( vect_java_files, ".java" );
    }

    assert( vect_java_files.size() );

    std::string inp;

    // construct substring to be parsed:
//  typedef edge< policy_space< flag_cpp_comments > > substr_T;
    typedef const_edge< policy_space< flag_cpp_comments > > substr_T;
    substr_T substring( inp );

    // construct the parser:
    java_lexer< java_parser< substr_T > > parser;

    for ( size_t file_cnt = 0; file_cnt < vect_java_files.size(); ++file_cnt ) {
        std::cout
            << time2string( current_time() )
            << " processing "
            << vect_java_files[ file_cnt ]
            ;

        file2string( vect_java_files[ file_cnt ], inp );
        size_t inp_length = inp.length();
        assert( inp_length );

        substring.first.go_bof();
        substring.second.go_eof();
        std::cout << "..." << substring.length() << " bytes";

        if ( parser.CompilationUnit( substring ) != std::string::npos ) {
            if ( inp_length != substring.second.offset() ) {
                string2file( vect_java_files[ file_cnt ], inp );
                std::cout << "...saved " << substring.second.offset() << std::endl;

            } else {
                std::cout << "...no changes required" << std::endl;
            }

        } else {
            std::cout << "\t\t *** Java PARSER FAILED *** " << std::endl;
            return 1;
        }
    }

    return 0;
}
