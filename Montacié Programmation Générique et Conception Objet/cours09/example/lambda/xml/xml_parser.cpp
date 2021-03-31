// xml_parser.cpp
// Utility to parse XML stream from a file

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on
//#define CTTL_LAMBDA_SINGULAR   // turns off multidimensional depositories

/**@file xml_parser.cpp
 * @brief Main driver of @ref index.
 *
 */

/**If defined, the parser will free up memory as as soon as possible.*/
#define DISPOSE_CONSUMED_DATA

#include <cstring>
#include <iostream>
#include <stack>
#include <algorithm>

#include "cttl/cttl.h"
#include "utils/fileio.h"
#include "lambda/lambda.h"
#include "utils/guard_node_stack.h"
#include "utils/inode.h"

#include "example/lambda/xml/xml_tree_struct.h"
#include "example/lambda/xml/xml_tree_show.h"
#include "example/lambda/xml/xml_stream_policy.h"

using namespace cttl;

namespace {
    // common xml alphabet
    const std::string LITERAL_XML_NAME          = CTTL_QWERTY_123_ ":-";
    const std::string LITERAL_XML_COMMENT_OPEN  = "<!--";
    const std::string LITERAL_XML_COMMENT_CLOSE = "-->";
    const std::string LITERAL_XML_PI_OPEN       = "<?";
    const std::string LITERAL_XML_PI_CLOSE      = "?>";
    const std::string LITERAL_XML_CLOSE_ELEM    = "</";
    const std::string LITERAL_XML_ELEM_CLOSED   = "/>";

    const std::pair< int, int > LENGTH_XML_COMMENT_OPEN ( LITERAL_XML_COMMENT_OPEN.length(), std::string::npos );
    const std::pair< int, int > LENGTH_XML_COMMENT_CLOSE( LITERAL_XML_COMMENT_CLOSE.length(), std::string::npos );
    const std::pair< int, int > LENGTH_XML_PI_OPEN      ( LITERAL_XML_PI_OPEN.length(), std::string::npos );
    const std::pair< int, int > LENGTH_XML_PI_CLOSE     ( LITERAL_XML_PI_CLOSE.length(), std::string::npos );
    const std::pair< int, int > LENGTH_XML_CLOSE_ELEM   ( LITERAL_XML_CLOSE_ELEM.length(), std::string::npos );
    const std::pair< int, int > LENGTH_XML_ELEM_CLOSED  ( LITERAL_XML_ELEM_CLOSED.length(), std::string::npos );
}

#include "example/lambda/xml/xml_parser.h"
#include "example/lambda/xml/xml_lexer.h"

/**Main entry point into the program.*/
int main(int argc, char* argv[])
{
    if ( argc < 2 ) {
        std::cout
            << "Usage: "
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " path/file.xml [-o]"
            << std::endl
            << "If -o switch is specified, results will be sent to the standard output."
            << std::endl
            ;
        return 1;

    } else if ( ( argc > 2 ) && strcmp( argv[ 2 ], "-o" ) ) {
        std::cout
            << "ERROR: unknown switch "
            << argv[ 2 ]
            << std::endl
            ;
        return 1;
    }


    std::string inp;
    edge<> consumed_data( inp ); 

    policy_relaxed_stream file_stream( consumed_data );
    if ( !file_stream.init( argv[ 1 ] ) ) {
        std::cout
            << "ERROR: failed to open input file "
            << std::endl
            << '\t'
            << argv[ 1 ]
            << std::endl
            ;
        return 1;
    }

    typedef edge< policy_relaxed_stream > substr_T;
    substr_T substring( consumed_data, file_stream );
    parser< substr_T > xml_parser;
    lexer< parser< substr_T > > xml_lexer( consumed_data, xml_parser );

    std::cout
        << "Parsing "
        << argv[ 1 ]
        << std::endl
        ;

    if ( xml_lexer.xml_grammar( substring ) == substr_T::string_T::npos ) {
        std::cout
            << "Parser failed"
            << std::endl
            ;

        return 1;
    }

    std::cout
        << "Done"
        << std::endl
        ;

    if ( ( argc > 2 ) && !strcmp( argv[ 2 ], "-o" ) ) {
        inode_reader<> root( xml_parser.vect_xml_tree, 1 );
        std::for_each(
            root,
            root.end(),
            xml_tree_show(
                1,
                xml_parser.vect_xml_names,
                xml_parser.vect_xml_text
                )
            );
    }
    return 0;
}
