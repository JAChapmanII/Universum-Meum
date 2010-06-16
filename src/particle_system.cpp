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

#include "force.cpp"
#include "particle.cpp"

class ParticleSystem
{
	public:
		this( long double iStep = 1.0f, long double iMaxSteps = 500.0f )
		{
			Step = iStep;
			MaxSteps = iMaxSteps;
			m_Particles = new LinkedList!( Particle );
		}

		void Work( long double deltaTime = 1.0f )
		{
			long double timeLeft = deltaTime;
			while( timeLeft > 0.0f )
			{
				long double currentMax = maxSpeed;
				if( ( currentMax * timeLeft ) > Step )
				{
					long double currentDelta = (Step / currentMax);
					if (currentDelta < (deltaTime / MaxSteps))
					{
						currentDelta = (deltaTime / MaxSteps);
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

		void WorkAll( ref long double deltaTime )
		{ //{{{
			foreach( i; m_Particles )
			{
				foreach( j; m_Particles )
				{
					i.Work( j, deltaTime );
				}
			}
		} //}}}

		void UpdateAll( ref long double deltaTime )
		{ //{{{
			foreach( i; m_Particles )
			{
				i.Update( deltaTime );
			}
		} //}}}

		long double maxSpeed()
		{ //{{{
			long double max = 0.0f;
			long double current = 0.0f;
			foreach( i; m_Particles )
			{
				current = i.Speed;
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
			foreach( i; m_Particles )
			{
				current = sqrt( i.XAcceleration*i.XAcceleration + i.YAcceleration*i.YAcceleration );
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
			if( (1.0f / Step) > (1.0 / nMax) )
			{
				m_MaxSteps = nMax;
			}
		}
		long double MaxSteps()
		{
			return m_MaxSteps;
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

		void AddParticle( Particle nParticle )
		{ //{{{
			if( !( nParticle is null ) )
			{
				m_Particles.add( nParticle );
			}
			else
			{
				log.warn( "Tried to add a null particle" );
			}
		} //}}}

		void RemoveParticle( Particle toRemove )
		{ //{{{
			if( m_Particles.contains( toRemove ) )
			{
				m_Particles.remove( toRemove, true );
			}
		} //}}}

	protected:
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

		LinkedList!( Particle ) m_Particles;
		Force[] m_Forces;

	private:

}
