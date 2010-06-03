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
		static Gravity Instance( real iG = 1.0f )
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

		override void Work( Particle A, Particle B, ref real deltaTime )
		{ //{{{
			real xDist = B.XPosition - A.XPosition;
			real yDist = B.YPosition - A.YPosition;
			real dist2 = (xDist * xDist) + (yDist * yDist);

			if( dist2 > 0 )
			{
				real gravMass = GravityConstant * B.Mass;
				real dist  = sqrt( dist2 );

				A.XAcceleration = A.NextXAcceleration +
					( gravMass )*(xDist/dist) / ( dist2 );

				A.YAcceleration = A.NextYAcceleration +
					( gravMass )*(yDist/dist) / ( dist2 );
			}
		} //}}}

		/// {G,S}etter m_GravityConstant
		real GravityConstant() //{{{
		{
			return m_GravityConstant;
		}
		void GravityConstant( real nG )
		{
			m_GravityConstant = nG;
		} //}}}

	protected:
		this( real iG )
		{
			m_GravityConstant = iG;
		}

		static Gravity m_Instance;

		real m_GravityConstant;

	private:

}
