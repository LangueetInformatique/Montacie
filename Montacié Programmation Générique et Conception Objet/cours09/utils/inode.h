////////////////////////////////////////////////////////////////////////
// Common Text Transformation Library
// Copyright (C) 1997-2006 by Igor Kholodov. 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// mailto:cttl@users.sourceforge.net
// http://sourceforge.net/projects/cttl/
////////////////////////////////////////////////////////////////////////

/**@file inode.h
 * @brief Header for classes and functions to model syntax trees.
 *
 */

// inode.h

#ifndef _CTTL_INODE_H_INCLUDED_
#define _CTTL_INODE_H_INCLUDED_

/**@struct inode_default_descriptor
 * @brief Describes field layout of the default node in an integer tree.
 *
 */
struct inode_default_descriptor {
    enum {
        /**Position of the field that points to the next node.*/
        NEXT_LINK,     // mandatory constant

        /**Position of the field that points to the previous node.*/
        PREVIOUS_LINK, // mandatory constant

        /**Position of the first data field (exemplary/unused).*/
        DATA_FIELD,

        /**Specifies the size of the node (exemplary/unused).*/
        NODE_SIZE
    };
};//struct inode_default_descriptor

#include "inode_writer.h"
#include "inode_reader.h"

#endif // _CTTL_INODE_H_INCLUDED_
