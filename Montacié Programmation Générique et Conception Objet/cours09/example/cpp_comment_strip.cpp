// cpp_comment_strip.cpp

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on

#include <iostream>
#include "cttl/cttl.h"
#include "utils/fileio.h"
#include "utils/pipe_input.h"
#include "example/cpp_comment.h"

using namespace cttl;

int main(int argc, char* argv[])
{
    std::vector< std::string > vect_input_files;

    if ( argc == 2 ) {
        // assume one file was specified as input argument
        vect_input_files.push_back( argv[1] );
    } else {
        // assume list of java input files was specified as pipe input
        pipe_input_2_vector( vect_input_files );
    }

    assert( vect_input_files.size() );

    std::string inp;
    policy_space< flag_follow_either > void_region;
    typedef const_edge< policy_space< flag_follow_either > > substr_T;
    substr_T substring( inp, void_region );

    for ( size_t file_cnt = 0; file_cnt < vect_input_files.size(); ++file_cnt ) {

        void_region.region_clear();
        file2string( vect_input_files[ file_cnt ], inp );
        assert( inp.length() );

        cpp_comment_lexer< cpp_comment_parser< substr_T > > comment_parser;
        substring.first.go_bof();
        substring.second.go_eof();
        if ( comment_parser.rule_symbols( substring ) ) {
            substring.first.go_bof();
            std::cout << substring.region_difference();
        }
    }

    return 0;
}
