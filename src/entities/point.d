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
module point;

import derelict.opengl.gl;

import entity;

class Point : Entity
{
	public:
		this( float iX, float iY )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = 1;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		this( float iX, float iY, float iRadius )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = iRadius;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		this( float iX, float iY, float iRadius, float iRed, float iGreen, float iBlue )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = iRadius;
			Color( iRed, iGreen, iBlue, 1.0f );
		} //}}}

		this( float iX, float iY, float iRadius, float iRed, float iGreen, float iBlue, float iAlpha )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = iRadius;
			Color( iRed, iGreen, iBlue, iAlpha );
		} //}}}

		override void Draw()
		{ //{{{
			glPointSize( Radius );
			glColor4f( Red, Green, Blue, Alpha );
			glBegin( GL_POINTS );
			glVertex2f( X, Y );
			glEnd();
		} //}}}

		// {G,S}etter for m_Radius
		float Radius() //{{{
		{
			return m_Radius;
		}
		void Radius( float nRadius )
		{
			m_Radius = nRadius;
		} //}}}

		void Color( float nRed, float nGreen, float nBlue, float nAlpha )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
			m_Color[ 3 ] = nAlpha;
		} //}}}

		void Color( float nRed, float nGreen, float nBlue )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 0 ]
		float Red() //{{{
		{
			return m_Color[ 0 ];
		}
		void Red( float nRed )
		{
			m_Color[ 0 ] = nRed;
		} //}}}

		// {G,S} for m_Color[ 1 ]
		float Green() //{{{
		{
			return m_Color[ 1 ];
		}
		void Green( float nGreen )
		{
			m_Color[ 1 ] = nGreen;
		} //}}}

		// {G,S} for m_Color[ 2 ]
		float Blue() //{{{
		{
			return m_Color[ 2 ];
		}
		void Blue( float nBlue )
		{
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 3 ]
		float Alpha() //{{{
		{
			return m_Color[ 3 ];
		}
		void Alpha( float nAlpha )
		{
			m_Color[ 3 ] = nAlpha;
		} //}}}

	protected:
		float m_Radius;
		float[ 4 ] m_Color;

	private:

}
