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
			m_Mass = 500000.0f;
			m_Radius = 0.0f;
			m_Acceleration[] = [ 0.0f, 0.0f ];
			m_Velocity[] = [ 0.0f, 0.0f ];
			m_Position[] = [ 0.0f, 0.0f ];

			m_nextAcceleration[] = [ 0.0f, 0.0f ];
			m_nextVelocity[] = [ 0.0f, 0.0f ];
		}

		void Update( float deltaTime )
		{
			m_Acceleration[] = m_nextAcceleration;
			m_nextAcceleration[] = [ 0.0f, 0.0f ];
			m_Velocity[ 0 ] = m_nextVelocity[ 0 ];
			m_Velocity[ 1 ] = m_nextVelocity[ 1 ];

			CurrentXVelocity = XVelocity + XAcceleration * deltaTime;
			CurrentYVelocity = YVelocity + YAcceleration * deltaTime;

			XPosition = XPosition + XVelocity * deltaTime;
			YPosition = YPosition + YVelocity * deltaTime;
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

		void Work( Particle B, float deltaTime )
		{ //{{{
			foreach( i; m_Forces )
			{
				if( !( i is null ) )
				{
					i.Work( this, B, deltaTime );
				}
			}
		} //}}}

		void Position( float nXPosition, float nYPosition )
		{
			XPosition = nXPosition;
			YPosition = nYPosition;
		}

		// {G,S}etter for m_Position[ 0 ]
		float XPosition () //{{{
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
			XVelocity = nXVelocity;
			YVelocity = nYVelocity;
		}

		// {G,S}etter for m_nextVelocity[ 0 ]
		float NextXVelocity() //{{{
		{
			return m_nextVelocity[ 0 ];
		}
		void XVelocity( float nXVelocity )
		{
			m_nextVelocity[ 0 ] += nXVelocity;
		} //}}}

		// {G,S}etter for m_nextVelocity[ 1 ]
		float NextYVelocity() //{{{
		{
			return m_nextVelocity[ 1 ];
		}
		void YVelocity( float nYVelocity )
		{
			m_nextVelocity[ 1 ] += nYVelocity;
		} //}}}

		// {G,S}etter for m_Velocity[ 0 ]
		float XVelocity() //{{{
		{
			return m_Velocity[ 0 ];
		}
		void CurrentXVelocity( float nXVelocity )
		{
			m_Velocity[ 0 ] = nXVelocity;
		} //}}}

		// {G,S}etter for m_Velocity[ 1 ]
		float YVelocity() //{{{
		{
			return m_Velocity[ 1 ];
		}
		void CurrentYVelocity( float nYVelocity )
		{
			m_Velocity[ 1 ] = nYVelocity;
		} //}}}

		// Setter for Both m_Velocity
		void CurrentVelocities( float nXVelocity, float nYVelocity) //{{{
		{
			m_Velocity[0] = nXVelocity;
			m_Velocity[1] = nYVelocity;
		}//}}}

		void Acceleration( float nXAcceleration, float nYAcceleration )
		{
			XAcceleration = nXAcceleration;
			YAcceleration = nYAcceleration;
		}

		// {G,S}etter for m_nextAcceleration[ 0 ]
		float NextXAcceleration() //{{{
		{
			return m_nextAcceleration[ 0 ];
		}
		void XAcceleration( float nXAcceleration )
		{
			m_nextAcceleration[ 0 ] = nXAcceleration;
		} //}}}

		// {G;,S}etter for m_nextAcceleration[ 1 ]
		float NextYAcceleration() //{{{
		{
			return m_nextAcceleration[ 1 ];
		}
		void YAcceleration( float nYAcceleration )
		{
			m_nextAcceleration[ 1 ] = nYAcceleration;
		} //}}}

		// {G,S}etter for m_Acceleration[ 0 ]
		float XAcceleration() //{{{
		{
			return m_Acceleration[ 0 ];
		}
		void CurrentXAcceleration( float nXAcceleration )
		{
			m_Acceleration[ 0 ] += nXAcceleration;
		 } //}}}

		// {G;,S}etter for m_Acceleration[ 1 ]
		float YAcceleration() //{{{
		{
			return m_Acceleration[ 1 ];
		}
		void CurrentYAcceleration( float nYAcceleration )
		{
			m_Acceleration[ 1 ] += nYAcceleration;
		} //}}}

		// Setter for Both m_Acceleration
		void CurrentAcceleration( float nXAcceleration, float nYAcceleration) //{{{
		{
			m_Acceleration[0] = nXAcceleration;
			m_Acceleration[1] = nYAcceleration;
		}//}}}


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

		float[ 2 ] m_nextVelocity;
		float[ 2 ] m_nextAcceleration;

		Entity[] m_Entities;
		Force[] m_Forces;

	private:

}
