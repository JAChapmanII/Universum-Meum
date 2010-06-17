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
		long double XPosition();
		void CurrentXPosition( long double nXPosition );

		// {G,S}etter for current YPosition
		long double YPosition();
		void CurrentYPosition( long double nYPosition );

		// Setter for both current Positions
		void CurrentPositions( long double nXPosition, long double nYPosition);

		// {G,S}etter for next XPosition
		long double NextXPosition();
		void XPosition( long double nXPosition );

		// {G,S}etter for next YPosition
		long double NextYPosition();
		void YPosition( long double nYPosition );

		// Setter for both next Positions
		void Positions( long double nXPosition, long double nYPosition );


		// {G,S}etter for current XVelocity
		long double XVelocity();
		void CurrentXVelocity( long double nXVelocity );

		// {G,S}etter for current YVelocity
		long double YVelocity();
		void CurrentYVelocity( long double nYVelocity );

		// Setter for both current Velocitys
		void CurrentVelocities( long double nXVelocity, long double nYVelocity);

		// {G,S}etter for next XVelocity
		long double NextXVelocity();
		void XVelocity( long double nXVelocity );

		// {G,S}etter for next YVelocity
		long double NextYVelocity();
		void YVelocity( long double nYVelocity );

		// Setter for both next Velocitys
		void Velocities( long double nXVelocity, long double nYVelocity );

		// Setter for both next Velocitys
		void Velocities( Vector< long double > nVelocity );


		// {G,S}etter for current XAcceleration
		long double XAcceleration();
		void CurrentXAcceleration( long double nXAcceleration );

		// {G,S}etter for current YAcceleration
		long double YAcceleration();
		void CurrentYAcceleration( long double nYAcceleration );

		// Setter for both current Accelerations
		void CurrentAccelerations( long double nXAcceleration, long double nYAcceleration);

		// {G,S}etter for next XAcceleration
		long double NextXAcceleration();
		void XAcceleration( long double nXAcceleration );

		// {G,S}etter for next YAcceleration
		long double NextYAcceleration();
		void YAcceleration( long double nYAcceleration );

		// Setter for both next Accelerations
		void Accelerations( long double nXAcceleration, long double nYAcceleration );


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
