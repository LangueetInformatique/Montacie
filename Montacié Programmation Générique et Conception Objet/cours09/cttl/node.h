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

/**@file node.h
* @brief Defines cttl::node class.
*
* @see
*  - cttl::const_edge
*/

// node.h

#ifndef _CTTL_NODE_H_INCLUDED_
#define _CTTL_NODE_H_INCLUDED_

#include "xtl_base.h"
#include "xtl_identity_functors.h"
#include "xtl_circularly_linked_list.h"

/**@namespace cttl
 * @brief Namespace @c cttl defines publicly visible classes and
 * functions of CTTL library.
 *
 */
namespace cttl {

    using namespace cttl_impl;

    /**@class node
    * @brief Implements placeholder of the logical position inside
    * parseable <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substring</a>.
    *
    * @tparam StringT
    *        specifies type of the referenced
    *        string. The default is
    *        <tt><a href="http://www.cplusplus.com/reference/string/">std::string</a></tt>
    *
    */

    template< typename StringT = CTTL_STD_STRING >
    class node : public xtl_circular_node< node< StringT > >
    {
    public:
        ////////////////////////////////////////////////////////////////////////////
        // CONSTRUCTORS, CONVERSIONS, AND ASSIGNMENT OPERATORS OF THE NODE OBJECT //
        ////////////////////////////////////////////////////////////////////////////

        /**Defines type of referenced string.*/
        typedef StringT string_T;

        /**Defines type of referenced character.*/
        typedef typename StringT::value_type char_T;

        /**Defines node value type.*/
        typedef typename StringT::value_type value_type;

        /**Defines node size type.*/
        typedef typename StringT::size_type size_type;

    protected:
        /**Stores node position.*/
        size_type m_offset;

        /**Stores pointer to the string.*/
        StringT* m_pstr;

    public:
        /**Constructor taking reference to a string.
        *
        * @post
        *     The node is positioned at the end of the string.
        *
        */
        node( StringT& inp_ )
            :
        m_offset( inp_.length() ),
            m_pstr( &inp_ )
        {
        }

        /**Constructor taking reference to a string and
        * initial node position.
        *
        * @param inp_
        *        Mutable reference to a @c string.
        *
        * @param offset_
        *        Initial offset of the node.
        *
        */
        node( StringT& inp_, size_type offset_ )
            :
        m_offset( offset_ ),
            m_pstr( &inp_ )
        {
        }

        /**Copy constructor manufactures exact copy of the node.
        *
        * @post
        *   The @c other_ node is inserted in front of @c this node, forming a circularly-linked list.
        *
        */
        node( node< StringT > const& other_ )
            :
        xtl_circular_node< node< StringT > >( other_ ),
            m_offset( other_.m_offset ),
            m_pstr( other_.m_pstr )
        {
        }

        /**Copy constructor with custom offset.
        *
        * @post
        *   The @c other_ node is inserted in front of @c this node, forming a circularly-linked list.
        *
        */
        node( node< StringT > const& other_, size_type offset_ )
            :
        xtl_circular_node< node< StringT > >( other_ ),
            m_offset( offset_ ),
            m_pstr( other_.m_pstr )
        {
        }

        /**Inserts other node in front of the current, forming a circularly-linked list.
        *
        * @pre
        *      - (a) The @c other_ node is expected to have the same parent string, and
        *      - (b) The @c other_ node should be single.
        *
        * @warning
        *      If the above pre-conditions are not met, the assert will fail on
        *      either condition in the debug build.
        *
        */
        node< StringT >& link( node< StringT >& other_ )
        {
            assert( m_pstr == other_.m_pstr );
            this->list_insert( other_ );
            return other_;
        }

        /**Assignment operator.
        *
        * @remarks
        *  Node assignment doesn't match the behavior
        *  of the node copy constructor. The assignment provides
        *  no automatic linkage of nodes.
        * @par
        *  Instead, the node position is assigned.
        * @par
        *  To manage list linkage, use @c node::link() member function.
        *
        */
        node< StringT >& operator= ( node< StringT > const& other_ )
        {
            if ( this == &other_ ) {
                return *this;
            }

            m_offset = other_.m_offset;
            return *this;
        }

        /**Assignment of types convertible to @c size_type updates node position.
        *
        */
        node< StringT >& operator= ( size_type offset_ )
        {
            m_offset = offset_;
            return *this;
        }

        /**Addition-assignment of string matches behavior of cttl::node::insert_go().
        *
        */
        node< StringT >& operator+= ( StringT const& str_ )
        {
            insert_go( str_ );
            return *this;
        }

        /**Subtraction-assignment of string matches behavior of cttl::node::insert_stay().
        *
        */
        node< StringT >& operator-= ( StringT const& str_ )
        {
            insert_stay( str_ );
            return *this;
        }

        ///////////////////////////////////
        // PROPERTIES OF THE NODE OBJECT //
        ///////////////////////////////////

        /**Returns mutable reference to the referenced @c string.*/
        StringT& parent()
        {
            return *m_pstr;
        }

        /**Returns constant reference to the referenced @c string.*/
        StringT const& parent() const
        {
            return *m_pstr;
        }

        /**Identifies node position relative to another node.
        * 
        * @param root_
        *     Reference to the relative node to measure the distance.
        *
        * @return 
        *     The function returns distance between the two nodes.
        *
        * @par
        *     The unit of measurement is the number of hops
        *     required to reach the other node.
        *
        * @par
        *     In addition, the function may return the following
        *     values:
        *     - Minus one: indicates that two nodes are not on the same list.
        *     Its meaning is that the distance cannot be measured.
        *     @n @n 
        *     - Zero: indicates that the node is single; no other
        *     nodes are present on the list.
        *
        */
        int identity( node< StringT > const& root_ ) const
        {
            return this->list_distance( root_ );
        }

        ///////////////////////////////////
        // NODE OPERATIONS
        ///////////////////////////////////

        /**Moves node position forward to the lower boundary of the specified character class.
        *
        * @return
        *      true if node offset was adjusted; false otherwise.
        *
        */
        template< typename PredicateT >
        bool find_class( PredicateT ( *iswhat_ )( PredicateT ) )
        {
            StringT const& str = parent();
            if ( iswhat_( str[ offset() ] ) ) {
                // successful match found for the specified character class,
                // find ending position
                typename StringT::const_iterator it = str.begin() + offset();
                it = std::find_if( it, str.end(), std::not1( std::ptr_fun( iswhat_ ) ) );
                if ( it != str.end() )
                    offset( std::distance( str.begin(), it ) ); // set ending position
                else
                    offset( str.length() ); // set ending position

                return true;
            }
            return false;
        }

        /**Moves node position backward to the upper boundary of the specified character class.
        *
        * @return
        *      true if node offset was adjusted; false otherwise.
        *
        */
        template< typename PredicateT >
        bool rfind_class( PredicateT ( *iswhat_ )( PredicateT ) )
        {
            StringT const& str = parent();
            if ( offset() && iswhat_( str[ offset() - 1 ] ) ) {
                // successful match found for the specified character class,
                // find beginning position for the character class:
                typename StringT::const_reverse_iterator it( str.begin() + offset() );
                typename StringT::const_reverse_iterator it_end( str.begin() );
                it = std::find_if( it, it_end, std::not1( std::ptr_fun( iswhat_ ) ) );
                offset( std::distance( it, it_end ) );  // set beginning position

                return true;
            }
            return false;
        }

        /**Returns node position.*/
        size_type offset() const
        {
            return m_offset;
        }

        /**Changes node position.
        *
        * @return
        *      old position of the node.
        *
        */
        size_type offset( size_type offset_ )
        {
            size_type tmp = m_offset;
            m_offset = offset_;
            return tmp;
        }

        /**Returns line number corresponding to the current position of the node.*/
        size_type line() const
        {
            if ( !m_pstr->length() )   // string is empty
                return 1;
            return 1 + std::count( m_pstr->begin(), m_pstr->begin() + m_offset, char_T( '\n' ) );
        }

        /**Moves node position to the beginning of the specified line.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_line( size_type line_ )
        {
            m_offset = 0;
            while ( --line_ ) {
                m_offset = m_pstr->find( char_T( '\n' ), m_offset );   // find lf
                if ( m_offset == StringT::npos )
                    return m_offset = m_pstr->length();
                ++m_offset;   // position next to lf
            }
            return m_offset;
        }

        //////////////////////////////
        // VERBS OF THE NODE OBJECT //
        //////////////////////////////

        /**Moves node position to the beginning of the referenced string.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_bof()
        {
            return m_offset = 0;
        }

        /**Moves node position to the ending of the referenced string.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_eof()
        {
            return m_offset = m_pstr->length();
        }

        /**Moves node position to the beginning of the next line.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_line_next()
        {
            m_offset = m_pstr->find( char_T( '\n' ), m_offset ); // find next lf
            if ( m_offset == StringT::npos )
                return m_offset = m_pstr->length();

            return ++m_offset;   // position next to lf
        }

        /**Moves node position to the beginning of the previous line.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_line_previous()
        {
            size_type current_line = line();
            if ( --current_line )
                return go_line( current_line );
            return offset();
        }

        /**Moves node position to the beginning of the current line.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_line_home()
        {
            if ( (*m_pstr)[ m_offset ] == char_T( '\n' ) )
                return m_offset; // stay where you are

            m_offset = m_pstr->rfind( char_T( '\n' ), m_offset );    // find previous lf
            if ( m_offset == StringT::npos )
                return m_offset = 0;

            return ++m_offset;   // position next to lf
        }

        /**Moves node position to the beginning of the specified line.
        *
        * @param line_
        *        target line number.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_line_home( size_type line_ )
        {
            go_line( line_ );
            return go_line_home();
        }

        /**Moves node position to the ending of the current line.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_line_end()
        {
            static const char_T end_of_line[] = { char_T( '\r' ), char_T( '\n' ), 0x00 };
            m_offset = m_pstr->find_first_of( end_of_line, m_offset );
            if ( m_offset == StringT::npos )
                return m_offset = m_pstr->length();

            return m_offset;
        }

        /**Moves node position to the ending of the specified line.
        *
        * @param line_
        *        target line number.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type go_line_end( size_type line_ )
        {
            go_line( line_ );
            return go_line_end();
        }

        /**Inserts text at the current position of the node.
        *
        * @param str_
        *       reference to the source string.
        *
        * @post
        *       node position is adjusted to the end of the inserted text.
        *       Logical positions of all nodes at the same position and at higher
        *       offsets are also adjusted.
        *
        * @return
        *       new position of the node.
        *
        */
        size_type insert_go( StringT const& str_ )
        {
            text_insert_go( str_ );
            return offset();
        }

        /**Inserts text at the current position of the node.
        *
        * @param str_
        *       reference to the source string.
        *
        * @post
        *       Logical positions of any node at the same position
        *       remain unchanged. Positions of all nodes at higher
        *       offset positions are adjusted.
        *
        */
        void insert_stay( StringT const& str_ )
        {
            text_insert_stay( str_ );
        }

        /**Inserts absolute substring at the position specified by the current node.*/
        void insert_go(
            StringT const& str_,
            size_type source_from_offset_, // a substring of the source string
            size_type source_to_offset_
            )
        {
            size_type str_length = source_to_offset_ - source_from_offset_;

            if ( !str_.length() )
                return; // nothing to do

            size_type insertion_offset = offset();

            m_pstr->insert(
                insertion_offset,
                str_,
                source_from_offset_,
                str_length
                );

            xtl_identity_insert_go< StringT > insert_go(
                insertion_offset,
                int( str_length )
                );

            adjust( insert_go );
        }

        /**Inserts absolute substring at the position specified by the current node.*/
        void insert_stay(
            StringT const& str_,
            size_type source_from_offset_, // a substring of the source string
            size_type source_to_offset_
            )
        {
            size_type str_length = source_to_offset_ - source_from_offset_;

            if ( !str_length )
                return; // nothing to do

            size_type insertion_offset = offset();

            m_pstr->insert(
                insertion_offset,
                str_,
                source_from_offset_,
                str_length
                );

            xtl_identity_insert_stay< StringT > insert_stay(
                insertion_offset,
                str_length
                );

            adjust( insert_stay );
        }

        /**Returns character from referenced string at the
        *  offset relative to the current position of the node.
        *
        * @param subscript_
        *       relative offset adjustment value.
        *
        */
        char_T const& operator[] ( int subscript_ ) const
        {
            return (*m_pstr)[ offset() + subscript_ ];
        }

        /**Returns mutable reference to the character of referenced string at the
        *  offset relative to the current position of the node.
        *
        * @param subscript_
        *       relative offset adjustment value.
        *
        */
        char_T& operator[] ( int subscript_ )
        {
            return (*m_pstr)[ offset() + subscript_ ];
        }

        /**Grammar rule <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page6810_adapt.html">adaptor</a>
        * of the node object.
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
        cttl_impl::xtl_wrap<
            xtl_node<
            node< StringT >,
            xtl_wrap< ExprT >
            >
        >
        operator() ( xtl_wrap< ExprT > const& expr_ )
        {
            // function-call operator must be a nonstatic member function
            typedef
                xtl_node<
                node< StringT >,
                xtl_wrap< ExprT >
                > xtl_node_T;

            return xtl_wrap< xtl_node_T >( xtl_node_T( *this, expr_ ) );
        }

        /////////////////////////////
        // Inter-node communication
        /////////////////////////////

        /**Generic function accepting an adjuster object that updates
        * positions of all nodes found in a circularly-linked list.
        *
        */
        template< typename AdjusterT >
        void adjust( AdjusterT const& adjuster_ )
        {
            node< StringT >* iter = this;
            do {
                adjuster_.adjust( iter->m_offset );
                iter = static_cast< node< StringT >* >( iter->m_pnext );

            } while ( iter != this );
        }

    private:
        /**Inserts substring at the position specified by the current node position.*/
        void text_insert_go( StringT const& str_ )
        {
            size_type str_length = str_.length();

            if ( !str_.length() )
                return; // nothing to do

            size_type insertion_offset = offset();

            m_pstr->insert(
                insertion_offset,
                str_
                );

            xtl_identity_insert_go< StringT > insert_go(
                insertion_offset,
                int( str_length )
                );

            adjust( insert_go );
        }

        /**Inserts substring at the position specified by the current node position.*/
        void text_insert_stay( StringT const& str_ )
        {
            size_type str_length = str_.length();

            if ( !str_length )
                return; // nothing to do

            size_type insertion_offset = offset();

            m_pstr->insert(
                insertion_offset,
                str_
                );

            xtl_identity_insert_stay< StringT > insert_stay(
                insertion_offset,
                int( str_length )
                );

            adjust( insert_stay );
        }

    };  // class node


    /////////////////////////////////////////////////
    // Overloaded operators to compare nodes
    /////////////////////////////////////////////////

    /**Compares two nodes. Nodes are equal if their offsets are the same.*/
    template< typename StringT >
    bool operator== ( node< StringT > const& one_, node< StringT > const& another_ )
    {
        return one_.offset() == another_.offset();
    }

    /**Compares two nodes. Nodes are equal if their offsets are the same.*/
    template< typename StringT >
    bool operator!= ( node< StringT > const& one_, node< StringT > const& another_ )
    {
        return one_.offset() != another_.offset();
    }

    /**Compares offsets of two nodes.*/
    template< typename StringT >
    bool operator> ( node< StringT > const& one_, node< StringT > const& another_ )
    {
        return one_.offset() > another_.offset();
    }

    /**Compares offsets of two nodes.*/
    template< typename StringT >
    bool operator< ( node< StringT > const& one_, node< StringT > const& another_ )
    {
        return one_.offset() < another_.offset();
    }

    /**Compares offsets of two nodes.*/
    template< typename StringT >
    bool operator>= ( node< StringT > const& one_, node< StringT > const& another_ )
    {
        return one_.offset() >= another_.offset();
    }

    /**Compares offsets of two nodes.*/
    template< typename StringT >
    bool operator<= ( node< StringT > const& one_, node< StringT > const& another_ )
    {
        return one_.offset() <= another_.offset();
    }

    /**Prefix increment operator increments node offset.*/
    template< typename StringT >
    node< StringT >& operator++ ( node< StringT >& node_ )
    {
        node_.offset( node_.offset() + 1 );
        return node_;
    }

    /**Prefix decrement operator decrements node offset.*/
    template< typename StringT >
    node< StringT >& operator-- ( node< StringT >& node_ )
    {
        node_.offset( node_.offset() - 1 );
        return node_;
    }

}   // namespace cttl

#endif // _CTTL_NODE_H_INCLUDED_
