// sample code: rule_adaptor.cpp
// demonstrates EBNF grammar rules

#include "cttl/cttl.h"

using namespace cttl;

// EBNF grammar for fractional number can be written as: 
//
//  <start>  := '-'* <fract>
//  <fract>  := <digits> ('.' <digits>)*
//  <digits> := ( '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' )+
//
// With cttl, these rules can be written as C++ functions:
//

size_t digits( const_edge<>& substr_ )
{
    return entity( isdigit ).match( substr_ );
}

size_t fract( const_edge<>& substr_ )
{
    return (
        rule( digits )
        +
        ( '.' + rule( digits ) ) * 1

    ).match( substr_ );
}

size_t start( const_edge<>& substr_ )
{
    return ( *symbol( '-' ) + rule( fract ) ).match( substr_ );
}

int main()
{
    std::string inp = "123.45";
    const_edge<> substring( inp );
    size_t result = rule( start ).match( substring );
    assert( result == 0 );
    assert( substring.length() == 0 );
    return 0;
}
