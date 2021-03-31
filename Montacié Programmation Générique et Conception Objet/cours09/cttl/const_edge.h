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

/**@file const_edge.h
* @brief Defines cttl::const_edge, constant substring class.
*
*  @see
*  - cttl::edge
*  - cttl::node
*
*/

// const_edge.h

#ifndef _CTTL_CONST_EDGE_H_INCLUDED_
#define _CTTL_CONST_EDGE_H_INCLUDED_

#include "node.h"
#include "xtl_edge_trait.h"

namespace cttl {

    /**@class const_edge
    * @brief Implements constant parseable
    * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam PolicyT
    *        specifies <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>
    *        for the grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a> of this substring.
    *        The default policy is @c cttl::policy_default.
    *
    * @tparam StringT
    *        specifies the type of the referenced string.
    *        The default type is
    *        <tt><a href="http://www.cplusplus.com/reference/string/">std::string</a></tt>.
    *
    */
    template< typename PolicyT = policy_default, typename StringT = CTTL_STD_STRING >
    class const_edge
    {
    public:
        /**Defines offset guard type for substring boundary.*/
        typedef xtl_const_offset_guard offset_guard_T;

        /**Defines type of referenced string.*/
        typedef StringT string_T;

        /**Defines type of referenced character.*/
        typedef typename StringT::value_type char_T;

        /**Defines value type of substring.*/
        typedef StringT value_type;

        /**Defines size type of substring.*/
        typedef typename StringT::size_type size_type;

        /**Defines type of the <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.*/
        typedef PolicyT policy_T;

        /**Defines type of the strict <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
        *
        */
        typedef typename PolicyT::strict_policy_T strict_policy_T;

        /**Defines type of the substring specialized for strict
        * grammar <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">evaluation algorithm</a>.
        *
        */
        typedef const_edge< strict_policy_T, StringT > strict_edge_T;

        /**Defines type of substring boundaries,
        * represented by instances of two @c cttl::node objects.
        *
        */
        typedef node< StringT > node_T;


        /**@c cttl::node representing substring upper boundary.*/
        node< StringT > first;

        /**@c cttl::node representing substring lower boundary.*/
        node< StringT > second;

    protected:
        /**Stores reference to the
        * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>
        * of this substring.
        */
        PolicyT& m_space_policy;

        /**Returns reference to a stateless static object representing
        *  default <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a> of the substring.
        *
        * @pre
        *        Note: static objects are not thread-safe, unless their
        *        implementation is stateless. Thus, multi-threaded environment
        *        may rely only on a stateless space policy, such as,
        *        for example, @c cttl::policy_default.
        * @par
        *        Note: @c PolicyT must be default-constructible.
        *
        */
        static inline PolicyT& default_policy()
        {
#ifdef CTTL_STATEFUL_RUNTIME_MATCH
            //assert( !"Stateful policy must be provided by the user." );
            static PolicyT* const ptr_bad_policy = NULL;
            return *ptr_bad_policy;
#else
            // Because const_edge::m_space_policy is mutable,
            // a static policy, such as
            //
            //      static PolicyT stateless_static_policy;
            //
            // is declared be mutable.
            // This might generate a compiler warning such as
            // "construction of local static object is not thread-safe,"
            // which can be ignored.

            static PolicyT stateless_static_policy;
            return stateless_static_policy;
#endif //CTTL_STATEFUL_RUNTIME_MATCH
        }

    public:
        /**Returns mutable reference to instance of the
        *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a> attached to this substring.
        *
        */
        PolicyT& space_policy()
        {
            return m_space_policy;
        }

        /**Returns constant reference to instance of the
        *  <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a> attached to this substring.
        *
        */
        PolicyT const& space_policy() const
        {
            return m_space_policy;
        }

        ///////////////////////////////////////////////////////
        // Constructors, conversions, and assignment operators
        ///////////////////////////////////////////////////////

        /**Constructor taking reference to a string.
        *
        * @param inp_
        *        Mutable reference to a string.
        *
        * @post
        *        Substring boundaries are set to the positions
        *        corresponding to the beginning
        *        and the ending of the referenced string.
        *
        */
        explicit const_edge( StringT& inp_ )
            :
        first( inp_, 0 ),
            second( inp_, inp_.length() ),
            m_space_policy( default_policy() )
        {
            first.link( second );
        }

        /**Constructor taking reference to a string and
        * specific boundary positions.
        *
        * @param inp_
        *        Mutable reference to a @c string.
        *
        * @param start_
        *        Initial offset of the upper boundary (edge::first node.)
        *
        * @param finish_
        *        Initial offset of the lower boundary (edge::second node.)
        *
        */
        const_edge( StringT& inp_, size_type start_, size_type finish_ )
            :
        first( inp_, start_ ),
            second( inp_, finish_ ),
            m_space_policy( default_policy() )
        {
            first.link( second );
        }

        /**Constructor taking two @c cttl::node objects that specify
        * substring boundaries.
        *
        * @param node_first_
        *        Specifies initial offset of the upper boundary.
        *
        * @param node_second_
        *        Specifies initial offset of the lower boundary.
        *
        * @pre
        *        The nodes must belong to the same parent string;
        *        @n the nodes must be part of the same list.
        *
        */
        const_edge( node< StringT > const& node_first_, node< StringT > const& node_second_ )
            :
        first( node_first_ ),
            second( node_second_ ),
            m_space_policy( default_policy() )
        {
            assert( &node_first_.parent() == &node_second_.parent() );
        }

        /**Constructor taking two @c cttl::node objects that specify
        * substring boundaries and override specific boundary positions.
        *
        * @param node_first_
        *        Specifies initial offset of the upper boundary.
        *
        * @param node_second_
        *        Specifies initial offset of the lower boundary.
        *
        * @param start_
        *        Initial offset of the upper boundary (edge::first node.)
        *
        * @param finish_
        *        Initial offset of the lower boundary (edge::second node.)
        *
        * @pre
        *        The nodes must belong to the same parent string;
        *        @n the nodes must be part of the same list.
        *
        */
        const_edge(
            node< StringT > const& node_first_,
            node< StringT > const& node_second_,
            size_type start_,
            size_type finish_
            )
            :
        first( node_first_, start_ ),
            second( node_second_, finish_ ),
            m_space_policy( default_policy() )
        {
            assert( &node_first_.parent() == &node_second_.parent() );
        }

        /**Constructor converting another @c cttl::edge or @c cttl::const_edge
        *  to a substring with a different <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a> type.
        *
        * @tparam Other_policyT
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>
        *        of another substring.
        *
        * @param other_
        *        reference to an instance of another substring.
        *
        * @post
        *        This constructor converts a "relaxed" substring
        *        with user-specified space policy
        *        to a "strict" substring, which is using the
        *        space policy obtained via
        *        call to @c const_edge::default_policy().
        *
        */
        template< typename Other_policyT >
        const_edge( const_edge< Other_policyT, StringT > const& other_ )
            :
        first( other_.first ),
            second( other_.second ),
            m_space_policy( default_policy() )
        {
        }

        /**Constructs exact copy of the existing substring.*/
        const_edge( const_edge< PolicyT, StringT > const& other_ )
            :
        first( other_.first ),
            second( other_.second ),
            m_space_policy( other_.m_space_policy )
        {
        }

        /**Constructs copy of the existing substring with
        * explicitly specified boundary positions.
        *
        * @param other_
        *        The reference to another substring.
        *
        * @param start_
        *        Initial offset of the upper boundary (edge::first node.)
        *
        * @param finish_
        *        Initial offset of the lower boundary (edge::second node.)
        *
        */
        const_edge(
            const_edge< PolicyT, StringT > const& other_,
            size_type start_,
            size_type finish_
            )
            :
        first( other_.first, start_ ),
            second( other_.second, finish_ ),
            m_space_policy( other_.m_space_policy )
        {
        }

        /**Constructor taking another substring and a user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
        *
        * @tparam Other_policyT
        *        Type of
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>
        *        of another substring.
        *
        * @param other_
        *        reference to instance of another substring.
        *
        * @param policy_
        *        mutable reference to an instance of the user-defined space policy
        *        object.
        *
        * @post
        *        References to the string and the policy objects are retained
        *        for the lifetime of the substring.
        *        The program should never let those two objects
        *        go out of scope for as long as the corresponding substrings
        *        are in use.
        *
        */
        template< typename Other_policyT >
        const_edge( const_edge< Other_policyT, StringT > const& other_, PolicyT& policy_ )
            :
        first( other_.first ),
            second( other_.second ),
            m_space_policy( policy_ )
        {
        }

        /**Constructor taking a string and a user-defined <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a>.
        *
        * @param inp_
        *        Mutable reference to string
        *
        * @param policy_
        *        mutable reference to an instance of the user-defined space policy
        *        object.
        *
        * @post
        *        References to the string and the policy objects are retained
        *        for the lifetime of the substring.
        *        The program should never let those two objects
        *        go out of scope for as long as the corresponding substrings
        *        are in use.
        *
        */
        const_edge( StringT& inp_, PolicyT& policy_ )
            :
            first( inp_, 0 ),
            second( inp_, inp_.length() ),
            m_space_policy( policy_ )
        {
            first.link( second );
        }

        /**Substring assignment.
        *
        * @param other_
        *        instance of another substring.
        *
        * Note: substring assignment mathces behavior of the copy constructor. 
        *
        */
        const_edge< PolicyT, StringT >& operator= ( const_edge< PolicyT, StringT > const& other_ )
        {
            if ( this != &other_ ) {
                first = other_.first;
                second = other_.second;
            }
            return *this;
        }


        /**Conversion to @c StringT.
        *
        * @pre
        *       A valid boundary range is expected:
        * @par
        *       <tt>0 <= first.offset() <= second.offset() <= inp.length()</tt>
        * @par
        *       @n where @c inp.length() is the length of
        *       the referenced string.
        *
        */
        operator StringT() const
        {
            return text();
        }

        /**Returns mutable reference to the referenced string.*/
        StringT& parent()
        {
            return first.parent();
        }

        /**Returns constant reference to the referenced string.*/
        StringT const& parent() const
        {
            return first.parent();
        }

    public:
        /**Returns content of the substring.*/
        StringT text() const
        {
            assert( &first.parent() == &second.parent() );
            assert( first.offset() <= second.offset() );
            assert( second.offset() <= second.parent().length() );

            if ( first.offset() == second.offset() ) {
                return StringT();
            }

            return second.parent().substr(
                first.offset(),
                length()
                );
        }

        /**Calculates and returns length of the referenced substring.
        *
        * @return
        *       the function returns @c StringT::npos, 
        *       if the following condition is false:
        * @par
        *       <tt>first.offset() <= second.offset()</tt>
        * @par
        *       where @c first and @c second are the substring boundaries
        *
        */
        size_type length() const
        {
            if ( first.offset() > second.offset() )
                return StringT::npos;

            return second.offset() - first.offset();
        }

        /**Inserts a region described by the current substring boundaries into
        *  the region-aware <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a> object
        *  attached to this substring.
        *
        */
        void region_insert()
        {
            space_policy().region_insert(
                first.offset(),
                second.offset()
                );
        }

        /**Erases region(s) described by the current substring boundaries from
        *  the region-aware <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a> object
        *  attached to this substring.
        *
        */
        void region_erase()
        {
            space_policy().region_erase(
                first.offset(),
                second.offset()
                );
        }

        /**Extracts and returns the content corresponding to the substring boundaries,
        *  excluding the intersecting client regions of the
        *  the region-aware <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1410_policy.html">space policy</a> object
        *  attached to this substring.
        *
        */
        StringT region_difference()
        {
            return space_policy().region_difference(
                parent(),
                first.offset(),
                second.offset()
                );
        }

        /**Converts substring to lowercase.*/
        void text_tolower()
        {
            typename StringT::iterator it_first = parent().begin() + first.offset();
            typename StringT::iterator it_last = parent().begin() + second.offset();

            std::transform(
                it_first,
                it_last,
                it_first,
                tolower
                );
        }

        /**Converts substring to uppercase.*/
        void text_toupper()
        {
            typename StringT::iterator it_first = parent().begin() + first.offset();
            typename StringT::iterator it_last = parent().begin() + second.offset();

            std::transform(
                it_first,
                it_last,
                it_first,
                toupper
                );
        }

        /**Grammar rule <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">adaptor</a>
        * of the edge object.
        *
        * @tparam ExprT
        *        Type of the
        *        <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1100_grammar.html">grammar expression</a>,
        *        determined by the C++ compiler at compile time.
        *
        * @param expr_
        *        CTTL grammar expression
        *
        */
        template< typename ExprT >
        xtl_wrap<
            xtl_edge<
            const_edge< PolicyT, StringT >,
            xtl_wrap< ExprT >
            >
        >
        operator() ( xtl_wrap< ExprT > const& expr_ )
        {
            typedef
                xtl_edge<
                const_edge< PolicyT, StringT >,
                xtl_wrap< ExprT >
                > xtl_edge_T;

            return xtl_wrap< xtl_edge_T >( xtl_edge_T( *this, expr_ ) );
        }

    };  // class const_edge


    ///////////////////////////////////////////////////////
    // Overloaded operators for constant substrings
    ///////////////////////////////////////////////////////


    /**Stream insertion operator performs substring output operation on @c std::ostream.*/
    template< typename PolicyT, typename StringT >
    inline 
    std::ostream& operator<<( std::ostream& os_, const_edge< PolicyT, StringT > const&  edge_ )
    {
        os_ << edge_.text();
        return os_;
    }

    /**Compares two substrings.
    *
    * @param one_
    *        left substring.
    *
    * @param another_
    *        right substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator< ( const_edge< PolicyT, StringT > const& one_, const_edge< PolicyT, StringT > const& another_ )
    {
        return one_.parent().compare(
            one_.first.offset(),
            one_.length(),
            another_.parent(),
            another_.first.offset(),
            another_.length()
            ) < 0;
    }

    /**Compares two substrings.
    *
    * @param one_
    *        left substring.
    *
    * @param another_
    *        right substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator> ( const_edge< PolicyT, StringT > const& one_, const_edge< PolicyT, StringT > const& another_ )
    {
        return one_.parent().compare(
            one_.first.offset(),
            one_.length(),
            another_.parent(),
            another_.first.offset(),
            another_.length()
            ) > 0;
    }

    /**Compares two substrings.
    *
    * @param one_
    *        left substring.
    *
    * @param another_
    *        right substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator>= ( const_edge< PolicyT, StringT > const& one_, const_edge< PolicyT, StringT > const& another_ )
    {
        return one_.parent().compare(
            one_.first.offset(),
            one_.length(),
            another_.parent(),
            another_.first.offset(),
            another_.length()
            ) >= 0;
    }

    /**Compares two substrings.
    *
    * @param one_
    *        left substring.
    *
    * @param another_
    *        right substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator<= ( const_edge< PolicyT, StringT > const& one_, const_edge< PolicyT, StringT > const& another_ )
    {
        return one_.parent().compare(
            one_.first.offset(),
            one_.length(),
            another_.parent(),
            another_.first.offset(),
            another_.length()
            ) <= 0;
    }

    /**Compares two substrings.
    *
    * @param one_
    *        left substring.
    *
    * @param another_
    *        right substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator== ( const_edge< PolicyT, StringT > const& one_, const_edge< PolicyT, StringT > const& another_ )
    {
        return one_.parent().compare(
            one_.first.offset(),
            one_.length(),
            another_.parent(),
            another_.first.offset(),
            another_.length()
            ) == 0;
    }

    /**Compares two substrings.
    *
    * @param one_
    *        left substring.
    *
    * @param another_
    *        right substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator!= ( const_edge< PolicyT, StringT > const& one_, const_edge< PolicyT, StringT > const& another_ )
    {
        return one_.parent().compare(
            one_.first.offset(),
            one_.length(),
            another_.parent(),
            another_.first.offset(),
            another_.length()
            ) != 0;
    }


    ///////////////////////////////////////////////////////
    // Overloaded operators for substring and a string
    ///////////////////////////////////////////////////////

    /**Compares substring to a string.
    *
    * @param substr_
    *        substring.
    *
    * @param str_
    *        string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator< ( const_edge< PolicyT, StringT > const& substr_, StringT const& str_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            str_
            ) < 0;
    }

    /**Compares substring to a string.
    *
    * @param substr_
    *        substring.
    *
    * @param str_
    *        string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator> ( const_edge< PolicyT, StringT > const& substr_, StringT const& str_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            str_
            ) > 0;
    }

    /**Compares substring to a string.
    *
    * @param substr_
    *        substring.
    *
    * @param str_
    *        string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator>= ( const_edge< PolicyT, StringT > const& substr_, StringT const& str_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            str_
            ) >= 0;
    }

    /**Compares substring to a string.
    *
    * @param substr_
    *        substring.
    *
    * @param str_
    *        string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator<= ( const_edge< PolicyT, StringT > const& substr_, StringT const& str_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            str_
            ) <= 0;
    }

    /**Compares substring to a string.
    *
    * @param substr_
    *        substring.
    *
    * @param str_
    *        string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator== ( const_edge< PolicyT, StringT > const& substr_, StringT const& str_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            str_
            ) == 0;
    }

    /**Compares substring to a string.
    *
    * @param substr_
    *        substring.
    *
    * @param str_
    *        string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator!= ( const_edge< PolicyT, StringT > const& substr_, StringT const& str_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            str_
            ) != 0;
    }


    ///////////////////////////////////////////////////////
    // Overloaded operators for string and a substring
    ///////////////////////////////////////////////////////

    /**Compares string to a substring.
    *
    * @param str_
    *        string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator< ( StringT const& str_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return str_.compare(
            0,
            str_.length(),
            substr_.parent(),
            substr_.first.offset(),
            substr_.length()
            ) < 0;
    }

    /**Compares string to a substring.
    *
    * @param str_
    *        string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator> ( StringT const& str_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return str_.compare(
            0,
            str_.length(),
            substr_.parent(),
            substr_.first.offset(),
            substr_.length()
            ) > 0;
    }

    /**Compares string to a substring.
    *
    * @param str_
    *        string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator>= ( StringT const& str_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return str_.compare(
            0,
            str_.length(),
            substr_.parent(),
            substr_.first.offset(),
            substr_.length()
            ) >= 0;
    }

    /**Compares string to a substring.
    *
    * @param str_
    *        string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator<= ( StringT const& str_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return str_.compare(
            0,
            str_.length(),
            substr_.parent(),
            substr_.first.offset(),
            substr_.length()
            ) <= 0;
    }

    /**Compares string to a substring.
    *
    * @param str_
    *        string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator== ( StringT const& str_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return str_.compare(
            0,
            str_.length(),
            substr_.parent(),
            substr_.first.offset(),
            substr_.length()
            ) == 0;
    }

    /**Compares string to a substring.
    *
    * @param str_
    *        string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator!= ( StringT const& str_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return str_.compare(
            0,
            str_.length(),
            substr_.parent(),
            substr_.first.offset(),
            substr_.length()
            ) != 0;
    }


    ///////////////////////////////////////////////////////
    // Overloaded operators for C string and a substring
    ///////////////////////////////////////////////////////

    /**Compares C string to a substring.
    *
    * @param cstr_
    *        C string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator< ( typename StringT::value_type const* cstr_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return -substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) < 0;
    }

    /**Compares C string to a substring.
    *
    * @param cstr_
    *        C string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator> ( typename StringT::value_type const* cstr_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return -substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) > 0;
    }

    /**Compares C string to a substring.
    *
    * @param cstr_
    *        C string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator>= ( typename StringT::value_type const* cstr_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return -substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) >= 0;
    }

    /**Compares C string to a substring.
    *
    * @param cstr_
    *        C string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator<= ( typename StringT::value_type const* cstr_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return -substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) <= 0;
    }

    /**Compares C string to a substring.
    *
    * @param cstr_
    *        C string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator== ( typename StringT::value_type const* cstr_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) == 0;
    }

    /**Compares C string to a substring.
    *
    * @param cstr_
    *        C string.
    *
    * @param substr_
    *        substring.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator!= ( typename StringT::value_type const* cstr_, const_edge< PolicyT, StringT > const& substr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) != 0;
    }


    ///////////////////////////////////////////////////////
    // Overloaded operators for substring and a C string
    ///////////////////////////////////////////////////////

    /**Compares substring to a C string.
    *
    * @param substr_
    *        substring.
    *
    * @param cstr_
    *        C string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator< ( const_edge< PolicyT, StringT > const& substr_, typename StringT::value_type const* cstr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) < 0;
    }

    /**Compares substring to a C string.
    *
    * @param substr_
    *        substring.
    *
    * @param cstr_
    *        C string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator> ( const_edge< PolicyT, StringT > const& substr_, typename StringT::value_type const* cstr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) > 0;
    }

    /**Compares substring to a C string.
    *
    * @param substr_
    *        substring.
    *
    * @param cstr_
    *        C string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator>= ( const_edge< PolicyT, StringT > const& substr_, typename StringT::value_type const* cstr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) >= 0;
    }

    /**Compares substring to a C string.
    *
    * @param substr_
    *        substring.
    *
    * @param cstr_
    *        C string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator<= ( const_edge< PolicyT, StringT > const& substr_, typename StringT::value_type const* cstr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) <= 0;
    }

    /**Compares substring to a C string.
    *
    * @param substr_
    *        substring.
    *
    * @param cstr_
    *        C string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator== ( const_edge< PolicyT, StringT > const& substr_, typename StringT::value_type const* cstr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) == 0;
    }

    /**Compares substring to a C string.
    *
    * @param substr_
    *        substring.
    *
    * @param cstr_
    *        C string.
    *
    */
    template< typename PolicyT, typename StringT >
    bool operator!= ( const_edge< PolicyT, StringT > const& substr_, typename StringT::value_type const* cstr_ )
    {
        return substr_.parent().compare(
            substr_.first.offset(),
            substr_.length(),
            cstr_
            ) != 0;
    }

}   // namespace cttl

#endif // _CTTL_CONST_EDGE_H_INCLUDED_
