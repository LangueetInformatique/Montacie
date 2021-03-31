// sample code: policy_dash.cpp
// demonstrates custom space policy
// defined as dash characters, '-'.

#include <iostream>
#include "cttl/cttl.h"

using namespace cttl;

struct policy_dash : public policy_default
{
    template< typename SubstrT >
    static size_t match( SubstrT& substr_ )
    {
        typedef typename SubstrT::char_T char_T;
        size_t ungreedy_offset = substr_.first.offset();
        ( true ^ *symbol( char_T( '-' ) ) ).match( substr_ );
        // policy_dash is non-greedy:
        return ungreedy_offset;
    }
};    // struct policy_dash

int main()
{
    std::string inp = "-a-b-c--d-e-f---";
    const_edge< policy_dash > substring( inp );
    const_edge<> data = substring;
    size_t result = ( data( +entity( isalpha ) ) ).match( substring );
    assert( result != std::string::npos );
    std::cout << "data: /" << data.text() << '/' << std::endl;
    return 0;
}
/*Output:
data: /a-b-c--d-e-f/
*/