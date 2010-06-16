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

#include <vector>

#include "particle.cpp"

class ParticleSystem
{
	public:
		ParticleSystem( long double iStep = 1.0f, long double iMaxSteps = 500.0f )
		{
			Step( iStep );
			MaxSteps( iMaxSteps );
		}

		void Work( long double deltaTime = 1.0f )
		{
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
		}

		void WorkAll( long double deltaTime )
		{ //{{{
			for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
			{
				for( std::vector< Particle* >::iterator j = m_Particles.begin(); j != m_Particles.end(); ++j )
				{
					(*i)->Work( *j, deltaTime );
				}
			}
		} //}}}

		void UpdateAll( long double deltaTime )
		{ //{{{
			for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
			{
				(*i)->Update( deltaTime );
			}
		} //}}}

		long double maxSpeed()
		{ //{{{
			long double max = 0.0f;
			long double current = 0.0f;
			for( std::vector< Particle* >::iterator i = m_Particles.begin(); i != m_Particles.end(); ++i )
			{
				current = (*i)->Speed();
				if( current >= max )
				{
					max = current;
				}
			}
			return max;
		} //}}}

		long double maxAcceleration()
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
		void Step( long double nStep ) //{{{
		{
			m_Step = nStep;
		}
		long double Step()
		{
			return m_Step;
		} //}}}

		// {G,S}etter for m_MaxSteps
		void MaxSteps( long double nMax ) //{{{
		{
			if( (1.0f / Step()) > (1.0 / nMax) )
			{
				m_MaxSteps = nMax;
			}
		}
		long double MaxSteps()
		{
			return m_MaxSteps;
		} //}}}

		void AddForce( Particle::Force nForce )
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

		void AddParticle( Particle *nParticle )
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

		void RemoveParticle( Particle *toRemove )
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

	private:
		long double abs( long double a )
		{
			if( a < 0 )
			{
				return -a;
			}
			return a;
		}

		long double m_Step;
		long double m_MaxSteps;

		std::vector< Particle* > m_Particles;
		std::vector< Particle::Force > m_Forces;

};

#endif // PARTICLE_SYSTEM_CPP
