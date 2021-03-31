// sample code: edge_sort.cpp
// demonstrates STL sort algorithm applied to a vector of edges

#include <iostream>
#include "cttl/cttl.h"
#include <vector>
#include <algorithm>
#include <iterator>    // needed for ostream_iterator

int main()
{
    using namespace cttl;
    std::string inp = "one\ntwo\nthree\nfour\nfive";

    std::cout << "--------------------------------" << std::endl;
    std::cout << "\t Input data:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << inp << std::endl;
    edge<> substring( inp );

    size_t line_count = substring.second.line();

    // each edge corresponds to a line in the input file:
    std::vector< edge<> > vector_sorted_edges;

    size_t ln = 1;
    for ( ; ln <= line_count; ++ln ) {
        edge<> tmp = substring;               // create new edge

        // navigate substring boundaries to the beginning/ending of line ln:
        tmp.first.go_line( ln );
        tmp.second.go_line_end( ln );

        // add substring to the vector to be sorted
        vector_sorted_edges.push_back( tmp );
    }

    std::cout << "--------------------------------" << std::endl;
    std::cout << "\t Unsorted vector of edges:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::copy(
        vector_sorted_edges.begin(),
        vector_sorted_edges.end(),
        std::ostream_iterator< std::string >( std::cout, "\n" )
        );

    std::sort( vector_sorted_edges.begin(), vector_sorted_edges.end() );

    std::cout << "--------------------------------" << std::endl;
    std::cout << "\t Sorted vector of edges:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::copy(
        vector_sorted_edges.begin(),
        vector_sorted_edges.end(),
        std::ostream_iterator< std::string >( std::cout, "\n" )
        );

    size_t idx = 0;
    for ( ; idx < vector_sorted_edges.size(); ++idx ) {
        edge<>& tmp = vector_sorted_edges[ idx ];
        if ( tmp == "one" ) tmp = "1";
        else if ( tmp == "two" ) tmp = "2";
        else if ( tmp == "three" ) tmp = "3";
        else if ( tmp == "four" ) tmp = "4";
        else if ( tmp == "five" ) tmp = "5";
        else
            assert( !"Corrupted data detected while modifying the input." );
    }

    std::cout << "--------------------------------" << std::endl;
    std::cout << "\t Modified input, same order:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::copy(
        vector_sorted_edges.begin(),
        vector_sorted_edges.end(),
        std::ostream_iterator< std::string >( std::cout, "\n" )
        );

    std::cout << "--------------------------------" << std::endl;
    std::cout << "\t Modified input string:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << inp << std::endl;

    std::cout << "--------------------------------" << std::endl;

    return 0;
}
