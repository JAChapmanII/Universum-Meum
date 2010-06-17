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
#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <vector>

#include "particle.cpp"

class ParticleSystem
{
	public:
		ParticleSystem( long double iStep = 1.0f, long double iMaxSteps = 500.0f );

		void Work( long double deltaTime = 1.0f );
		void WorkAll( long double deltaTime );
		void UpdateAll( long double deltaTime );

		long double maxSpeed();
		long double maxAcceleration();

		// {G,S}etter for m_Step
		void Step( long double nStep );
		long double Step();

		// {G,S}etter for m_MaxSteps
		void MaxSteps( long double nMax );
		long double MaxSteps();

		void AddForce( Particle::Force nForce );

		void AddParticle( Particle *nParticle );
		void RemoveParticle( Particle *toRemove );

	private:
		long double abs( long double a );

		long double m_Step;
		long double m_MaxSteps;

		std::vector< Particle* > m_Particles;
		std::vector< Particle::Force > m_Forces;

};

#endif // PARTICLE_SYSTEM_HPP
