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
#ifndef POLYGON_CPP
#define POLYGON_CPP

#include <math.h>

#include <GL/gl.h>

#include "../entity.cpp"

const long double PI = 3.14159216535898;
const long double PI_2 = 1.5707963267949;

class Polygon : public Entity
{
	public:
		Polygon( long double iX, long double iY ) :
			Entity( iX, iY, 0 ), //{{{
			m_Radius( 1 ),
			m_NumSegments( 36 )
		{
			this->position.x = iX;
			this->position.y = iY;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		Polygon( long double iX, long double iY, long double iRadius ) :
			Entity( iX, iY, 0 ), //{{{
			m_Radius( iRadius ),
			m_NumSegments( 36 )
		{
			this->position.x = iX;
			this->position.y = iY;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		Polygon( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue ) :
			Entity( iX, iY, 0 ), //{{{
			m_Radius( iRadius ),
			m_NumSegments( 36 )
		{
			this->position.x = iX;
			this->position.y = iY;
			Color( iRed, iGreen, iBlue, 1.0f );
		} //}}}

		Polygon( long double iX, long double iY, long double iRadius, long double iRed, long double iGreen, long double iBlue, long double iAlpha ) :
			Entity( iX, iY, 0 ), //{{{
			m_Radius( iRadius ),
			m_NumSegments( 36 )
		{
			this->position.x = iX;
			this->position.y = iY;
			Color( iRed, iGreen, iBlue, iAlpha );
		} //}}}

		void Draw( long double m_Zoom = 1 )
		{ //{{{
			glColor4f( Red(), Green(), Blue(), Alpha() );
			glPolygonMode( GL_FRONT, GL_FILL );
			glBegin( GL_POLYGON );
				long double delTheta = 2 * PI / (long double)( NumSegments() );
				long double theta = 0;
				for( unsigned int segment = 0; segment < NumSegments(); ++segment )
				{
					theta = segment * delTheta;
					glVertex2f( Radius() * cos( theta ) + position.x,
								Radius() * sin( theta ) + position.y );
				}
			glEnd();
		} //}}}

		/// {G,S}etter for m_NumSegments
		unsigned int NumSegments() //{{{
		{
			return m_NumSegments;
		}
		void NumSegments( unsigned int nNumSegments )
		{
			m_NumSegments = nNumSegments;
		} //}}}

		/// {G,S}etter for m_Radius
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

	private:
		long double m_Radius;
		long double m_Color[ 4 ];
		unsigned int m_NumSegments;

};

#endif // POLYGON_CPP
