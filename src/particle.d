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

import tango.util.log.Log;
import tango.util.log.AppendConsole;

import force;
import entity;

Logger log;
static this()
{
	log = Log.lookup( "particle" );
	log.add( new AppendConsole() );
}

class Particle
{
	public:
		this()
		{
			m_Mass = 50.0f;
			m_Radius = 0.0f;
			Position( 0.0f, 0.0f );
			Velocity( 0.0f, 0.0f );
			Acceleration( 0.0f, 0.0f );
		}

		void Update()
		{
			XVelocity = XVelocity + XAcceleration;
			YVelocity = YVelocity + YAcceleration;

			XPosition = XPosition + XVelocity;
			YPosition = YPosition + YVelocity;
		}

		void AddForce( Force nForce )
		{ //{{{
			if( !( nForce is null ) )
			{
				m_Forces.length = m_Forces.length + 1;
				m_Forces[ $-1 ] = nForce;
			}
			else
			{
				log.warn( "Tried to add a null force" );
			}
		} //}}}

		void AddEntity( Entity nEntity )
		{ //{{{
			if( !( nEntity is null ) )
			{
				m_Entities.length = m_Entities.length + 1;
				m_Entities[ $-1 ] = nEntity;
			}
			else
			{
				log.warn( "Tried to add a null entity" );
			}
		} //}}}

		void Work( Particle B )
		{ //{{{
			foreach( i; m_Forces )
			{
				if( !( i is null ) )
				{
					i.Work( this, B );
				}
			}
		} //}}}

		void Position( float nXPosition, float nYPosition )
		{
			m_Position[ 0 ] = nXPosition;
			m_Position[ 1 ] = nYPosition;
		}

		// {G,S}etter for m_Position[ 0 ]
		float XPosition() //{{{
		{
			return m_Position[ 0 ];
		}
		void XPosition( float nXPosition )
		{
			m_Position[ 0 ] = nXPosition;
			foreach( i; m_Entities )
			{
				i.X = nXPosition;
			}
		} //}}}

		// {G,S}etter for m_Position[ 1 ]
		float YPosition() //{{{
		{
			return m_Position[ 1 ];
		}
		void YPosition( float nYPosition )
		{
			m_Position[ 1 ] = nYPosition;
			foreach( i; m_Entities )
			{
				i.Y = nYPosition;
			}
		} //}}}

		void Velocity( float nXVelocity, float nYVelocity )
		{
			m_Velocity[ 0 ] = nXVelocity;
			m_Velocity[ 1 ] = nYVelocity;
		}

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

		void Acceleration( float nXAcceleration, float nYAcceleration )
		{
			m_Acceleration[ 0 ] = nXAcceleration;
			m_Acceleration[ 1 ] = nYAcceleration;
		}
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

		// {G,S}eetter for m_Mass
		float Mass() //{{{
		{
			return m_Mass;
		}
		void Mass( float nMass )
		{
			m_Mass = nMass;
		} //}}}

		// {G,S}eetter for m_Radius
		float Radius() //{{{
		{
			return m_Radius;
		}
		void Radius( float nRadius )
		{
			m_Radius = nRadius;
		} //}}}

	protected:
		float m_Mass;
		float m_Radius;

		float[ 2 ] m_Position;
		float[ 2 ] m_Velocity;
		float[ 2 ] m_Acceleration;

		Entity[] m_Entities;
		Force[] m_Forces;

	private:

}
