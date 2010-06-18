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

class Entity
{
	public:
		virtual void Draw( long double m_Zoom = 1 )
		{
		}

		virtual void Update()
		{
		}

		Vector< long double > position;

		Entity() :
			position()
		{
		}

		Entity( long double iX, long double iY, long double iZ ) :
			position( iX, iY, iZ )
		{
		}

		Entity( Entity const& r ) :
			position( r.position )
		{
		}

		Entity( Vector< long double > iPosition ) :
			position( iPosition )
		{
		}

		virtual ~Entity()
		{
		}

	private:

};

#endif // ENTITY_CPP
