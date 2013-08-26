/***************************************************************************
                         imagefile.h  -  description
                             -------------------
    begin                : Fri Mar 15 2002
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

#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <string>
using namespace std;

#include "vfs.h"
#include "pointer.h"

#define local_min(a,b) ((a) < (b) ? (a) : (b))
#define local_max(a,b) ((a) > (b) ? (a) : (b))

typedef unsigned char ColorValue ;

class CPixel {
public:
    CPixel() : r(0), g(0), b(0), a(0) {} ;
    CPixel(ColorValue r, ColorValue g, ColorValue b, ColorValue a) : r(r), g(g), b(b), a(a) {} ;
    CPixel operator+(const CPixel &p) const {
        S32 nr,nb,ng,na;
        nr = local_min(r + p.r, 255);
        ng = local_min(g + p.g, 255);
        nb = local_min(b + p.b, 255);
        na = local_min(a + p.a, 255);
		return CPixel(nr, nb, ng, na);
	}
    CPixel operator-(const CPixel &p) const {
        S32 nr,nb,ng,na;
        nr = local_max(r - p.r, 0);
        ng = local_max(g - p.g, 0);
        nb = local_max(b - p.b, 0);
        na = local_max(a - p.a, 0);
		return CPixel(nr, nb, ng, na);
	}
    CPixel operator*(const F32 f) const {
        S32 nr,nb,ng,na;
        nr = (ColorValue)local_max(local_min((F32)r * f, 255.0), 0);
        ng = (ColorValue)local_max(local_min((F32)g * f, 255.0), 0);
        nb = (ColorValue)local_max(local_min((F32)b * f, 255.0), 0);
        na = (ColorValue)local_max(local_min((F32)a * f, 255.0), 0);
		return CPixel(nr, nb, ng, na);
	}
    static CPixel lighten(const CPixel &a, const CPixel &b) {
        return CPixel(local_max(a.r, b.r), local_max(a.g, b.g), local_max(a.b, b.b), local_max(a.a, b.a));
    }
    static CPixel darken(const CPixel &a, const CPixel &b) {
        return CPixel(local_min(a.r, b.r), local_min(a.g, b.g), local_min(a.b, b.b), local_min(a.a, b.a));
    }
    static CPixel normalsAdd(const CPixel &a, const CPixel &b);
    ColorValue r, g, b, a;
};

SmartPointer(CImage);
class CImage : public CRefObject {
public:
	enum EColorFormat {
		GRAYSCALE,
		RGB,
		RGBA,
		NORMAL
	};
    enum EMixType {
        ADD,
        SUB,
        MUL
    };

	CImage();
	virtual ~CImage();
	
	virtual void            process(void *data, S32 size) = 0;
	virtual void            scale(S32 w, S32 h) = 0;
	virtual S32             getWidth() = 0;
	virtual S32             getHeight() = 0;
    virtual void            setWidth(F32 w) = 0;
	virtual void setHeight(F32 h) = 0;
	virtual EColorFormat getColorFormat() = 0;
    virtual void setColorFormat(EColorFormat f) = 0;
    virtual void create() = 0;
	virtual void setConvertParam(F32 p1) = 0;
	virtual void convertTo(EColorFormat f) = 0;
    virtual void getPixel(CPixel &p, S32 x, S32 y) = 0;
    virtual void setPixel(const CPixel &p, S32 x, S32 y) = 0;
	virtual void *getImageData() = 0;
	virtual S32 getImageDataSize() = 0;

    virtual void makeBlack();


    static CImage *mix(CImage *a, CImage *b, EMixType type);
};

SmartPointer(CImageBase);
class CImageBase : public CImage {
public:
	CImageBase();
	virtual ~CImageBase();
	
	virtual void process(void *data, S32 size);
	virtual void scale(S32 w, S32 h);
	virtual S32 getWidth();
	virtual S32 getHeight();
    virtual void setWidth(F32 w);
	virtual void setHeight(F32 h);
	virtual EColorFormat getColorFormat();
    virtual void setColorFormat(EColorFormat f);
    virtual void create();
	virtual void setConvertParam(F32 p1);
	virtual void convertTo(EColorFormat f);
    virtual void getPixel(CPixel &p, S32 x, S32 y);
    virtual void setPixel(const CPixel &p, S32 x, S32 y);
	virtual void *getImageData();
	virtual S32 getImageDataSize();
protected:
	virtual void allocateImageData(S32 size);
	virtual void freeImageData();

	S32 width;
	S32 height;
	EColorFormat mColorFormat;
	S32 imageDataSize;
	F32 param1;
	void *imageData;
};

SmartPointer(CImageDummy);
class CImageDummy : public CImageBase {
public:
	CImageDummy();
	virtual ~CImageDummy();

	virtual void process(void *data, S32 size);
};

SmartPointer(CImageTGA);
class CImageTGA : public CImageBase {
public:
	CImageTGA();
	virtual ~CImageTGA();

	virtual void process(void *data, S32 size);
};

SmartPointer(CImagePNG);
class CImagePNG : public CImageBase {
public:
	CImagePNG();
	virtual ~CImagePNG();

	virtual void process(void *data, S32 size);
};

#ifdef __GNUC__
#define boolean S32
#endif

struct jpeg_decompress_struct;

SmartPointer(CImageJPEG);
class CImageJPEG : public CImageBase {
public:
	CImageJPEG();
	virtual ~CImageJPEG();

	virtual void process(void *data, S32 size);
protected:
	static void jpg_noop(jpeg_decompress_struct * cinfo);
	static boolean jpg_fill_input_buffer(jpeg_decompress_struct * cinfo);
	static void jpg_skip_input_data(jpeg_decompress_struct * cinfo, long num_bytes);
	static void jpeg_mem_src(jpeg_decompress_struct * cinfo, byte *mem, S32 len);
};
#ifdef __GNUC__
#undef boolean
#endif

SmartPointer(CImageLoaderPtr);
class CImageLoader {
public:
	static CImage *loadImage(CFile &file);
};

#endif
