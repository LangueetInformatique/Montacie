// bitset_access.cpp
// Program demonstrates lambda access to std::bitset.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    // bitset
    lambda< std::bitset< 8 > >::scalar eight_bits;
    lambda< bool >::scalar bool_result;
    lambda< size_t >::scalar count_result;
    lambda< unsigned long >::scalar ulong_result;
    
    (
        bool_result = alias::any( eight_bits )
        ,
        count_result = alias::count( eight_bits )
        ,
        bool_result = alias::test( eight_bits, size_t( 3 ) )
        ,
        ulong_result = alias::to_ulong( eight_bits )
        ,
        eight_bits = alias::flip< 8 >( &eight_bits )
        ,
        eight_bits = alias::flip< 8 >( &eight_bits, size_t( 3 ) )
        ,
        eight_bits = alias::reset< 8 >( &eight_bits )
        ,
        eight_bits = alias::reset< 8 >( &eight_bits, size_t( 3 ) )
        ,
        eight_bits = alias::set< 8 >( &eight_bits )
        ,
        ulong_result = alias::to_ulong( eight_bits )

        ).evaluate();


    return 0;
}
