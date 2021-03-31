// xtl_bitflags.cpp
// demonstrates cttl_impl::xtl_bitflags usage

#include <iostream>
#include "cttl/xtl_bitflags.h"

int main()
{
    using cttl_impl::xtl_bitflags;

    xtl_bitflags flags( 1 );
    std::cout << "flags " << flags << std::endl;
    std::cout << " flags.clear( 1 ) ";   flags.clear( 1 );  std::cout << std::endl;
    std::cout << " flags.set( 128 ) ";   flags.set( 128 );  std::cout << std::endl;
    std::cout << "  flags.test( 2 ) " << flags.test( 2 );   std::cout << std::endl;
    std::cout << "flags.test( 128 ) " << flags.test( 128 ); std::cout << std::endl;
    std::cout << "   flags.set( 2 ) ";   flags.set( 2 );    std::cout << std::endl;
    std::cout << "  flags.test( 2 ) " << flags.test( 2 );   std::cout << std::endl;
    std::cout << " flags.clear( 2 ) ";   flags.clear( 2 );  std::cout << std::endl;
    std::cout << "  flags.test( 2 ) " << flags.test( 2 );   std::cout << std::endl;
    std::cout << "flags.test( 128 ) " << flags.test( 128 ); std::cout << std::endl;

    return 0;
}
