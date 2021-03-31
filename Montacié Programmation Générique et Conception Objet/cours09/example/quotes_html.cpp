// quotes_html.cpp
//#define CTTL_TRACE_RULES
#include "cttl/cttl.h"

using namespace cttl;

/**This grammar rule matches HTML text.*/
size_t rule_text( const_edge<>& substr_ )
{
    if ( substr_.length() == 0 ) {
        return std::string::npos;
    }
    // Assume that the entire parseable substring
    // represents the text inside an HTML tag:
    std::cout
        << "TEXT: [" << substr_ << ']'
        << std::endl
        ;
    // Grab starting position of text:
    size_t result = substr_.first.offset();
    // Update ending position of text:
    substr_.first = substr_.second;
    return result;
}

/**This is the starting grammar rule to match HTML tags.*/
size_t rule_element( const_edge<>& substr_ )
{
    const_edge<> interior = substr_;
    const_edge<> element_name = substr_;

    size_t result =
        quote(
            quote( '<', literal(), '>' ),
            interior( CTTL_STATIC_RULE( rule_element ) ),
            quote( symbol('<')+'/', element_name( literal() ), symbol( '>' ) )
        ).match( substr_ );

    if ( result != std::string::npos ) {
        // A tag was found: print some info:
        std::cout
            << "ELEMENT " << element_name
            << ": [" << interior << ']'
            << std::endl
            ;
        // Since more tags may exist, try to evaluate them too:
        ( *CTTL_STATIC_RULE( rule_element ) ).match( substr_ );
        return result;
    }

    return CTTL_STATIC_RULE( rule_text ).match( substr_ );
}

/**Very simple program to match some HTML tags.*/
int main()
{
    // Construct simple HTML.
    // HTML elements are formed by pairs of tags:
    std::string inp =
        "<HTML>"
        "<BODY>"
        "<p id='greeting'>Hello, World!</p>"
        "<p>2nd paragraph</p>"
        "</BODY>"
        "</HTML>"
        ;
    const_edge<> substring( inp );
    CTTL_STATIC_RULE( rule_element ).match( substring );
    return 0;
}
/*Output
TEXT: [Hello, World!]
ELEMENT p: [Hello, World!]
TEXT: [2nd paragraph]
ELEMENT p: [2nd paragraph]
ELEMENT BODY: [<p id='greeting'>Hello, World!</p><p>2nd paragraph</p>]
ELEMENT HTML: [<BODY><p id='greeting'>Hello, World!</p><p>2nd paragraph</p></BODY>]
*/
