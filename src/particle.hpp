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

		/// Mass of particle
		long double mass;
		/// Radius -- used for collisions which is bad, need more generic collision system
		long double radius; // TODO See the comment above
		/// Magnitude of velocity vector
		long double speed;
		/// this->speed*this->mass, momentum of particle
		long double momentum;

		Vector< long double > position;
		Vector< long double > velocity;

		/// Movers (changes in position) that should affect particle
		std::vector< Vector< long double > > movers;
		/// Impulses (changes in velocity) that should act on particle
		std::vector< Vector< long double > > impulses;

	private:
		/// std::vector of Entity's representincg this object on the screen
		std::vector< Entity* > m_Entities;
		/// std::vector of Forces this particle "emits"
		std::vector< Force* > m_Forces;

};

#endif // "PARTICLE_HPP"
