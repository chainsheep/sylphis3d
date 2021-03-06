/***************************************************************************
                          exception.h  -  description
                             -------------------
    begin                : Thu Mar 14 2002
    copyright            : (C) 2002 by Harry Kalogirou
    email                : harkal@sylphis3d.com
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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

#include <platform/types.h>

#define THROW(msg) { \
	throw CException( msg, __FILE__, __LINE__ ); \
}

class CException : public std::runtime_error {
public: 
    CException();
    CException(const std::string &s);
    CException(const std::string &s, const S8 *file, S32 line);
    virtual ~CException() throw() {};
	
    std::string getExplanation();
    virtual const char *what() const throw() ;
protected:
    std::string mWhat;
    std::string mFileName;
    S32         mLineNumber;
};

#endif
