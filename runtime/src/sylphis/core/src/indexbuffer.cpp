/***************************************************************************
                    indexbuffer.cpp  -  description
                            -------------------
                begin                : Sun Sep 4 2005
                copyright            : (C) 2005 by Harry Kalogirou
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


#include <indexbuffer.h>


CIndexBuffer::CIndexBuffer(){

}

CIndexBuffer::~CIndexBuffer(){

}

void CIndexBuffer::allocate(U32 size, eUsageType usage, bool system, void *data) {
    mSize = size;
    mUsage = usage;
    mLocked = false;
    //system = true;
    //GLEW_ARB_vertex_buffer_object = false;
    if(GLEW_ARB_vertex_buffer_object && !system){
        mSystemMemory = false;
        checkGLError();
        glGenBuffersARB(1, &mBufferId);
        checkGLError();
        GLenum use;
        switch (usage) {
            case STATIC:
                use = GL_STATIC_DRAW_ARB;
                break;
            case DYNAMIC:
                use = GL_STREAM_DRAW_ARB;
                break;
        }
        activate();
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mSize, data, use);checkGLError();
        deactivate();
    } else {
        mSystemMemory = true;
        mSysAddr = malloc(mSize);
        if(data){
            memcpy(mSysAddr, data, mSize);
        }
    }
}

void *CIndexBuffer::_map(eOperation op){
    GLenum oper;
    switch (op) {
        case WRITE_ONLY:
            oper = GL_WRITE_ONLY_ARB;
            break;
        case READ_ONLY:
            oper = GL_READ_ONLY_ARB;
            break;
        case READ_WRITE:
            oper = GL_READ_WRITE_ARB;
            break;
        default:
            oper = GL_READ_WRITE_ARB;
    }
    return glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, oper);
}

void CIndexBuffer::_unmap(){
    glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);checkGLError();
}

void CIndexBuffer::_uploadData(void *data, U32 offset, U32 size){
    glBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, offset, size, data); checkGLError();
}

void CIndexBuffer::_activate(){
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, mBufferId); checkGLError();
};

void CIndexBuffer::_deactivate(){
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0); checkGLError();
};
