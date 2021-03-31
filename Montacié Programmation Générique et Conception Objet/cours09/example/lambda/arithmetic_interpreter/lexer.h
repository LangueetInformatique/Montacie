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

/**@mainpage CTTL arithmetic expression parser sample
 * @htmlinclude banner.htm
 *
 * @par
 * The program demonstrates various aspects of
 * CTTL library
 * <a href="http://cttl.sourceforge.net/"><tt>http://cttl.sourceforge.net/</tt></a>,
 * including
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/lambda/page1000_syntax_tree.html">syntax tree</a>
 * generation.
 *
 * <hr>
 * @htmlinclude copyright2009.txt
 */

/**@file lexer.h
 * @brief Defines classes for CTTL arithmetic interpreter sample.
 *
 */

// calc_lexer.h
#ifndef _CALC_LEXER_H_INCLUDED_
#define _CALC_LEXER_H_INCLUDED_

namespace {
    // non-terminal node constants
    static const int op_code = 0;
    static const int left_node = 1;
    static const int right_node = 2;
    static const int non_terminal_size = 3;

    // terminal node constants
    static const int double_value = 1;
    static const int terminal_size = 2;

    // factor non-terminal node constants
    static const int factor_node = 1;
    static const int factor_node_size = 2;

    // arithmetic interpreter constants
    static const int op_add = '+';
    static const int op_subtract = '-';
    static const int op_multiply = '*';
    static const int op_divide = '/';
    static const int op_negate = 'N';
    static const int op_terminal = 'T';
} // namespace


/**@struct calc_lexer
 * @brief Lexer class for @ref index.
 *
 * @tparam ParserT
 *        specifies type of parser to be used with the lexer.
 *
 * The calc_lexer class implements input grammar rules.
 *
 */
template< typename SubstrT >
struct calc_lexer
{
    typedef typename SubstrT::string_T string_T;
    typedef typename SubstrT::policy_T policy_T;
    typedef calc_lexer< SubstrT > lexer_T;

    std::vector< int >& vect_parse_tree;
    const_edge<>& edge_value;
    std::vector< double >& vect_doubles;

    lambda< std::back_insert_iterator< std::vector< int > > >::scalar m_tree_inserter;
    lambda<>::stack m_stack_nodes;
    lambda<>::scalar m_temp;

public:
    /**Constructs and initializes lexer object.*/
    calc_lexer(
        std::vector< int >& vect_parse_tree_,
        const_edge<>& edge_value_,
        std::vector< double >& vect_doubles_
        )
        :
        vect_parse_tree( vect_parse_tree_ ),
        edge_value( edge_value_ ),
        vect_doubles( vect_doubles_ ),
        m_tree_inserter( scalar( std::back_insert_iterator< std::vector< int > >( vect_parse_tree ) ) )
    {
        assert( vect_parse_tree_.size() );
    }

private:
    /**Assignment is disabled.*/
    calc_lexer< SubstrT >& operator=( calc_lexer< SubstrT > const& );

public:

    bool grammar( SubstrT& substr_ )
    {
        size_t result =
            (
                CTTL_RULE( lexer_T::lex_expr )
                +
                // make sure entire input was parsed:
                end()
            ).match( substr_ );

        if ( result == SubstrT::string_T::npos )
            // parser failed
            return false;

        assert( m_stack_nodes.size() == 1 );
        vect_parse_tree[ 0 ] = m_stack_nodes.top();
        return true;

    } // rule

//////////////////////////////////////////////////////////////////////
// arithmetic calculator grammar
//////////////////////////////////////////////////////////////////////
     size_t lex_expr( SubstrT& substr_ )
     {
         return
         (
            CTTL_RULE( lexer_T::lex_term )
            +
            *(
                (
                    symbol( '+' )
                    +
                    CTTL_RULE( lexer_T::lex_term )
                    +
                    *(
                        *m_tree_inserter++ = const_scalar( op_add ),  // code of operation
                        m_temp = *m_stack_nodes--,             // the right side on top of the stack
                        *m_tree_inserter++ = *m_stack_nodes--, // store left operand
                        *m_tree_inserter++ = m_temp,           // store right operand
                        m_stack_nodes = alias::size( scalar( &vect_parse_tree ) ),
                        *m_stack_nodes -= non_terminal_size
                    )
                )
                |
                (
                    symbol( '-' )
                    +
                    CTTL_RULE( lexer_T::lex_term )
                    +
                    *(
                        *m_tree_inserter++ = const_scalar( op_subtract ),  // code of operation
                        m_temp = *m_stack_nodes--,             // the right side on top of the stack
                        *m_tree_inserter++ = *m_stack_nodes--, // store left operand
                        *m_tree_inserter++ = m_temp,           // store right operand
                        m_stack_nodes = alias::size( scalar( &vect_parse_tree ) ),
                        *m_stack_nodes -= non_terminal_size
                    )
                )
            )
        ).match( substr_ );

     } // rule


     size_t lex_term( SubstrT& substr_ )
     {
         return
         (
           CTTL_RULE( lexer_T::lex_factor )
           +
           *(
                (
                    symbol( '*' )
                    +
                    CTTL_RULE( lexer_T::lex_factor )
                    +
                    *(
                        *m_tree_inserter++ = const_scalar( op_multiply ),  // code of operation
                        m_temp = *m_stack_nodes--,             // the right side on top of the stack
                        *m_tree_inserter++ = *m_stack_nodes--, // store left operand
                        *m_tree_inserter++ = m_temp,           // store right operand
                        m_stack_nodes = alias::size( scalar( &vect_parse_tree ) ),
                        *m_stack_nodes -= non_terminal_size
                    )
                )
                |
                (
                    symbol( '/' )
                    +
                    CTTL_RULE( lexer_T::lex_factor )
                    +
                    *(
                        *m_tree_inserter++ = const_scalar( op_divide ),  // code of operation
                        m_temp = *m_stack_nodes--,             // the right side on top of the stack
                        *m_tree_inserter++ = *m_stack_nodes--, // store left operand
                        *m_tree_inserter++ = m_temp,           // store right operand
                        m_stack_nodes = alias::size( scalar( &vect_parse_tree ) ),
                        *m_stack_nodes -= non_terminal_size
                    )
                )
           )
         ).match( substr_ );

     } // rule


     size_t lex_factor( SubstrT& substr_ )
     {
         return
         (
           (
                edge_value(
                    entity( isdigit ) + ( '.' + entity( isdigit ) ) * 1
                )
                +
                *(
                    *m_tree_inserter++ = const_scalar( op_terminal ),  // code of operation
                    *m_tree_inserter++ = ++( scalar( 0 )^vect_doubles^atof^edge_value ),
                    m_stack_nodes = alias::size( scalar( &vect_parse_tree ) ),
                    *m_stack_nodes -= terminal_size
                )
           )
           |
           (
             symbol( '(' )
             +
             CTTL_RULE( lexer_T::lex_expr )
             +
             symbol( ')' )
           )
           |
           (
             symbol( '-' )
             +
             CTTL_RULE( lexer_T::lex_factor )
             +
             *(
                *m_tree_inserter++ = const_scalar( op_negate ),  // code of operation
                *m_tree_inserter++ = *m_stack_nodes--,
                m_stack_nodes = alias::size( scalar( &vect_parse_tree ) ),
                *m_stack_nodes -= factor_node_size
             )
           )
           |
           (
             symbol( '+' )
             +
             CTTL_RULE( lexer_T::lex_factor )
           )
         ).match( substr_ );

     } // rule

};  // struct calc_lexer

#endif //_CALC_LEXER_H_H_INCLUDED_
