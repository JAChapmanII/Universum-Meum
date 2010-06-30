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

/// Class representing an object that should be consrained by some system
class Particle
{
	public:
		/// The Force function pointer type definition
		typedef void( *Force )( Particle*, Particle*, long double );

		/// Default Consructor
		Particle();
		/// Default Destructor
		~Particle();

		/// Work all of this's forces on B, using deltaTime as a time increment
		void Work( Particle* B, long double deltaTime );
		/// Update this particle based on acceleration/velocity and next values
		void Update( long double deltaTime );

		/// Push Force into m_Forces
		void AddForce( Force *nForce );
		/// Push Entity into m_Entities, used to draw a representation of this particle
		void AddEntity( Entity *nEntity );

		/// Return first entity in m_Entities or null if there are none.
		Entity* GetEntity();

		/// Getter for current XPosition
		inline long double XPosition();
		/// Setter for current XPosition
		inline void CurrentXPosition( long double nXPosition );

		/// Getter for current YPosition
		inline long double YPosition();
		/// Setter for current YPosition
		inline void CurrentYPosition( long double nYPosition );

		/// Setter for both current Positions
		inline void CurrentPositions( long double nXPosition, long double nYPosition);

		/// Getter for next XPosition
		inline long double NextXPosition();
		/// Setter for next XPosition
		inline void XPosition( long double nXPosition );

		/// Getter for next YPosition
		inline long double NextYPosition();
		/// Setter for next YPosition
		inline void YPosition( long double nYPosition );

		/// Setter for both next Positions
		inline void Positions( long double nXPosition, long double nYPosition );


		/// Getter for current XVelocity
		inline long double XVelocity();
		/// Setter for current XVelocity
		inline void CurrentXVelocity( long double nXVelocity );

		/// Getter for current YVelocity
		inline long double YVelocity();
		/// Setter for current YVelocity
		inline void CurrentYVelocity( long double nYVelocity );

		/// Setter for both current Velocitys
		inline void CurrentVelocities( long double nXVelocity, long double nYVelocity);

		/// Getter for next XVelocity
		inline long double NextXVelocity();
		/// Setter for next XVelocity
		inline void XVelocity( long double nXVelocity );

		/// Getter for next YVelocity
		inline long double NextYVelocity();
		/// Setter for next YVelocity
		inline void YVelocity( long double nYVelocity );

		/// Setter for both next Velocitys
		inline void Velocities( long double nXVelocity, long double nYVelocity );

		/// Setter for both next Velocitys
		inline void Velocities( Vector< long double > nVelocity );


		/// Getter for current XAcceleration
		inline long double XAcceleration();
		/// Setter for current XAcceleration
		inline void CurrentXAcceleration( long double nXAcceleration );

		/// Getter for current YAcceleration
		inline long double YAcceleration();
		/// Setter for current YAcceleration
		inline void CurrentYAcceleration( long double nYAcceleration );

		/// Setter for both current Accelerations
		inline void CurrentAccelerations( long double nXAcceleration, long double nYAcceleration);

		/// Getter for next XAcceleration
		inline long double NextXAcceleration();
		/// Setter for next XAcceleration
		inline void XAcceleration( long double nXAcceleration );

		/// Getter for next YAcceleration
		inline long double NextYAcceleration();
		/// Setter for next YAcceleration
		inline void YAcceleration( long double nYAcceleration );

		/// Setter for both next Accelerations
		inline void Accelerations( long double nXAcceleration, long double nYAcceleration );

		/// Mass of particle
		long double mass;
		/// Radius -- used for collisions which is bad, need more generic collision system
		long double radius; // TODO See the comment above
		/// Magnitude of velocity vector
		long double speed;
		/// this->speed*this->mass, momentum of particle
		long double momentum;

	private:

		/// Vector representing the current position of the particle
		Vector< long double > m_Position;
		/// Vector representing the current velocity of the particle
		Vector< long double > m_Velocity;
		/// Vector representing the current acceleration of the particle
		Vector< long double > m_Acceleration;

		/// Vector representing the next position of the particle
		Vector< long double > m_nextPosition;
		/// Vector representing the next velocity of the particle
		Vector< long double > m_nextVelocity;
		/// Vector representing the next acceleration of the particle
		Vector< long double > m_nextAcceleration;

		/// std::vector of Entity's representincg this object on the screen
		std::vector< Entity* > m_Entities;
		/// std::vector of Forces this particle "emits"
		std::vector< Force* > m_Forces;

};

#endif // "PARTICLE_HPP"
