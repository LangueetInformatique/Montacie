// rule_traced.cpp
// Examples of function signatures that can be used
// as wrapper functions for CTTL grammar rules.

#define CTTL_TRACE_RULES // Turns on rule()-level tracing
#include "cttl/cttl.h"

using namespace cttl;

// Global functions:
size_t gfc( const_edge<>& ) { CTTL_TRACE_MESSAGE( "global function accepting const_edge" ); return 0; }
size_t gfm( edge<>& )       { CTTL_TRACE_MESSAGE( "global function accepting edge" ); return 0; }

// Member functions:
struct Parser {
    static size_t sfc( const_edge<>& ) { CTTL_TRACE_MESSAGE( "static member accepting const_edge" ); return 0; }
    static size_t sfm( edge<>& )       { CTTL_TRACE_MESSAGE( "static member accepting edge" ); return 0; }
    size_t mfc( const_edge<>& )        { CTTL_TRACE_MESSAGE( "member function accepting const_edge" ); return 0; }
    size_t mfcc( const_edge<>& ) const { CTTL_TRACE_MESSAGE( "const member accepting const_edge" ); return 0; }
    size_t mfm( edge<>& )              { CTTL_TRACE_MESSAGE( "member function accepting edge" ); return 0; }
    size_t mfmc( edge<>& ) const       { CTTL_TRACE_MESSAGE( "const member accepting edge" ); return 0; }
};//struct Parser

// Function objects (functors):
struct Rc  { size_t operator() ( const_edge<>& )       { CTTL_TRACE_MESSAGE( "functor accepting const_edge" ); return 0; }       };
struct Rcc { size_t operator() ( const_edge<>& ) const { CTTL_TRACE_MESSAGE( "const functor accepting const_edge" ); return 0; } };
struct Re  { size_t operator() ( edge<>& )             { CTTL_TRACE_MESSAGE( "functor accepting edge" ); return 0; }             };
struct Rec { size_t operator() ( edge<>& ) const       { CTTL_TRACE_MESSAGE( "const functor accepting edge" ); return 0; }       };

int main()
{
    std::string inp;
    const_edge<> const_substr( inp );
    edge<> mute_substr( inp );

    CTTL_STATIC_RULE( gfc ).match( const_substr );
    CTTL_STATIC_RULE( gfm ).match( mute_substr );

    CTTL_STATIC_RULE( Parser::sfc ).match( const_substr );
    CTTL_STATIC_RULE( Parser::sfm ).match( mute_substr );

    Parser parser;
    CTTL_MEMBER_RULE( parser, &Parser::mfc  ).match( const_substr );
    CTTL_MEMBER_RULE( parser, &Parser::mfcc ).match( const_substr );

    CTTL_MEMBER_RULE( parser, &Parser::mfm  ).match( mute_substr );
    CTTL_MEMBER_RULE( parser, &Parser::mfmc ).match( mute_substr );

    Rc  rc;
    Rcc rcc;
    CTTL_STATIC_RULE( rc  ).match( const_substr );
    CTTL_STATIC_RULE( rcc ).match( const_substr );

    Re  re;
    Rec rec;
    CTTL_STATIC_RULE( re  ).match( mute_substr );
    CTTL_STATIC_RULE( rec ).match( mute_substr );

    return 0;
}
