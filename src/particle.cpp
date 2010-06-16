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

#include <vector>
#include <math.h>

#include "entity.cpp"

class Particle
{
	public:
		typedef void( *Force )( Particle*, Particle*, long double );

		Particle()
		{ //{{{
			m_Mass = 20.0f;
			m_Radius = 0.0f;
			m_Acceleration.Zero();
			m_Velocity.Zero();
			m_Position.Zero();

			m_nextAcceleration.Zero();
			m_nextVelocity.Zero();
			m_nextPosition.Zero();
			m_Speed = 0.0f;
		} //}}}

		void Update( long double deltaTime )
		{ //{{{
			m_nextVelocity.x += m_nextAcceleration.x * deltaTime;
			m_nextVelocity.y += m_nextAcceleration.y * deltaTime;

			m_nextPosition.x += m_nextVelocity.x * deltaTime;
			m_nextPosition.y += m_nextVelocity.y * deltaTime;

			m_nextAcceleration.x = 0.0;
			m_nextAcceleration.y = 0.0;

			m_Acceleration.x = m_nextAcceleration.x;
			m_Acceleration.y = m_nextAcceleration.y;

			m_Velocity.x = m_nextVelocity.x;
			m_Velocity.y = m_nextVelocity.y;

			m_Position.x = m_nextPosition.x;
			m_Position.y = m_nextPosition.y;

			for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); ++i )
			{
				(*i)->position.x = XPosition();
				(*i)->position.y = YPosition();
			}

			Speed( sqrt( XVelocity()*XVelocity() + YVelocity()*YVelocity() ) );
		} //}}}

		void AddForce( Force *nForce )
		{ //{{{
			if( nForce != 0 )
			{
				m_Forces.push_back( nForce );
			}
			else
			{
				// TODO Error
			}
		} //}}}

		void AddEntity( Entity *nEntity )
		{ //{{{
			if( nEntity != 0 )
			{
				m_Entities.push_back( nEntity );
			}
			else
			{
				// TODO error
			}
		} //}}}

		/// Return first entity in m_Entities or null if there are none.
		Entity* GetEntity()
		{ //{{{
			if( m_Entities.size() > 0 )
			{
				return m_Entities.front();
			}
			// TODO Error
		} //}}}

		void Work( Particle* B, long double deltaTime )
		{ //{{{
			for( std::vector< Force* >::iterator i = m_Forces.begin(); i != m_Forces.end(); i++ )
			{
				if( (*i) != 0 )
				{
					(*(*i))( this, B, deltaTime );
				}
			}
		} //}}}

		// Position stuff
		//{{{
		// {G,S}etter for current XPosition
		long double XPosition() //{{{
		{
			return m_Position.x;
		}
		void CurrentXPosition( long double nXPosition )
		{
			m_Position.x = nXPosition;
			m_nextPosition.x = nXPosition;
			for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); ++i )
			{
				(*i)->position.x = nXPosition;
			}
		} //}}}

		// {G,S}etter for current YPosition
		long double YPosition() //{{{
		{
			return m_Position.y;
		}
		void CurrentYPosition( long double nYPosition )
		{
			m_Position.y = nYPosition;
			m_nextPosition.y = nYPosition;
			for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); i++ )
			{
				(*i)->position.y = nYPosition;
			}
		} //}}}

		// Setter for both current Positions
		void CurrentPositions( long double nXPosition, long double nYPosition) //{{{
		{
			m_Position.x = nXPosition;
			m_Position.y = nYPosition;
			m_nextPosition.x = nXPosition;
			m_nextPosition.y = nYPosition;
			for( std::vector< Entity* >::iterator i = m_Entities.begin(); i != m_Entities.end(); i++ )
			{
				(*i)->position.x = nXPosition;
				(*i)->position.y = nYPosition;
			}
		} //}}}


		// {G,S}etter for next XPosition
		long double NextXPosition() //{{{
		{
			return m_nextPosition.x;
		}
		void XPosition( long double nXPosition )
		{
			m_nextPosition.x = nXPosition;
		} //}}}

		// {G,S}etter for next YPosition
		long double NextYPosition() //{{{
		{
			return m_nextPosition.y;
		}
		void YPosition( long double nYPosition )
		{
			m_nextPosition.y = nYPosition;
		} //}}}

		// Setter for both next Positions
		void Positions( long double nXPosition, long double nYPosition ) //{{{
		{
			XPosition( nXPosition );
			YPosition( nYPosition );
		} //}}}
		//}}}

		// Velocity stuff
		//{{{
		// {G,S}etter for current XVelocity
		long double XVelocity() //{{{
		{
			return m_Velocity.x;
		}
		void CurrentXVelocity( long double nXVelocity )
		{
			m_Velocity.x = nXVelocity;
			Speed( sqrt( nXVelocity*nXVelocity + YVelocity()*YVelocity() ) );
		} //}}}

		// {G,S}etter for current YVelocity
		long double YVelocity() //{{{
		{
			return m_Velocity.y;
		}
		void CurrentYVelocity( long double nYVelocity )
		{
			m_Velocity.y = nYVelocity;
			Speed( sqrt( XVelocity()*XVelocity() + nYVelocity*nYVelocity ) );
		} //}}}

		// Setter for both current Velocitys
		void CurrentVelocities( long double nXVelocity, long double nYVelocity) //{{{
		{
			m_Velocity.x = nXVelocity;
			m_Velocity.y = nYVelocity;
			Speed( sqrt( nXVelocity*nXVelocity + nYVelocity*nYVelocity ) );
		} //}}}

		// {G,S}etter for next XVelocity
		long double NextXVelocity() //{{{
		{
			return m_nextVelocity.x;
		}
		void XVelocity( long double nXVelocity )
		{
			m_nextVelocity.x = nXVelocity;
		} //}}}

		// {G,S}etter for next YVelocity
		long double NextYVelocity() //{{{
		{
			return m_nextVelocity.y;
		}
		void YVelocity( long double nYVelocity )
		{
			m_nextVelocity.y = nYVelocity;
		} //}}}

		// Setter for both next Velocitys
		void Velocities( long double nXVelocity, long double nYVelocity ) //{{{
		{
			XVelocity( nXVelocity );
			YVelocity( nYVelocity );
		} //}}}
		//}}}

		// Acceleration stuff
		//{{{
		// {G,S}etter for current XAcceleration
		long double XAcceleration() //{{{
		{
			return m_Acceleration.x;
		}
		void CurrentXAcceleration( long double nXAcceleration )
		{
			m_Acceleration.x = nXAcceleration;
		} //}}}

		// {G,S}etter for current YAcceleration
		long double YAcceleration() //{{{
		{
			return m_Acceleration.y;
		}
		void CurrentYAcceleration( long double nYAcceleration )
		{
			m_Acceleration.y = nYAcceleration;
		} //}}}

		// Setter for both current Accelerations
		void CurrentAccelerations( long double nXAcceleration, long double nYAcceleration) //{{{
		{
			m_Acceleration.x = nXAcceleration;
			m_Acceleration.y = nYAcceleration;
		} //}}}


		// {G,S}etter for next XAcceleration
		long double NextXAcceleration() //{{{
		{
			return m_nextAcceleration.x;
		}
		void XAcceleration( long double nXAcceleration )
		{
			m_nextAcceleration.x = nXAcceleration;
		} //}}}

		// {G,S}etter for next YAcceleration
		long double NextYAcceleration() //{{{
		{
			return m_nextAcceleration.y;
		}
		void YAcceleration( long double nYAcceleration )
		{
			m_nextAcceleration.y = nYAcceleration;
		} //}}}

		// Setter for both next Accelerations
		void Accelerations( long double nXAcceleration, long double nYAcceleration ) //{{{
		{
			XAcceleration( nXAcceleration );
			YAcceleration( nYAcceleration );
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

		Vector< long double > m_Position;
		Vector< long double > m_Velocity;
		Vector< long double > m_Acceleration;

		Vector< long double > m_nextPosition;
		Vector< long double > m_nextVelocity;
		Vector< long double > m_nextAcceleration;

		long double m_Speed;

		std::vector< Entity* > m_Entities;
		std::vector< Force* > m_Forces;

	private:

};

#endif // "PARTICLE_CPP"
