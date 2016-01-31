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
#include <cmath>

#include <SFML/Graphics/Shape.hpp>
using sf::Shape;

#include <SFML/System/Vector2.hpp>
using sf::Vector2;

#include "util.cpp"

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
		/// Push Shape into m_Shapes, used to draw a representation of this particle
		void AddShape( Shape *nShape );

		/// Return first entity in m_Shapes or null if there are none.
		Shape* GetShape();

		/// Mass of particle
		long double mass;
		/// Radius -- used for collisions which is bad, need more generic collision system
		long double radius; // TODO See the comment above
		/// Magnitude of velocity vector
		long double speed;
		/// this->speed*this->mass, momentum of particle
		long double momentum;

		Vector2< long double > position;
		Vector2< long double > velocity;

		/// Movers (changes in position) that should affect particle
		std::vector< Vector2< long double > > movers;
		/// Impulses (changes in velocity) that should act on particle
		std::vector< Vector2< long double > > impulses;

	private:
		/// std::vector of Shapes representincg this object on the screen
		std::vector< Shape* > m_Shapes;
		/// std::vector of Forces this particle "emits"
		std::vector< Force* > m_Forces;

};

#endif // "PARTICLE_HPP"
