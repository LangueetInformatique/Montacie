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

/**@file xml_tree_struct.h
 * @brief Custom descriptors of xml tree nodes.
 *
 */

// xml_tree_struct.h

#ifndef _XML_TREE_STRUCT_H_INCLUDED_
#define _XML_TREE_STRUCT_H_INCLUDED_

// XML node descriptors: element, attribute, and text

/**XML element descriptor.*/
struct xml_element_descriptor {
    enum {
        NEXT_LINK,     // mandatory
        PREVIOUS_LINK = NEXT_LINK, // mandatory (not used)

        NEXT_ELEMENT = NEXT_LINK,
        ELEMENT_NAME,
        FIRST_ATTRIBUTE,
        LAST_ATTRIBUTE,
        FIRST_TEXT,
        LAST_TEXT,
        FIRST_ELEMENT, // First child
        LAST_ELEMENT,  // Last child
        ELEMENT_SIZE   // The size of element node
    };
};//struct xml_element_descriptor

/**XML attribute descriptor.*/
struct xml_attribute_descriptor {
    enum {
        NEXT_LINK,     // mandatory
        PREVIOUS_LINK = NEXT_LINK, // mandatory (not used)

        NEXT_ATTRIBUTE = NEXT_LINK,
        ATTRIBUTE_NAME,
        ATTRIBUTE_VALUE,
        ATTRIBUTE_SIZE
    };
};//struct xml_attribute_descriptor

/**XML text descriptor.*/
struct xml_text_descriptor {
    enum {
        NEXT_LINK,     // mandatory
        PREVIOUS_LINK = NEXT_LINK, // mandatory (not used)

        NEXT_TEXT = NEXT_LINK,
        TEXT_VALUE,
        TEXT_SIZE
    };
};//struct xml_text_descriptor

// Constant scalars describing the fields of xml nodes:
const_scalar_type( xml_element_descriptor::NEXT_ELEMENT )       FLD_NEXT_ELEMENT;
const_scalar_type( xml_element_descriptor::ELEMENT_NAME )       FLD_ELEMENT_NAME;
const_scalar_type( xml_element_descriptor::FIRST_ATTRIBUTE )    FLD_FIRST_ATTRIBUTE;
const_scalar_type( xml_element_descriptor::LAST_ATTRIBUTE )     FLD_LAST_ATTRIBUTE;
const_scalar_type( xml_element_descriptor::FIRST_TEXT )         FLD_FIRST_TEXT;
const_scalar_type( xml_element_descriptor::LAST_TEXT )          FLD_LAST_TEXT;
const_scalar_type( xml_element_descriptor::FIRST_ELEMENT )      FLD_FIRST_ELEMENT;
const_scalar_type( xml_element_descriptor::LAST_ELEMENT )       FLD_LAST_ELEMENT;

const_scalar_type( xml_attribute_descriptor::NEXT_ATTRIBUTE )     FLD_NEXT_ATTRIBUTE;
const_scalar_type( xml_attribute_descriptor::ATTRIBUTE_NAME )     FLD_ATTRIBUTE_NAME;
const_scalar_type( xml_attribute_descriptor::ATTRIBUTE_VALUE )    FLD_ATTRIBUTE_VALUE;

const_scalar_type( xml_text_descriptor::NEXT_TEXT )          FLD_NEXT_TEXT;
const_scalar_type( xml_text_descriptor::TEXT_VALUE )         FLD_TEXT_VALUE;

#endif //_XML_TREE_STRUCT_H_INCLUDED_
