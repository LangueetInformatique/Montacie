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

/**@file xtl_quote_sym.h
* @brief Defines formats of CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>s.
*
* @warning
*      This is internal CTTL header file and should not
*      be included by user programs.
*
*/

// xtl_quote_sym.h

#ifndef _CTTL_XTL_QUOTE_SYM_H_INCLUDED_
#define _CTTL_XTL_QUOTE_SYM_H_INCLUDED_

namespace cttl {

    using namespace cttl_impl;

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * for implementation of generic quote.
    *
    * @tparam LeftT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing opening clause of the quote.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @tparam RightT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing closing unit of the quote.
    *
    * @param left_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing opening clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @param right_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing closing unit of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing generic quote.
    *
    */
    template< typename LeftT, typename MiddleT, typename RightT >
    inline
        xtl_wrap<
        xtl_quote_generic<
        xtl_wrap< LeftT >,
        xtl_wrap< MiddleT >,
        xtl_wrap< RightT >
        >
        >
        quote( xtl_wrap< LeftT > const& left_, xtl_wrap< MiddleT > const& middle_, xtl_wrap< RightT > const& right_ )
    {
        typedef
            xtl_quote_generic<
            xtl_wrap< LeftT >,
            xtl_wrap< MiddleT >,
            xtl_wrap< RightT >
            >
            xtl_quote_T;

        return xtl_wrap< xtl_quote_T >( xtl_quote_T( left_, middle_, right_ ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for asymmetric quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @tparam RightT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing closing unit of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @param right_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing closing unit of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing asymmetric quote.
    *
    */
    template< typename MiddleT, typename RightT >
    inline
        xtl_wrap<
        xtl_quote_bool<
        xtl_wrap< MiddleT >,
        xtl_wrap< RightT >
        >
        >
        quote( bool, xtl_wrap< MiddleT > const& middle_, xtl_wrap< RightT > const& right_ )
    {
        typedef
            xtl_quote_bool<
            xtl_wrap< MiddleT >,
            xtl_wrap< RightT >
            >
            xtl_quote_T;

        return xtl_wrap< xtl_quote_T >( xtl_quote_T( middle_, right_ ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7940_lkbhind.html">positive lookbehind assertion</a>
    * helper function.
    *
    * @tparam BehindT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing the first expression in lookbehind relation.
    *
    * @tparam AheadT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing the second expression in lookbehind relation.
    *
    * @param behind_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        to the first expression.
    *
    * @param ahead_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        to the second expression.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing positive lookbehind relation.
    *
    */
    template< typename BehindT, typename AheadT >
    inline
        xtl_wrap<
        xtl_quote_bool<
        xtl_wrap< BehindT >,
        xtl_wrap< AheadT >
        >
        >
        lookbehind( xtl_wrap< BehindT > const& behind_, xtl_wrap< AheadT > const& ahead_ )
    {
        typedef
            xtl_quote_bool<
            xtl_wrap< BehindT >,
            xtl_wrap< AheadT >
            >
            xtl_quote_T;

        return xtl_wrap< xtl_quote_T >( xtl_quote_T( behind_, ahead_ ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for single-character quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param left_
    *        character representing opening of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @param right_
    *        character representing closing of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing single-character quote.
    *
    */
    template< typename MiddleT >
    inline
        xtl_wrap<
        xtl_quote_generic<
        xtl_wrap< xtl_char< CTTL_STD_CHAR > >,
        xtl_wrap< MiddleT >,
        xtl_wrap< xtl_char< CTTL_STD_CHAR > >
        >
        >
        quote( CTTL_STD_CHAR left_, xtl_wrap< MiddleT > const& middle_, CTTL_STD_CHAR right_ )
    {
        typedef
            xtl_quote_generic<
            xtl_wrap< xtl_char< CTTL_STD_CHAR > >,
            xtl_wrap< MiddleT >,
            xtl_wrap< xtl_char< CTTL_STD_CHAR > >
            >
            xtl_quote_T;

        return xtl_wrap< xtl_quote_T >( xtl_quote_T( xtl_char< CTTL_STD_CHAR >( left_ ), middle_, xtl_char< CTTL_STD_CHAR >( right_ ) ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for single wide character quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param left_
    *        character representing opening of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @param right_
    *        character representing closing of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing single wide character quote.
    *
    */
    template< typename MiddleT >
    inline
        xtl_wrap<
        xtl_quote_generic<
        xtl_wrap< xtl_char< CTTL_STD_WCHAR > >,
        xtl_wrap< MiddleT >,
        xtl_wrap< xtl_char< CTTL_STD_WCHAR > >
        >
        >
        wchar_quote( CTTL_STD_WCHAR left_, xtl_wrap< MiddleT > const& middle_, CTTL_STD_WCHAR right_ )
    {
        typedef
            xtl_quote_generic<
            xtl_wrap< xtl_char< CTTL_STD_WCHAR > >,
            xtl_wrap< MiddleT >,
            xtl_wrap< xtl_char< CTTL_STD_WCHAR > >
            >
            xtl_quote_T;

        return xtl_wrap< xtl_quote_T >( xtl_quote_T( xtl_char< CTTL_STD_WCHAR >( left_ ), middle_, xtl_char< CTTL_STD_WCHAR >( right_ ) ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for ANSI single quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing ANSI single quote.
    *
    */
    template< typename MiddleT >
    inline
        xtl_wrap<
        xtl_quote_ansi_single_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR >
        >
        ansi_single_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_ansi_single_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR > >( xtl_quote_ansi_single_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR >( middle_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for ANSI single quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing ANSI single quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including
    *        an empty string.
    *
    */
    inline ansi_single_quote_T
        ansi_single_quote()
    {
        return ansi_single_quote_T( xtl_quote_ansi_single_quote< relaxed_bool_T, CTTL_STD_CHAR >( true ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for
    * ANSI double quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing ANSI double quote.
    *
    */
    template< typename MiddleT >
    inline xtl_wrap< xtl_quote_ansi_double_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR > >
        ansi_double_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_ansi_double_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR > >( xtl_quote_ansi_double_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR >( middle_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for ANSI double quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing ANSI double quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including
    *        an empty string.
    *
    */
    inline ansi_double_quote_T
        ansi_double_quote()
    {
        return ansi_double_quote_T( xtl_quote_ansi_double_quote< relaxed_bool_T, CTTL_STD_CHAR >( true ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for C single quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing C single quotes quote.
    *
    */
    template< typename MiddleT >
    inline
        xtl_wrap<
        xtl_quote_c_single_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR >
        >
        c_single_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_c_single_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR > >( xtl_quote_c_single_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR >( middle_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for C single quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing C single quotes quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including
    *        an empty string.
    *
    */
    inline c_single_quote_T
        c_single_quote()
    {
        return c_single_quote_T( xtl_quote_c_single_quote< relaxed_bool_T, CTTL_STD_CHAR >( true ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for C double quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing C double quote.
    *
    */
    template< typename MiddleT >
    inline xtl_wrap< xtl_quote_c_double_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR > >
        c_double_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_c_double_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR > >( xtl_quote_c_double_quote< xtl_wrap< MiddleT >, CTTL_STD_CHAR >( middle_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for C double quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing C double quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including 
    *        an empty string.
    *
    */
    inline c_double_quote_T
        c_double_quote()
    {
        return c_double_quote_T( xtl_quote_c_double_quote< relaxed_bool_T, CTTL_STD_CHAR >( true ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character ANSI single quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character ANSI single quote.
    *
    */
    template< typename MiddleT >
    inline
        xtl_wrap<
        xtl_quote_ansi_single_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR >
        >
        wchar_ansi_single_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_ansi_single_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR > >( xtl_quote_ansi_single_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR >( middle_ ) );
    }

    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character ANSI single quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character ANSI single quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including
    *        an empty string.
    *
    */
    inline wchar_ansi_single_quote_T
        wchar_ansi_single_quote()
    {
        return wchar_ansi_single_quote_T( xtl_quote_ansi_single_quote< relaxed_bool_T, CTTL_STD_WCHAR >( true ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character ANSI double quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character ANSI double quote.
    *
    */
    template< typename MiddleT >
    inline xtl_wrap< xtl_quote_ansi_double_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR > >
        wchar_ansi_double_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_ansi_double_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR > >( xtl_quote_ansi_double_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR >( middle_ ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character ANSI double quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character ANSI double quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including
    *        an empty string.
    *
    */
    inline wchar_ansi_double_quote_T
        wchar_ansi_double_quote()
    {
        return wchar_ansi_double_quote_T( xtl_quote_ansi_double_quote< relaxed_bool_T, CTTL_STD_WCHAR >( true ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character C single quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character C single quote.
    *
    */
    template< typename MiddleT >
    inline
        xtl_wrap<
        xtl_quote_c_single_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR >
        >
        wchar_c_single_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_c_single_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR > >( xtl_quote_c_single_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR >( middle_ ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character C single quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character C single quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including
    *        an empty string.
    *
    */
    inline wchar_c_single_quote_T
        wchar_c_single_quote()
    {
        return wchar_c_single_quote_T( xtl_quote_c_single_quote< relaxed_bool_T, CTTL_STD_WCHAR >( true ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character C double quotes.
    *
    * @tparam MiddleT
    *        specifies type of
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
    *        describing interior clause of the quote.
    *
    * @param middle_
    *        constant reference to CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing interior clause of the quote.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character C double quote.
    *
    */
    template< typename MiddleT >
    inline xtl_wrap< xtl_quote_c_double_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR > >
        wchar_c_double_quote( xtl_wrap< MiddleT > const& middle_ )
    {
        return xtl_wrap< xtl_quote_c_double_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR > >( xtl_quote_c_double_quote< xtl_wrap< MiddleT >, CTTL_STD_WCHAR >( middle_ ) );
    }


    /**CTTL <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page7100_quote.html">quote helper function</a>
    * function generating implementation for wide character C double quotes.
    *
    * @return
    *        Instance of C++ implementation class for CTTL
    *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>
    *        describing wide character C double quote.
    *
    * @remarks
    *        This version of overloaded function assumes that any
    *        content inside the quotes is acceptable, including
    *        an empty string.
    *
    */
    inline wchar_c_double_quote_T
        wchar_c_double_quote()
    {
        return wchar_c_double_quote_T( xtl_quote_c_double_quote< relaxed_bool_T, CTTL_STD_WCHAR >( true ) );
    }


}   // namespace cttl


#endif // _CTTL_XTL_QUOTE_SYM_H_INCLUDED_
