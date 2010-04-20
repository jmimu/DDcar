//      gameobject.h
//      
//      Copyright 2010  <jmmuller@myhost>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#ifndef CUSTOMCONTACTLISTENER_H
#define  CUSTOMCONTACTLISTENER_H


#include <Box2D.h>

/* various classes to manage contact points
 * http://www.box2d.org/wiki/index.php?title=Buffering_ContactPoints (for version 2.0.1)
 * */


class CustomContactListener : public b2ContactListener {
public:
	CustomContactListener(){};
	/*void Add(const b2ContactPoint *point);
	void Remove(const b2ContactPoint *point);
	void Persist(const b2ContactPoint* point);
	void Result(const b2ContactResult* point);*/

	virtual ~CustomContactListener() {};
	virtual void BeginContact(b2Contact* contact) { B2_NOT_USED(contact); }
	virtual void EndContact(b2Contact* contact) { B2_NOT_USED(contact); }
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){};
	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}
};



#endif /*  CUSTOMCONTACTLISTENER_H */ 
