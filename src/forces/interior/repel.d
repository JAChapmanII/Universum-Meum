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
module repel;

import tango.util.log.Log;
import tango.util.log.AppendConsole;
import Integer = tango.text.convert.Integer;

import tango.math.Math;

import force;
import particle;

Logger log;
static this()
{
	log = Log.lookup( "forces.repel" );
	log.add( new AppendConsole() );
}

class Repel : Force
{
	public:
		static Repel Instance( real iR = 1.0 )
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new Repel( iR );
				}
				catch( Exception e )
				{
					log.fatal( "Repel could not be instantiated." );
					throw e;
				}
			}
			return m_Instance;
		} //}}}

		alias Instance opCall;

		/// Uses the gravity code *-2 to simulate anti-gravity.
		override void Work( Particle A, Particle B, ref real deltaTime )
		{ //{{{
			real xDist = B.XPosition - A.XPosition;
			real yDist = B.YPosition - A.YPosition;
			real dist2 = (xDist * xDist) + (yDist * yDist);
			real dist  = sqrt( dist2 );

			if( ( dist < (A.Radius + B.Radius) ) && ( dist2 > 0 ) )
			{
				real repMass = RepelConstant * B.Mass * 1.2;
				real sectLength = (A.Radius+B.Radius) - dist;
				real unitX = xDist / dist;
				real unitY = yDist / dist;

				A.XAcceleration = A.NextXAcceleration -
					( repMass ) * ( unitX ) / ( dist2 );

				A.YAcceleration = A.NextYAcceleration -
					( repMass ) * ( unitY ) / ( dist2 );
			}
		} //}}}

		/// {G,S}etter m_RepelConstant
		real RepelConstant() //{{{
		{
			return m_RepelConstant;
		}
		void RepelConstant( real nR )
		{
			m_RepelConstant = nR;
		} //}}}

	protected:
		this( real iR )
		{
			m_RepelConstant = iR;
		}

		static Repel m_Instance;

		real m_RepelConstant;

	private:

}