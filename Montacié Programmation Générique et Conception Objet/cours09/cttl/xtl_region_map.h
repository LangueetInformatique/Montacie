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

/**@file xtl_region_map.h
* @brief Defines @c cttl_impl::xtl_region_map class.
*
* @warning
*      This is internal CTTL header file and should not
*      be included by user programs.
*
*/

// xtl_region_map.h

#ifndef _CTTL_XTL_REGION_MAP_H_INCLUDED_
#define _CTTL_XTL_REGION_MAP_H_INCLUDED_

#include <vector>
#include <map>
#include <string>
#include <iterator>

namespace cttl_impl {

    /**@class xtl_region_map
    * @brief Manages user-defined regions of user input text.
    *
    * @remarks
    * Region map encapsulates private instance of
    * the STL @c std::map object.
    *
    */
    class xtl_region_map
    {
        /**Instance the map of user-defined offset regions.*/
        std::map< size_t, size_t > m_map_region;

    public:
        /**Default constructor required by @c node::get_region_none().*/
        xtl_region_map()
        {
        }

        /**Adjusts map of regions according to the specified position and delta.
        *
        * @remarks
        * Adjustments guarantee integrity of regions
        * as long as insertions and deletions are made outside
        * of any existing region.

        * @pre
        *    If deletion range includes existing region(s), the caller
        *    is responsible for calling @c xtl_region_map::erase()
        *    prior to calling this function.
        *
        */
        void adjust( size_t after_offset_, int delta_offset_ )
        {
            if ( !delta_offset_ )
                return;

            std::map< size_t, size_t >::iterator from_iter =
                m_map_region.lower_bound( after_offset_ );

            if ( from_iter != m_map_region.end() ) {
                std::vector< std::pair< size_t, size_t > > adjustment_vector;
                std::back_insert_iterator< std::vector< std::pair< size_t, size_t > > >
                    vector_back_inserter( adjustment_vector );

                std::copy( from_iter, m_map_region.end(), vector_back_inserter );
                m_map_region.erase( from_iter, m_map_region.end() );

                for ( size_t i = 0; i < adjustment_vector.size(); ++i ) {
                    if ( adjustment_vector[ i ].first > after_offset_ )
                        adjustment_vector[ i ].first += delta_offset_;

                    if ( adjustment_vector[ i ].second > after_offset_ )
                        adjustment_vector[ i ].second += delta_offset_;

                    m_map_region.insert( adjustment_vector[ i ] );
                }
            }
        }

        /**Create new void region.
        *
        * @pre
        *    Function assumes that no offset regions overlap inside
        *    the map.
        *
        * @post
        *    Existing regions are unionized if necessary.
        *
        */
        void insert( size_t from_offset_, size_t to_offset_ )
        {
            if ( from_offset_ == to_offset_ )   // no need to add empty ranges
                return;

            size_t invalid_from = 0;
            size_t invalid_to = 0;

            std::map< size_t, size_t >::const_iterator iter =
                m_map_region.lower_bound( from_offset_ );

            if ( iter != m_map_region.end() ) {
                invalid_from = iter->second;
                invalid_to = iter->first;

                if ( ( invalid_from <= from_offset_ ) && ( from_offset_ <= invalid_to ) ) {
                    // offset is invalid
                    from_offset_ = invalid_from;
                }
            }

            iter = m_map_region.lower_bound( to_offset_ );

            if ( iter != m_map_region.end() ) {
                invalid_from = iter->second;
                invalid_to = iter->first;

                if ( ( invalid_from <= to_offset_ ) && ( to_offset_ < invalid_to ) ) {
                    // offset is invalid
                    to_offset_ = invalid_to;
                }
            }

            // even if no adjustments were made to this region,
            // any enclosed ranges should be removed:
            erase( from_offset_, to_offset_ );

            m_map_region[ to_offset_ ] = from_offset_;
        }

        /**Erase region(s) within the specified offset range.*/
        void erase( size_t from_offset_, size_t to_offset_ )
        {
            if ( from_offset_ == to_offset_ )   // no need to erase empty ranges
                return;

            if ( m_map_region.empty() )
                return; // there are no regions - nothing to do

            std::map< size_t, size_t >::iterator from_iter =
                m_map_region.lower_bound( from_offset_ );

            if ( from_iter != m_map_region.end() ) {
                std::map< size_t, size_t >::iterator to_iter =
                    m_map_region.upper_bound( to_offset_ );

                m_map_region.erase( from_iter, to_iter );
            }
        }

        /**Tests if offset falls into a void region.
        *
        * @return
        *     false if given offset does not intersect with
        *     any region, true otherwise.
        *
        */
        bool intersection( size_t offset_ ) const
        {
            if ( m_map_region.empty() )
                return false;   // there is no regions

            // Find closest region:
            std::map< size_t, size_t >::const_iterator iter =
                m_map_region.lower_bound( offset_ );

            // If nothing found,
            if ( iter == m_map_region.end() )
                return false;   // offset is outside of any region, good to go

            size_t invalid_from = iter->second;
            size_t invalid_to = iter->first;

            if ( ( invalid_from <= offset_ ) && ( offset_ < invalid_to ) )
                return true;    // offset is inside a region

            return false;   // no intersection with a region was found
        }

        /**Calculates lower boundary of the intersecting range.
        *
        * @param offset_
        *   specifies entry position into the map of void regions.
        *
        * @param str_length_
        *   specifies alternative user input position, usually the
        *   length of the input string.
        *
        * @return
        *    Adjusted position.
        *
        * @remarks
        *    - If specified @c offset_ is outside a void region, it remains
        *      unchanged.
        *    - Otherwise, the function calculates and returns new offset
        *      guaranteed to be outside any void region.
        *    - String length (EOF position is guaranteed to be outside
        *      any void region.
        *
        */
        size_t find_not_region( size_t offset_, size_t str_length_ ) const
        {
            if ( offset_ > str_length_ )
                // ik-6/11/2009
                // A weak check against user-provided offset:
                // If condition ( offset_ > str_length_ ) is false at this point,
                // the algorithm below may return an offset higher than str_length_.
                return str_length_;

            if ( m_map_region.empty() )
                return offset_; // there are no void regions defined.

            // Find closest region:
            std::map< size_t, size_t >::const_iterator iter =
                m_map_region.lower_bound( offset_ );

            // Has map entry been found ?
            if ( iter != m_map_region.end() ) {

                size_t invalid_from = iter->second;
                size_t invalid_to = iter->first;

                if ( ( invalid_from <= offset_ ) && ( offset_ < invalid_to ) )
                    // The offset_ is inside a void region, so advance to the first
                    // character outside of this region.
                    // ( invalid_to is guaranteed to be valid offset ):
                    offset_ = invalid_to;
            }

            return offset_;
        }

        /**Finds upper boundary of the next void region.
        *
        * @remarks
        * - If specified @c offset_ is located inside a void region,
        *   that particular region is chosen.
        *   @n @n Therefore, the returned offset can be less than the
        *   initial @c offset_.
        *   @n @n
        * - If next void region does not exist, the function
        *   returns @c default_offset_ provided by the user
        *   (usually as std::string::npos, or something else.)
        *
        */
        size_t find_upper_boundary( size_t offset_, size_t str_length_, size_t default_offset_ ) const
        {
            // regions are ordered by the RHS offsets, so
            // the search always starts at the specified
            // position plus one to exclude the region if
            // offset_ is already at one of the region's
            // end position.

            ++offset_;
            if ( offset_ >= str_length_ )
                return default_offset_;

            if ( m_map_region.empty() )
                return default_offset_; // there are no regions

            // Find closest region:
            std::map< size_t, size_t >::const_iterator iter =
                m_map_region.lower_bound( offset_ );

            if ( iter != m_map_region.end() )
                return iter->second;    // region LHS position

            return default_offset_;
        }


        /**Finds lower boundary of the next void region.
        *
        * @remarks
        * If no such region exist, function
        * returns @c default_offset_ provided by the caller
        * (for example, @c std::string::npos, or something else.)
        *
        */
        size_t find_lower_boundary( size_t offset_, size_t str_length_, size_t default_offset_ ) const
        {
            // regions are ordered by the RHS offsets, so
            // the search always starts at the specified position plus one to exclude
            // the region if offset_ is already at one of the region's end position.
            ++offset_;
            if ( offset_ >= str_length_ )
                return default_offset_;

            if ( m_map_region.empty() )
                return default_offset_; // there are no regions

            // Find closest region:
            std::map< size_t, size_t >::const_iterator iter =
                m_map_region.lower_bound( offset_ );

            if ( iter != m_map_region.end() )
                return iter->first; // region RHS position

            return default_offset_;
        }


        /**Finds offset pair corresponding to the next void region.
        *
        * @remarks
        * - If specified @c offset_ is located inside one of the void regions,
        *   that particular region is chosen.
        * - If next void region does not exist, the function returns a pair of
        *   @c default_offset_ values provided by the user
        * (for example, @c std::string::npos, or something else.)
        *
        */
        std::pair< size_t, size_t > find_region( size_t offset_, size_t str_length_, size_t default_offset_ ) const
        {
            // regions are ordered by the RHS offsets, so
            // the search always starts at the specified
            // position plus one:

            ++offset_;
            if ( offset_ >= str_length_ )
                return std::make_pair( default_offset_, default_offset_ );

            if ( m_map_region.empty() )
                return std::make_pair( default_offset_, default_offset_ );

            // Find closest region:
            std::map< size_t, size_t >::const_iterator iter =
                m_map_region.lower_bound( offset_ );

            if ( iter != m_map_region.end() )
                return std::make_pair( iter->second, iter->first ); // pair( LHS, RHS )

            return std::make_pair( default_offset_, default_offset_ );
        }

        /**Clears region map.*/
        void clear()
        {
            m_map_region.clear();
        }

        /**Returns true if map of regions is empty, false otherwise.*/
        bool empty() const
        {
            return m_map_region.empty();
        }


        /**Returns true if region specified by the range intersects
        * with another existing regions.
        *
        */
        bool intersection( size_t from_offset_, size_t to_offset_ ) const
        {
            if ( m_map_region.empty() )
                return false;   // there are no regions

            std::map< size_t, size_t >::const_iterator from_iter =
                m_map_region.lower_bound( from_offset_ );

            if ( from_iter != m_map_region.end() ) {
                //    compare region found:  (from_iter->second)-----(from_iter->first)
                // with region in question:        (from_offset)-----(to_offset)
                if ( ( from_offset_ <= from_iter->second ) && ( from_iter->second < to_offset_ ) )
                    return true;
                if ( ( from_iter->second <= from_offset_ ) && ( from_offset_ < from_iter->first ) )
                    return true;
            }

            std::map< size_t, size_t >::const_iterator to_iter =
                m_map_region.upper_bound( to_offset_ );

            if ( to_iter != m_map_region.end() ) {
                //    compare region found: (to_iter->second)-----(to_iter->first)
                // with region in question:     (from_offset)-----(to_offset)
                if ( ( from_offset_ <= to_iter->second ) && ( to_iter->second < to_offset_ ) )
                    return true;
                if ( ( to_iter->second <= from_offset_ ) && ( from_offset_ < to_iter->first ) )
                    return true;
            }

            return false;   // no regions found inside specified pair of offsets
        }

        /**Returns true if region specified by the range is contained entirely
        * within another existing region.
        *
        */
        bool contains( size_t from_offset_, size_t to_offset_ ) const
        {
            if ( m_map_region.empty() )
                return false;   // there are no regions defined

            std::map< size_t, size_t >::const_iterator from_iter =
                m_map_region.lower_bound( from_offset_ );

            if ( from_iter != m_map_region.end() ) {
                //                does region (from_iter->second)-------(from_iter->first)
                // contain region in question       (from_offset)-------(to_offset) ?
                if ( ( from_iter->second <= from_offset_ ) && ( from_offset_ < from_iter->first )
                    && ( from_iter->second <= to_offset_ ) && ( to_offset_ <= from_iter->first ) )
                    return true;
            }

            std::map< size_t, size_t >::const_iterator to_iter =
                m_map_region.upper_bound( to_offset_ );

            if ( to_iter != m_map_region.end() ) {
                //                does region (to_iter->second)------(to_iter->first)
                // contain region in question     (from_offset)------(to_offset) ?
                if ( ( to_iter->second <= from_offset_ ) && ( from_offset_ < to_iter->first )
                    && ( to_iter->second <= to_offset_ ) && ( to_offset_ <= to_iter->first ) )
                    return true;
            }

            return false;   // specified region contains valid space
        }

        /**Returns substring pointed by the range, excluding any existing void regions.*/
        template< typename StringT >
        StringT text_difference( StringT const& str_, size_t from_offset_, size_t to_offset_ ) const
        {
            if ( from_offset_ == to_offset_ )
                return StringT();

            StringT str_difference;

            std::map< size_t, size_t >::const_iterator map_iter = m_map_region.lower_bound( from_offset_ );
            if ( map_iter == m_map_region.end() )
                return str_.substr( from_offset_, to_offset_ - from_offset_ );

            size_t current_offset_from = from_offset_;
            size_t current_offset_to = to_offset_;

            for ( ; map_iter != m_map_region.end(); ++map_iter ) {
                size_t region_from = map_iter->second;
                size_t region_to = map_iter->first;

                if ( ( region_from <= current_offset_from ) && ( current_offset_from < region_to ) ) {
                    current_offset_from = region_to;
                    continue;
                }

                if ( ( region_from <= current_offset_to ) && ( current_offset_to < region_to ) )
                    current_offset_to = region_from;

                if ( ( current_offset_from <= region_from ) && ( region_from < current_offset_to ) )
                    current_offset_to = region_from;

                if ( current_offset_from > current_offset_to  )
                    return str_difference;

                if ( current_offset_to > to_offset_ )
                    return str_difference;

                str_difference += str_.substr( current_offset_from, current_offset_to - current_offset_from );

                if ( current_offset_to < region_from )
                    return str_difference;

                current_offset_from = region_to;
                current_offset_to = to_offset_;
            }

            if ( current_offset_from < current_offset_to )
                str_difference += str_.substr( current_offset_from, current_offset_to - current_offset_from );

            return str_difference;
        }

    };  // xtl_region_map

}   // namespace cttl_impl

#endif // _CTTL_XTL_REGION_MAP_H_INCLUDED_
