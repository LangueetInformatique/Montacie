// sample code: action_handler.cpp
// demonstrates semantic action implemented as member function template.

#include "cttl/cttl.h"

using namespace cttl;

class handler
{
    //...
public:
    template< typename SubstrT >
    size_t action( SubstrT& substr_ )
    {
        //...
        return substr_.first.offset();
    }
};


int main(int argc, char* argv[])
{
    std::string inp;             // construct input object
    typedef const_edge<> substr_T;   // type of parseable substring
    substr_T substring( inp );       // construct substring
    handler sa_handler;              // handler class implements
                                     // semantic actions
    // VC7.1 error C2784 workaround:
    typedef size_t ( handler::* action_T ) ( substr_T& );
    
    size_t result = rule(
        sa_handler,
        action_T( &handler::action< substr_T > )
        ).match( substring );

    assert( result != std::string::npos );  // assert that match succeeded
    return 0;
}
