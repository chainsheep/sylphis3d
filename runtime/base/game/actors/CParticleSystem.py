"""
This file is part of the "Sylphis" 3D engine
Copyright (c) 2002 - 2007 by Harry Kalogirou

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
"""
import sys, sylphis
from string import *
from CSimpleActor import *
from util import manage
import pyui

class CParticleSystem(CSimpleActor):
    __classname__ = 'particle_system'
    __desc__ = 'A particle system'
    __actortype__ = 'e'
    __specs__ = [
        {'name':'emitter', 'doc':'The emitting point of the particle system'}
    ]
    
    emitter = ''
    
    def __init__(self, *args):
        CSimpleActor.__init__(self, *args)

    def join(self, ent):
        CSimpleActor.join(self, ent)
        
        from core.particlesystem import manager
        
        self.partdef = manager.registerParticleSystem(self.particledef)
       	
        m = manage(sylphis.CRenderableMultiMesh, self.mScene)
        p = manage(sylphis.CParticleSystem)
        
        p.setDefinition(self.partdef)
        p.setDefaultShader(self.partdef.getMaterial())
        p.setDieAfterUse(False)
        self.mScene.addParticleSystem(p)
        m.getBound().setBounds(sylphis.CVector3(-1000, -1000, -1000), sylphis.CVector3(1000, 1000, 1000))
        m.addMesh(p)
        	
        m.setPosition(self.origin)
        
        self.node = m
        self.particleSystem = p

    def start(self):
        CSimpleActor.start(self)
        if self.emitter != '':
            emitter = self.mCont.actors.getActorByName(self.emitter)
            if emitter != None:
                self.particleSystem.setEmitter(emitter.node)

    def Action_fire(self, other):
        print "FIRE"
        self.particleSystem.fire()
        	
        	

        

