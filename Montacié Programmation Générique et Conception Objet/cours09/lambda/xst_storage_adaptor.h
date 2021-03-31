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

/**@file xst_storage_adaptor.h
 * @brief Utility structures for common storage interface to instances and references to C++ objects.
 *
 * @warning
 *      This is internal CTTL header file and should not
 *      be included by user programs.
 *
 */

// xst_storage_adaptor.h

#ifndef _XST_STORAGE_ADAPTOR_H_INCLUDED_
#define _XST_STORAGE_ADAPTOR_H_INCLUDED_

namespace cttl_impl {

/**@class xst_storage_adaptor
 * @brief Primary template implements interface for an instance of C++ object.
 *
 * @tparam ValueT
 *        specifies type of the object to store.
 *
 */
template< typename ValueT >
class xst_storage_adaptor
{
private:
    /**Stores instance of object.*/
    ValueT m_value;

public:
    /**Defines value type of stored object.*/
    typedef ValueT value_type;

    /**Defines reference type of stored object.*/
    typedef ValueT& reference;

    /**Defines constant reference type of stored object.*/
    typedef ValueT const& const_reference;

    /**Default constructor.*/
    xst_storage_adaptor()
        :
    m_value( ValueT() )
    {
    }

    /**Constructor from a value type.*/
    xst_storage_adaptor( ValueT const& value_ )
        :
    m_value( value_ )
    {
    }

    /**Copy constructor.*/
    xst_storage_adaptor( xst_storage_adaptor< ValueT > const& other_ )
    :
    m_value( other_.m_value )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_storage_adaptor< ValueT >& operator=( xst_storage_adaptor< ValueT > const& );

public:
    /**Returns constant reference to the stored object.*/
    const_reference const_value() const
    {
        return m_value;
    }

    /**Returns mutable reference to the stored object.*/
    reference value()
    {
        return m_value;
    }

    /**Auxiliary function to identify actual instance inside lambda expression trace.*/
    static char trace_char()
    {
        return '_';
    }

}; // class xst_storage_adaptor


/**@class xst_storage_adaptor
 * @brief Partial specialization for mutable reference to object.
 *
 * @tparam ValueT
 *        specifies type of the object to store the reference for.
 *
 */
template< typename ValueT >
class xst_storage_adaptor< ValueT& >
{
private:
    /**Stores reference to object.*/
    ValueT& m_value;

public:
    /**Defines value type of referred object.*/
    typedef ValueT value_type;

    /**Defines reference type.*/
    typedef ValueT& reference;

    /**Defines constant reference type.*/
    typedef ValueT const& const_reference;

    /**Constructor for existing instance.*/
    xst_storage_adaptor( ValueT& value_ )
        :
    m_value( value_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_storage_adaptor< ValueT& >& operator=( xst_storage_adaptor< ValueT& > const& );

public:
    /**Returns constant reference to object.*/
    const_reference const_value() const
    {
        return m_value;
    }

    /**Returns mutable reference to object.*/
    reference value() const
    {
        return m_value;
    }

    /**Auxiliary function to identify reference object to inside lambda expression trace.*/
    static char trace_char()
    {
        return ' ';
    }

}; // class xst_storage_adaptor


/**@class xst_storage_adaptor
 * @brief Partial specialization for constant reference to object.
 *
 * @tparam ValueT
 *        specifies type of the object to store the reference for.
 *
 */
template< typename ValueT >
class xst_storage_adaptor< ValueT const& >
{
private:
    /**Stores constant reference to object.*/
    ValueT const& m_value;

public:
    /**Defines value type of referred object.*/
    typedef ValueT value_type;

    /**Reference type is defined, but not used inside this specialization.*/
    typedef ValueT& reference;

    /**Defines constant reference type.*/
    typedef ValueT const& const_reference;

    /**Constructor for existing instance.*/
    xst_storage_adaptor( ValueT const& value_ )
        :
    m_value( value_ )
    {
    }

private:
    /**Assignment is disabled.*/
    xst_storage_adaptor< ValueT const& >& operator=( xst_storage_adaptor< ValueT const& > const& );

public:
    /**Returns constant reference to object.*/
    const_reference const_value() const
    {
        return m_value;
    }

    /**Returns <b>constant</b> reference to object.*/
    const_reference value() const
    {
        return m_value;
    }

    /**Auxiliary function to identify constant reference to object inside lambda expression trace.*/
    static char trace_char()
    {
        return '&';
    }

}; // class xst_storage_adaptor


}   // namespace cttl_impl

#endif // _XST_STORAGE_ADAPTOR_H_INCLUDED_
