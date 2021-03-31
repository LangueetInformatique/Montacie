// sample code: node_find_class.cpp
// demonstrates cttl::node::find_class() and cttl::node::rfind_class()

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING

#include <iostream>

#include "cttl/cttl.h"

int main()
{
    using std::string;
    using cttl::node;
    using cttl::const_edge;

    std::string inp = "ABC 123";
    node<> from = inp;
    node<> to = from;

    from.go_bof();
    to.go_bof();

    to.find_class( isspace );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;

    to.find_class( isalpha );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;

    to.find_class( isspace );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;

    to.find_class( isdigit );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;
    /////////////////////////////////////
    to.rfind_class( isdigit );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;

    to.rfind_class( isspace );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;

    to.rfind_class( isalpha );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;

    to.rfind_class( isspace );
    std::cout
        << '\''
        << const_edge<>( from, to )
        << '\''
        << std::endl
        ;

    return 0;
}
/*Output:
''
'ABC'
'ABC '
'ABC 123'
'ABC '
'ABC'
''
''
*/
