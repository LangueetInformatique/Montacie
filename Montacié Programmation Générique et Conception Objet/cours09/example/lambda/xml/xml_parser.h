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

/**@file xml_parser.h
 * @brief Defines parser class for @ref index.
 *
 */

// xml_parser.h

#ifndef _XML_PARSER_H_INCLUDED_
#define _XML_PARSER_H_INCLUDED_

/**@struct parser
 * @brief Parser class for @ref index.
 *
 * @tparam SubstrT
 *        specifies type of the parseable substring.
 *        Can be either <tt>cttl::const_edge</tt> or <tt>cttl::edge</tt>.
 *
 * The parser implements error handlers and semantic actions that populate
 * abstract syntax tree for an xml input.
 *
 */
template< typename SubstrT >
struct parser {

    /**Defines type of parseable substring.*/
    typedef SubstrT substr_T;

    /**Defines strict substring type.*/
    typedef typename SubstrT::strict_edge_T strict_input_T;

    /**Defines CTTL node type.*/
    typedef typename SubstrT::node_T node_T;

    /**Defines chracter type in use by the parser.*/
    typedef typename SubstrT::char_T char_T;

    /**Defines vector of xml names.*/
    std::vector< std::string > vect_xml_names;

    /**Symbol table that stores names of xml elements and attributes.*/
    std::map< std::string, size_t > map_xml_names;

    // A pair has to be be assembled to represent a :
    /**Dictionary table that maps xml text fragments to their internal IDs and back.*/
    std::pair< std::vector< std::string >*, std::map< std::string, size_t >* > xml_name_dictionary;

    /**Container that stores text of xml elements and values of xml attributes.*/
    std::vector< std::string > vect_xml_text;

    /**Stack of input positions used by xml syntax error reporting of nested xml elements.*/
    std::stack< node_T > xml_offset_stack;

    /**The parse tree.*/
    std::vector< size_t > vect_xml_tree;

    /**Constructs and initializes the object.*/
    parser()
        :
        xml_name_dictionary( &vect_xml_names, &map_xml_names ),
        vect_xml_tree( 1 )
    {
    }

public:
    /**Displays information about syntax error encountered by lexer.*/
    void error_show( substr_T& substr_, char_T const* message_ )
    {
#ifndef SUPPRESS_VERBOSE_ERRORS
        size_t offset_from_ = xml_offset_stack.top().offset();
        size_t offset_to_ = substr_.first.offset();

        if ( offset_from_ < offset_to_ )
            std::cout
                << "..."
                << substr_.parent().substr(
                    offset_from_,
                    std::min( offset_to_, offset_from_ + 50 ) - offset_from_
                    )
                << "..."
                ;

        std::cout
            << std::endl
            << "*** Error: "
#ifdef DISPOSE_CONSUMED_DATA
            << '@'
            << offset_from_
            << '-'
            << offset_to_
#else
            << "line "
            << substr_.first.line()
#endif // DISPOSE_CONSUMED_DATA
           << '\t'
            << message_
            << std::endl
            ;
#endif // SUPPRESS_VERBOSE_ERRORS
    }

    /**Error handler for generic parser error.*/
    size_t error_parser_failed( substr_T& substr_ )
    {
        error_show(
            substr_,
            "error_parser_failed"
            );
        return substr_T::string_T::npos;
    }

    /**Error handler for bad xml processing instruction format.*/
    size_t error_bad_pi( substr_T& substr_ )
    {
        error_show(
            substr_,
            "missing PI name"
            );
        return substr_T::string_T::npos;
    }

    /**Error handler for missing closing tag of the xml element.*/
    size_t error_missing_close_element( substr_T& substr_ )
    {
        error_show(
            substr_,
            "error_missing_close_element"
            );
        return substr_T::string_T::npos;
    }

    /**Error handler for missing closing unit of the processing instruction.*/
    size_t error_missing_pi_close( substr_T& substr_ )
    {
        error_show(
            substr_,
            "error_missing_pi_close"
            );
        return substr_T::string_T::npos;
    }

    /**Error handler for missing closing unit of the xml comment.*/
    size_t error_missing_comment_close( substr_T& substr_ )
    {
        error_show(
            substr_,
            "error_missing_comment_close"
            );
        return substr_T::string_T::npos;
    }

    /**Error handler for bad xml attribute format.*/
    size_t error_bad_attr_format( substr_T& substr_ )
    {
        error_show(
            substr_,
            "error_bad_attr_format"
            );
        return substr_T::string_T::npos;
    }
    
};  // struct parser


#endif //_XML_PARSER_H_INCLUDED_
