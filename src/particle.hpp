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
#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>
#include <math.h>

#include "entity.cpp"

class Particle
{
	public:
		typedef void( *Force )( Particle*, Particle*, long double );

		Particle();
		~Particle();

		void Work( Particle* B, long double deltaTime );
		void Update( long double deltaTime );

		void AddForce( Force *nForce );
		void AddEntity( Entity *nEntity );

		/// Return first entity in m_Entities or null if there are none.
		Entity* GetEntity();

		// {G,S}etter for current XPosition
		inline long double XPosition();
		inline void CurrentXPosition( long double nXPosition );

		// {G,S}etter for current YPosition
		inline long double YPosition();
		inline void CurrentYPosition( long double nYPosition );

		// Setter for both current Positions
		inline void CurrentPositions( long double nXPosition, long double nYPosition);

		// {G,S}etter for next XPosition
		inline long double NextXPosition();
		inline void XPosition( long double nXPosition );

		// {G,S}etter for next YPosition
		inline long double NextYPosition();
		inline void YPosition( long double nYPosition );

		// Setter for both next Positions
		inline void Positions( long double nXPosition, long double nYPosition );


		// {G,S}etter for current XVelocity
		inline long double XVelocity();
		inline void CurrentXVelocity( long double nXVelocity );

		// {G,S}etter for current YVelocity
		inline long double YVelocity();
		inline void CurrentYVelocity( long double nYVelocity );

		// Setter for both current Velocitys
		inline void CurrentVelocities( long double nXVelocity, long double nYVelocity);

		// {G,S}etter for next XVelocity
		inline long double NextXVelocity();
		inline void XVelocity( long double nXVelocity );

		// {G,S}etter for next YVelocity
		inline long double NextYVelocity();
		inline void YVelocity( long double nYVelocity );

		// Setter for both next Velocitys
		inline void Velocities( long double nXVelocity, long double nYVelocity );

		// Setter for both next Velocitys
		inline void Velocities( Vector< long double > nVelocity );


		// {G,S}etter for current XAcceleration
		inline long double XAcceleration();
		inline void CurrentXAcceleration( long double nXAcceleration );

		// {G,S}etter for current YAcceleration
		inline long double YAcceleration();
		inline void CurrentYAcceleration( long double nYAcceleration );

		// Setter for both current Accelerations
		inline void CurrentAccelerations( long double nXAcceleration, long double nYAcceleration);

		// {G,S}etter for next XAcceleration
		inline long double NextXAcceleration();
		inline void XAcceleration( long double nXAcceleration );

		// {G,S}etter for next YAcceleration
		inline long double NextYAcceleration();
		inline void YAcceleration( long double nYAcceleration );

		// Setter for both next Accelerations
		inline void Accelerations( long double nXAcceleration, long double nYAcceleration );


		long double mass;
		long double radius;
		long double speed;
		long double momentum;

	private:

		Vector< long double > m_Position;
		Vector< long double > m_Velocity;
		Vector< long double > m_Acceleration;

		Vector< long double > m_nextPosition;
		Vector< long double > m_nextVelocity;
		Vector< long double > m_nextAcceleration;

		std::vector< Entity* > m_Entities;
		std::vector< Force* > m_Forces;

};

#endif // "PARTICLE_HPP"
