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

// icsubstring.cpp
// Demonstrates usage of case-insensitive strings in STL and CTTL

/*
Protoype of this program was taken from:
http://www.josuttis.com/libbook/string/icstring1.cpp.html

The following code example is taken from the book
The C++ Standard Library - A Tutorial and Reference
by Nicolai M. Josuttis, Addison-Wesley, 1999
(c) Copyright Nicolai M. Josuttis 1999
*/

#include "example/icstring/icstring.h"
#define CTTL_STD_STRING icstring
#include "cttl/cttl.h"

int main()
{
    using std::cout;
    using std::endl;
    cout << "\tCase-insensitive STL string:" << endl;

    icstring s1("hallo");
    icstring s2("otto");
    icstring s3("hALLo");
    
    cout << std::boolalpha;
    cout << s1 << " == " << s2 << " : " << (s1==s2) << endl;
    cout << s1 << " == " << s3 << " : " << (s1==s3) << endl;

    icstring::size_type idx = s1.find("All");
    if (idx != icstring::npos) {
        cout << "index of \"All\" in \"" << s1 << "\": "
             << idx << endl;
    }

    else {
        cout << "\"All\" not found in \"" << s1 << endl;
    }

    cout << "\tCase-insensitive CTTL substring:" << endl;
    using namespace cttl;
    const_edge<> sub1( s1 );
    const_edge<> sub2( s2 );
    const_edge<> sub3( s3 );

    cout << sub1 << " == " << sub2 << " : " << (sub1==sub2) << endl;
    cout << sub1 << " == " << sub3 << " : " << (sub1==sub3) << endl;

    idx = ( symbol( "All" ) ).find( sub1 );

    if (idx != icstring::npos) {
        cout << "index of \"All\" in \"" << s1 << "\": "
             << idx << endl;
    }

    else {
        cout << "\"All\" not found in \"" << s1 << endl;
    }

    return 0;
}
