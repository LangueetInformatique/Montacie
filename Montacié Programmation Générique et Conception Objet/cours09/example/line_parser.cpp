// sample code: line_parser.cpp
// demonstrates text line parser using positive lookbehind
// assertion to parse individual lines of input text

//#define CTTL_TRACE_EVERYTHING    //define to turn tracing on
//#define CTTL_TRACE_RULES    //define to turn rule tracing on

#include "cttl/cttl.h"

using namespace cttl;

int main()
{
    std::string inp = "line1\nline2\nline3";
    const_edge<> substring( inp );
    const_edge<> line = substring;

    while (
            substring.length()
            &&
            lookbehind(
                line( entity() ),
                '\n' | end()
            ).match( substring ) != std::string::npos
        )
    {
        std::cout << "Line: " << line << std::endl;
    }

    return 0;
}
/*Output:
Line: line1
Line: line2
Line: line3
*/
