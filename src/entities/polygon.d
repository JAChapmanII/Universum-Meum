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
module polygon;

import derelict.opengl.gl;

import entity;

import tango.math.Math;

class Polygon : Entity
{
	public:
		this( real iX, real iY )
		{ //{{{
			XPosition = iX;
			YPosition = iY;
			Radius = 1;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		this( real iX, real iY, real iRadius )
		{ //{{{
			XPosition = iX;
			YPosition = iY;
			Radius = iRadius;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		this( real iX, real iY, real iRadius, real iRed, real iGreen, real iBlue )
		{ //{{{
			XPosition = iX;
			YPosition = iY;
			Radius = iRadius;
			Color( iRed, iGreen, iBlue, 1.0f );
		} //}}}

		this( real iX, real iY, real iRadius, real iRed, real iGreen, real iBlue, real iAlpha )
		{ //{{{
			XPosition = iX;
			YPosition = iY;
			Radius = iRadius;
			Color( iRed, iGreen, iBlue, iAlpha );
		} //}}}

		override void Draw( real m_Zoom = 1 )
		{ //{{{
			glColor4f( Red, Green, Blue, Alpha );
			glPolygonMode( GL_FRONT, GL_FILL );
			glBegin( GL_POLYGON );
				real delTheta = 2 * PI / cast( real )( NumSegments );
				real theta = 0;
				for( uint segment = 0; segment < NumSegments; ++segment )
				{
					theta = segment * delTheta;
					glVertex2f( Radius * cos( theta ) + XPosition,
								Radius * sin( theta ) + YPosition );
				}
			glEnd();
		} //}}}

		/// {G,S}etter for m_NumSegments
		uint NumSegments() //{{{
		{
			return m_NumSegments;
		}
		void NumSegments( uint nNumSegments )
		{
			m_NumSegments = nNumSegments;
		} //}}}

		/// {G,S}etter for m_Radius
		real Radius() //{{{
		{
			return m_Radius;
		}
		void Radius( real nRadius )
		{
			m_Radius = nRadius;
		} //}}}

		void Color( real nRed, real nGreen, real nBlue, real nAlpha )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
			m_Color[ 3 ] = nAlpha;
		} //}}}

		void Color( real nRed, real nGreen, real nBlue )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 0 ]
		real Red() //{{{
		{
			return m_Color[ 0 ];
		}
		void Red( real nRed )
		{
			m_Color[ 0 ] = nRed;
		} //}}}

		// {G,S} for m_Color[ 1 ]
		real Green() //{{{
		{
			return m_Color[ 1 ];
		}
		void Green( real nGreen )
		{
			m_Color[ 1 ] = nGreen;
		} //}}}

		// {G,S} for m_Color[ 2 ]
		real Blue() //{{{
		{
			return m_Color[ 2 ];
		}
		void Blue( real nBlue )
		{
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 3 ]
		real Alpha() //{{{
		{
			return m_Color[ 3 ];
		}
		void Alpha( real nAlpha )
		{
			m_Color[ 3 ] = nAlpha;
		} //}}}

	protected:
		real m_Radius;
		real[ 4 ] m_Color;
		uint m_NumSegments = 360;

	private:

}
