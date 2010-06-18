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
#ifndef POINT_HPP
#define POINT_HPP

#include <GL/gl.h>

#include "../entity.cpp"

class Point : public Entity
{
	public:
		Point( long double iX, long double iY );
		Point( long double iX, long double iY, long double iRadius );
		Point( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue );
		Point( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue, long double iAlpha );

		void Draw( long double zoom = 1 );

		void Color( long double nRed, long double nGreen, long double nBlue, long double nAlpha );
		void Color( long double nRed, long double nGreen, long double nBlue );

		// {G,S} for m_Color[ 0 ]
		long double Red();
		void Red( long double nRed );

		// {G,S} for m_Color[ 1 ]
		long double Green();
		void Green( long double nGreen );

		// {G,S} for m_Color[ 2 ]
		long double Blue();
		void Blue( long double nBlue );

		// {G,S} for m_Color[ 3 ]
		long double Alpha();
		void Alpha( long double nAlpha );

		long double radius;

	protected:
		long double m_Color[ 4 ];

};

#endif // POINT_HPP
