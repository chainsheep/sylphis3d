/***************************************************************************
                       glrenderersystem.h  -  description
                             -------------------
    begin                : Mon Apr 4 2006
    copyright            : (C) 2006 by Harry Kalogirou
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

#ifndef _GLRENDERERSYSTEM_H_
#define _GLRENDERERSYSTEM_H_

#include <rendersystem.h>

class CGLRenderSystem : public CRenderSystem {
public:
    CGLRenderSystem();
    virtual ~CGLRenderSystem();

    virtual void startup();
    virtual void shutdown();
    virtual CRenderingView* createRenderingView();
    virtual CTexture1D*     createTexture1D();
    virtual CTexture2D*     createTexture2D();
    virtual CTexture3D*     createTexture3D();
    virtual CTextureCube*   createTextureCube();
    virtual CRenderTexture* createRenderTexture();

    virtual void pushWorldMatrix();
    virtual void popWorldMatrix();
    virtual void resetWorldMatrix();

    virtual void pushProjMatrix();
    virtual void popProjMatrix();
    virtual void resetProjMatrix();
};

#endif
