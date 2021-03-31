// rule_formats.cpp
// Examples of function signatures that can be used
// as wrapper functions for CTTL grammar rules.

#include "cttl/cttl.h"

using namespace cttl;

// Global functions:
size_t gfc( const_edge<>& ) { std::cout << "global function accepting const_edge\n"; return 0; }
size_t gfm( edge<>& )       { std::cout << "global function accepting edge\n"; return 0; }

// Member functions:
struct Parser {
    static size_t sfc( const_edge<>& ) { std::cout << "static member accepting const_edge\n"; return 0; }
    static size_t sfm( edge<>& )       { std::cout << "static member accepting edge\n"; return 0; }
    size_t mfc( const_edge<>& )        { std::cout << "member function accepting const_edge\n"; return 0; }
    size_t mfcc( const_edge<>& ) const { std::cout << "const member accepting const_edge\n"; return 0; }
    size_t mfm( edge<>& )              { std::cout << "member function accepting edge\n"; return 0; }
    size_t mfmc( edge<>& ) const       { std::cout << "const member accepting edge\n"; return 0; }
};//struct Parser

// Function objects (functors):
struct Rc  { size_t operator() ( const_edge<>& )       { std::cout << "functor accepting const_edge\n"; return 0; }       };
struct Rcc { size_t operator() ( const_edge<>& ) const { std::cout << "const functor accepting const_edge\n"; return 0; } };
struct Re  { size_t operator() ( edge<>& )             { std::cout << "functor accepting edge\n"; return 0; }             };
struct Rec { size_t operator() ( edge<>& ) const       { std::cout << "const functor accepting edge\n"; return 0; }       };

int main()
{
    std::string inp;
    const_edge<> const_substr( inp );
    edge<> mute_substr( inp );

    rule( gfc ).match( const_substr );
    rule( gfm ).match( mute_substr );

    rule( Parser::sfc ).match( const_substr );
    rule( Parser::sfm ).match( mute_substr );

    Parser parser;
    rule( parser, &Parser::mfc  ).match( const_substr );
    rule( parser, &Parser::mfcc ).match( const_substr );

    rule( parser, &Parser::mfm  ).match( mute_substr );
    rule( parser, &Parser::mfmc ).match( mute_substr );

    Rc  rc;
    Rcc rcc;
    rule( rc  ).match( const_substr );
    rule( rcc ).match( const_substr );

    Re  re;
    Rec rec;
    rule( re  ).match( mute_substr );
    rule( rec ).match( mute_substr );

    return 0;
}
