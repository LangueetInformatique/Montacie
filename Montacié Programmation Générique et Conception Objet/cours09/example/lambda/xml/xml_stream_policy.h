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

/**@file xml_stream_policy.h
 * @brief Defines user-defined space policy classes to handle
 * file input and white space of @ref index.
 *
 */

// xml_stream_policy.h

#ifndef _XML_STREAM_POLICY_H_INCLUDED_
#define _XML_STREAM_POLICY_H_INCLUDED_

/**@class policy_strict_stream
 * @brief CTTL policy class for @ref index.
 *
 * Keeps track of xml input file state at run time.
 * <tt>policy_strict_stream</tt> ignores white space:
 * No white space is recognized or skipped by this class.
 *
 */
class policy_strict_stream : public policy_default
{
    /**Buffer padding size.*/
    static const size_t buffer_pad_size = 16;

    /**Number of bytes to read from the stream: anywhere from 1 byte and up.*/
    static const size_t max_byte_count_2_read = 1024 * buffer_pad_size;

protected:
    /**Input buffer size.*/
    //DEBUG//static const size_t file_buffer_size = 1;
    static const size_t file_buffer_size = max_byte_count_2_read;

    /**Character buffer for reading the data.*/
    char m_character_buffer[ max_byte_count_2_read + buffer_pad_size ];

    /**Input file stream.*/
    std::ifstream m_file_stream;

    /**Substring of input that has been successfully processed by the parser,
    * and can be safely discarded to free up memory.
    *
    */
    edge<>& consumed_data;

public:
    /**Constructs and initializes the policy object.*/
    policy_strict_stream( edge<>& consumed_data_ )
        :
        consumed_data( consumed_data_ )
    {
    }

private:
    /**Assignment is disabled.*/
    policy_strict_stream& operator=( policy_strict_stream const& );

public:
    /**Initializes the object: opens the input file.
    *
    * @return
    *    The function returns true if the input file has been opened
    *    for reading successfully, false otherwise.
    *
    */
    bool init( char* file_ )
    {
        assert( !m_file_stream.is_open() );
        m_file_stream.open( file_, std::ios::in | std::ios::binary );
        if ( m_file_stream.bad() ) {
            // m_file_stream is corrupted
            return false;
        }
        return m_file_stream.is_open();
    }

    /** Defines CTTL production rule function to evaluate
    *   grammar describing white space.
    *
    * @tparam SubstrT
    *        specifies type of the parseable substring.
    *        Mutable substring, <tt>cttl::edge</tt>, is expected.
    *
    * @param substr_
    *        Reference to the parseable substring.
    *
    * @return
    *        Absolute position of the substring upper boundary
    *        after white space expression has been evaluated.
    *
    * @post
    *        This function always succeeds and returns a valid offset
    *        within the specified parseable substring.
    *        The function incrementally reads information from the input
    *        file, if data is available. If end of file is reached, the
    *        function closes the input file and updates state of the policy
    *        object accordingly. Before new data is loaded from the stream,
    *        the data specified by @c consumed_data substring may be discarded
    *        to free the memory.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& substr_ )
    {
        if ( m_file_stream.is_open() && !substr_.length() ) {
            m_file_stream.read( m_character_buffer, file_buffer_size );
            if ( m_file_stream.bad() ) {
                // m_file_stream is corrupted
                return 0;
            }
            size_t numread = m_file_stream.gcount();
            if ( numread ) {
                m_character_buffer[ numread ] = 0x00;

#ifdef DISPOSE_CONSUMED_DATA
                assert( !consumed_data.first.offset() );
                if ( consumed_data.length() )
                    consumed_data.erase();
#endif // DISPOSE_CONSUMED_DATA

                // Append new data to the input string
                substr_.parent().append( m_character_buffer );
                substr_.second.go_eof();
                assert( substr_.length() );

            } else {
                assert( m_file_stream.eof() );
                m_file_stream.close();
            }
        }

        return substr_.first.offset();
    }
};  // struct policy_strict_stream


/**@class policy_relaxed_stream
 * @brief CTTL policy class for @ref index.
 *
 * This policy class keeps track of the state of xml input file at run time.
 * <tt>policy_relaxed_stream</tt> skips white space characters, such as
 * ht, lf, vt, ff, cr, and space.
 *
 */
class policy_relaxed_stream : public policy_strict_stream
{
public:
    /**Constructs and initializes the policy object.*/
    policy_relaxed_stream( edge<>& consumed_data_ )
        :
        policy_strict_stream( consumed_data_ )
    {
    }

    /** Defines CTTL production rule function
    *   describing white space grammar.
    *
    * @tparam SubstrT
    *        specifies type of the parseable substring.
    *        Mutable substring, <tt>cttl::edge</tt>, is expected.
    *
    * @param substr_
    *        Reference to the parseable substring.
    *
    * @return
    *        Absolute position of the substring upper boundary
    *        after white space expression has been evaluated.
    *
    * @post
    *        This function always succeeds and returns a valid offset
    *        within the specified parseable substring.
    *        The function incrementally reads information from the input
    *        file, if data is available. If end of file is reached, the
    *        function closes the input file and updates policy state
    *        accordingly. Before new data is loaded from the stream,
    *        the data specified by @c consumed_data substring can be discarded
    *        to free up the memory.
    *
    */
    template< typename SubstrT >
    size_t match( SubstrT& substr_ )
    {
        ( true ^ ( entity( isspace ) | true ) ).match( substr_ );

        if ( this->m_file_stream.is_open() && !substr_.length() ) {
            this->m_file_stream.read( this->m_character_buffer, this->file_buffer_size );
            if ( m_file_stream.bad() ) {
                // m_file_stream is corrupted
                return 0;
            }
            size_t numread = this->m_file_stream.gcount();
            if ( numread ) {
                this->m_character_buffer[ numread ] = 0x00;

#ifdef DISPOSE_CONSUMED_DATA
                assert( !consumed_data.first.offset() );
                if ( consumed_data.length() )
                    consumed_data.erase();
#endif // DISPOSE_CONSUMED_DATA

                // Append new data to the input string
                substr_.parent().append( this->m_character_buffer );
                substr_.second.go_eof();
                assert( substr_.length() );

            } else {
                assert( m_file_stream.eof() );
                this->m_file_stream.close();
            }
            return match( substr_ );
        }

        return substr_.first.offset();
    }
};  // struct policy_relaxed_stream


#endif //_XML_STREAM_POLICY_H_INCLUDED_
