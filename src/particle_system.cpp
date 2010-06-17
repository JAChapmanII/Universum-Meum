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
#ifndef PARTICLE_SYSTEM_CPP
#define PARTICLE_SYSTEM_CPP

#include "particle_system.hpp"

ParticleSystem::ParticleSystem( long double iStep, long double iMaxSteps )
{ //{{{
	Step( iStep );
	MaxSteps( iMaxSteps );
} //}}}

void ParticleSystem::Work( long double deltaTime )
{ //{{{
	long double timeLeft = deltaTime;
	while( timeLeft > 0.0f )
	{
		long double currentMax = maxSpeed();
		if( ( currentMax * timeLeft ) > Step() )
		{
			long double currentDelta = (Step() / currentMax);
			if (currentDelta < (deltaTime / MaxSteps()))
			{
				currentDelta = (deltaTime / MaxSteps());
			}
			if( currentDelta > timeLeft )
			{
				currentDelta = timeLeft;
			}
			WorkAll( currentDelta );
			UpdateAll( currentDelta );
			timeLeft -= currentDelta;
		}
		else
		{
			WorkAll( deltaTime );
			UpdateAll( deltaTime );
			timeLeft = 0.0f;
		}
	}
} //}}}

void ParticleSystem::WorkAll( long double deltaTime )
{ //{{{
	for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
	{
		for( std::vector< Particle* >::iterator j = m_Particles.begin(); j != m_Particles.end(); ++j )
		{
			(*i)->Work( *j, deltaTime );
		}
	}
} //}}}

void ParticleSystem::UpdateAll( long double deltaTime )
{ //{{{
	for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
	{
		(*i)->Update( deltaTime );
	}
} //}}}

long double ParticleSystem::maxSpeed()
{ //{{{
	long double max = 0.0f;
	long double current = 0.0f;
	for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
	{
		current = (*i)->speed;
		if( current >= max )
		{
			max = current;
		}
	}
	return max;
} //}}}

long double ParticleSystem::maxAcceleration()
{ //{{{
	long double max = 0.0f;
	long double current = 0.0f;
	for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
	{
		current = sqrt( (*i)->XAcceleration()*(*i)->XAcceleration() +
						(*i)->YAcceleration()*(*i)->YAcceleration() );
		if( current >= max )
		{
			max = current;
		}
	}
	return max;
} //}}}

// {G,S}etter for m_Step
void ParticleSystem::Step( long double nStep ) //{{{
{
	m_Step = nStep;
}
long double ParticleSystem::Step()
{
	return m_Step;
} //}}}

// {G,S}etter for m_MaxSteps
void ParticleSystem::MaxSteps( long double nMax ) //{{{
{
	if( (1.0f / Step()) > (1.0 / nMax) )
	{
		m_MaxSteps = nMax;
	}
}
long double ParticleSystem::MaxSteps()
{
	return m_MaxSteps;
} //}}}

void ParticleSystem::AddForce( Particle::Force nForce )
{ //{{{
	if( nForce != 0 )
	{
		m_Forces.push_back( nForce );
	}
	else
	{
		// TODO error
	}
} //}}}

void ParticleSystem::AddParticle( Particle *nParticle )
{ //{{{
	if( nParticle != 0 )
	{
		m_Particles.push_back( nParticle );
	}
	else
	{
		// TODO error
	}
} //}}}

void ParticleSystem::RemoveParticle( Particle *toRemove )
{ //{{{
	for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
	{
		if( (*i) == toRemove )
		{
			m_Particles.erase( i );
			break;
		}
	}
} //}}}

#endif // PARTICLE_SYSTEM_CPP
