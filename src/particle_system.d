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

import force;
import particle;

class ParticleSystem
{
	public:
		this()
		{
		}

		void Work()
		{
			for( uint i = 0; i < m_Particles.length; i++ )
			{
				for( uint j = i + 1; j < m_Particles.length; j++ )
				{
					m_Particles[ i ].Work( m_Particles[ j ] );
				}
			}
		}

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
		Particle[] m_Particles;
		Force[] m_Forces;

	private:

}
