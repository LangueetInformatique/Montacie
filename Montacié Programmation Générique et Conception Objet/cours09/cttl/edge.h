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

/**@file edge.h
* @brief Defines @c cttl::edge, mutable substring class.
*
*  @see
*  - cttl::const_edge
*  - cttl::node
*
*/

// edge.h

#ifndef _CTTL_EDGE_H_INCLUDED_
#define _CTTL_EDGE_H_INCLUDED_

#include "const_edge.h"

namespace cttl {

    /**@class edge
    * @brief Implements mutable parseable
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
    class edge : public const_edge< PolicyT, StringT > {

        //////////////////////////////////////////////////////
        // Note: typedefs conversion operators are inherited
        // from the base classes. However, typedefs with
        // "typename" are redefined for the simplicity of
        // the implementation and outside usage.
        //////////////////////////////////////////////////////

    public:
        /**Defines offset guard type for substring boundary.*/
        typedef xtl_mutable_offset_guard< StringT > offset_guard_T;

        /**Defines type of referenced character.*/
        typedef typename StringT::value_type char_T;

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
        typedef edge< strict_policy_T, StringT > strict_edge_T;

        /**Defines type of substring boundaries,
        * represented by instances of two @c cttl::node objects.
        *
        */
        typedef typename const_edge< PolicyT, StringT >::node_T node_T;


        //////////////////////////////////////////////////////
        // Substring constructors
        //////////////////////////////////////////////////////

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
        explicit edge( StringT& inp_ )
            :
        const_edge< PolicyT, StringT >( inp_ )
        {
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
        edge( StringT& inp_, size_type start_, size_type finish_ )
            :
        const_edge< PolicyT, StringT >( inp_, start_, finish_ )
        {
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
        edge( node< StringT >& node_first_, node< StringT >& node_second_ )
            :
        const_edge< PolicyT, StringT >( node_first_, node_second_ )
        {
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
        edge(
            node< StringT >& node_first_,
            node< StringT >& node_second_,
            size_type start_,
            size_type finish_
            )
            :
        const_edge< PolicyT, StringT >( node_first_, node_second_, start_, finish_ )
        {
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
        edge( const_edge< Other_policyT, StringT > const& other_ )
            :
        const_edge< PolicyT, StringT >( other_ )
        {
        }

        /**Constructs exact copy of the existing substring.*/
        edge( const_edge< PolicyT, StringT > const& other_ )
            :
        const_edge< PolicyT, StringT >( other_ )
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
        edge(
            const_edge< PolicyT, StringT > const& other_,
            size_type start_,
            size_type finish_
            )
            :
        const_edge< PolicyT, StringT >( other_, start_, finish_ )
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
        edge( const_edge< Other_policyT, StringT > const& other_, PolicyT& policy_ )
            :
        const_edge< PolicyT, StringT >( other_, policy_ )
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
        edge( StringT& inp_, PolicyT& policy_ )
            :
        const_edge< PolicyT, StringT >( inp_, policy_ )
        {
        }

        /**Replaces content of the substring.*/
        void text( StringT const& str_ )
        {
            text_replace( str_ );
        }

        /**Replaces content of the substring with the
        * content of another substring.
        *
        */
        void text( const_edge< PolicyT, StringT > const& other_ )
        {
            text_replace(
                other_.parent(),
                other_.first.offset(),
                other_.second.offset()
                );
        }

        /**Replaces content of the substring with the
        * content of another substring.
        *
        */
        void text( edge< PolicyT, StringT > const& other_ )
        {
            text_replace(
                other_.parent(),
                other_.first.offset(),
                other_.second.offset()
                );
        }

        /**Returns content of the substring.*/
        StringT text() const
        {
            return const_edge< PolicyT, StringT >::text();
        }

        /**Exchanges text content with another substring.
        *
        * @remarks
        *       Standard version of @c std::swap() exchanges
        *       positions of the substring boundaries.
        *
        */
        void text_swap( edge< PolicyT, StringT >& other_ )
        {
            const StringT str_this = text();
            text( other_ );
            other_.text( str_this );
        }

        /**Inserts substring at the current position of the node.
        *
        * @param node_
        *       the node specifying the target position.
        *
        * @post
        *       node position is adjusted to the end of the inserted text.
        *       Logical positions of all nodes at the same position and at higher
        *       offsets are also adjusted.
        *
        */
        void insert_go( node_T& node_ )
        {
            node_.insert_go(
                this->parent(),
                this->first.offset(),
                this->second.offset()
                );
        }

        /**Inserts substring at the current position of the node.
        *
        * @param node_
        *       the node specifying the target position.
        *
        * @post
        *       Logical positions of any node at the same position
        *       remain unchanged. Positions of all nodes at higher
        *       offset positions are adjusted.
        *
        */
        void insert_stay( node_T& node_ )
        {
            node_.insert_stay(
                this->parent(),
                this->first.offset(),
                this->second.offset()
                );
        }

        /**Erases content of the substring.
        *
        * @warning
        *        Erase, like other mutating substring operations,
        *        are prohibited inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
        *
        * @post
        *        The function preserves logical positions of the
        *        substring boundaries before and after the operation.
        *        Client regions are adjusted accordingly:
        *        all offsets remain in sync with existing client regions.
        *
        */
        void erase()
        {
            size_t offset_from_i = this->first.offset();
            size_t offset_to_i = this->second.offset();

            // Compute negative length of the erased substring:
            int delta_offset = this->length();
            delta_offset = -delta_offset;

            if ( !delta_offset )
                return; // nothing to do

            assert( offset_from_i <= offset_to_i );
            assert( offset_from_i <= this->parent().length() );
            assert( ( offset_to_i - offset_from_i ) <= this->parent().length() );

            this->parent().erase(
                offset_from_i,
                offset_to_i - offset_from_i
                );

            this->space_policy().region_erase(
                offset_from_i,
                offset_to_i
                );

            this->space_policy().region_adjust(
                offset_from_i,
                delta_offset
                );

            // ( delta_offset < 0 )
            xtl_identity_collapse< StringT > collapse(
                offset_to_i,
                delta_offset
                );

            this->first.adjust( collapse );

            this->first.offset( offset_from_i );
        }

        //////////////////////////////////////////////////////
        // Overloaded assignment operators
        //////////////////////////////////////////////////////

        /**Substring assignment.
        *
        * @param other_
        *        instance of another substring.
        *
        * Note: substring assignment mathces behavior of the copy constructor. 
        *
        */
        edge< PolicyT, StringT >& operator=( const_edge< PolicyT, StringT > const& other_ )
        {
            const_edge< PolicyT, StringT >::operator=( other_ );
            return *this;
        }

        /**Assigns new content to the substring.
        *
        * @param str_
        *        reference to the source string.
        *
        */
        edge< PolicyT, StringT >& operator= ( StringT const& str_ )
        {
            text( str_ );
            return *this;
        }

    private:
        /**Replaces content of the substring.
        *
        * @param str_
        *        reference to the source string.
        *
        */
        void text_replace( StringT const& str_ )
        {
            size_t str_length = str_.length();
            size_t offset_from_i = this->first.offset();
            size_t offset_to_i = this->second.offset();

            assert( offset_from_i <= offset_to_i );
            assert( offset_from_i <= this->parent().length() );
            assert( ( offset_to_i - offset_from_i ) <= this->parent().length() );

            this->parent().replace(
                offset_from_i,
                offset_to_i - offset_from_i,
                str_
                );

            int delta_offset = 
                int( offset_from_i - offset_to_i ) // negative length of the old substring
                +
                int( str_length )                  // positive length of the new substring
                ;

            if ( !delta_offset )
                return; // nothing else to do

            this->space_policy().region_erase(
                offset_from_i,
                offset_to_i
                );

            this->space_policy().region_adjust(
                offset_from_i,
                delta_offset
                );

            if ( delta_offset < 0 ) {
                xtl_identity_collapse< StringT > collapse(
                    offset_to_i,
                    delta_offset
                    );

                this->first.adjust( collapse );

            } else {
                xtl_identity_insert_go< StringT > insert_and_go(
                    offset_to_i,
                    delta_offset
                    );

                this->first.adjust( insert_and_go );
            }

            this->first.offset( offset_from_i );
        }

        /**Replaces substring content with the text fragment of the source string.
        *
        * @param str_
        *        reference to the source string.
        *
        * @param source_from_offset_
        *        upper boundary of the source substring.
        *
        * @param source_to_offset_
        *        lower boundary of the source substring.
        *
        * @warning
        *        Replacements, like other mutating substring operations,
        *        are prohibited inside <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1440_region.html">void regions</a>.
        *
        * @post
        *        The function preserves logical positions of the
        *        substring boundaries before and after the replacement.
        *        Client regions are adjusted accordingly:
        *        all offsets remain in sync with existing client regions.
        *
        */
        void text_replace(
            StringT const& str_,
            size_t source_from_offset_,
            size_t source_to_offset_
            )
        {
            size_t str_length = str_.length();
            size_t offset_from_i = this->first.offset();
            size_t offset_to_i = this->second.offset();

            assert( offset_from_i <= offset_to_i );
            assert( offset_from_i <= this->parent().length() );
            assert( ( offset_to_i - offset_from_i ) <= this->parent().length() );

            str_length = source_to_offset_ - source_from_offset_;
            this->parent().replace(
                offset_from_i,
                offset_to_i - offset_from_i,
                str_,
                source_from_offset_,
                str_length
                );

            int delta_offset = 
                offset_from_i - offset_to_i // negative length of the old substring
                +
                str_length                  // positive length of the new substring
                ;

            if ( !delta_offset )
                return; // nothing else left to do

            this->space_policy().region_erase(
                offset_from_i,
                offset_to_i
                );

            this->space_policy().region_adjust(
                offset_from_i,
                delta_offset
                );

            if ( delta_offset < 0 ) {
                xtl_identity_collapse< StringT > collapse(
                    offset_to_i,
                    delta_offset
                    );

                this->first.adjust( collapse );

            } else {
                xtl_identity_insert_go< StringT > insert_and_go(
                    offset_to_i,
                    delta_offset
                    );

                this->first.adjust( insert_and_go );

            }

            this->first.offset( offset_from_i );
        }


    };  // class edge


    ///////////////////////////////////////////////////////
    // Overloaded operators for mutable substrings
    ///////////////////////////////////////////////////////

    /**Input stream extraction operator performs an input operation on @c std::istream.*/
    template< typename PolicyT, typename StringT >
    inline 
        std::istream& operator>>( std::istream& is_, edge< PolicyT, StringT >&  edge_ )
    {
        StringT temp;
        is_ >> temp;
        edge_.text( temp );
        return is_;
    }

}   // namespace cttl


#endif // _CTTL_EDGE_H_INCLUDED_
