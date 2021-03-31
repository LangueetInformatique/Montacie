// node_2_character_access.cpp
// Program demonstrates overloaded subscript operators.
// Subscript access to characters of std::string via cttl::node operator[].

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main()
{
    std::string inp = "abcdef";
    node<> node1( inp );
    node<> node2 = node1;
    lambda< char >::scalar ch;
    lambda< node<> >::scalar n1( node1 );
    lambda< node<> >::scalar n2( node2 );
    (
        // update node positions:
        alias::offset( &n1, size_t( 0 ) ),
        alias::offset( &n2, size_t( 1 ) ),
        // swap characters:
        ch = n1[ const_scalar( 0 ) ],
        n1[ const_scalar( 0 ) ] = n2[ scalar( 0 ) ],
        n2[ const_scalar( 0 ) ] = ch
    ).evaluate();
    assert( inp == "bacdef" );
}
