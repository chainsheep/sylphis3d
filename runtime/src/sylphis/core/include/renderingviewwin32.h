/***************************************************************************
                          renderingviewwin32.h  -  description
                             -------------------
    begin                : Thu Mar 21 2002
    copyright            : (C) 2002 by Harry Kalogirou
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

#ifndef RENDERINGVIEWWIN32_H
#define RENDERINGVIEWWIN32_H

#include <renderingview.h>
#include <inputdevice.h>

class CRenderingViewWin32 : public CRenderingView {
public:
	CRenderingViewWin32();
	virtual ~CRenderingViewWin32();

	virtual void startup();
	virtual void shutdown();

	virtual void setDimentions(const std::pair<S32,S32> &d);
	
	virtual void swapBuffers();
	
	virtual void handleEvents();

	virtual S32 getPointerX();
	virtual S32 getPointerY();
	virtual void getPointerXY(S32 &x, S32 &y);
	virtual void setPointer(S32 x, S32 y);
	virtual void getPointerCenter(S32 &x, S32 &y);
	virtual void centerPointer();
protected:
	void changeResolution(S32 width, S32 height, S32 bpp);
	void createWindow();
	void destroyWindow();

	BOOL SetupPixelFormat(HDC hdc);
	
	HWND hwnd; 
	HDC   hdc; 
	HGLRC hrc; 
};


#endif
