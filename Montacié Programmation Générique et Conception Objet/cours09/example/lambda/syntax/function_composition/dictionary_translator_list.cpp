// dictionary_translator_list.cpp
// Program demonstrates dictionary translator for
// sequence and associative container.
// The program is using std::list as a sequence.

#include <list>

#define CTTL_TRACE_RULES        // Automatically turns lambda tracing on
//#define CTTL_TRACE_DEPOSITS_OFF

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "zero one zero one";
    const_edge< policy_space<> > substring( inp );

    typedef std::list< std::string >::size_type size_T;

    // User can construct a dictionary using default
    // constructors for sequence and associative container:
    std::pair<
        std::list< std::string >,
        std::map< std::string, size_T
        >
    > symbol_table_a;

    // Alternatively, parts of the dictionary can be
    // individually constructed:
    std::list< std::string > symbol_sequence;
    std::map< std::string, size_T > symbol_map;

    // A pair of pointers represents a dictionary:
    std::pair<
        std::list< std::string >*,
        std::map< std::string, size_T >*
    > symbol_table_b( &symbol_sequence, &symbol_map );

    size_t result = 
        (
            *(
                entity( isalpha )
                &
                *(
                    ++( scalar( size_T( 0 ) )^symbol_table_a^substring ),
                    ++( scalar( size_T( 0 ) )^symbol_table_b^substring )
                )
            )
        ).match( substring );

    assert( result != std::string::npos );
    assert( symbol_table_a.first.front() == "zero" );
    assert( symbol_table_a.second.find( "zero" ) != symbol_table_a.second.end() );
    assert( symbol_table_a.second.find( "zero" )->second == 0 );

    assert( symbol_sequence.back() == "one" );
    assert( symbol_map.find( "one" ) != symbol_map.end() );
    assert( symbol_map.find( "one" )->second == 1 );

    return 0;
}
