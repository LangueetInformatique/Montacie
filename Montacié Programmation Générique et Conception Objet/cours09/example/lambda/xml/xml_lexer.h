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

/**@mainpage CTTL XML stream parser sample
 * @htmlinclude banner.htm
 *
 * @par
 * XML parser source code is located in <tt>example/lambda/xml</tt>
 * subdirectory. The program demonstrates various aspects of
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page1450_stream.html">incremental parsing</a>
 * in CTTL.
 *
 * @par
 * The parser creates and populates an abstract syntax tree (AST),
 * built on top of CTTL
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/lambda/page1010_itree.html">integer tree</a>
 * facility. The tree annotation is made using CTTL
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/lambda/index.html">lambda library</a>,
 * which extends the functionality of the grammar expression
 * by in-line semantic actions.
 *
 * <hr>
 * @htmlinclude copyright2009.txt
 */

/**@file xml_lexer.h
 * @brief Defines lexer class for @ref index.
 *
 */

// xml_lexer.h

#ifndef _XML_LEXER_H_INCLUDED_
#define _XML_LEXER_H_INCLUDED_

using namespace cttl;

/**@struct lexer
 * @brief Lexer class for @ref index.
 *
 * @tparam ParserT
 *        specifies type of parser to be used with this lexer.
 *
 * The lexer implements XML grammar for simple xml input test:
 *
 @code
  1:    grammar = node*;
  2:    node = pi | xmlElement | text;
  3:    xmlElement = openElement node* closeElement | closedElement;
  4:  
  5:    pi = "<?" name (CHARACTER - "?>")* "?>";
  6:  
  7:    openElement = "<" name attr* ">";
  8:    closeElement = "</" name ">";
  9:    closedElement = "<" name attr* "/>";
 10:  
 11:    text = (CHARACTER - '<')+;
 12:  
 13:    attr = name '=' value;
 14:    name = ALPHA (ALPHA | DIGIT | '_' | ':')*;
 15:    value = '"' (CHARACTER - '"')* '"';
 16:  
 17:    - Grammar terminals can be separated by any amount of whitespace.
 18:    - Grammar terminals are "text", "name", "value", and all literals.
 @endcode
 *
 */
template< typename ParserT >
struct lexer {

    /**Defines substring type of xml lexer.*/
    typedef typename ParserT::substr_T substr_T;

    /**Defines strict substring type of xml lexer.*/
    typedef typename substr_T::strict_edge_T strict_input_T;

    /**Parser to be used with this lexer.*/
    ParserT& m_parser;

    /**Reference to substring that can be safely removed from the input at any time.*/
    strict_input_T& consumed_data;

    /**Substring specifying xml name.*/
    strict_input_T edge_xml_name;

    /**Substring specifying attribute value.*/
    strict_input_T attribute_value;
    
    /**Scalar representing xml text node.*/
    lambda< inode_writer< xml_text_descriptor > >::scalar inode_text;

    /**Scalar representing xml element node.*/
    lambda< inode_writer< xml_element_descriptor > >::scalar inode_element;

    /**Scalar representing first xml child node in xml parse tree.*/
    lambda< inode_writer< xml_element_descriptor > >::scalar inode_first;

    /**Scalar representing last xml child node in xml parse tree.*/
    lambda< inode_writer< xml_element_descriptor > >::scalar inode_last;

    /**Scalar representing xml attribute node.*/
    lambda< inode_writer< xml_attribute_descriptor > >::scalar inode_attribute;

    /**Scalar representing parent node in xml parse tree.*/
    lambda< inode_writer< xml_element_descriptor > >::scalar inode_parent;

    /**Stack of element ids in xml parse tree.*/
    lambda< size_t >::stack element_stack;

    /**Temporary storage of xml name id.*/
    lambda< size_t >::scalar id_xml_element;

    /**Temporary storage of id of xml attribute value.*/
    lambda< size_t >::scalar id_attribute_value;


    /**Constructs and initializes the object.*/
    lexer( strict_input_T& consumed_data_, ParserT& parser_ )
        :
        m_parser( parser_ ),
        consumed_data( consumed_data_ ),
        edge_xml_name( consumed_data_ ),
        attribute_value( consumed_data_ ),
        inode_text( inode_writer< xml_text_descriptor >( parser_.vect_xml_tree ) ),
        inode_element( inode_writer< xml_element_descriptor >( parser_.vect_xml_tree ) ),
        inode_first( inode_writer< xml_element_descriptor >( parser_.vect_xml_tree ) ),
        inode_last( inode_writer< xml_element_descriptor >( parser_.vect_xml_tree ) ),
        inode_attribute( inode_writer< xml_attribute_descriptor >( parser_.vect_xml_tree ) ),
        inode_parent( inode_writer< xml_element_descriptor >( parser_.vect_xml_tree ) )
    {
    }

private:
    /**Assignment is disabled.*/
    lexer< ParserT >& operator=( lexer< ParserT > const& );

public:

    /**XML grammar start rule: describes a series of nodes at the top level of xml tree.*/
    size_t xml_grammar( substr_T& substr_ )
    {
        guard_node_stack< typename ParserT::node_T > error_info( m_parser.xml_offset_stack, substr_.first );

        return (
            *CTTL_RULE( lexer< ParserT >::xml_node )
            +
            ( end() | CTTL_MEMBER_RULE( m_parser, &ParserT::error_parser_failed ) )

        ).match( substr_ )
        ;
    }

    /**XML grammar rule: describes types of xml nodes.*/
    size_t xml_node( substr_T& substr_ )
    {
        return (

#ifdef DISPOSE_CONSUMED_DATA
            consumed_data.second( begin( true ) )
            +
#endif // DISPOSE_CONSUMED_DATA

            (
                CTTL_RULE( lexer< ParserT >::xml_pi )
                |
                CTTL_RULE( lexer< ParserT >::xml_element )
                |
                CTTL_RULE( lexer< ParserT >::xml_comment )
                |
                CTTL_RULE( lexer< ParserT >::xml_text )
            )

        ).match( substr_ )
        ;
    }

    /**XML grammar rule: describes name of xml element or attribute.*/
    size_t xml_name( substr_T& substr_ )
    {
        edge< policy_strict_stream > strict_stream_input( substr_, substr_.space_policy() );
        typedef typename lambda< typename ParserT::node_T >::scalar_reference scalar_node_T;
        scalar_node_T scalar_strict_first( &strict_stream_input.first );
        scalar_node_T scalar_strict_second( &strict_stream_input.second );
        scalar_node_T scalar_inp_first( &substr_.first );
        scalar_node_T scalar_inp_second( &substr_.second );

        return (
            *entity( isspace )
            +
            edge_xml_name( +entity( &LITERAL_XML_NAME ) )
            +
            // In this implementation xml elements and
            // attributes share name dictionary:
            *(
                ++( id_xml_element.make_reference() ^ m_parser.xml_name_dictionary ^ edge_xml_name ),
                scalar_inp_first = scalar_strict_first,
                scalar_inp_second = scalar_strict_second
            )
        ).match( strict_stream_input )
        ;
    }

    /**XML grammar rule: describes xml comment construct.*/
    size_t xml_comment( substr_T& substr_ )
    {
        guard_node_stack< typename ParserT::node_T > error_info( m_parser.xml_offset_stack, substr_.first );

        return (
            begin( symbol() + LENGTH_XML_COMMENT_OPEN )
            +
            &LITERAL_XML_COMMENT_OPEN    //"<!--"
            +
            *(
                -(
                    begin( symbol() + LENGTH_XML_COMMENT_CLOSE )
                    +
                    &LITERAL_XML_COMMENT_CLOSE
                )
                +
                symbol()
            )
            +
            begin( symbol() + LENGTH_XML_COMMENT_CLOSE )
            +
            (
                &LITERAL_XML_COMMENT_CLOSE   // "-->"
                |
                CTTL_MEMBER_RULE( m_parser, &ParserT::error_missing_comment_close )
            )

        ).match( substr_ )
        ;
    }

    /**XML grammar rule: describes xml processing instruction.*/
    size_t xml_pi( substr_T& substr_ )
    {
        guard_node_stack< typename ParserT::node_T > error_info( m_parser.xml_offset_stack, substr_.first );

        return (
            begin( symbol() + LENGTH_XML_PI_OPEN )
            +
            &LITERAL_XML_PI_OPEN    // "<?"
            +
            ( CTTL_RULE( lexer< ParserT >::xml_name ) | CTTL_MEMBER_RULE( m_parser, &ParserT::error_bad_pi ) )
            +
            *(
                -(
                    begin( symbol() + LENGTH_XML_PI_CLOSE )
                    +
                    &LITERAL_XML_PI_CLOSE
                )
                +
                symbol()
            )
            +
            begin( symbol() + LENGTH_XML_PI_CLOSE )
            +
            (
                &LITERAL_XML_PI_CLOSE   // "?>"
                |
                CTTL_MEMBER_RULE( m_parser, &ParserT::error_missing_pi_close )
            )

        ).match( substr_ )
        ;
    }

    /**XML grammar rule: describes xml element.*/
    size_t xml_element( substr_T& substr_ )
    {
        guard_node_stack< typename ParserT::node_T > error_info( m_parser.xml_offset_stack, substr_.first );
        return (
            '<'
            +
            CTTL_RULE( lexer< ParserT >::xml_name )
            +
            // The element begins
            (
                // in-line semantic action to create new xml element node:
                inode_element << xml_element_descriptor::ELEMENT_SIZE,
                inode_element[ FLD_ELEMENT_NAME ] = id_xml_element,
                element_stack = alias::offset( inode_element )
                ,
                const_scalar( 1 )
            )
            +
            *CTTL_RULE( lexer< ParserT >::xml_attr )
            +
            (
                (
                    begin( symbol() + LENGTH_XML_ELEM_CLOSED )
                    +
                    &LITERAL_XML_ELEM_CLOSED    // "/>" closed inode_element
                )
                |
                (
                    '>'                         // open inode_element
                    +
                    *CTTL_RULE( lexer< ParserT >::xml_node )
                    +
                    ( CTTL_RULE( lexer< ParserT >::xml_closeElement ) | CTTL_MEMBER_RULE( m_parser, &ParserT::error_missing_close_element ) )
                )
            )
            +
            // The element ended
            (
                // in-line semantic action to add xml element to the parse tree:
                CTTL_LAMBDA_ASSERT( +element_stack ),
                inode_element = *element_stack--, // restore element node id
                +element_stack                    // check if the parent node presents on the stack
                && (
                    // if parent element exists:
                    inode_parent = *element_stack, // position the parent node
                    inode_first = inode_parent[ FLD_FIRST_ELEMENT ] // position the first child node
                    ,
                    (
                        (
                            ( !inode_first )
                            &&
                            // if no children exist,
                            (
                                // remember this element as the first child:
                                inode_parent[ FLD_FIRST_ELEMENT ] = alias::offset( inode_element ),
                                const_scalar( 1 ) // say "true"
                            )
                        )
                        ||
                        (
                            // otherwise, if children already exist:
                            inode_last = inode_parent[ FLD_LAST_ELEMENT ],
                            CTTL_LAMBDA_ASSERT( alias::offset( inode_last ) ),
                            inode_last[ FLD_NEXT_ELEMENT ] = alias::offset( inode_element ),
                            const_scalar( 1 ) // say "true"
                        )
                    )
                    ,
                    inode_parent[ FLD_LAST_ELEMENT ] = alias::offset( inode_element )
                )
                ,
                const_scalar( 1 )
            )

        ).match( substr_ )
        ;
    }

    /**XML grammar rule: describes xml closing inode_element.*/
    size_t xml_closeElement( substr_T& substr_ )
    {
        return (
            begin( symbol() + LENGTH_XML_CLOSE_ELEM )
            +
            &LITERAL_XML_CLOSE_ELEM // "</"
            +
            CTTL_RULE( lexer< ParserT >::xml_name )
            +
            '>'

        ).match( substr_ )
        ;
    }

    /**Returns @c std::string::npos if text field contains only white space.*/
    static int validate_text( substr_T& substr_ )
    {
        substr_.first.find_class( isspace );
        substr_.second.rfind_class( isspace );
        return substr_.length();
    }

    /**XML grammar rule: xml text.*/
    size_t xml_text( substr_T& substr_ )
    {
        return (
            +( -symbol( '<' ) + symbol() )
            &
            (
                // In-line semantic action to add text node to the current xml element:
                ++(
                    scalar( 0 )
                    ^
                    CTTL_STATIC_ACTION(
                        std::ptr_fun( &lexer< ParserT >::validate_text ),
                        &substr_
                    )
                )
                &&
                (
                    inode_text << xml_text_descriptor::TEXT_SIZE,
                    inode_text[ FLD_TEXT_VALUE ] = ++( scalar( size_t( 0 ) )^m_parser.vect_xml_text^substr_ ),
                    CTTL_LAMBDA_ASSERT( +element_stack ),
                    inode_element = *element_stack,
                    inode_first = inode_element[ FLD_FIRST_TEXT ]
                    ,
                    (
                        ( !inode_first )
                        &&
                        (
                            (
                                // if no children exist,
                                inode_element[ FLD_FIRST_TEXT ] = alias::offset( inode_text ),
                                const_scalar( 1 )
                            ) || (
                                inode_last = inode_element[ FLD_LAST_TEXT ],
                                CTTL_LAMBDA_ASSERT( alias::offset( inode_last ) ),
                                inode_last[ FLD_NEXT_TEXT ] = alias::offset( inode_text ),
                                const_scalar( 1 )
                            )
                        )
                    )
                    ,
                    inode_element[ FLD_LAST_TEXT ] = alias::offset( inode_text )
                )
                ,
                const_scalar( 1 )

            )

        ).match( substr_ )
        ;
    }

    /**XML grammar rule: describes xml attribute.*/
    size_t xml_attr( substr_T& substr_ )
    {
        guard_node_stack< typename ParserT::node_T > error_info( m_parser.xml_offset_stack, substr_.first );

        return (
            CTTL_RULE( lexer< ParserT >::xml_name )
            +
            '='
            +
            (
                (
                    CTTL_RULE( lexer< ParserT >::xml_value )
                    +
                    *( ++( id_attribute_value ^ m_parser.vect_xml_text ^ attribute_value ) )
                )
                |
                CTTL_MEMBER_RULE( m_parser, &ParserT::error_bad_attr_format )
            )
            +
            // in-line semantic action to add xml attribute node to the parse subtree
            // (attributes and xml elements share symbol table of names).
            (
                inode_attribute << xml_attribute_descriptor::ATTRIBUTE_SIZE,
                inode_attribute[ FLD_ATTRIBUTE_NAME ] = id_xml_element,
                inode_attribute[ FLD_ATTRIBUTE_VALUE ] = id_attribute_value,

                // link with parent element
                CTTL_LAMBDA_ASSERT( +element_stack ),
                inode_element = *element_stack,
                inode_first = inode_element[ FLD_FIRST_ATTRIBUTE ]
                ,
                (
                    ( !inode_first )
                    &&
                    (
                        (
                            inode_element[ FLD_FIRST_ATTRIBUTE ] = alias::offset( inode_attribute )
                        ) || (
                            inode_last = inode_element[ FLD_LAST_ATTRIBUTE ],
                            CTTL_LAMBDA_ASSERT( alias::offset( inode_last ) ),
                            inode_last[ FLD_NEXT_ATTRIBUTE ] = alias::offset( inode_attribute ),
                            const_scalar( 1 )
                        )
                    )
                )
                ,
                inode_element[ FLD_LAST_ATTRIBUTE ] = alias::offset( inode_attribute ),
                const_scalar( 1 )
            )

        ).match( substr_ )
        ;
    }

    /**XML grammar rule: describes xml attribute value.*/
    size_t xml_value( substr_T& substr_ )
    {
        return (
            (
                '\"'
                +
                attribute_value( *( -symbol( '\"' ) + symbol() ) )
                +
                '\"'
            )
            |
            (
                '\''
                +
                attribute_value( *( -symbol( '\'' ) + symbol() ) )
                +
                '\''
            )
        ).match( substr_ )
        ;
    }
};

#endif //_XML_LEXER_H_INCLUDED_
