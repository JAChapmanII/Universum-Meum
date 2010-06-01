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
module particle;

import force;
import point;

class Particle
{
	public:
		this()
		{
			m_Mass = 0;
			m_Radius = 0;
			m_Point = new Point( 0, 0 );
		}

		// {G,S}etter for m_Position[ 0 ]
		float XPosition() //{{{
		{
			return m_Position[ 0 ];
		}
		void XPosition( float nXPosition )
		{
			m_Position[ 0 ] = nXPosition;
		} //}}}

		// {G,S}etter for m_Position[ 1 ]
		float YPosition() //{{{
		{
			return m_Position[ 1 ];
		}
		void YPosition( float nYPosition )
		{
			m_Position[ 1 ] = nYPosition;
		} //}}}

		// {G,S}etter for m_Velocity[ 0 ]
		float XVelocity() //{{{
		{
			return m_Velocity[ 0 ];
		}
		void XVelocity( float nXVelocity )
		{
			m_Velocity[ 0 ] = nXVelocity;
		} //}}}

		// {G,S}etter for m_Velocity[ 1 ]
		float YVelocity() //{{{
		{
			return m_Velocity[ 1 ];
		}
		void YVelocity( float nYVelocity )
		{
			m_Velocity[ 1 ] = nYVelocity;
		} //}}}

		// {G,S}etter for m_Acceleration[ 0 ]
		float XAcceleration() //{{{
		{
			return m_Acceleration[ 0 ];
		}
		void XAcceleration( float nXAcceleration )
		{
			m_Acceleration[ 0 ] = nXAcceleration;
		} //}}}

		// {G;,S}etter for m_Acceleration[ 1 ]
		float YAcceleration() //{{{
		{
			return m_Acceleration[ 1 ];
		}
		void YAcceleration( float nYAcceleration )
		{
			m_Acceleration[ 1 ] = nYAcceleration;
		} //}}}

	protected:
		float m_Mass;
		float m_Radius;

		float[ 2 ] m_Position;
		float[ 2 ] m_Velocity;
		float[ 2 ] m_Acceleration;

		Point m_Point;

		Force m_Force;

	private:

}
