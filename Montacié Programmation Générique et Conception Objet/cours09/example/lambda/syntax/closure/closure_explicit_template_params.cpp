// closure_explicit_template_params.cpp
//
// Program demonstrates closure with explicit template parameters.
// Sometimes template parameters for std::mem_fun must be provided
// explicitly. This situation occurs when class has overloaded
// functions with different return types.
//
// Also note, that alias::offset() cannot be used for
// the inode_writer class, because alias::offset() is expecting
// size_t as a return type. 

#define CTTL_TRACE_RULES // turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"
#include "utils/inode.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::vector< size_t > vec( 1, 0 ); // one elem with zero value
    lambda< inode_writer<> >::scalar iwriter = inode_writer<>( vec );
    (
        // closure equivalent of iwriter = size_t( 0 ):
        *scalar(
            CTTL_MEMBER_ACTION(
                &iwriter.top(),
                ( std::mem_fun< void, inode_writer<>, size_t >( &inode_writer<>::offset ) ),
                size_t( 0 )
            )
        ),
        CTTL_LAMBDA_ASSERT( alias::offset( iwriter ) == 0u )

    ).evaluate();

    return 0;
}
