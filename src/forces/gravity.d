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
module gravity;

import tango.io.Stdout;

import tango.util.log.Log;
import tango.util.log.AppendConsole;
import tango.math.Math;

import force;
import particle;

Logger log;
static this()
{
	log = Log.lookup( "forces.gravity" );
	log.add( new AppendConsole() );
}

class Gravity : Force
{
	public:
		static Gravity Instance( float iG = 12.0f )
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new Gravity( iG );
				}
				catch( Exception e )
				{
					log.fatal( "Gravity could not be instantiated." );
					throw e;
				}
			}
			return m_Instance;
		} //}}}

		alias Instance opCall;

		override void Work( Particle A, Particle B, ref float deltaTime )
		{ //{{{
			//log.info( "Gravity has done work" );
			float distX = B.XPosition - A.XPosition;
			float distY = B.YPosition - A.YPosition;
			float dist2 = distX*distX + distY*distY;
			float dist = sqrt( dist2 );
			if( dist > (A.Radius+B.Radius+1.0) )
			{
				float force = ( GravityConstant * A.Mass * B.Mass ) / ( dist2 );
				float delX = ( distX / dist ) * force * deltaTime;
				float delY = ( distY / dist ) * force * deltaTime;

				float nXA = A.NextXAcceleration + delX;
				float nYA = A.NextYAcceleration + delY;

				if( abs(nXA) > 3 || abs(nYA) > 3 )
				{
					Stdout.formatln( "----------- {} | {} -------------", nXA, nYA );
				}

				A.XAcceleration = nXA;
				A.YAcceleration = nYA;
			}
		} //}}}

		/// {G,S}etter m_GravityConstant
		float GravityConstant() //{{{
		{
			return m_GravityConstant;
		}
		void GravityConstant( float nG )
		{
			m_GravityConstant = nG;
		} //}}}

	protected:
		this( float iG )
		{
			m_GravityConstant = iG;
		}

		static Gravity m_Instance;

		float m_GravityConstant;

	private:

}
