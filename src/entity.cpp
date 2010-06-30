/* {{{
	Copyright 2010 Jeff Chapman (and Nolan Brown)

	This file is a part of Universum Meum

	Universum Meum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Universum Meum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Universum Meum.  If not, see <http://www.gnu.org/licenses/>.

*/// }}}
#ifndef ENTITY_CPP
#define ENTITY_CPP

#include "vector.cpp"

/// An object that should be allowed to be drawn to the screen
class Entity
{
	public:
		/// Draw object to screen using OpenGL commands, zoom is with reference to default
		virtual void Draw( long double m_Zoom = 1 )
		{
		}

		/// Update the object in anyway needed, called each frame
		virtual void Update()
		{
		}

		/// Position of Entity in whatever coordinate system it chooses
		Vector< long double > position;

		/// Default constructor
		Entity() :
			position()
		{
		}

		/// Construct with an initial position
		Entity( long double iX, long double iY, long double iZ ) :
			position( iX, iY, iZ )
		{
		}

		/// Copy consturctor
		Entity( Entity const& r ) :
			position( r.position )
		{
		}

		/// Consturctor that initializes this->position to an input Vector
		Entity( Vector< long double > iPosition ) :
			position( iPosition )
		{
		}

		/// Default destructor made virtual
		virtual ~Entity()
		{
		}

	protected:

	private:

};

#endif // ENTITY_CPP
