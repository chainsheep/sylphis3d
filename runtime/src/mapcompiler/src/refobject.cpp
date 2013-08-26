/***************************************************************************
                          refobject.cpp  -  description
                             -------------------
    begin                : Sun Jun 2 2002
    copyright            : (C) 2002 by Harry Kalogirou
    email                : harkal@gmx.net
  ***************************************************************************
    This file is part of "Sylphis3D Game Engine".

	Copyright (c) 2013 Charilaos Kalogirou.
	All rights reserved.

	Redistribution and use in source and binary forms are permitted
	provided that the above copyright notice and this paragraph are
	duplicated in all such forms and that any documentation,
	advertising materials, and other materials related to such
	distribution and use acknowledge that the software was developed
	by Charilaos Kalogirou. The name of the
	Charilaos Kalogirou may not be used to endorse or promote products derived
	from this software without specific prior written permission.
	THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/
#include <iostream>
#include <assert.h>
#include "refobject.h"

using namespace std;

unsigned int CRefObject::totalRefObjects = 0;

CRefObject::CRefObject(){
    references = 0;
    totalRefObjects++;
}

CRefObject::~CRefObject(){
    assert(totalRefObjects);
    totalRefObjects--;
}

void CRefObject::incReferences(){
	references++;
//    cout << "refs " << references << "\n";
}

void CRefObject::decReferences(){
    references--;
//    cout << "refs " << references << "\n";
    if(references == 0){
//        cout << "deleting " << this << "\n";
        delete this;
    }
}

unsigned int CRefObject::getReferences(){
     return references;
}

unsigned int CRefObject::getTotalRefObjects(){
    return totalRefObjects;
}


