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

class Point : Entity
{
	public:
		this( uint iX, uint iY )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = 1;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		this( uint iX, uint iY, uint iRadius )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = iRadius;
			Color( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		this( uint iX, uint iY, uint iRadius, uint iRed, uint iGreen, uint iBlue )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = iRadius;
			Color( iRed, iGreen, iBlue, 1.0f );
		} //}}}

		this( uint iX, uint iY, uint iRadius, uint iRed, uint iGreen, uint iBlue, uint iAlpha )
		{ //{{{
			X = iX;
			Y = iY;
			Radius = iRadius;
			Color( iRed, iGreen, iBlue, iAlpha );
		} //}}}

		void Draw()
		{ //{{{
			glPushMatrix();
			glPointSize( Radius );
			glColor4f( Red, Green, Blue, Alpha );
			glBegin( GL_POINTS );
			glVertex2f( cast( float )( X ) + 0.5f, cast( float )( Y ) + 0.5f );
			glEnd();
			glPopMatrix();
		} //}}}

		// {G,S}etter for m_Radius
		uint Radius() //{{{
		{
			return Radius;
		}
		void Radius( uint nRadius )
		{
			m_Radius = nRadius;
		} //}}}

		void Color( uint nRed, uint nGreen, uint nBlue, uint nAlpha )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
			m_Color[ 3 ] = nAlpha;
		} //}}}

		void Color( uint nRed, uint nGreen, uint nBlue )
		{ //{{{
			m_Color[ 0 ] = nRed;
			m_Color[ 1 ] = nGreen;
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 0 ]
		uint Red() //{{{
		{
			return m_Color[ 0 ];
		}
		void Red( uint nRed )
		{
			m_Color[ 0 ] = nRed;
		} //}}}

		// {G,S} for m_Color[ 1 ]
		uint Blue() //{{{
		{
			return m_Color[ 1 ];
		}
		void Blue( uint nBlue )
		{
			m_Color[ 1 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 2 ]
		uint Blue() //{{{
		{
			return m_Color[ 2 ];
		}
		void Blue( uint nBlue )
		{
			m_Color[ 2 ] = nBlue;
		} //}}}

		// {G,S} for m_Color[ 3 ]
		uint Alpha() //{{{
		{
			return m_Color[ 3 ];
		}
		void Alpha( uint nAlpha )
		{
			m_Color[ 3 ] = nAlpha;
		} //}}}

	protected:
		uint m_Radius;
		float[ 4 ] m_Color;

	private:

}
