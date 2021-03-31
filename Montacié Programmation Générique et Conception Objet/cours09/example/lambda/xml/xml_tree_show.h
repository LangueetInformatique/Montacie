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

/**@file xml_tree_show.h
 * @brief Defines function object to dump xml subtree on the standard output.
 *
 */

// xml_tree_show.h

#ifndef _XML_TREE_SHOW_H_INCLUDED_
#define _XML_TREE_SHOW_H_INCLUDED_

using namespace cttl;

/**@struct xml_tree_show
 * @brief Function object, which, if called as a function,
 *        dumps xml element subtree on the standard output.
 *
 */
struct xml_tree_show : public std::unary_function< inode_reader<>, void >
{
    /**Specifies current level of xml subtree, 1, 2, 3, and so on.*/
    size_t level;

    /**Specifies reference of the symbol table containing names of xml elements and attributes.*/
    std::vector< std::string > const& vect_xml_names;

    /**Specifies reference of the symbol table containing text values of xml text and attribute nodes.*/
    std::vector< std::string > const& vect_xml_text;

    /**Constructs and initializes the object.*/
    xml_tree_show(
        size_t level_,
        std::vector< std::string > const& vect_xml_names_,
        std::vector< std::string > const& vect_xml_text_
        )
        :
        level( level_ ),
        vect_xml_names( vect_xml_names_ ),
        vect_xml_text( vect_xml_text_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xml_tree_show& operator=( xml_tree_show const& );

public:
    /**Justifies output according to the current level in the xml tree.*/
    void show_level( char c_ = '.' ) const
    {
        for ( size_t lvl = 0; lvl < level; ++lvl )
            std::cout << c_;
    }

    /**Function call operator to dump the xml subtree.*/
    void operator() ( inode_reader<> const& inode_ ) const
    {
        show_level();
        std::cout
            /*
            << "element("
            << inode_.offset()
            <<") = "
            << inode_[ ELEMENT_NAME ] << '^'
            << inode_[ FIRST_ATTRIBUTE ] << '^'
            << inode_[ LAST_ATTRIBUTE ] << '^'
            << inode_[ FIRST_TEXT ] << '^'
            << inode_[ LAST_TEXT ] << '^'
            << inode_[ FIRST_ELEMENT ] << '^'
            << inode_[ LAST_ELEMENT ]
            << '\t'
            */
            << vect_xml_names[ inode_[ xml_element_descriptor::ELEMENT_NAME ] ]
            << std::endl
            ;

        for (
            inode_reader<> attr = inode_( xml_element_descriptor::FIRST_ATTRIBUTE );
            attr != inode_.end();
            ++attr
            )
        {
            show_level();
            std::cout
                << '.'
                << vect_xml_names[ attr[ xml_attribute_descriptor::ATTRIBUTE_NAME ] ]
                /*
                << "attribute("
                << attr.offset()
                <<") = "
                << attr[ ATTRIBUTE_NAME ] << '^'
                << attr[ ATTRIBUTE_VALUE ]
                */
                << '='
                << vect_xml_text[ attr[ xml_attribute_descriptor::ATTRIBUTE_VALUE ] ]
                << std::endl
                ;
        }

        for (
            inode_reader<> txt = inode_( xml_element_descriptor::FIRST_TEXT );
            txt != inode_.end();
            ++txt
            )
        {
            show_level();
            std::cout
                << '.'
                << "TEXT_VALUE:"
                << vect_xml_text[ txt[ xml_text_descriptor::TEXT_VALUE ] ]
                << std::endl
                ;
        }

        std::for_each(
            inode_( xml_element_descriptor::FIRST_ELEMENT ),
            inode_.end(),
            xml_tree_show(
                level + 1,
                vect_xml_names,
                vect_xml_text
                )
            );

    }
    
}; // struct xml_tree_show


#endif //_XML_TREE_SHOW_H_INCLUDED_
