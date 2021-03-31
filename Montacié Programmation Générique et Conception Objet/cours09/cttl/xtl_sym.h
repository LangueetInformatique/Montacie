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

/**@file xtl_sym.h
* @brief Defines CTTL
*        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme functions</a>
*        and <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptors</a>.
*
* @warning
*      This is internal CTTL header file and should not
*      be included by user programs.
*
*/

// xtl_sym.h

#ifndef _CTTL_XTL_SYM_H_INCLUDED_
#define _CTTL_XTL_SYM_H_INCLUDED_

namespace cttl {

    using namespace cttl_impl;

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptor</a>,
    * generating implementation for static grammar rule adaptor.
    *
    * @tparam Static_predicateT
    *        specifies type which is copy-constructible,
    *        and, if @c SubstrT is a typename that represents
    *        @c cttl::const_edge or @c cttl::edge, @c Static_predicateT can be invoked as
    @code
    size_t operator()( SubstrT& );
    @endcode
    *
    * @param pred_
    *        Address of the rule implementation function, which can be
    *        either global, or static member function.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        the static grammar rule adaptor.
    *
    */
    template< typename Static_predicateT >
    inline xtl_wrap< xtl_predicate< Static_predicateT > >
        rule( const Static_predicateT pred_ )
    {
        return xtl_wrap< xtl_predicate< Static_predicateT > >( pred_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6800_funct.html">function adaptor</a>,
    * generating implementation for member function adaptor.
    *
    * @tparam ObjectT
    *        specifies type of C++ class that defines
    *        non-static member function @c Member_predicateT.
    *
    * @tparam Member_predicateT
    *        specifies type of a non-static member function,
    *        accepting specialization of @c cttl::const_edge or @c cttl::edge
    *        as a parameter, and returning @c size_t <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1300_interface.html">evaluation result</a>.
    *
    * @param object_ref_
    *        Object reference.
    *
    * @param pred_
    *        Address of the rule implementation member function,
    *        which can be declared either @c const or mutable.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        member function adaptor.
    *
    */
    template< typename ObjectT, typename PredicateT >
    inline xtl_wrap< xtl_member_predicate< ObjectT, PredicateT > >
        rule( ObjectT& object_ref_, PredicateT pred_ )
    {
        return xtl_wrap< xtl_member_predicate< ObjectT, PredicateT > >( xtl_member_predicate< ObjectT, PredicateT >( object_ref_, pred_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol( )
    @endcode
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char_symbol >
        symbol()
    {
        return xtl_wrap< xtl_char_symbol >();
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin( )
    @endcode expression.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_position_bof >
        begin()
    {
        return xtl_wrap< xtl_position_bof >();
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(true)
    @endcode
    * and
    @code
    symbol(false)
    @endcode
    *
    * @param bool_
    *        boolean flag specifying type of the lexeme.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_bool< false > >
        symbol( bool bool_ )
    {
        // fails on empty substring
        return xtl_wrap< xtl_bool< false > >( bool_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(true)
    @endcode
    * and
    @code
    begin(false)
    @endcode
    *
    * @param bool_
    *        boolean flag specifying type of the lexeme.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_bool< true > >
        begin( bool bool_ )
    {
        // succeeds on empty substring
        return xtl_wrap< xtl_bool< true > >( bool_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(CTTL_STD_CHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char< CTTL_STD_CHAR > >
        symbol( CTTL_STD_CHAR char_ )
    {
        return xtl_wrap< xtl_char< CTTL_STD_CHAR > >( char_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(CTTL_STD_WCHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char< CTTL_STD_WCHAR > >
        symbol( CTTL_STD_WCHAR char_ )
    {
        return xtl_wrap< xtl_char< CTTL_STD_WCHAR > >( char_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(int)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char< CTTL_STD_CHAR > >
        symbol( int char_ )
    {
        // allows symbol( 0x0a ) notation for individual characters
        return xtl_wrap< xtl_char< CTTL_STD_CHAR > >( CTTL_STD_CHAR( char_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(CTTL_STD_CHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char_begin< CTTL_STD_CHAR > >
        begin( CTTL_STD_CHAR char_ )
    {
        return xtl_wrap< xtl_char_begin< CTTL_STD_CHAR > >( char_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(CTTL_STD_WCHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char_begin< CTTL_STD_WCHAR > >
        begin( CTTL_STD_WCHAR char_ )
    {
        return xtl_wrap< xtl_char_begin< CTTL_STD_WCHAR > >( char_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(int)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char_begin< CTTL_STD_CHAR > >
        begin( int char_ )
    {
        // allows begin( 0x0a ) notation for individual characters
        return xtl_wrap< xtl_char_begin< CTTL_STD_CHAR > >( CTTL_STD_CHAR( char_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(CTTL_STD_CHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char_end< CTTL_STD_CHAR > >
        end( CTTL_STD_CHAR char_ )
    {
        return xtl_wrap< xtl_char_end< CTTL_STD_CHAR > >( char_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(CTTL_STD_WCHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char_end< CTTL_STD_WCHAR > >
        end( CTTL_STD_WCHAR char_ )
    {
        return xtl_wrap< xtl_char_end< CTTL_STD_WCHAR > >( char_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(int)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char_end< CTTL_STD_CHAR > >
        end( int char_ )
    {
        // allows end( 0x0a ) notation for individual characters
        return xtl_wrap< xtl_char_end< CTTL_STD_CHAR > >( CTTL_STD_CHAR( char_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(std::set<std::string>&)
    @endcode
    *
    * @param keywords_
    *        reference to the @c std::set&lt;std::string&gt;& object.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_keyword< CTTL_STD_STRING > >
        begin( std::set< CTTL_STD_STRING > const& keywords_ )
    {
        return xtl_wrap< xtl_keyword< CTTL_STD_STRING > >( keywords_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(std::set<std::wstring>&)
    @endcode
    *
    * @param keywords_
    *        reference to the @c std::set&lt;std::wstring&gt;& object.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_keyword< CTTL_STD_WSTRING > >
        begin( std::set< CTTL_STD_WSTRING > const& keywords_ )
    {
        return xtl_wrap< xtl_keyword< CTTL_STD_WSTRING > >( keywords_ );
    }

    //////////////////////////////////////////////////////////////////////////////

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(is...)
    @endcode
    *
    * @param iswhat_
    *        address of C character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswhat_begin >
        begin( iswhat_T iswhat_ )
    {
        return xtl_wrap< xtl_iswhat_begin >( iswhat_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(is...)
    @endcode
    *
    * @param iswhat_
    *        address of C character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswhat_end >
        end( iswhat_T iswhat_ )
    {
        return xtl_wrap< xtl_iswhat_end >( iswhat_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(is...)
    @endcode
    *
    * @param iswhat_
    *        address of C character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswhat_first >
        first( iswhat_T iswhat_ )
    {
        return xtl_wrap< xtl_iswhat_first >( iswhat_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(is...)
    @endcode
    *
    * @param iswhat_
    *        address of C character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswhat_entity >
        entity( iswhat_T iswhat_ )
    {
        return xtl_wrap< xtl_iswhat_entity >( iswhat_ );
    }

    //////////////////////////////////////////////////////////////////////////////


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(isw...)
    @endcode
    *
    * @par @c iswwhat_
    *        address of C wide character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswwhat_begin >
        begin( iswwhat_T iswwhat_ )
    {
        return xtl_wrap< xtl_iswwhat_begin >( iswwhat_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(isw...)
    @endcode
    *
    * @par @c iswwhat_
    *        address of C wide character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswwhat_end >
        end( iswwhat_T iswwhat_ )
    {
        return xtl_wrap< xtl_iswwhat_end >( iswwhat_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(isw...)
    @endcode
    *
    * @par @c iswwhat_
    *         address of C wide character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswwhat_first >
        first( iswwhat_T iswwhat_ )
    {
        return xtl_wrap< xtl_iswwhat_first >( iswwhat_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(isw...)
    @endcode
    *
    * @par @c iswwhat_
    *         address of C wide character classification routine.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_iswwhat_entity >
        entity( iswwhat_T iswwhat_ )
    {
        return xtl_wrap< xtl_iswwhat_entity >( iswwhat_ );
    }

    //////////////////////////////////////////////////////////////////////////////


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(CTTL_STD_CHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >
        begin( CTTL_STD_CHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(CTTL_STD_WCHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >
        begin( CTTL_STD_WCHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(std::string const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >
        begin( CTTL_STD_STRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(std::wstring const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >
        begin( CTTL_STD_WSTRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(std::string const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_begin< CTTL_STD_STRING > >
        begin( CTTL_STD_STRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_begin< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    begin(std::wstring const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_begin< CTTL_STD_WSTRING > >
        begin( CTTL_STD_WSTRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_begin< CTTL_STD_WSTRING > >( any_text_ );
    }

    //////////////////////////////////////////////////////////////////////////


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(CTTL_STD_CHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_end< CTTL_STD_STRING > >
        end( CTTL_STD_CHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_end< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(CTTL_STD_WCHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > >
        end( CTTL_STD_WCHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(std::string const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_end< CTTL_STD_STRING > >
        end( CTTL_STD_STRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_end< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(std::wstring const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > >
        end( CTTL_STD_WSTRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(std::string const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_end< CTTL_STD_STRING > >
        end( CTTL_STD_STRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_end< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end(std::wstring const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_end< CTTL_STD_WSTRING > >
        end( CTTL_STD_WSTRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_end< CTTL_STD_WSTRING > >( any_text_ );
    }

    //////////////////////////////////////////////////////////////////////////////////

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(CTTL_STD_CHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_first< CTTL_STD_STRING > >
        first( CTTL_STD_CHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_first< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(CTTL_STD_WCHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_first< CTTL_STD_WSTRING > >
        first( CTTL_STD_WCHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_first< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(std::string const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_first< CTTL_STD_STRING > >
        first( CTTL_STD_STRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_first< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(std::wstring const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_first< CTTL_STD_WSTRING > >
        first( CTTL_STD_WSTRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_first< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(std::string const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_first< CTTL_STD_STRING > >
        first( CTTL_STD_STRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_first< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    first(std::wstring const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_first< CTTL_STD_WSTRING > >
        first( CTTL_STD_WSTRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_first< CTTL_STD_WSTRING > >( any_text_ );
    }

    ///////////////////////////////////////////////////////////////////////


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(CTTL_STD_CHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char< CTTL_STD_CHAR > >
        entity( CTTL_STD_CHAR char_ )
    {
        return xtl_wrap< xtl_char< CTTL_STD_CHAR > >( char_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(CTTL_STD_WCHAR)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char< CTTL_STD_WCHAR > >
        entity( CTTL_STD_WCHAR char_ )
    {
        return xtl_wrap< xtl_char< CTTL_STD_WCHAR > >( char_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(int)
    @endcode
    *
    * @param char_
    *        character to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_char< CTTL_STD_CHAR > >
        entity( int char_ )
    {
        // allows entity( 0x0a ) notation for individual characters
        return xtl_wrap< xtl_char< CTTL_STD_CHAR > >( CTTL_STD_CHAR( char_ ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(CTTL_STD_CHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_entity< CTTL_STD_STRING > >
        entity( CTTL_STD_CHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_entity< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(CTTL_STD_WCHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_entity< CTTL_STD_WSTRING > >
        entity( CTTL_STD_WCHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_entity< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(std::string const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_entity< CTTL_STD_STRING > >
        entity( CTTL_STD_STRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_entity< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(std::wstring const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_entity< CTTL_STD_WSTRING > >
        entity( CTTL_STD_WSTRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_entity< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(std::string const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_entity< CTTL_STD_STRING > >
        entity( CTTL_STD_STRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_entity< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    entity(std::wstring const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_entity< CTTL_STD_WSTRING > >
        entity( CTTL_STD_WSTRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_entity< CTTL_STD_WSTRING > >( any_text_ );
    }

    //////////////////////////////////////////////////////////////////////////////


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(CTTL_STD_CHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_symbol< CTTL_STD_STRING > >
        symbol( CTTL_STD_CHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_symbol< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(CTTL_STD_WCHAR const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_symbol< CTTL_STD_WSTRING > >
        symbol( CTTL_STD_WCHAR const* any_text_ )
    {
        return xtl_wrap< xtl_text_symbol< CTTL_STD_WSTRING > >( any_text_ );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(std::string const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_symbol< CTTL_STD_STRING > >
        symbol( CTTL_STD_STRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_symbol< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(std::wstring const&)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_symbol< CTTL_STD_WSTRING > >
        symbol( CTTL_STD_WSTRING const& any_text_ )
    {
        return xtl_wrap< xtl_text_symbol< CTTL_STD_WSTRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(std::string const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_symbol< CTTL_STD_STRING > >
        symbol( CTTL_STD_STRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_symbol< CTTL_STD_STRING > >( any_text_ );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    symbol(std::wstring const*)
    @endcode
    *
    * @param any_text_
    *        text to match.
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_text_ref_symbol< CTTL_STD_WSTRING > >
        symbol( CTTL_STD_WSTRING const* any_text_ )
    {
        return xtl_wrap< xtl_text_ref_symbol< CTTL_STD_WSTRING > >( any_text_ );
    }


    /////////////////////////////////////////////////////////////////////////////////


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">lexeme function</a>
    * helper implementation.
    *
    * Usage:
    @code
    end( )
    @endcode
    *
    * @return
    *        Instance of C++ lexeme implementation class.
    *
    */
    inline xtl_wrap< xtl_position_eof >
        end()
    {
        return xtl_wrap< xtl_position_eof >();
    }

}   // namespace cttl

#endif // _CTTL_XTL_SYM_H_INCLUDED_
