// integer_tree.cpp
// Program demonstrates basic principles of tree
// construction and iteration.

//#define CTTL_TRACE_DEPOSITS // turn on lambda expression tracing

#include "cttl/cttl.h"
#include "lambda/lambda.h"
#include "utils/inode.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::vector< size_t > vec( 1, 0 ); // one elem with zero value

    /////////////////////////////////////////
    // Construct and populate integer tree
    /////////////////////////////////////////
    static const int DATA_FIELD = inode_writer<>::inode_descriptor_T::DATA_FIELD;
    static const int NODE_SIZE = inode_writer<>::inode_descriptor_T::NODE_SIZE;
    const_scalar_type( DATA_FIELD ) DATA_FLD;
    lambda< inode_writer<> >::scalar iprev = inode_writer<>( vec );
    lambda< inode_writer<> >::scalar inext = inode_writer<>( vec );
    lambda< inode_writer<> >::scalar iparent = inode_writer<>( vec );
    (
        iprev << ( scalar(0)^0^1 ) // iprev:(n1)
        ).evaluate();
    (
        inext << ( scalar(0)^0^2 ) // inext:(n2)
        ).evaluate();
    (
        iprev += inext             // (n1) -> (n2)
        ).evaluate();
    (
        iprev[ DATA_FLD ] += 100   // update (n1) data field
        ).evaluate();
    (
        inext[ DATA_FLD ] += 200   // update (n2) data field
        ).evaluate();
    (
        iprev = inext              // iprev:(n2)
        ).evaluate();
    (
        inext << ( scalar(0)^0^3 ) // inext:(n3)
        ).evaluate();
    (
        iprev += inext             // (n2) -> (n3)
        ).evaluate();
    (
        iprev = inext              // iprev:(n3)
        ).evaluate();
    (
        inext << ( scalar(0)^0^4 ) // inext:(n4)
        ).evaluate();
    (
        iprev += inext             // (n3) -> (n4)
        ).evaluate();
    (
        iprev[ DATA_FLD ] += 300   // update (n3) data field
        ).evaluate();
    (
        inext[ DATA_FLD ] += 400   // update (n4) data field
        ).evaluate();
    (
        iparent << NODE_SIZE       // iparent:(p)
        ).evaluate();
    (
        iprev = 1                  // iprev:(n1)
        ).evaluate();
    (
        iparent *= iprev           // (p) <- *(n1, n2, n3, n4)
        ).evaluate();
    (
        iparent += iprev           // (p) -> (n1)
        ).evaluate();
    (
        inext -= iparent           // (n4) <- (p)
        ).evaluate();

    /////////////////////////////////////////
    // Display raw content of the vector
    /////////////////////////////////////////

    std::copy(
        vec.begin(),
        vec.end(),
        std::ostream_iterator< int >( std::cout, " " )
        );

    /////////////////////////////////////////
    // Display the logical tree data
    /////////////////////////////////////////

    // construct reader at the "root" position of the iparent:
    inode_reader<> root = inode_reader<>( vec, iparent.top().offset() );
    inode_reader<> child = root;

    // The output begins at the parent node:
    std::cout
        << std::endl
        << "parent "
        ;

    // iterate integer tree
    for( ; child != root.end(); ++child ) {
        std::cout
            << "node("
            << child.offset()
            << ") data: "
            << child[ DATA_FIELD ]
            << std::endl
            ;
    }

    return 0;
}
/*Output:
0 4 13 101 7 13 202 10 13 303 0 13 404 1 10 0
parent node(13) data: 0
node(1) data: 101
node(4) data: 202
node(7) data: 303
node(10) data: 404
*/
