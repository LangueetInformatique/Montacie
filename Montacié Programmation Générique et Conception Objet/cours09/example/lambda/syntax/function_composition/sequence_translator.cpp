// sequence_translator.cpp
// Program demonstrates sequence translator to integral type,
// obtained as a position of the value inserted into
// a sequence container.

#include <list>

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "XYZ";
    const_edge<> substring( inp );

    // Sequence symbol tables
    std::vector< std::string > table_vect;
    std::pair< std::vector< std::string >*, int > table_vect_ref( &table_vect, int() );
    std::pair< std::list< std::string >, int > table_list;
    (
        ++( scalar( 0 )^table_list^"ABC" )
        ,
        ++( scalar( 0 )^table_list^substring )
        ,
        ++( scalar( 0 )^table_vect^"DEF" )
        ,
        ++( scalar( 0 )^table_vect^substring )
        ,
        ++( scalar( 0 )^table_vect_ref^"GHI" )
        ,
        ++( scalar( 0 )^table_vect_ref^substring )

    ).evaluate();

    assert( table_list.first.front() == "ABC" );
    assert( table_list.first.back() == "XYZ" );

    assert( table_vect.at( 0 ) == "DEF" );
    assert( table_vect.at( 1 ) == "XYZ" );
    assert( table_vect.at( 2 ) == "GHI" );
    assert( table_vect.at( 3 ) == "XYZ" );

    return 0;
}
