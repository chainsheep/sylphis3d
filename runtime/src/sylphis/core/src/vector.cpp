/***************************************************************************
                         vector.cpp  -  description
                            -------------------
                begin                : Aug 23 2002
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
#include <vector.h>
#include <serializer.h>

const CVector3 CVector3::ZERO(0,0,0);
const CVector3 CVector3::UNIT_X(1,0,0);
const CVector3 CVector3::UNIT_Y(0,1,0);
const CVector3 CVector3::UNIT_Z(0,0,1);

void CVector3::save(CSerializer *ser) const {
	ser->writeFloat(x);
	ser->writeFloat(y);
	ser->writeFloat(z);
}

void CVector3::load(CSerializer *ser){
	x = ser->readFloat();
	y = ser->readFloat();
	z = ser->readFloat();
}

template<>
void CVector4::save(CSerializer *ser) const {
	ser->writeFloat(x);
	ser->writeFloat(y);
	ser->writeFloat(z);
	ser->writeFloat(w);
}

template<>
void CVector4::load(CSerializer *ser){
	x = ser->readFloat();
	y = ser->readFloat();
	z = ser->readFloat();
	w = ser->readFloat();
}

void CVector2::save(CSerializer *ser) const {
	ser->writeFloat(x);
	ser->writeFloat(y);
}

void CVector2::load(CSerializer *ser){
	x = ser->readFloat();
	y = ser->readFloat();
}