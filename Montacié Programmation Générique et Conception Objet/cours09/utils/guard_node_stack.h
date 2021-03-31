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

/**@file guard_node_stack.h
 * @brief Defines utility class to protect multiple offsets
 *        of input on the user-provided stack.
 *
 */

// guard_node_stack.h

#ifndef _GUARD_NODE_STACK_H_INCLUDED_
#define _GUARD_NODE_STACK_H_INCLUDED_

namespace cttl {

/**@class guard_node_stack
 * @brief Utility class to track positions of parseable
 * <a href="http://cttl.sourceforge.net/cttl300docs/manual/cttl/page0300_edge.html">substrings</a>.
 *
 * @tparam UniverseT
 *        specifies type of the parseable universe.
 *        Can be either <tt>cttl::const_edge</tt> or <tt>cttl::edge</tt>.
 *
 * @remarks
 * When content of the CTTL input mutates at run time, the parser
 * must rely on guarded logical positions of input symbols.
 * For example, stream parsers routinely discard parts of already
 * consumed input. In such case tracking input positions for error
 * reporting may become problematic, especially
 * when dealing with nested grammar constructs.
 * Using @c guard_node_stack utility class simplifies this task.
 *
 * @par
 * Class guard_node_stack uses CTTL position tracking mechanism
 * to preserve significant logical positions of inside user input.
 *
 * @par
 * Usage
 * @n @n
 * To use the guard, user program creates a stack
 * of logical positions. For example,
 @code
    std::stack< size_t > xml_offset_stack;
 @endcode
 * Any grammar rule which has to keep
 * track of the original input positions, can then
 * instantiate a guard object as follows:
 @code
    size_t xml_grammar( universe_T& universe_ )
    {
        guard_node_stack< universe_T > error_info( this->xml_offset_stack, universe_.first );
        // ...
    }
 @endcode
 * Constructor of the guard takes two arguments:
 * an instance of the stack, and the logical input position pointed by
 * the CTTL node object. If parser program later detects an error,
 * it can obtain original guarded offset as follows:
 @code
    void show_error( universe_T& universe_ )
    {
        size_t offset = guard_node_stack< universe_T >::offset( universe_, xml_offset_stack.top() );
        // ...
    }
 @endcode
 * Note that in case of nested grammars, implementation of
 * <tt>show_error()</tt> function remains fit to report
 * correct offsets, since the stack is properly
 * unwound by destructors when nested grammar calls return.
 *
 */
template< typename NodeT >
class guard_node_stack {

protected:
    /**Reference to the stack of nodes.*/
    std::stack< NodeT >& m_node_stack;

public:
    /**Constructs and initializes the object.
    *
    * 
    */
    guard_node_stack( std::stack< NodeT >& node_stack_, NodeT const& node_ )
        :
    m_node_stack( node_stack_ )
    {
        m_node_stack.push( node_ );
    }

    /**Destructor removes stack identity of the offset managed by this object.*/
    ~guard_node_stack()
    {
        m_node_stack.pop();
    }

private:
    // Assignment is disabled:
    guard_node_stack<NodeT>& operator=( guard_node_stack<NodeT> const& );

}; //guard_node_stack


}   // namespace cttl


#endif //_GUARD_NODE_STACK_H_INCLUDED_
