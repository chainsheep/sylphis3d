/***************************************************************************
                       renderersystem.h  -  description
                             -------------------
    begin                : Mon Apr 4 2006
    copyright            : (C) 2006 by Harry Kalogirou
    email                : harkal@sylphis3d.com
   ***************************************************************************
    This file is part of "Sylphis3D Game Engine".

    "Sylphis3D Game Engine" is free software; you can redistribute it and/or 
    modify it under the terms of the GNU General Public License as 
    published by the Free Software Foundation; either version 2 of the 
    License, or (at your option) any later version, 
    plus a special exception:
      Linking "Sylphis3D Game Engine" statically or dynamically with other 
    modules is making a combined work based on this library. Thus, the 
    terms and conditions of the GNU General Public License cover the whole 
    combination. As a special exception, the copyright holders of this 
    library give you permission to link this library with independent 
    modules to produce an executable, regardless of the license terms of 
    these independent modules, and to copy and distribute the resulting 
    executable under terms of your choice, provided that you also meet, 
    for each linked independent module, the terms and conditions of the 
    license of that module. An independent module is a module which is 
    not derived from or based on this program. If you modify this program,
    you may extend this exception to your version of the library, but you 
    are not obligated to do so. If you do not wish to do so, delete this 
    exception statement from your version.

    "Sylphis3D Game Engine" is distributed in the hope that it will be 
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with "Sylphis3D Game Engine"; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 ***************************************************************************/

#ifndef _RENDERERSYSTEM_H_
#define _RENDERERSYSTEM_H_

class CRenderingView;
class CTexture1D;
class CTexture2D;
class CTexture3D;
class CTextureCube;
class CRenderTexture;

class CRenderSystem {
public:
    CRenderSystem();
    virtual ~CRenderSystem();

    virtual void startup() = 0;
    virtual void shutdown() = 0;
    virtual CRenderingView* createRenderingView() = 0;
    virtual CTexture1D*     createTexture1D() = 0;
    virtual CTexture2D*     createTexture2D() = 0;
    virtual CTexture3D*     createTexture3D() = 0;
    virtual CTextureCube*   createTextureCube() = 0;
    virtual CRenderTexture* createRenderTexture() = 0;

    virtual void pushWorldMatrix() = 0;
    virtual void popWorldMatrix() = 0;
    virtual void resetWorldMatrix() = 0;

    virtual void pushProjMatrix() = 0;
    virtual void popProjMatrix() = 0;
    virtual void resetProjMatrix() = 0;

	
};

extern CRenderSystem*   gRSystem;

#endif
