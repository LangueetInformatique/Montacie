// inode_writer.cpp
// Program demonstrates data manipulation by inode_writer,
// its overloaded operators, and alias calls.

//#define CTTL_TRACE_RULES // turn lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"
#include "utils/inode.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::vector< size_t > vec( 1, 0 ); // one elem with zero value
    lambda< inode_writer<> >::scalar iwriter = inode_writer<>( vec );
    // vec:{ 0| }
    (
        // set position at end of container, insert composite values
        iwriter << ( scalar( size_t( 1 ) )^scalar( size_t( 2 ) )^scalar( size_t( 3 ) ) )
        ,  // vec:{ 0,|1, 2, 3 }
        // writing does not modify inode position
        CTTL_LAMBDA_ASSERT( alias::offset( iwriter ) == alias::size( scalar( &vec ) ) - 3 )
        ,
        // replace values at current position
        iwriter <<= ( scalar( size_t( 4 ) )^scalar( size_t( 5 ) )^scalar( size_t( 6 ) ) )
        ,  // vec:{ 0,|4, 5, 6 }
        // insert two elements at the end:
        iwriter << scalar( 2 )
        ,  // vec:{ 0, 4, 5, 6,|0, 0 }
        // read data field value:
        CTTL_LAMBDA_ASSERT( iwriter[ 0 ] == scalar( 0u ) )
        ,
        CTTL_LAMBDA_ASSERT( iwriter[ 1 ] == scalar( 0u ) )
        ,
        // set data field value:
        iwriter[ 1 ] = 7
        ,  // vec:{ 0, 4, 5, 6,|0, 7 }
        // explicitly set new inode position:
        iwriter = iwriter[ 0 ]
        ,  // vec:{ |0, 4, 5, 6, 0, 7 }
        // verify inode position is zero:
        CTTL_LAMBDA_ASSERT( !iwriter )
        ,
        // verify inode position at the beginning:
        CTTL_LAMBDA_ASSERT( iwriter == alias::begin( iwriter ) )
        ,
        // STL iterator access to first data field, like iwriter[ 0 ] = value:
        *iwriter = alias::size( scalar( &vec ) )
        ,  // vec:{ |6, 4, 5, 6, 0, 7 }
        // prefix and postfix offset increment:
        (++iwriter)++
        ,  // vec:{ 6, 4,|5, 6, 0, 7 }
        CTTL_LAMBDA_ASSERT( alias::offset( iwriter ) == scalar( 2u ) )
        ,
        // set inode position at the end:
        iwriter = alias::size( scalar( &vec ) )
        ,  // vec:{ 6, 4, 5, 6, 0, 7| }
        CTTL_LAMBDA_ASSERT( alias::offset( iwriter ) == alias::size( scalar( &vec ) ) )
        ,
        // compare offsets
        CTTL_LAMBDA_ASSERT( iwriter == alias::size( scalar( &vec ) ) )
        ,
        // verify inode position is not zero:
        CTTL_LAMBDA_ASSERT( !!iwriter )
        ,
        // verify inode position is at the end:
        CTTL_LAMBDA_ASSERT( iwriter == alias::end( iwriter ) )

    ).evaluate();

    std::copy(
        vec.begin(),
        vec.end(),
        std::ostream_iterator< size_t >( std::cout, " " )
        );

    return 0;
}
/*
Program output:
6 4 5 6 0 7
*/
