////////////////////////////////////////////////////////////////////////
//
// This file is part of Common Text Transformation Library.
// Copyright (C) 1997-2009 by Igor Kholodov. 
//
// Common Text Transformation Library is free software: you can
// redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Common Text Transformation Library is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Common Text Transformation Library.
// If not, see <http://www.gnu.org/licenses/>.
//
// mailto:cttl@users.sourceforge.net
// http://cttl.sourceforge.net/
// http://sourceforge.net/projects/cttl/
//
////////////////////////////////////////////////////////////////////////

/**@file xtl_trace.h
 * @brief Defines CTTL
 *        grammar trace macros and implementation primitives
 *        in support of grammar debugging.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 * @warning
 *      None of CTTL tracing facilities are thread safe:
 *      Please limit your debugging techniques to a single
 *      thread while working in a multi-threaded environment.
 *
 * @warning
 *      There is no wide character support at present time.
 *
 */

// xtl_trace.h

#ifndef _CTTL_XTL_TRACE_H_INCLUDED_
#define _CTTL_XTL_TRACE_H_INCLUDED_

#include <iostream>
#include <string>

#define CTTL_QUOTED_EXPRESSION_HELPER( x ) #x
#define CTTL_QUOTED_EXPRESSION( x ) CTTL_QUOTED_EXPRESSION_HELPER( x )
// usage:
// CTTL_UNILOG_STREAM << CTTL_QUOTED_EXPRESSION( __LINE__ )

#define CTTL_TRACE_VARIABLE_2( xprefix, xsuffix ) xprefix ## xsuffix
#define CTTL_TRACE_VARIABLE_1( xprefix, xsuffix ) CTTL_TRACE_VARIABLE_2( xprefix, xsuffix )
#define CTTL_TRACE_VARIABLE( xprefix ) CTTL_TRACE_VARIABLE_1( xprefix, __LINE__ )

#ifdef CTTL_TRACE_EVERYTHING

#   ifdef CTTL_TRACE_EXPRESSION_TYPEID
#       define CTTL_TRACE_TYPEID( p ) ( typeid( *p ).name() )
#   else
#       ifdef CTTL_TRACE_EXPRESSION_IMPL
#           define CTTL_TRACE_TYPEID( p ) __FILE__ ";" CTTL_QUOTED_EXPRESSION( __LINE__ )
#       else
#           define CTTL_TRACE_TYPEID( p ) ""
#       endif // CTTL_TRACE_EXPRESSION_IMPL
#   endif // CTTL_TRACE_EXPRESSION_TYPEID

#   define CTTL_TRACE_LEVEL_MATCH( xchar ) cttl_impl::xtl_trace_grammar tlv( CTTL_TRACE_TYPEID( this ), edge_, xchar, cttl_impl::xtl_trace_grammar::trace_grammar_mode_match )
#   define CTTL_TRACE_LEVEL_FIND( xchar ) cttl_impl::xtl_trace_grammar tlv( CTTL_TRACE_TYPEID( this ), edge_, xchar, cttl_impl::xtl_trace_grammar::trace_grammar_mode_find )
#   define CTTL_TRACE_LEVEL_BANG( xchar ) cttl_impl::xtl_trace_grammar tlv( CTTL_TRACE_TYPEID( this ), edge_, xchar, cttl_impl::xtl_trace_grammar::trace_grammar_mode_bang )

#   define CTTL_TRACE_STATIC_LEVEL_MATCH( xchar, callbackid ) cttl_impl::xtl_trace_grammar tlv( callbackid, edge_, xchar, cttl_impl::xtl_trace_grammar::trace_grammar_mode_match )
#   define CTTL_TRACE_STATIC_LEVEL_FIND( xchar, callbackid ) cttl_impl::xtl_trace_grammar tlv( callbackid, edge_, xchar, cttl_impl::xtl_trace_grammar::trace_grammar_mode_find )
#   define CTTL_TRACE_STATIC_LEVEL_BANG( xchar, callbackid ) cttl_impl::xtl_trace_grammar tlv( callbackid, edge_, xchar, cttl_impl::xtl_trace_grammar::trace_grammar_mode_bang )

#   define CTTL_TRACE_RESULT( RESULT_, xchar ) cttl_impl::xtl_trace_grammar::trace_fragment< RESULT_ >( CTTL_TRACE_TYPEID( this ), edge_, xchar, NULL, -1 )
#   define CTTL_TRACE_STATIC_RESULT( RESULT_, xchar, xtext ) cttl_impl::xtl_trace_grammar::trace_fragment< RESULT_ >( xtext, edge_, xchar, NULL, -1 )

#   define CTTL_TRACE_EDGE_RESULT_TRUE( xchar ) cttl_impl::xtl_trace_grammar::trace_edge< true >( CTTL_TRACE_TYPEID( this ), m_edge, xchar, NULL )
#   define CTTL_TRACE_NODE_RESULT_TRUE( xchar, xedge ) cttl_impl::xtl_trace_grammar::trace_edge< true >( CTTL_TRACE_TYPEID( this ), xedge, xchar, NULL )

#   define CTTL_TRACE_EDGE_RESULT_FALSE( xchar, xidentity )  cttl_impl::xtl_trace_grammar::trace_fragment< false >( CTTL_TRACE_TYPEID( this ), edge_, xchar, NULL, xidentity )
#   define CTTL_TRACE_NODE_RESULT_FALSE( xchar, xidentity )  CTTL_TRACE_EDGE_RESULT_FALSE( xchar, xidentity )

#   define CTTL_TRACE_NODE_IDENTITY( xidentity )  cttl_impl::xtl_trace_grammar::trace_identity( xidentity )

#   define CTTL_TRACE_TEXT_RESULT( RESULT_, xchar, xtext ) cttl_impl::xtl_trace_grammar::trace_fragment< RESULT_ >( CTTL_TRACE_TYPEID( this ), edge_, xchar, xtext, -1 )
#   define CTTL_TRACE_TEXT( xchar, xtext ) cttl_impl::xtl_trace_grammar::trace_fragment< true >( xtext, edge_, xchar, NULL, -1 )
#   define CTTL_TRACE_MESSAGE( xtext ) cttl_impl::xtl_trace_grammar::trace_message( xtext )
#   define CTTL_TRACE_JUSTIFY() cttl_impl::xtl_trace_grammar::trace_justify()
#   define CTTL_RULE( xrule ) cttl_impl::xtl_traced_rule( __LINE__, CTTL_QUOTED_EXPRESSION( xrule ), *this, &xrule )
#   define CTTL_MEMBER_RULE( xobject, xrule ) cttl_impl::xtl_traced_rule( __LINE__, CTTL_QUOTED_EXPRESSION( xrule ), xobject, xrule )
#   define CTTL_STATIC_RULE( xrule ) cttl_impl::xtl_traced_rule( __LINE__, CTTL_QUOTED_EXPRESSION( xrule ), xrule )
#   define CTTL_TRACE_SILENT( xbool ) cttl_impl::xtl_trace_silencer< xbool > CTTL_TRACE_VARIABLE( xtl_trace_silencer_ ); if ( sizeof( CTTL_TRACE_VARIABLE( xtl_trace_silencer_ ) ) ){}

#   ifdef UNILOG_TRACING_ON
#       define CTTL_UNILOG_PROLOG std::basic_stringstream< char > UNILOG_STREAM_
#       define CTTL_UNILOG_STREAM UNILOG_STREAM_
#       define CTTL_UNILOG_FLUSH  UNILOG_ID_TRACE( 0x0000FEED, UNILOG_STREAM_.str().c_str() ); UNILOG_STREAM_.str( "" )
#   else
#       define CTTL_UNILOG_PROLOG
#       ifndef CTTL_UNILOG_STREAM
#           define CTTL_UNILOG_STREAM std::cout
#       endif // CTTL_UNILOG_STREAM
#       define CTTL_UNILOG_FLUSH  CTTL_UNILOG_STREAM << std::endl
#   endif //UNILOG_TRACING_ON

#else

#   define CTTL_TRACE_TYPEID( p )

#   define CTTL_TRACE_LEVEL_MATCH( xchar )
#   define CTTL_TRACE_LEVEL_FIND( xchar )
#   define CTTL_TRACE_LEVEL_BANG( xchar )

#   define CTTL_TRACE_STATIC_LEVEL_MATCH( xchar, callbackid )
#   define CTTL_TRACE_STATIC_LEVEL_FIND( xchar, callbackid )
#   define CTTL_TRACE_STATIC_LEVEL_BANG( xchar, callbackid )

#   define CTTL_TRACE_RESULT( RESULT_, xchar )
#   define CTTL_TRACE_STATIC_RESULT( RESULT_, xchar, xtext )
#   define CTTL_TRACE_EDGE_RESULT_TRUE( xchar )
#   define CTTL_TRACE_NODE_RESULT_TRUE( xchar, xedge )
#   define CTTL_TRACE_EDGE_RESULT_FALSE( xchar, xidentity ) 
#   define CTTL_TRACE_NODE_RESULT_FALSE( xchar, xidentity )
#   define CTTL_TRACE_NODE_IDENTITY( xidentity )
#   define CTTL_TRACE_TEXT_RESULT( RESULT_, xchar, xtext )
#   define CTTL_TRACE_TEXT( xchar, xtext )
#   define CTTL_TRACE_JUSTIFY()
#   ifdef CTTL_TRACE_RULES
#       define CTTL_TRACE_MESSAGE( xtext ) cttl_impl::xtl_trace_grammar::trace_message( xtext )
#       define CTTL_RULE( xrule ) cttl_impl::xtl_traced_rule( __LINE__, CTTL_QUOTED_EXPRESSION( xrule ), *this, &xrule )
#       define CTTL_MEMBER_RULE( xobject, xrule ) cttl_impl::xtl_traced_rule( __LINE__, CTTL_QUOTED_EXPRESSION( xrule ), xobject, xrule )
#       define CTTL_STATIC_RULE( xrule ) cttl_impl::xtl_traced_rule( __LINE__, CTTL_QUOTED_EXPRESSION( xrule ), xrule )
#       define CTTL_TRACE_SILENT( xbool ) cttl_impl::xtl_trace_silencer< xbool > CTTL_TRACE_VARIABLE( xtl_trace_silencer_ ); if ( sizeof( CTTL_TRACE_VARIABLE( xtl_trace_silencer_ ) ) ){}
#       ifdef UNILOG_TRACING_ON
#           define CTTL_UNILOG_PROLOG std::basic_stringstream< char > UNILOG_STREAM_
#           define CTTL_UNILOG_STREAM UNILOG_STREAM_
#           define CTTL_UNILOG_FLUSH  UNILOG_ID_TRACE( 0x0000FEED, UNILOG_STREAM_.str().c_str() ); UNILOG_STREAM_.str( "" )
#       else
#           define CTTL_UNILOG_PROLOG
#           ifndef CTTL_UNILOG_STREAM
#               define CTTL_UNILOG_STREAM std::cout
#           endif // CTTL_UNILOG_STREAM
#           define CTTL_UNILOG_FLUSH  CTTL_UNILOG_STREAM << std::endl
#       endif //UNILOG_TRACING_ON
#   else
#       ifdef CTTL_TRACE_TRIVIAL
#           define CTTL_TRACE_MESSAGE( xtext ) cttl_impl::xtl_trace_grammar::trace_message( xtext )
#       else
#           define CTTL_TRACE_MESSAGE( xtext )
#       endif // CTTL_TRACE_TRIVIAL
#       ifdef UNILOG_TRACING_ON
#           define CTTL_UNILOG_PROLOG std::basic_stringstream< char > UNILOG_STREAM_
#           define CTTL_UNILOG_STREAM UNILOG_STREAM_
#           define CTTL_UNILOG_FLUSH
#       else
#           define CTTL_UNILOG_PROLOG
#           ifndef CTTL_UNILOG_STREAM
#               define CTTL_UNILOG_STREAM std::cout
#           endif // CTTL_UNILOG_STREAM
#           define CTTL_UNILOG_FLUSH
#       endif //UNILOG_TRACING_ON
#       define CTTL_RULE( xrule ) rule( *this, &xrule )
#       define CTTL_MEMBER_RULE( xobject, xrule ) rule( xobject, xrule )
#       define CTTL_STATIC_RULE( xrule ) rule( xrule )
#       define CTTL_TRACE_SILENT( xbool )
#   endif // CTTL_TRACE_RULES

#endif // CTTL_TRACE_EVERYTHING

#ifndef UNILOG_DISABLE_AUTO_TRACE
#define UNILOG_DISABLE_AUTO_TRACE
#endif //UNILOG_DISABLE_AUTO_TRACE

namespace cttl_impl {

struct xtl_trace_grammar {

    static const size_t fragment_length = 25;

    enum trace_grammar_mode {
        trace_grammar_mode_match,
        trace_grammar_mode_find,
        trace_grammar_mode_bang
    };

    template< typename EdgeT >
    xtl_trace_grammar( CTTL_STD_CHAR const* object_name_, EdgeT const& edge_, CTTL_STD_CHAR char_, trace_grammar_mode mode_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            CTTL_UNILOG_STREAM
                << exact_edge2text( edge_, true ).c_str()
                << '?'
                ;

            build_skyline();

            CTTL_UNILOG_STREAM
                << '{'
                << char_
                << ( mode_ == trace_grammar_mode_match ? "" : ( mode_ == trace_grammar_mode_find ? "!" : "!!" ) )
                << "\t\t"
                << edge_.first.offset()
                << '-'
                << edge_.second.offset()
                << '\t'
                << object_name_
                ;
            CTTL_UNILOG_FLUSH;
        }

        depth( 1 );
    }

    template< typename EdgeT >
    xtl_trace_grammar( int object_callback_id_, EdgeT const& edge_, CTTL_STD_CHAR char_, trace_grammar_mode mode_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            CTTL_UNILOG_STREAM
                << exact_edge2text( edge_, true )
                << '?'
                ;

            build_skyline();

            CTTL_UNILOG_STREAM
                << '{'
                << char_
                << object_callback_id_
                << ( mode_ == trace_grammar_mode_match ? "" : ( mode_ == trace_grammar_mode_find ? "!" : "!!" ) )
                << "\t\t"
                << edge_.first.offset()
                << '-'
                << edge_.second.offset()
                ;
            CTTL_UNILOG_FLUSH;
        }
        depth( 1 );
    }

    ~xtl_trace_grammar()
    {
        UNILOG_DISABLE_AUTO_TRACE;
        depth( -1 );
        trace_message( "}" );
    }

    static int depth( int change_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        static int depth_ = 0;
        depth_ += change_;
        return depth_;
    }

    template< typename EdgeT >
    static typename EdgeT::string_T edge2text( EdgeT const& edge_, bool result_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        // show text located in front of the specified edge_
        CTTL_STD_STRING text_extract;

        if ( edge_.length() == EdgeT::string_T::npos ) {
            text_extract = "***INVALID***";
            padtext( text_extract, result_ );
            return text_extract;
        }

        size_t end_offset = edge_.first.offset();
        size_t begin_offset = end_offset + 1 - fragment_length;    // +1 accounts for the '@' added at the end
        if ( end_offset + 1 < fragment_length )
            begin_offset = 0;

        //ik-6/6/2009 removed text_absolute_substring()
        //text_extract = edge_.text_absolute_substring( begin_offset, end_offset ).c_str();
        assert( begin_offset <= end_offset );
        assert( end_offset <= edge_.parent().length() );
        //if ( begin_offset != end_offset ) (
        //  return StringT();
        //)
        text_extract = edge_.parent().substr(
            begin_offset,
            end_offset - begin_offset
            );
        //ik-6/6/2009

        text_extract += '@';

        padtext( text_extract, result_ );
        return text_extract;
    }

    template< typename EdgeT >
    static typename EdgeT::string_T exact_edge2text( EdgeT const& edge_, bool result_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        // show text at the beginning of the fragment

        CTTL_STD_STRING text_extract;

        if ( edge_.length() == EdgeT::string_T::npos ) {
            text_extract = "***INVALID***";
            padtext( text_extract, result_ );
            return text_extract;
        }

        size_t begin_offset = edge_.first.offset();
        size_t end_offset = edge_.second.offset();
        if ( ( end_offset - begin_offset ) > fragment_length - 1 )
            end_offset = begin_offset + fragment_length - 1;    // -1 accounts for the '@' added in front.

        text_extract = '@';
        //ik-6/6/2009 removed text_absolute_substring()
        //text_extract += edge_.text_absolute_substring( begin_offset, end_offset ).c_str();
        assert( begin_offset <= end_offset );
        assert( end_offset <= edge_.parent().length() );
        //if ( begin_offset != end_offset ) (
        //  return StringT();
        //)
        text_extract += edge_.parent().substr(
            begin_offset,
            end_offset - begin_offset
            );
        //ik-6/6/2009

        padtext( text_extract, result_ );
        return text_extract;
    }

    static CTTL_STD_STRING& whitespace2monospace( CTTL_STD_STRING& text_extract_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        CTTL_STD_STRING::size_type pos = text_extract_.length();
        while ( pos )
            if ( text_extract_[ --pos ] < ' ' )
                text_extract_[ pos ] = '.';

        return text_extract_;
    }

    static void padtext( CTTL_STD_STRING& text_extract_, bool result_  )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        whitespace2monospace( text_extract_ );

        if ( text_extract_.length() < fragment_length ) {
            if ( CTTL_UNILOG_STREAM.good() ) {
                if ( result_ )
                    for ( size_t pad = 0; pad < fragment_length - text_extract_.length(); ++ pad )
                        CTTL_UNILOG_STREAM << '-';

                else
                    for ( size_t pad = 0; pad < fragment_length - text_extract_.length(); ++ pad )
                        CTTL_UNILOG_STREAM << '~';
            }
        }
    }

    static void output_monospace_text( CTTL_STD_CHAR const* text_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            while( *text_ ) {
                CTTL_UNILOG_STREAM << ( isprint( *text_ ) ? *text_ : '.' );
                text_++;
            }
        }
    }

    static void trace_identity( size_t identity_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            if ( identity_ ) {
                CTTL_UNILOG_STREAM << ':' << identity_;
            } else {
                CTTL_UNILOG_STREAM << std::endl;
            }
        }
    }

    template< bool result_, typename EdgeT >
    static void trace_fragment( CTTL_STD_CHAR const* object_name_, EdgeT const& edge_, CTTL_STD_CHAR char_, CTTL_STD_CHAR const* text_, int identity_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            // please note that text_ can be NULL;
            // identity_ can be minus one
            CTTL_UNILOG_STREAM
                << edge2text( edge_, result_ ).c_str()
                << ( result_ ? '|' : '~' )
                ;

            build_skyline();

            CTTL_UNILOG_STREAM
                << char_;

            if ( identity_ != -1 )
                CTTL_UNILOG_STREAM << identity_;

            CTTL_UNILOG_STREAM
                << '\t'
                << '\t'
                << edge_.first.offset()
                << '-'
                << edge_.second.offset()
                << '\t'
                << ( result_ ? "" : "FAIL " )
                ;
            if ( text_ ) {
                output_monospace_text( text_ );
            } else {
                CTTL_UNILOG_STREAM << object_name_;
            }
            CTTL_UNILOG_FLUSH;
        }
    }

    template< bool result_, typename EdgeT >
    static void trace_edge( CTTL_STD_CHAR const* object_name_, EdgeT const& edge_, CTTL_STD_CHAR char_, CTTL_STD_CHAR const* text_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            // please note that text_ can be NULL
            CTTL_UNILOG_STREAM
                << exact_edge2text( edge_, result_ ).c_str()
                << ( result_ ? '|' : '~' )
                ;

            build_skyline();

            CTTL_UNILOG_STREAM
                << char_
                //DEBUG//<< edge_.first.identity()
                << "\t\t"
                << edge_.first.offset()
                << '-'
                << edge_.second.offset()
                << '\t'
                ;
            if ( text_ ) {
                output_monospace_text( text_ );
            } else {
                CTTL_UNILOG_STREAM << object_name_;
            }
            CTTL_UNILOG_FLUSH;
        }
    }

    static void trace_message( CTTL_STD_CHAR const* text_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            trace_justify();
            CTTL_UNILOG_STREAM << text_;
            //CTTL_UNILOG_FLUSH;
#ifdef UNILOG_TRACING_ON
            UNILOG_ID_TRACE( 0x0000FEED, UNILOG_STREAM_.str().c_str() ); UNILOG_STREAM_.str( "" );
#else
            CTTL_UNILOG_STREAM << std::endl;
#endif //UNILOG_TRACING_ON
        }
    }

    static void trace_message( CTTL_STD_STRING const& text_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            trace_justify();
            CTTL_UNILOG_STREAM << text_;
            //CTTL_UNILOG_FLUSH;
#ifdef UNILOG_TRACING_ON
            UNILOG_ID_TRACE( 0x0000FEED, UNILOG_STREAM_.str().c_str() ); UNILOG_STREAM_.str( "" );
#else
            CTTL_UNILOG_STREAM << std::endl;
#endif //UNILOG_TRACING_ON
        }
    }

    static void trace_justify( CTTL_STD_CHAR pad_char_ = ' ' )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            for ( size_t pad = 0; pad <= fragment_length; ++pad )
                CTTL_UNILOG_STREAM << pad_char_;

            build_skyline( pad_char_ );
        }
    }

    static void build_skyline( CTTL_STD_CHAR pad_char_ = ' ' )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( CTTL_UNILOG_STREAM.good() ) {
            for ( int dp = 0; dp < depth( 0 ); ++dp )
                CTTL_UNILOG_STREAM << pad_char_;
        }
    }

    static char const* cttl_trace_iswhat( cttl_impl::iswhat_T function_ )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        static char const* function_name[] = {
            "isspace",  // 0
            "isprint",  // 1
            "iscntrl",  // 2
            "isupper",  // 3
            "islower",  // 4
            "isalpha",  // 5
            "isdigit",  // 6
            "ispunct",  // 7
            "isxdigit", // 8
            "isalnum",  // 9
            "isgraph",  // 10
            "char class"  // 11
        };

        // (int ( * )( int )) used to avoid error: "address of overloaded function with no contextual type information"
        if ( function_ == (int ( * )( int ))&isspace ) return function_name[ 0 ];
        if ( function_ == (int ( * )( int ))&isprint ) return function_name[ 1 ];
        if ( function_ == (int ( * )( int ))&iscntrl ) return function_name[ 2 ];
        if ( function_ == (int ( * )( int ))&isupper ) return function_name[ 3 ];
        if ( function_ == (int ( * )( int ))&islower ) return function_name[ 4 ];
        if ( function_ == (int ( * )( int ))&isalpha ) return function_name[ 5 ];
        if ( function_ == (int ( * )( int ))&isdigit ) return function_name[ 6 ];
        if ( function_ == (int ( * )( int ))&ispunct ) return function_name[ 7 ];
        if ( function_ == (int ( * )( int ))&isxdigit) return function_name[ 8 ];
        if ( function_ == (int ( * )( int ))&isalnum ) return function_name[ 9 ];
        if ( function_ == (int ( * )( int ))&isgraph ) return function_name[ 10 ];
        return function_name[ 11 ];

    }// cttl_trace_iswhat

};  // struct xtl_trace_grammar

template< bool MakeSilentT >
struct xtl_trace_silencer {
    xtl_trace_silencer()
        :
    m_badbit( ( CTTL_UNILOG_STREAM.rdstate() & std::ios_base::badbit ) != 0 )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( !m_badbit ) {
            // silence output
            CTTL_UNILOG_STREAM.flush();
            CTTL_UNILOG_STREAM.setstate( std::ios_base::badbit );
        }
    }
    ~xtl_trace_silencer()
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( !m_badbit ) {
            // vocalize output
            CTTL_UNILOG_STREAM.clear();
        }
    }
private:
    // records original badbit state of the environment
    bool m_badbit;

};  // struct xtl_trace_silencer

// full specializaton for 
template<>
struct xtl_trace_silencer< false > {
    xtl_trace_silencer()
        :
    m_badbit( ( CTTL_UNILOG_STREAM.rdstate() & std::ios_base::badbit ) != 0 )
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( m_badbit ) {
            // vocalize output
            CTTL_UNILOG_STREAM.clear();
        }
    }
    ~xtl_trace_silencer()
    {
        UNILOG_DISABLE_AUTO_TRACE;
        if ( m_badbit ) {
            // silence output
            CTTL_UNILOG_STREAM.flush();
            CTTL_UNILOG_STREAM.setstate( std::ios_base::badbit );
        }
    }
private:
    // records original badbit state of the environment
    bool m_badbit;

};  // struct xtl_trace_silencer

}   // namespace cttl_impl


#endif // _CTTL_XTL_TRACE_H_INCLUDED_
