/***************************************************************************
                        soundbuffer.cpp  -  description
                             -------------------
    begin                : Fri Jun 6 2003
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

#include <sound/soundbuffer.h>

CSoundBuffer::CSoundBuffer(bool streaming){
	mStreaming = streaming;
	mNextBuffer = 0;
}

CSoundBuffer::~CSoundBuffer(){
	alDeleteBuffers(mBuffers.size(), &mBuffers[0]);
}

ALuint CSoundBuffer::getBuffer(){
	return mBuffers[mNextBuffer];
}

#include <console.h>
static ALvoid alError(char *szText){
	ALint error;
	if(error = alGetError() != AL_NO_ERROR)
		gcon.printf("%s%s", szText, 0);
}
ALuint CSoundBuffer::newBuffer(){
	ALuint buffer;
	alGenBuffers(1, &buffer);
	alError("gen buffers ");
	mBuffers.push_back(buffer);
	return buffer;
}

bool CSoundBuffer::isStreaming(){
	return mStreaming;
}
