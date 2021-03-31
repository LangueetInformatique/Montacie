// sample code: string_set_lexeme.cpp
// demonstrates begin( std::set< std::string > ) lexeme

#include <iostream>
#include "cttl/cttl.h"

using namespace cttl;

int main()
{
    std::set< std::string > numbers;
    numbers.insert( "one" );
    numbers.insert( "two" );
    numbers.insert( "three" );
    numbers.insert( "fourteen" );

    std::string inp = "one two three four fourteen";
    const_edge< policy_space<> > substring( inp );
    const_edge<> data = substring;
    if (
        data(
            +(
                entity( isalpha )
                &
                cttl::begin( numbers )
            )
        ).match( substring ) != std::string::npos
    )
    {
        std::cout << "data: /" << data << '/' << std::endl;

    } else {
        std::cout << "*** evaluation failed ***" << std::endl;
        return 1;
    }

    return 0;
}
/* program output:
data: /one two three/
*/
