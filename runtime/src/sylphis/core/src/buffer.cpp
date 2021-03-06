/***************************************************************************
                         buffer.cpp  -  description
                            -------------------
                begin                : Sun Sep 4 2005
                copyright            : (C) 2005 by Harry Kalogirou
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

#include <buffer.h>
#include <gutil.h>

GLuint CBuffer::mActiveBuffer = 0;

CBuffer::CBuffer(){
    mSize = 0;
    mMapAddress = 0;
}

CBuffer::~CBuffer(){
    if(!mSize)
        return;
    if(!mSystemMemory){
        unmap();
        glDeleteBuffersARB(1, &mBufferId);
        checkGLError();
    } else {
        free(mSysAddr);
    }
}

void CBuffer::activate(){
    if(mActiveBuffer == mBufferId)
        return;
    if(mSystemMemory)
        return;
    _activate();
    checkGLError();
    mActiveBuffer = mBufferId;
};

void CBuffer::deactivate(){
    if(mSystemMemory)
        return;
    assert(mActiveBuffer == mBufferId);
    _deactivate();
    checkGLError();
    mActiveBuffer = 0;
};

void *CBuffer::map(eOperation op){
    if(mMapAddress)
        return mMapAddress;

    if(!mSystemMemory){
        activate();
        mMapAddress = _map(op);
        assert(mMapAddress);
        checkGLError();
        deactivate();
    } else {
        mMapAddress = mSysAddr;
    }

    return mMapAddress;
}

void CBuffer::unmap(){
    if(!mMapAddress)
        return;
    if(mSystemMemory)
        return;
    mMapAddress = 0;
    activate();
    _unmap();
    checkGLError();
    deactivate();
    if(mUsage == STATIC)
        mLocked = true;
}

void CBuffer::uploadData(void *data, U32 offset, U32 size){
    if(mSystemMemory)
        memcpy(mSysAddr, data, size);
    else {
        assert(mMapAddress == 0);
        activate();
        _uploadData(data, offset, size);
        deactivate();
    }
}

void *CBuffer::_map(eOperation op){
    return 0;
}

void CBuffer::_unmap(){
}

void CBuffer::_uploadData(void *data, U32 offset, U32 size){

}

void CBuffer::_activate(){

};

void CBuffer::_deactivate(){

};

