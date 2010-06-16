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

#include <GL/gl.h>

#include "../entity.cpp"

class Point : Entity
{
	public:
		Point( long double iX, long double iY )
		{ //{{{
			this->position.x = iX;
			this->position.y = iY;
			Radius( 1 );
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		Point( long double iX, long double iY, long double iRadius )
		{ //{{{
			this->position.x = iX;
			this->position.y = iY;
			Radius( iRadius );
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		Point( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue )
		{ //{{{
			this->position.x = iX;
			this->position.y = iY;
			Radius( iRadius );
			Color( iRed, iGreen, iBlue, 1.0f );
		} //}}}

		Point( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue, long double iAlpha )
		{ //{{{
			this->position.x = iX;
			this->position.y = iY;
			Radius( iRadius );
			Color( iRed, iGreen, iBlue, iAlpha );
		} //}}}

		void Draw( long double m_Zoom = 1 )
		{ //{{{
			// glPointSize takes a diameter
			glPointSize( Radius() * 2 * m_Zoom );
			glColor4f( Red(), Green(), Blue(), Alpha() );
			glBegin( GL_POINTS );
			glVertex2f( this->position.x, this->position.y );
			glEnd();
		} //}}}

		// {G,S}etter for m_Radius
		long double Radius() //{{{
		{
			return m_Radius;
		}
		void Radius( long double nRadius )
		{
			m_Radius = nRadius;
		} //}}}

		void Color( long double nRed, long double nGreen, long double nBlue, long double nAlpha )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
			m_Color[ 3 ] = nAlpha;
		} //}}}

		void Color( long double nRed, long double nGreen, long double nBlue )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 0 ]
		long double Red() //{{{
		{
			return m_Color[ 0 ];
		}
		void Red( long double nRed )
		{
			m_Color[ 0 ] = nRed;
		} //}}}

		// {G,S} for m_Color[ 1 ]
		long double Green() //{{{
		{
			return m_Color[ 1 ];
		}
		void Green( long double nGreen )
		{
			m_Color[ 1 ] = nGreen;
		} //}}}

		// {G,S} for m_Color[ 2 ]
		long double Blue() //{{{
		{
			return m_Color[ 2 ];
		}
		void Blue( long double nBlue )
		{
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 3 ]
		long double Alpha() //{{{
		{
			return m_Color[ 3 ];
		}
		void Alpha( long double nAlpha )
		{
			m_Color[ 3 ] = nAlpha;
		} //}}}

	protected:
		long double m_Radius;
		long double m_Color[ 4 ];

	private:

}
