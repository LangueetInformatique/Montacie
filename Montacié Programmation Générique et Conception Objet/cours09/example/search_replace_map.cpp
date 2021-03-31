// search_replace_map.cpp
// The program uses std::map to replace text fragments.

#include <iostream>
#include <map>
#include "cttl/cttl.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::map< std::string, std::string > search_replace_map;
    search_replace_map[ "one" ] = "1";
    search_replace_map[ "two" ] = "2";
    search_replace_map[ "three" ] = "3";

    std::string inp = "four three two one five";
    edge<> substring( inp );
    edge<> word = substring;

    // search and replace:
    while (
            word( symbol( "one" ) || "two" || "three" ).find( substring )
            !=
            std::string::npos
        )
    {
        word = search_replace_map[ word ];
    }

    std::cout << inp;

    return 0;
}
/*Output:
four 3 2 1 five
*/
