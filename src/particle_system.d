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
module particle_system;

import tango.math.Math : sqrt;

import force;
import particle;

class ParticleSystem
{
	public:
		this( float iStep = 1.0f, float iMaxStep = 500 )
		{
			Step = iStep;
			maxStep = iMaxStep;
		}

		void Work( float deltaTime = 1.0f )
		{
			float timePassed = 0.0f;
			if( maxSpeed > ( deltaTime * Step ) )
			{
				while( timePassed < deltaTime )
				{
					float currentDelta = (Step / maxSpeed);
					if (currentDelta < (deltaTime / maxStep))
					{
						currentDelta = (deltaTime / maxStep);
					}
					WorkAll( currentDelta );
					UpdateAll( currentDelta );

					timePassed += currentDelta;

				}
			}

			WorkAll( deltaTime - timePassed );
			UpdateAll( deltaTime - timePassed );
		}

		void WorkAll( float deltaTime )
		{ //{{{
			for( uint i = 0; i < m_Particles.length; i++ )
			{
				for( uint j = 0; j < m_Particles.length; j++ )
				{
					m_Particles[ i ].Work( m_Particles[ j ], deltaTime );
				}
			}
		} //}}}

		void UpdateAll( float deltaTime )
		{ //{{{
			foreach( i; m_Particles )
			{
				i.Update( deltaTime );
			}
		} //}}}

		float maxSpeed()
		{ //{{{
			float max = 0.0f;
			float current = 0.0f;
			foreach( i; m_Particles )
			{
				current = sqrt( i.XVelocity*i.XVelocity + i.YVelocity*i.YVelocity );
				if( current >= max )
				{
					max = current;
				}
			}
			return max;
		} //}}}

		float maxAcceleration()
		{ //{{{
			float max = 0.0f;
			float current = 0.0f;
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
		void Step( float nStep ) //{{{
		{
			m_Step = nStep;
		}
		float Step()
		{
			return m_Step;
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
				m_Particles.length = m_Particles.length + 1;
				m_Particles[ $-1 ] = nParticle;
			}
			else
			{
				log.warn( "Tried to add a null particle" );
			}
		} //}}}


	protected:

		float maxStep;

		float abs( float a )
		{
			if( a < 0 )
			{
				return -a;
			}
			return a;
		}

		float m_Step;

		Particle[] m_Particles;
		Force[] m_Forces;

	private:

}
