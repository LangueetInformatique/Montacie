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

// sample code: gumus.cpp
// Gumus script preprocessor utility.
// Usage: specify source file to convert to C++.
// syntax:
//   text
//   text <<.variable.>> <<.variable.>>...
//   text
// .C++ code
// .//C++ comment, etc.
// The dots control indentation level for the line output.

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on
//#define GUMUS_TRACE_VARS  //define to debug gumus script variables

#include <iostream>
#include <stack>

#include "cttl/cttl.h"
#include "utils/fileio.h"
#include "utils/itos.h"

using namespace cttl;

struct gumus {
    std::string line_prefix;        // std::cout or str_. To be used as LHS with output operator.
    std::string output_operator;    // either << for std::cout, or += for string output.
    std::string line_suffix;        // std::endl or '\n'. To be used as RHS with output operator.
    size_t indentation_level;

    gumus(
        std::string const& line_prefix_     /*= "std::cout"*/,
        std::string const& output_operator_ /*= "<<"*/,
        std::string const& line_suffix_     /*= "std::endl;"*/,
        int indentation_level_ = 2
        )
        :
        line_prefix( line_prefix_ ),
        output_operator( output_operator_ ),
        line_suffix( line_suffix_ ),
        indentation_level( indentation_level_ )
    {
    }

    void remove_cr( edge<>& edge_ )
    {
        // dos file on unix will contain cr+lf: remove cr, if any:
        edge<> edge_cr = edge_;
        while ( edge_cr( !symbol( '\r' ) ).match( edge_ ) != std::string::npos )
        {
            edge_cr.erase();
        }
        edge_.first.go_bof();
        edge_.second.go_eof();
    }

    size_t match_lines( edge<>& edge_ )
    {
        return (
            +(
                -end()
                +
                lookbehind(
                    (
                        begin( '.' )
                        +
                        CTTL_RULE( gumus::event_code_line )
                    )
                    |
                    (
                        CTTL_RULE( gumus::event_line )
                        &
                        *CTTL_RULE( gumus::find_escape )
                        &
                        *CTTL_RULE( gumus::find_variable )
                    )
                    ,
                    '\n' | end()
                )
            )
        ).match( edge_ );
    }

    size_t event_code_line( edge<>& edge_ )
    {
        for (
            indentation_level = 0
            ;
            ( edge_.first[ indentation_level ] == '.' )
            &&
            ( indentation_level < edge_.length() )
            ;
            ++indentation_level
            )
        {
            edge_.first[ indentation_level ] = ' ';
        }

        return edge_.second.offset();
    }

    size_t event_line( edge<>& edge_ )
    {
        // line decorations
        std::string indentation( indentation_level, ' ' );

        if ( edge_.length() ) {
            // non-empty line
            edge_.first.insert_go( indentation + line_prefix + output_operator + "\"" );
            edge_.second.insert_stay( "\"" + output_operator + line_suffix );
        } else {
            edge_.first.insert_go( indentation + line_prefix + output_operator + line_suffix );
        }

        return edge_.first.offset( edge_.second.offset() );
    }

    size_t find_escape( edge<>& edge_ )
    {
        return (
            (
                first( "\"\'\t\\" )
            )
            &
            CTTL_RULE( gumus::event_escape_char )

        ).find( edge_ );
    }

    size_t event_escape_char( edge<>& edge_ )
    {
        if ( edge_.first[ 0 ] == '\t' )
            edge_.text( "\\t" );
        else
            edge_.first.insert_go( "\\" );
        return edge_.second.offset();
    }

    size_t find_variable( edge<>& edge_ )
    {
        return (
            (
                symbol( "<<." )
                +
                !symbol( ".>>" )
            )
            &
            CTTL_RULE( gumus::event_variable )

        ).find( edge_ );
    }

    size_t event_variable( edge<>& edge_ )
    {
        // left connector
        edge_.first[ 0 ] = output_operator[ 0 ]; //'<' -or- ';'
        edge_.first[ 1 ] = output_operator[ 1 ]; //'<' -or- '+'
        edge_.first[ 2 ] = output_operator[ 2 ]; //' ' -or- '='

        edge_.first.insert_go( "\"" );

        edge_.second[ -3 ] = output_operator[ 0 ]; //'<' -or- ';'
        edge_.second[ -2 ] = output_operator[ 1 ]; //'<' -or- '+'
        edge_.second[ -1 ] = output_operator[ 2 ]; //' ' -or- '='

        edge_.second.insert_go( "\"" );
#ifdef GUMUS_TRACE_VARS
        edge_.second.insert_go( "/*" + edge_.text().substr( 3, edge_.length() - 7 ) + "*/" );
#endif // GUMUS_TRACE_VARS

        return 0;
    }

    bool parse( edge<>& substr_ )
    {
        remove_cr( substr_ );
        assert( substr_.length() == substr_.parent().length() );
        if ( match_lines( substr_ ) != std::string::npos )
            return true;
        return false;
    }
};

int main(int argc, char* argv[])
{
    std::string line_prefix( "std::cout" );
    std::string output_operator( "<< " );
    std::string line_suffix( "std::endl;" );

    if ( argc == 1 ) {
        std::cout
            << std::endl
            << "Gumus script preprocessor"
            << std::endl
            << "http://cttl.sourceforge.net/cttl300docs/manual/cttl/page8360_gumus.html"
            << std::endl
            << "Usage:"
            << std::endl
            << "To preprocess file, provide full path as first command-line argument:"
            << std::endl
            << std::endl
            << '>' << argv[ 0 ] << " path/file.ext [str_] [end-of-line-suffix]"
            << std::endl
            << std::endl
            << "\t Second argument (optional) specifies name of the output stream."
            << std::endl
            << "\t The default is \'std::cout\'."
            << std::endl
            << std::endl
            << "\t Third argument (optional) specifies end-of-line suffix."
            << std::endl
            << "\t The default is \'std::endl;\'."
            << std::endl
            << "\t If second argument present, the default end-of-line suffix becomes"
            << std::endl
            << "\t \'\\n\'."
            << std::endl
            ;
        return 1;

    } else if ( argc == 3 ) {
        line_prefix = argv[ 2 ];
        line_suffix = "\'\\n\';";

    } else if ( argc == 4 ) {
        line_prefix = argv[ 2 ];
        line_suffix = argv[ 3 ];
    }

    std::string inp;
    file2string( argv[ 1 ], inp );
    assert( inp.length() );
    edge<> substring( inp );

    gumus parser( line_prefix, output_operator, line_suffix );
    if ( parser.parse( substring ) ) {
        std::cout << inp;
        return 0;
    }

    std::cout << "*** parser failed ***" << std::endl;
    return 1;
}
