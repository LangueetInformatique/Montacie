/***************************************************************************
 *   Copyright (C) 2006 by Veli M�kinen                                    *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/


#include <cstring>
#include <string>
#include <iostream>
#include "SSTree.h"
#include "Tools.h"
using namespace std;

// Longest Common SubString (A,B)
string lcss(string A, string B)
{
	 string aux = A + "$" + B;
	 uchar *text = (uchar*)(aux.c_str());

    // One could read from file as follows:
    // uchar *text = Tools::GetFileContents("filename", maxlen);
   
    ulong n = aux.size();
    n++; // this takes the end symbol 0u as part of the text
    
    ulong splitpos = A.size(); // A is to the left, B is to the right
    SSTree *sst = new SSTree(text, n);
    
    // text could be deleted now, and recovered as follows:

    
    // NOTE: to save some memory during construction, one can also
    // instruct the constructor to delete the text as soon as it is
    // no longer needed by calling it with an additional parameter:
    // SSTree *sst = new SSTree(text, n, true); 

    /****************************************************************
    * Suffix tree is now represented using several compressed       *
    * data structures. Most important to understant the usage       *
    * is the Balanced Parantheses (BP) representation of the tree   *
    * hierarchy: the tree is traversed prefix order printing "("    *
    * when a node is visited first time and printing ")" when       *
    * a node is visited last time. E.g. "((()())())" is a tree with *
    * root having two children, its left child having two leaves,   *
    * and its right child being a leaf.                             *
    *                                                               *
    * A NODE IN THE TREE IS REPRESENTED BY THE INDEX OF THE         *
    * CORRESPONDING "(" IN THE BP REPRESENTATION                    *  
    *                                                               *  
    * All the traversal operations operate on the indexes on BP.    *
    ****************************************************************/   

    // position of last leaf of root in BP
    ulong lastleaf = sst->rightmost(0); 
    ulong i;
    bool *left = new bool[lastleaf+1], *right = new bool[lastleaf+1];
  
    /*******************************************************************
    * BP representation makes it easy to allocate additional fields    *
    * associated with suffix tree nodes. In this example, we use       *
    * tables left and right that will be filled such that left[i]=true *
    * (right[i]=true) iff a suffix of A (of B) is located in the       *
    * subtree rooted at a node whose "(" is at BP[i].                  * 
    *                                                                  *
    * NOTE: To minimize space-usage one should use tailor-made boolean *
    * storage; sizeof(bool)=byte, not 1 bit. File Tools.cpp provides   *
    * such. The following illustrates:                                 *
    *                                                                  * 
    * ulong *left = new ulong[(lastleaf+1)/W +1]; // W=comp. word size *
    * SetField(left,1,i,0); // sets i-th 1-bit length field to 0       *
    * GetField(left,1,i); // should return 0 now                       *  
    *******************************************************************/
    
    /*******************************************************************
    * The following makes a reverse prefix order traversal on the tree.*
    * This is accomplished just by scanning BP backwards.              *
    * This guarantees that once a node is reached all its children     *
    * have been visited, and its counters left and right updated       * 
    * correctly.                                                       *
    *******************************************************************/
    
    for (i=0; i<=lastleaf; i++) {
       left[i] = false; right[i]=false;
    }
        
    for (i=lastleaf;i>0;i--) {
        if (sst->isleaf(i)) {
           if (sst->textpos(i) < splitpos) {left[i]=true;right[i]=false;} 
           else {left[i]=false; right[i]=true;} 
        }
	if (sst->isOpen(i)) {
           left[sst->parent(i)] |= left[i];
           right[sst->parent(i)] |= right[i];             
	}
    }

    /*******************************************************************
    * Now node i has left[i] && right[i] iff label(root,i) is          *
    * substring of both A and B.                                       *
    * Let's find the longest such substring, i.e., deepest node        *
    * in the tree satisfying the condition.                            *            
    *******************************************************************/
    
   ulong maxdepth=0, maxindex=0;
   for (i=0; i<=lastleaf; i++)
      if (sst->isOpen(i) && left[i]== true && right[i] == true && (sst->depth(i) > maxdepth)) {
         maxdepth = sst->depth(i);
         maxindex = i;
      }


   // Let's find a text position containing the substring
   // ulong textpos = sst->textpos(sst->firstChild(maxindex));
   
   string res((char*)sst->pathlabel(maxindex));
   

   delete sst;
   delete [] left;
   delete [] right;

   return(res);
}


