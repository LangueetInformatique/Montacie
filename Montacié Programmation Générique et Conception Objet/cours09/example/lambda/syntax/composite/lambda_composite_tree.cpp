// lambda_composite_tree.cpp
// Program demonstrates usage of lambda composite tree.

//#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"
#include "utils/inode.h"
#include "example/lambda/syntax/composite/dump_lambda.h"

using namespace cttl;

template< typename LambdaT >
void auto_Cpp0X( LambdaT tree )
{
    // Display tree content
    dump_lambda( tree );
    std::cout
        << "\n\tTree size: "
        << get_lambda_size( tree )
        << "\n\tTree capacity: "
        << tree.capacity_
        << " (number of nodes in the tree)"
        << '\n'
        ;

    // Deposit data into the tree nodes
    tree.top( const_scalar( 1 ) ) = -10;
    tree.top( const_scalar( 2 ) ) = -20;

    // Stack operations on tree nodes:
    tree.push( const_scalar( 3 )^const_scalar( 0 ), 100 );
    tree.push( const_scalar( 3 )^const_scalar( 0 ), 200 );
    tree.push( const_scalar( 3 )^const_scalar( 0 ), 300 );

    tree.top( const_scalar( 3 )^const_scalar( 1 ) ) = -310;

    // Display tree content
    dump_lambda( tree );
    std::cout
        << "\n\tTree size: "
        << get_lambda_size( tree )
        << "\n\tTree capacity: "
        << tree.capacity_
        << " (number of nodes in the tree)"
        << '\n'
        ;

    // Serialize tree into a vector:
    std::vector< int > vect_tree( 1 );
    inode_writer< inode_default_descriptor, std::vector< int > > writer( vect_tree );

    // Note 1: the stack nodes must be populated;
    // If a stack is empty, the assert should fail.

    // Note 2: only top element of the stack gets serialized;
    // The stack content remains unchanged as a result of serialization.
    writer <<= tree;

    //Display vector:
    std::cout
        << std::endl
        << "\tResulting vector:"
        << std::endl
        ;
    std::copy(
        vect_tree.begin(),
        vect_tree.end(),
        std::ostream_iterator< int >( std::cout, "; " )
        );

    std::cout << std::endl;

}

int main(/*int argc, char* argv[]*/)
{
    // Under C++0x a tree can be instantiated as a standalone object:
    // auto tree = initializer;
    // For now, using a surrogate function auto_Cpp0X()
    // to demo the lambda composite structure:

    auto_Cpp0X(
        // Construct a tree
        scalar( 1 )
        ^
        (
            scalar( 10 )
            ^
            scalar( 11 )
        )
        ^
        scalar( 2 )
        ^
        (
            make_stack( 30 )
            ^
            scalar( 31 )
        )
        ^
        scalar( 4 )
        );
    return 0;
}

/*Output:
--------------------------------------------------------------
subscript       size    stack_ptr               top
---------       -----   ----------      ----------------------
0               1       0               1
1^0             1       0               10
1^1             1       0               11
2               1       0               2
3^0             0       0x22febc                empty
3^1             1       0               31
4               1       0               4

        Tree size: 6
        Tree capacity: 7 (number of nodes in the tree)

--------------------------------------------------------------
subscript       size    stack_ptr               top
---------       -----   ----------      ----------------------
0               1       0               1
1^0             1       0               -10
1^1             1       0               11
2               1       0               -20
3^0             3       0x22febc                300
3^1             1       0               -310
4               1       0               4

        Tree size: 9
        Tree capacity: 7 (number of nodes in the tree)

        Resulting vector:
0; 1; -10; 11; -20; 300; -310; 4;
*/
