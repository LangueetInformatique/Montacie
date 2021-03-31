// custom_space_policy.cpp
// Program demonstrates a user-defined stateful space policy class.
#include "cttl/cttl.h"

using namespace cttl;

template< typename CharT = char >
class custom_space_policy : public policy_default
{
    CharT const* m_white_space;

public:
    custom_space_policy( CharT const* white_space_  )
        :
    m_white_space( white_space_ )
    {
    }

    template< typename SubstrT >
    size_t match( SubstrT& substr_ ) const
    {
        (
            symbol( true )^entity( m_white_space )
        ).match( substr_ );

        return substr_.first.offset();
    }
};//class custom_space_policy

int main()
{
    std::string inp = "ABC\nDEF";
    custom_space_policy<> policy( "\n" );
    const_edge< custom_space_policy<> > substring( inp, policy );
    node<> character = substring.first;

    while( character( symbol() ).match( substring ) != std::string::npos )
    {
        std::cout << character[ 0 ] << std::endl;
    }
    return 0;
}
/*Output:
A
B
C
D
E
F
*/