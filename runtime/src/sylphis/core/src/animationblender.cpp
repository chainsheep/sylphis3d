/***************************************************************************
                      animationblender.cpp  -  description
                             -------------------
    begin                : Wed Dec 18 2002
    copyright            : (C) 2002, 2003 by Harry Kalogirou
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

#include <assert.h>
#include <list>

#include <animationblender.h>
#include <skeletoninstance.h>
#include <console.h>

CAnimation::CAnimation(CSkelAnimation *sa){
    mSkelAnimation = sa;
    mTime = 0;
    mWeight = 0;
    mState = STATE_NONE;
	mClearing = false;
}

CAnimation::~CAnimation(){
}

F32 CAnimation::getDuration(){
    return mSkelAnimation->getDuration();
}

CSkelAnimation *CAnimation::getSkelAnimation(){
    return mSkelAnimation;
}

CAnimationCycle::CAnimationCycle(CSkelAnimation *sa) : CAnimation(sa) {
    setBlend(0.0, 0.0);
    mState = STATE_SYNC;
}

CAnimationCycle::~CAnimationCycle(){
}

void CAnimationCycle::setBlend(F32 fullWeight, F32 blendDelay){
    mBlendDelay = blendDelay;
    mFullWeight = fullWeight;
}

bool CAnimationCycle::update(F32 time){
   if(mBlendDelay <= time){
        mWeight = mFullWeight;
        mBlendDelay = 0.0;

        if(mWeight == 0.0 && mClearing)
            return true; //Animation ended.
    } else {
        F32 factor = time / mBlendDelay;
        mWeight = (1.0f - factor) * mWeight + factor * mFullWeight;
        mBlendDelay -= time;
    }

    if(mState == STATE_ASYNC){
        mTime += time;
        if(mTime >= mSkelAnimation->getDuration()){
            mTime = fmod(mTime, mSkelAnimation->getDuration());
        }
    }

    return false;
}

//-----------------------------

CAnimationAction::CAnimationAction(CSkelAnimation *sa) : CAnimation(sa) {
    mState = STATE_SYNC;
}

CAnimationAction::~CAnimationAction(){
}

void CAnimationAction::execute(F32 delayIn, F32 delayOut){
	mDelayIn = delayIn;
	mDelayOut = delayOut;
	mState = STATE_IN;
}

bool CAnimationAction::update(F32 time){
	mTime += time;
	if(mState == STATE_IN){
		if(mTime < mDelayIn){
			mWeight = mTime / mDelayIn;
		} else {
			mState = STATE_STEADY;
			mWeight = 1.0f;
		}	
	}
	else if(mState == STATE_STEADY){
		if(mTime >= mSkelAnimation->getDuration() - mDelayOut)
		    mState = STATE_OUT;
 	}
	else if(mState == STATE_OUT){
		F32 duration = mSkelAnimation->getDuration();
		if(mTime < duration){
			mWeight = ( duration - mTime ) / mDelayOut;
		} else {
			mWeight = 0.0f;
			return true;
		}
	}

	return false;
}

//-----------------------------

CAnimationBlender::CAnimationBlender(){
}

CAnimationBlender::~CAnimationBlender(){
}

void CAnimationBlender::addAnimationCycle(CAnimationCycle *a){
    mAnimationCycles.push_front(a);
}

void CAnimationBlender::addAnimationAction(CAnimationAction *a){
	mAnimationActions.push_front(a);
}

void CAnimationBlender::update(F32 time){
    if(mAnimationDuration == 0.0){
        mAnimationTime = 0.0;
    } else {
        mAnimationTime += time;
        if(mAnimationTime >= mAnimationDuration){
            mAnimationTime = fmod(mAnimationTime, mAnimationDuration);
        }
    }

	AnimationActionList::iterator action;
	action = mAnimationActions.begin();

	while(action != mAnimationActions.end()){
		if((*action)->update(time)){
			action = mAnimationActions.erase(action);
			wake();
			continue;
		}
		action++;
	}

    F32 accumulatedWeight = 0.0;
    F32 accumulatedDuration = 0.0;
    
    AnimationCycleList::iterator i;
    i = mAnimationCycles.begin();
   
    while(i != mAnimationCycles.end()){
        if((*i)->update(time)){
            i = mAnimationCycles.erase(i); 
            continue;
        }
        
        if((*i)->getState() == CAnimation::STATE_SYNC){
            accumulatedWeight += (*i)->getWeight();
            accumulatedDuration += (*i)->getWeight() * (*i)->getDuration();
        }

        i++;
    }

    if(accumulatedWeight > 0.0f) {
        mAnimationDuration = accumulatedDuration / accumulatedWeight;
    } else {
        mAnimationDuration = 0.0f;
    }    
}

F32 CAnimationBlender::getAnimWeight(const std::string &name){
	AnimationCycleList::iterator i;

	for(i = mAnimationCycles.begin() ; i != mAnimationCycles.end() ; i++){
		if((*i)->getName() == name){
			return (*i)->getWeight();
		}
	}
	return -1.0; //return -1 if threre is no animation by name "name"
}

void CAnimationBlender::blendCycle(CSkelAnimation *anim, const std::string &name, F32 weight, F32 delay){
    assert(anim);

    CAnimationCyclePtr ac = new CAnimationCycle(anim);
	ac->setName(name);
    ac->setBlend(weight, delay);
    addAnimationCycle(ac);
}

void CAnimationBlender::weightCycle(const std::string &name, F32 weight, F32 delay){
	AnimationCycleList::iterator i;

	for(i = mAnimationCycles.begin() ; i != mAnimationCycles.end() ; i++){
		if((*i)->getName() == name){
			(*i)->setBlend(weight, delay);
			return;
		}
	}
}

void CAnimationBlender::clearCycle(const std::string &name, F32 delay){
	AnimationCycleList::iterator i;

	for(i = mAnimationCycles.begin() ; i != mAnimationCycles.end() ; i++){
		if((*i)->getName() == name){
			(*i)->setBlend(0.0, delay);
			(*i)->setClearing(true);
			return;
		}
	}
}

void CAnimationBlender::clearAllCycle(F32 delay){
	AnimationCycleList::iterator i;

	for(i = mAnimationCycles.begin() ; i != mAnimationCycles.end() ; i++){
		(*i)->setBlend(0.0, delay);
	}
}

void CAnimationBlender::executeAction(CSkelAnimation *anim, const std::string &name, F32 delayIn, F32 delayOut){
	assert(anim);

    CAnimationActionPtr ac = new CAnimationAction(anim);
	ac->setName(name);
    ac->execute(delayIn, delayOut);
    addAnimationAction(ac);
}

#include <console.h>

void CAnimationBlender::updateSkeleton(CSkeletonInstance *s){
    assert(s);

    s->reset();

	AnimationActionList::iterator action;
	for(action = mAnimationActions.begin() ; action != mAnimationActions.end() ; action++){
		CSkelAnimation *sa = (*action)->getSkelAnimation();
		
		CSkelAnimation::BoneTrackVector &tracks = sa->getBoneTracks();
        CSkelAnimation::BoneTrackVector::iterator ti;
        for(ti = tracks.begin() ; ti != tracks.end() ; ti++){
			CQuaternion q;
            CVector3 v;
            (*ti)->getAt((*action)->getTime(), v, q);

            CBoneInstance *b = s->getBone((*ti)->getBoneId());
            b->blend((*action)->getWeight(), v, q);
		}
	}

	s->fixate();
    
    AnimationCycleList::iterator ai;
    for(ai = mAnimationCycles.begin() ; ai != mAnimationCycles.end() ; ai++){
        CSkelAnimation *sa = (*ai)->getSkelAnimation();

        F32 animTime;
        if((*ai)->getState() == CAnimation::STATE_SYNC){
            if(mAnimationDuration == 0.0){
                animTime = 0.0;
            } else {
                animTime = mAnimationTime * (*ai)->getDuration() / mAnimationDuration;
            }
        } else {
            animTime = (*ai)->getTime();
        }

        CSkelAnimation::BoneTrackVector &tracks = sa->getBoneTracks();
        CSkelAnimation::BoneTrackVector::iterator ti;
		//gcon.printf("-- %f\n", (*ai)->getWeight());
        for(ti = tracks.begin() ; ti != tracks.end() ; ti++){
            CQuaternion q;
            CVector3 v;
            (*ti)->getAt(animTime, v, q);

            CBoneInstance *b = s->getBone((*ti)->getBoneId());
            b->blend((*ai)->getWeight(), v, q);
        }
    }

    s->fixate();

    s->update();
}
