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
#ifndef PARTICLE_CPP
#define PARTICLE_CPP

#include "force.cpp"
#include "entity.cpp"

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
		{ //{{{
			m_Mass = 20.0f;
			m_Radius = 0.0f;
			m_Acceleration[] = [ 0.0f, 0.0f ];
			m_Velocity[] = [ 0.0f, 0.0f ];
			m_Position[] = [ 0.0f, 0.0f ];

			m_nextAcceleration[] = [ 0.0f, 0.0f ];
			m_nextVelocity[] = [ 0.0f, 0.0f ];
			m_nextPosition[] = [ 0.0, 0.0 ];
			m_Speed = 0.0f;
		} //}}}

		void Update( long double deltaTime )
		{ //{{{
			m_nextVelocity[ 0 ] += m_nextAcceleration[ 0 ] * deltaTime;
			m_nextVelocity[ 1 ] += m_nextAcceleration[ 1 ] * deltaTime;

			m_nextPosition[ 0 ] += m_nextVelocity[ 0 ] * deltaTime;
			m_nextPosition[ 1 ] += m_nextVelocity[ 1 ] * deltaTime;

			m_nextAcceleration[ 0 ] = 0.0;
			m_nextAcceleration[ 1 ] = 0.0;

			m_Acceleration[ 0 ] = m_nextAcceleration[ 0 ];
			m_Acceleration[ 1 ] = m_nextAcceleration[ 1 ];

			m_Velocity[ 0 ] = m_nextVelocity[ 0 ];
			m_Velocity[ 1 ] = m_nextVelocity[ 1 ];

			m_Position[ 0 ] = m_nextPosition[ 0 ];
			m_Position[ 1 ] = m_nextPosition[ 1 ];

			foreach( i; m_Entities )
			{
				i.position.x = XPosition;
				i.position.y = YPosition;
			}

			Speed = sqrt( XVelocity*XVelocity + YVelocity*YVelocity );
		} //}}}

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

		/// Return first entity in m_Entities or null if there are none.
		Entity GetEntity()
		{ //{{{
			if( m_Entities.length > 0 )
			{
				return m_Entities[ 0 ];
			}
			return null;
		} //}}}

		void Work( Particle B, long double deltaTime )
		{ //{{{
			foreach( i; m_Forces )
			{
				if( !( i is null ) )
				{
					i( this, B, deltaTime );
				}
			}
		} //}}}

		// Position stuff
		//{{{
		// {G,S}etter for current XPosition
		long double XPosition() //{{{
		{
			return m_Position[ 0 ];
		}
		void CurrentXPosition( long double nXPosition )
		{
			m_Position[ 0 ] = nXPosition;
			m_nextPosition[ 0 ] = nXPosition;
			foreach( i; m_Entities )
			{
				i.position.x = nXPosition;
			}
		} //}}}

		// {G,S}etter for current YPosition
		long double YPosition() //{{{
		{
			return m_Position[ 1 ];
		}
		void CurrentYPosition( long double nYPosition )
		{
			m_Position[ 1 ] = nYPosition;
			m_nextPosition[ 1 ] = nYPosition;
			foreach( i; m_Entities )
			{
				i.position.y = nYPosition;
			}
		} //}}}

		// Setter for both current Positions
		void CurrentPositions( long double nXPosition, long double nYPosition) //{{{
		{
			m_Position[ 0 ] = nXPosition;
			m_Position[ 1 ] = nYPosition;
			m_nextPosition[ 0 ] = nXPosition;
			m_nextPosition[ 1 ] = nYPosition;
			foreach( i; m_Entities )
			{
				i.position.x = nXPosition;
				i.position.y = nYPosition;
			}
		} //}}}


		// {G,S}etter for next XPosition
		long double NextXPosition() //{{{
		{
			return m_nextPosition[ 0 ];
		}
		void XPosition( long double nXPosition )
		{
			m_nextPosition[ 0 ] = nXPosition;
		} //}}}

		// {G,S}etter for next YPosition
		long double NextYPosition() //{{{
		{
			return m_nextPosition[ 1 ];
		}
		void YPosition( long double nYPosition )
		{
			m_nextPosition[ 1 ] = nYPosition;
		} //}}}

		// Setter for both next Positions
		void Positions( long double nXPosition, long double nYPosition ) //{{{
		{
			XPosition = nXPosition;
			YPosition = nYPosition;
		} //}}}
		//}}}

		// Velocity stuff
		//{{{
		// {G,S}etter for current XVelocity
		long double XVelocity() //{{{
		{
			return m_Velocity[ 0 ];
		}
		void CurrentXVelocity( long double nXVelocity )
		{
			m_Velocity[ 0 ] = nXVelocity;
			Speed = sqrt( nXVelocity*nXVelocity + YVelocity*YVelocity );
		} //}}}

		// {G,S}etter for current YVelocity
		long double YVelocity() //{{{
		{
			return m_Velocity[ 1 ];
		}
		void CurrentYVelocity( long double nYVelocity )
		{
			m_Velocity[ 1 ] = nYVelocity;
			Speed = sqrt( XVelocity*XVelocity + nYVelocity*nYVelocity );
		} //}}}

		// Setter for both current Velocitys
		void CurrentVelocities( long double nXVelocity, long double nYVelocity) //{{{
		{
			m_Velocity[ 0 ] = nXVelocity;
			m_Velocity[ 1 ] = nYVelocity;
			Speed = sqrt( nXVelocity*nXVelocity + nYVelocity*nYVelocity );
		} //}}}

		// {G,S}etter for next XVelocity
		long double NextXVelocity() //{{{
		{
			return m_nextVelocity[ 0 ];
		}
		void XVelocity( long double nXVelocity )
		{
			m_nextVelocity[ 0 ] = nXVelocity;
		} //}}}

		// {G,S}etter for next YVelocity
		long double NextYVelocity() //{{{
		{
			return m_nextVelocity[ 1 ];
		}
		void YVelocity( long double nYVelocity )
		{
			m_nextVelocity[ 1 ] = nYVelocity;
		} //}}}

		// Setter for both next Velocitys
		void Velocities( long double nXVelocity, long double nYVelocity ) //{{{
		{
			XVelocity = nXVelocity;
			YVelocity = nYVelocity;
		} //}}}
		//}}}

		// Acceleration stuff
		//{{{
		// {G,S}etter for current XAcceleration
		long double XAcceleration() //{{{
		{
			return m_Acceleration[ 0 ];
		}
		void CurrentXAcceleration( long double nXAcceleration )
		{
			m_Acceleration[ 0 ] = nXAcceleration;
		} //}}}

		// {G,S}etter for current YAcceleration
		long double YAcceleration() //{{{
		{
			return m_Acceleration[ 1 ];
		}
		void CurrentYAcceleration( long double nYAcceleration )
		{
			m_Acceleration[ 1 ] = nYAcceleration;
		} //}}}

		// Setter for both current Accelerations
		void CurrentAccelerations( long double nXAcceleration, long double nYAcceleration) //{{{
		{
			m_Acceleration[ 0 ] = nXAcceleration;
			m_Acceleration[ 1 ] = nYAcceleration;
		} //}}}


		// {G,S}etter for next XAcceleration
		long double NextXAcceleration() //{{{
		{
			return m_nextAcceleration[ 0 ];
		}
		void XAcceleration( long double nXAcceleration )
		{
			m_nextAcceleration[ 0 ] = nXAcceleration;
		} //}}}

		// {G,S}etter for next YAcceleration
		long double NextYAcceleration() //{{{
		{
			return m_nextAcceleration[ 1 ];
		}
		void YAcceleration( long double nYAcceleration )
		{
			m_nextAcceleration[ 1 ] = nYAcceleration;
		} //}}}

		// Setter for both next Accelerations
		void Accelerations( long double nXAcceleration, long double nYAcceleration ) //{{{
		{
			XAcceleration = nXAcceleration;
			YAcceleration = nYAcceleration;
		} //}}}
		//}}}

		// {G,S}eetter for m_Mass
		long double Mass() //{{{
		{
			return m_Mass;
		}
		void Mass( long double nMass )
		{
			m_Mass = nMass;
		} //}}}

		// {G,S}eetter for m_Radius
		long double Radius() //{{{
		{
			return m_Radius;
		}
		void Radius( long double nRadius )
		{
			m_Radius = nRadius;
		} //}}}

		// {G,S}eetter for m_Radius
		long double Speed() //{{{
		{
			return m_Speed;
		}
		void Speed( long double nSpeed )
		{
			m_Speed = nSpeed;
		} //}}}

	protected:
		long double m_Mass;
		long double m_Radius;

		long double[ 2 ] m_Position;
		long double[ 2 ] m_Velocity;
		long double[ 2 ] m_Acceleration;

		long double[ 2 ] m_nextPosition;
		long double[ 2 ] m_nextVelocity;
		long double[ 2 ] m_nextAcceleration;

		long double m_Speed;

		Entity[] m_Entities;
		Force[] m_Forces;

	private:

}

#endif // "PARTICLE_CPP"
