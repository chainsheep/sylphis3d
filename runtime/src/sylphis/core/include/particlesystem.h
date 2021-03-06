/***************************************************************************
                        particlesystem.h  -  description
                             -------------------
    begin                : Sat May 13 2006
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

#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include <renderable.h>
#include <list>
#include <interpolator.h>
#include <string>

SmartPointer(CMaterial);

class CParticle {
public:

    CVector3    mPosition;
    CVector3    mVelocity;
    CVector3    mColor;
    F32         mSizeX;
    F32         mSizeY;
    F32         mRotation;
    F32         mRotationSpeed;
    F32         mLifetime;
    F32         mTimeLived;
};

typedef struct {
    CVector4    position;
    CVector3    color;
    CTexCoord   texCoord;
} TParticleVertex;

enum EParticleType {
    PARTICLE_BILLBOARD,
    PARTICLE_TRACER
};

enum EParticleEmitterShape {
	PARTICLE_EMITTER_BOX,
	PARTICLE_EMITTER_SPHERE
};

enum EParticleSpawnDirection {
	PARTICLE_SPAWN_DIRECTION_NATURAL,
	PARTICLE_SPAWN_DIRECTION_AIMED
};

class CParticleSystemDef {
public:
    CParticleSystemDef();

	void					setMaterial(const std::string &name);
	CMaterial*				getMaterial();
	CInterpolatorF32*		getSizeEnvelope();
	CInterpolatorF32*		getAspectRatioEnvelope();
	CInterpolatorVector3*   getColorEnvelope();

    // Emmiter properties
	EParticleEmitterShape	mEmitterShape;
	CVector3				mEmitterDimensions;

	EParticleSpawnDirection	mSpawnDirection;
	F64						mSpawnDirectionVariation;
	F64						mSpawnVelocityMin;
	F64						mSpawnVelocityMax;

    F64						mEmitRate;
    F64		                mEmitTime;

    U32						mBudget;
    CVector3				mAcceleration;

    F32                     mRotation;
	F32						mRotationSpeed;

	F64						mLifeTime;

	bool					mCollitionsEnabled;
	F32						mBounce;

    CInterpolatorVector3Ptr mColorEnvelope;
    CInterpolatorF32Ptr     mSizeEnvelope;
    CInterpolatorF32Ptr     mAspectRatioEnvelope;
    
    EParticleType			mParticleType;

	CMaterialPtr			mMaterial;
};

SmartPointer(CParticleEmitter);

SmartPointer(CParticleSystem);
class CParticleSystem : public CRenderable {
public:
                            CParticleSystem();
    virtual                 ~CParticleSystem();

    virtual void            setFrame(F32 f);
    virtual void            render(CRenderer &r, const CMatrix4 &transform);
    virtual CSilhouette*    getSilhoutte(CVector3 &o);
    virtual void            renderWithShader(CRenderer &r, CMaterial *shader);

    virtual bool            update(F64 time);

    void                    setBudget(U32 count);
    U32                     getBudget();

	void                    setDieAfterUse(bool b);
    bool                    isDieAfterUse() const;

	void					setEmitter(CSceneObject *o);
	CSceneObject*			getEmitter();

	void					fire();

    void                    setDefinition(CParticleSystemDef *d){
                                mDef = d;
                                setBudget(mDef->mBudget);
                            };

    CParticleSystemDef      *getDefinition(){return mDef;};

    CParticle*              createParticle();

    typedef std::list<CParticle*> ParticleList;
protected:
    void                addParticle(U32 pos, const CParticle &p);

    // Hardware buffers
    CVertexBufferPtr    mVertexBuffer;
    CIndexBufferPtr     mElems;

    // Temp buffers
    TParticleVertex     *mSVertexBuffer;

    CSceneObjectPtr     mEmitter;
    F64                 mEmitFrac;
    F64                 mEmittingTime;

    ParticleList        mParticles;    

    U32                 mBudget;

	bool				mDieAfterUse;

    CParticleSystemDef  *mDef;
};

typedef std::list<CParticleSystemPtr> ParticleSystemList;

#endif

