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

/**@file interpreter.h
 * @brief Defines classes for CTTL arithmetic interpreter sample.
 *
 */

// interpreter.h

/**@struct interpreter
 * @brief Interpreter class for @ref index.
 *
 */
struct interpreter
{
    std::vector< int > const& m_tree;
    std::vector< double > const& m_vector_doubles;

    interpreter(
        std::vector< int > const& tree_,
        std::vector< double > const& vector_doubles_
        )
        :
        m_tree( tree_ ),
        m_vector_doubles( vector_doubles_ )
    {
    }

private:
    /**Assignment is disabled.*/
    interpreter& operator=( interpreter const& );

public:

    double non_terminal( size_t id )
    {
        // input: id of the node
        // field            content
        //m_tree[ id + 0 ]  opcode
        //m_tree[ id + 1 ]  left operand id
        //m_tree[ id + 2 ]  right operand id (optional)

        assert( id < m_tree.size() );

        switch ( m_tree[ id ] ) {
        case op_add:
            return
                non_terminal( m_tree[ id + left_node ] )
                +
                non_terminal( m_tree[ id + right_node ] )
                ;

        case op_subtract:
            return
                non_terminal( m_tree[ id + left_node ] )
                -
                non_terminal( m_tree[ id + right_node ] )
                ;

        case op_multiply:
            return
                non_terminal( m_tree[ id + left_node ] )
                *
                non_terminal( m_tree[ id + right_node ] )
                ;

        case op_divide:
            return
                non_terminal( m_tree[ id + left_node ] )
                /
                non_terminal( m_tree[ id + right_node ] )
                ;

        case op_negate:
            return
                -non_terminal( m_tree[ id + factor_node ] );

        case op_terminal:
            return
                m_vector_doubles[ m_tree[ id + double_value ] ];

        default:
            std::cout
                << "Error: unknown node type @" << id
                << ", opcode " << m_tree[ id ]
                << std::endl
                ;
            return 0;
        };
    }

};  // struct interpreter
