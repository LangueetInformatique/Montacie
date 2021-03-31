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

/**@file xtl_metaphor.h
 * @brief Defines CTTL
 *        metaphor functions,
 *        encapsulating complex expressions relying on other
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">primitives</a>,
 *        such as <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7500_operator.html">overloaded operators</a>
 *        and <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6200_lexeme.html">grammar lexemes</a>.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xtl_metaphor.h

#ifndef _CTTL_XTL_METAPHOR_H_INCLUDED_
#define _CTTL_XTL_METAPHOR_H_INCLUDED_

/**@def CTTL_QWERTY_
 * @brief String literal containing alphabetic characters and underscore.
 *
 */
#define CTTL_QWERTY_ "QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm"

/**@def CTTL_QWERTY_123_
 * @brief String literal containing alphabetic characters, underscore, and digits.
 *
 */
#define CTTL_QWERTY_123_ "QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm1234567890"

/**@def CTTL_WCHAR_QWERTY_
 * @brief Wide-character string literal containing alphabetic characters and underscore.
 *
 */
#define CTTL_WCHAR_QWERTY_ L"QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm"

/**@def CTTL_WCHAR_QWERTY_123_
 * @brief Wide-character string literal containing alphabetic characters, underscore, and numbers.
 *
 */
#define CTTL_WCHAR_QWERTY_123_ L"QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm1234567890"


namespace cttl {

using namespace cttl_impl;

/**Implements behavior of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 *
 @code
    begin( CTTL_QWERTY_ ) ^ end( CTTL_QWERTY_123_ )
 @endcode
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_end< CTTL_STD_STRING > > > >
literal()
{
    const CTTL_STD_CHAR CTTL_QWERTY_CONST[] = CTTL_QWERTY_;
    const CTTL_STD_CHAR CTTL_QWERTY_123_CONST[] = CTTL_QWERTY_123_;
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_end< CTTL_STD_STRING > > > >(
        //begin( CTTL_STD_STRING( CTTL_QWERTY_ ) ) ^ end( CTTL_STD_STRING( CTTL_QWERTY_123_ ) )
        begin( CTTL_STD_STRING( CTTL_QWERTY_CONST ) )
        ^
        end( CTTL_STD_STRING( CTTL_QWERTY_123_CONST ) )
        );
}

/**Implements behavior of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @param text_begin_
 *        character entity specifying upper boundary of the literal.
 *
 * @param text_end_
 *        character entity specifying lower boundary of the literal.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 @code
    begin( text_begin_ ) ^ end( text_end_ )
 @endcode
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_end< CTTL_STD_STRING > > > >
literal( CTTL_STD_CHAR const* text_begin_, CTTL_STD_CHAR const* text_end_ )
{
    // compile time function
    // literal() is example of a function returning complex expression of type "expr ^ expr"
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_end< CTTL_STD_STRING > > > >(
        begin( text_begin_ ) ^ end( text_end_ )
        );
}

/**Implements behavior of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @param text_begin_
 *        character entity specifying upper boundary of the literal.
 *
 * @param text_end_
 *        character entity specifying lower boundary of the literal.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 @code
    begin( text_begin_ ) ^ end( text_end_ )
 @endcode
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_end< CTTL_STD_STRING > > > >
literal( CTTL_STD_STRING const& text_begin_, CTTL_STD_STRING const& text_end_ )
{
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_end< CTTL_STD_STRING > > > >(
        begin( text_begin_ ) ^ end( text_end_ )
        );
}

/**Implements behavior of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @param text_begin_
 *        address of character entity string specifying upper boundary of the literal.
 *
 * @param text_end_
 *        address of character entity string specifying lower boundary of the literal.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 @code
    begin( text_begin_ ) ^ end( text_end_ )
 @endcode
 *
 * @pre
 *        This function generates reference-based implementation. Therefore,
 *        strings pointed by @c text_begin_ and @c text_end_ should stay in scope
 *        while literal is in use.
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_ref_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_ref_end< CTTL_STD_STRING > > > >
literal( CTTL_STD_STRING const* text_begin_, CTTL_STD_STRING const* text_end_ )
{
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_ref_begin< CTTL_STD_STRING > >, xtl_wrap< xtl_text_ref_end< CTTL_STD_STRING > > > >(
        begin( text_begin_ ) ^ end( text_end_ )
        );
}

/**Implements behavior of wide character
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 @code
    begin( CTTL_WCHAR_QWERTY_ ) ^ end( CTTL_WCHAR_QWERTY_123_ )
 @endcode
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > > > >
wchar_literal()
{
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > > > >(
        begin( CTTL_STD_WSTRING( CTTL_WCHAR_QWERTY_ ) ) ^ end( CTTL_STD_WSTRING( CTTL_WCHAR_QWERTY_123_ ) )
        );
}


/**Implements behavior of wide character
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @param text_begin_
 *        character entity specifying upper boundary of the literal.
 *
 * @param text_end_
 *        character entity specifying lower boundary of the literal.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 @code
    begin( text_begin_ ) ^ end( text_end_ )
 @endcode
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > > > >
wchar_literal( CTTL_STD_WCHAR const* text_begin_, CTTL_STD_WCHAR const* text_end_ )
{
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > > > >(
        begin( text_begin_ ) ^ end( text_end_ )
        );
}


/**Implements behavior of wide character
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @param text_begin_
 *        character entity specifying upper boundary of the literal.
 *
 * @param text_end_
 *        character entity specifying lower boundary of the literal.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 @code
    begin( text_begin_ ) ^ end( text_end_ )
 @endcode
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > > > >
wchar_literal( CTTL_STD_WSTRING const& text_begin_, CTTL_STD_WSTRING const& text_end_ )
{
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_end< CTTL_STD_WSTRING > > > >(
        begin( text_begin_ ) ^ end( text_end_ )
        );
}


/**Implements behavior of wide character
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6450_literal.html">literal</a>
 * metaphor
 * inside CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @param text_begin_
 *        address of character entity string specifying upper boundary of the literal.
 *
 * @param text_end_
 *        address of character entity string specifying lower boundary of the literal.
 *
 * @return
 *        Instance of C++ implementation class for grammar expression
 @code
    begin( text_begin_ ) ^ end( text_end_ )
 @endcode
 *
 * @pre
 *        This function generates reference-based implementation. Therefore,
 *        strings pointed by @c text_begin_ and @c text_end_ should stay in scope
 *        while literal is in use.
 *
 */
inline xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_ref_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_ref_end< CTTL_STD_WSTRING > > > >
wchar_literal( CTTL_STD_WSTRING const* text_begin_, CTTL_STD_WSTRING const* text_end_ )
{
    return xtl_wrap< xtl_opbinconcat< xtl_wrap< xtl_text_ref_begin< CTTL_STD_WSTRING > >, xtl_wrap< xtl_text_ref_end< CTTL_STD_WSTRING > > > >(
        begin( text_begin_ ) ^ end( text_end_ )
        );
}


/**Helper function to create implemention object for
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7030_entity.html">entity adaptor</a>
 * filtering successful result of grammar evaluation
 * based on <i>non-empty match</i>.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        which is determined by the C++ compiler at compile time.
 *
 * @param expr_
 *        constant reference to C++ object representing CTTL
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @return
 *        Instance of C++ implementation class for
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7030_entity.html">entity adaptor</a>.
 *
 */
template< typename ExprT >
xtl_wrap<
    xtl_entity<
        xtl_wrap< ExprT >
    >
>
entity( xtl_wrap< ExprT > const& expr_ )
{
    typedef
        xtl_entity<
            xtl_wrap< ExprT >
        > xtl_entity_T;

    return xtl_wrap< xtl_entity_T >( xtl_entity_T( expr_ ) );
}


/**Helper function to create implemention object for
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6230_entity.html">entity lexeme</A>.
 *
 * @return
 *        Instance of C++ implementation class that
 *        matches current substring.
 *
 */
inline universe_T
entity()
{
    return universe_T(
        relaxed_bool_T( true ) + !end()
        );
}


/**Helper function to create implemention object for
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7005_begin.html">positive lookahead assertion</a>
 * adaptor.
 *
 * @tparam ExprT
 *        specifies type of
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
 *        which is determined by the C++ compiler at compile time.
 *
 * @param expr_
 *        constant reference to C++ object representing CTTL
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>.
 *
 * @return
 *        Instance of C++ implementation class for
 *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7005_begin.html">positive lookahead assertion</a>
 *        adaptor.
 *
 */
template< typename ExprT >
xtl_wrap<
    xtl_lookahead<
        xtl_wrap< ExprT >
    >
>
begin( xtl_wrap< ExprT > const& expr_ )
{
    typedef
        xtl_lookahead<
            xtl_wrap< ExprT >
        > xtl_lookahead_T;

    return xtl_wrap< xtl_lookahead_T >( xtl_lookahead_T( expr_ ) );
}


}   // namespace cttl

#endif // _CTTL_XTL_METAPHOR_H_INCLUDED_
