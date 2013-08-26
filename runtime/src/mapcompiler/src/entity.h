/***************************************************************************
                          entity.h  -  description
                             -------------------
    begin                : Sat Jun 8 2002
    copyright            : (C) 2002 by Vassili Tenente
                           (C) 2002-2005 Harry Kalogirou (harkal@gmail.com)
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
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <map>
#include <vector>

#include "brush.h"

using namespace std;

class CEntity {
public:
	CEntity();
	~CEntity();
	string getProperty(const string & prop);
	CVector3 getAsVector(const string & prop);
	void setProperty(const string & prop, const string & value);
	int getNoProperties();

	CPolygon *getLargerPolygon();
	void appendStructural(list<CPolygon *> *polygonList);
	void appendStructuralAndVisible(list<CPolygon *> *polygonList);

	void callCreatePolygons();
	void addBrush(CBrush & b);
	CBrush & getBrush(const int &id);
	vector < CBrush > &getBrushes(void);
	int getBrushesNo(void);
	CBrush & getLastBrush(void);
	string asString();
	bool isMainEntity();
	bool isPortalEntity();
	bool isModelEntity();
	bool isLeakEntity();

	CBrush &operator[] (const int index){
		return brushes[index];
	};
	string &operator[] (const string & key){
		return props[key];
	}

	vector<CBrush>::iterator bBegin(){ return brushes.begin(); }
	vector<CBrush>::iterator bEnd(){ return brushes.end(); }

	void setLeakEntity(CShaderFlags *leakFlags);
	void moveEntity(CVector3 &middle);
	void debug(void);
	void appendChopped( list<CPolygon *> *polygonList );
	void appendChoppedAndStructural( list<CPolygon *> *polygonList );
	void appendChoppedStructuralAndVisible( list<CPolygon *> *polygonList );
private:
	map < string, string > props;
	vector < CBrush > brushes;
};

#endif 
