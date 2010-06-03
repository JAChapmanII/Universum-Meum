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

import tango.io.Stdout;
import tango.util.log.Log;
import tango.util.log.AppendConsole;
import tango.math.Math;

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
		{ //{{{
			m_Mass = 20.0f;
			m_Radius = 0.0f;
			m_Acceleration[] = [ 0.0f, 0.0f ];
			m_Velocity[] = [ 0.0f, 0.0f ];
			m_Position[] = [ 0.0f, 0.0f ];

			m_nextAcceleration[] = [ 0.0f, 0.0f ];
			m_nextVelocity[] = [ 0.0f, 0.0f ];
			m_Speed = 0.0f;
		} //}}}

		void Update( real deltaTime )
		{ //{{{
			m_Acceleration[ 0 ] = m_nextAcceleration[ 0 ];
			m_Acceleration[ 1 ] = m_nextAcceleration[ 1 ];

			m_Velocity[ 0 ] = m_nextVelocity[ 0 ];
			m_Velocity[ 1 ] = m_nextVelocity[ 1 ];

			m_Position[ 0 ] = m_nextPosition[ 0 ];
			m_Position[ 1 ] = m_nextPosition[ 1 ];

			CurrentXVelocity = XVelocity + XAcceleration * deltaTime;
			CurrentYVelocity = YVelocity + YAcceleration * deltaTime;

			Speed = sqrt( XVelocity*XVelocity + YVelocity*YVelocity );

			if( abs( (XPosition + XVelocity*deltaTime)- XPosition ) > 2
					|| abs( (YPosition + YVelocity*deltaTime)- YPosition ) > 2 )
			{
				Stdout.formatln( "----------------------------------------------------------------------" );
				Stdout.formatln( " P  {}, {} || {}, {}",
						XPosition, (XPosition + XVelocity*deltaTime),
						YPosition, (YPosition + YVelocity*deltaTime) );
			}

			CurrentXPosition = XPosition + XVelocity * deltaTime;
			CurrentYPosition = YPosition + YVelocity * deltaTime;

			m_nextAcceleration[] = [ 0.0f, 0.0f ];
			m_Acceleration[] = [ 0.0f, 0.0f ];
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

		void Work( Particle B, real deltaTime )
		{ //{{{
			foreach( i; m_Forces )
			{
				if( !( i is null ) )
				{
					i.Work( this, B, deltaTime );
				}
			}
		} //}}}

		// Position stuff
		//{{{
		// {G,S}etter for current XPosition
		real XPosition() //{{{
		{
			return m_Position[ 0 ];
		}
		void CurrentXPosition( real nXPosition )
		{
			m_Position[ 0 ] = nXPosition;
			m_nextPosition[ 0 ] = nXPosition;
			foreach( i; m_Entities )
			{
				i.XPosition = nXPosition;
			}
		} //}}}

		// {G,S}etter for current YPosition
		real YPosition() //{{{
		{
			return m_Position[ 1 ];
		}
		void CurrentYPosition( real nYPosition )
		{
			m_Position[ 1 ] = nYPosition;
			m_nextPosition[ 1 ] = nYPosition;
			foreach( i; m_Entities )
			{
				i.YPosition = nYPosition;
			}
		} //}}}

		// Setter for both current Positions
		void CurrentPositions( real nXPosition, real nYPosition) //{{{
		{
			m_Position[ 0 ] = nXPosition;
			m_Position[ 1 ] = nYPosition;
			m_nextPosition[ 0 ] = nXPosition;
			m_nextPosition[ 1 ] = nYPosition;
			foreach( i; m_Entities )
			{
				i.XPosition = nXPosition;
				i.YPosition = nYPosition;
			}
		} //}}}


		// {G,S}etter for next XPosition
		real NextXPosition() //{{{
		{
			return m_nextPosition[ 0 ];
		}
		void XPosition( real nXPosition )
		{
			m_nextPosition[ 0 ] = nXPosition;
		} //}}}

		// {G,S}etter for next YPosition
		real NextYPosition() //{{{
		{
			return m_nextPosition[ 1 ];
		}
		void YPosition( real nYPosition )
		{
			m_nextPosition[ 1 ] = nYPosition;
		} //}}}

		// Setter for both next Positions
		void Positions( real nXPosition, real nYPosition ) //{{{
		{
			XPosition = nXPosition;
			YPosition = nYPosition;
		} //}}}
		//}}}

		// Velocity stuff
		//{{{
		// {G,S}etter for current XVelocity
		real XVelocity() //{{{
		{
			return m_Velocity[ 0 ];
		}
		void CurrentXVelocity( real nXVelocity )
		{
			m_Velocity[ 0 ] = nXVelocity;
			Speed = sqrt( nXVelocity*nXVelocity + YVelocity*YVelocity );
		} //}}}

		// {G,S}etter for current YVelocity
		real YVelocity() //{{{
		{
			return m_Velocity[ 1 ];
		}
		void CurrentYVelocity( real nYVelocity )
		{
			m_Velocity[ 1 ] = nYVelocity;
			Speed = sqrt( XVelocity*XVelocity + nYVelocity*nYVelocity );
		} //}}}

		// Setter for both current Velocitys
		void CurrentVelocities( real nXVelocity, real nYVelocity) //{{{
		{
			m_Velocity[ 0 ] = nXVelocity;
			m_Velocity[ 1 ] = nYVelocity;
			Speed = sqrt( nXVelocity*nXVelocity + nYVelocity*nYVelocity );
		} //}}}


		// {G,S}etter for next XVelocity
		real NextXVelocity() //{{{
		{
			return m_nextVelocity[ 0 ];
		}
		void XVelocity( real nXVelocity )
		{
			m_nextVelocity[ 0 ] = nXVelocity;
		} //}}}

		// {G,S}etter for next YVelocity
		real NextYVelocity() //{{{
		{
			return m_nextVelocity[ 1 ];
		}
		void YVelocity( real nYVelocity )
		{
			m_nextVelocity[ 1 ] = nYVelocity;
		} //}}}

		// Setter for both next Velocitys
		void Velocities( real nXVelocity, real nYVelocity ) //{{{
		{
			XVelocity = nXVelocity;
			YVelocity = nYVelocity;
		} //}}}
		//}}}

		// Acceleration stuff
		//{{{
		// {G,S}etter for current XAcceleration
		real XAcceleration() //{{{
		{
			return m_Acceleration[ 0 ];
		}
		void CurrentXAcceleration( real nXAcceleration )
		{
			m_Acceleration[ 0 ] = nXAcceleration;
		} //}}}

		// {G,S}etter for current YAcceleration
		real YAcceleration() //{{{
		{
			return m_Acceleration[ 1 ];
		}
		void CurrentYAcceleration( real nYAcceleration )
		{
			m_Acceleration[ 1 ] = nYAcceleration;
		} //}}}

		// Setter for both current Accelerations
		void CurrentAccelerations( real nXAcceleration, real nYAcceleration) //{{{
		{
			m_Acceleration[ 0 ] = nXAcceleration;
			m_Acceleration[ 1 ] = nYAcceleration;
		} //}}}


		// {G,S}etter for next XAcceleration
		real NextXAcceleration() //{{{
		{
			return m_nextAcceleration[ 0 ];
		}
		void XAcceleration( real nXAcceleration )
		{
			m_nextAcceleration[ 0 ] = nXAcceleration;
		} //}}}

		// {G,S}etter for next YAcceleration
		real NextYAcceleration() //{{{
		{
			return m_nextAcceleration[ 1 ];
		}
		void YAcceleration( real nYAcceleration )
		{
			m_nextAcceleration[ 1 ] = nYAcceleration;
		} //}}}

		// Setter for both next Accelerations
		void Accelerations( real nXAcceleration, real nYAcceleration ) //{{{
		{
			XAcceleration = nXAcceleration;
			YAcceleration = nYAcceleration;
		} //}}}
		//}}}

		// {G,S}eetter for m_Mass
		real Mass() //{{{
		{
			return m_Mass;
		}
		void Mass( real nMass )
		{
			m_Mass = nMass;
		} //}}}

		// {G,S}eetter for m_Radius
		real Radius() //{{{
		{
			return m_Radius;
		}
		void Radius( real nRadius )
		{
			m_Radius = nRadius;
		} //}}}

		// {G,S}eetter for m_Radius
		real Speed() //{{{
		{
			return m_Speed;
		}
		void Speed( real nSpeed )
		{
			m_Speed = nSpeed;
		} //}}}

	protected:
		real m_Mass;
		real m_Radius;

		real[ 2 ] m_Position;
		real[ 2 ] m_Velocity;
		real[ 2 ] m_Acceleration;

		real[ 2 ] m_nextPosition;
		real[ 2 ] m_nextVelocity;
		real[ 2 ] m_nextAcceleration;

		real m_Speed;

		Entity[] m_Entities;
		Force[] m_Forces;

	private:

}
