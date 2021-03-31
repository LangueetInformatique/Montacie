// sample code: line_navigate.cpp

#include <iostream>
#include "cttl/cttl.h"

int main()
{
    using std::string;
    using cttl::node;
    using cttl::const_edge;

    // one\r\ntwo
    // 0123 4 567890
    // B  E   B  E
    // 1  1   2  2
    string inp = "one\r\ntwo";
    node<> B1( inp );
    node<> B2 = B1;
    node<> E1 = B2;
    node<> E2 = E1;

    B1.go_line_home( 1 );
    B2.go_line_home( 2 );
    E1.go_line_end( 1 );
    E2.go_line_end( 2 );

    // show results:
    std::cout
        << "line "
        << B1.line()
        << " ["
        << B1.offset() << '-' << E1.offset()
        << ") /" << const_edge<>( B1, E1 ) << '/'
        << std::endl
        ;

    std::cout
        << "line "
        << B2.line()
        << " ["
        << B2.offset() << '-' << E2.offset()
        << ") /" << const_edge<>( B2, E2 ) << '/'
        << std::endl
        ;

    B1.offset( 3 ); // CR character
    std::cout
        << "@ offset=="
        << B1.offset()
        << " line=="
        << B1.line()
        << std::endl
        ;

    B1.offset( 4 ); // LF character
    std::cout
        << "@ offset=="
        << B1.offset()
        << " line=="
        << B1.line()
        << std::endl
        ;

/* program output:
line 1 [0-3) /one/
line 2 [5-8) /two/
line @ offset 3 is 1
line @ offset 4 is 1
*/
    return 0;
}
