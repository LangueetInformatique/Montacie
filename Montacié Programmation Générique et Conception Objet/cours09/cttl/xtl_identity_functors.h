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

/**@file xtl_identity_functors.h
* @brief Defines internal CTTL offset adjustment helper classes.
*
* @warning
*      This is internal CTTL header file and should not
*      be included by user programs.
*
* @remarks
*        avoid adjustments with @code
delta_offset_ == 0,
@endcode
*        which is ineffective.
*
* @see
*  - @c cttl_impl::xtl_identity_adjust_base
*  - @c cttl_impl::xtl_identity_collapse
*  - @c cttl_impl::xtl_identity_insert_go
*  - @c cttl_impl::xtl_identity_insert_stay
*
*/

// xtl_identity_functors.h

#ifndef _CTTL_XTL_IDENTITY_FUNCTORS_H_INCLUDED_
#define _CTTL_XTL_IDENTITY_FUNCTORS_H_INCLUDED_

namespace cttl_impl {

    /**Base class for other offset helper classes.*/
    class xtl_identity_adjust_base {
    protected:

        /**Points to the insertion position.*/
        const size_t  m_insertion_point_offset;

        /**Stores adjustment value.*/
        const int     m_delta_offset;

    public:

        /**Constructs object and initializes the values.*/
        xtl_identity_adjust_base( size_t insertion_point_offset_, int delta_offset_ )
            :
        m_insertion_point_offset( insertion_point_offset_ ),
            m_delta_offset( delta_offset_ )
        {
        }
    private:
        /**Assignment is disabled.*/
        xtl_identity_adjust_base& operator=( xtl_identity_adjust_base const& );

    };  // class xtl_identity_adjust_base

    /**Helper class implementing "collapse" algorithm.
    *
    * @tparam StringT
    *        specifies type of the
    *        adjusted string.
    *
    */
    template< typename StringT >
    class xtl_identity_collapse : public xtl_identity_adjust_base {
    public:
        /**Constructs object and initializes the values.*/
        xtl_identity_collapse( size_t insertion_point_offset_, int delta_offset_ )
            :
        xtl_identity_adjust_base( insertion_point_offset_, delta_offset_ )
        {
        }

        /**Implements "collapse" algorithm.
        *
        * @param target_offset_
        *        reference to the offset to be adjusted.
        *
        @code
        // collapse diagram:
        //                        .--- m_insertion_point_offset
        //                        |    may no longer be valid
        //                        v
        // before -----1-BEFORE-2-3-4-------
        //             |        |/ /
        //             |        / /
        //             |      2/ /
        // after  -----1-AFTER3-4-------
        //                    ^
        //                    |
        //                    `-- collapse_offset=( m_insertion_point_offset + m_delta_offset )
        //                        is always valid
        @endcode
        *
        */
        void adjust( size_t& target_offset_ ) const
        {
            if ( target_offset_ == StringT::npos )
                return;

            if ( target_offset_ < m_insertion_point_offset ) {
                if ( ( m_insertion_point_offset + m_delta_offset ) < target_offset_ )
                    target_offset_ = m_insertion_point_offset + m_delta_offset;

                return; // skip low-offset nodes
            }
            target_offset_ += m_delta_offset;
        }
    };  // class xtl_identity_collapse


    /**Helper class implementing "insert_go" adjustment.
    *
    * @tparam StringT
    *        specifies type of the
    *        adjusted string.
    *
    */
    template< typename StringT >
    class xtl_identity_insert_go : public xtl_identity_adjust_base {
    public:

        /**Constructs object and initializes the values.*/
        xtl_identity_insert_go( size_t insertion_point_offset_, int delta_offset_ )
            :
        xtl_identity_adjust_base( insertion_point_offset_, delta_offset_ )
        {
        }

        /**Implements "insert_go" adjustment.
        *
        * @param target_offset_
        *        reference to the offset to be adjusted.
        *
        */
        void adjust( size_t& target_offset_ ) const
        {
            if ( target_offset_ == StringT::npos )
                return;

            if ( target_offset_ >= m_insertion_point_offset )
                target_offset_ += m_delta_offset;
        }
    };  // class xtl_identity_insert_go


    /**Helper class implementing "insert_stay" adjustment.
    *
    * @tparam StringT
    *        specifies type of the
    *        adjusted string.
    *
    */
    template< typename StringT >
    class xtl_identity_insert_stay : public xtl_identity_adjust_base {
    public:

        /**Constructs object and initializes the values.*/
        xtl_identity_insert_stay( size_t insertion_point_offset_, int delta_offset_ )
            :
        xtl_identity_adjust_base( insertion_point_offset_, delta_offset_ )
        {
        }

        /**Implements "insert_stay" adjustment.
        *
        * @param target_offset_
        *        reference to the offset to be adjusted.
        *
        */
        void adjust( size_t& target_offset_ ) const
        {
            if ( target_offset_ == StringT::npos )
                return;

            if ( target_offset_ > m_insertion_point_offset )
                target_offset_ += m_delta_offset;
        }
    };  // class xtl_identity_insert_stay

}   // namespace cttl_impl

#endif // _CTTL_XTL_IDENTITY_FUNCTORS_H_INCLUDED_
