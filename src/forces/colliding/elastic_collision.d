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
module elastic_collision;

import tango.util.log.Log;
import tango.util.log.AppendConsole;
import Integer = tango.text.convert.Integer;

import tango.math.Math;

import force;
import particle;

Logger log;
static this()
{
	log = Log.lookup( "forces.elastic_collision" );
	log.add( new AppendConsole() );
}

class Elastic_collision : Force
{
	public:
		static Elastic_collision Instance( real iR = 1.0 )
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new Elastic_collision( iR );
				}
				catch( Exception e )
				{
					log.fatal( "Elastic_collision could not be instantiated." );
					throw e;
				}
			}
			return m_Instance;
		} //}}}

		alias Instance opCall;

		/// In the case of a perefct collision, uses elastic collision code. Otherwise, it uses the
		/// gravity code *-2 to simulate anti-gravity.
		override void Work( Particle A, Particle B, ref real deltaTime )
		{ //{{{
			real xDist = B.XPosition - A.XPosition;
			real yDist = B.YPosition - A.YPosition;
			real dist2 = (xDist * xDist) + (yDist * yDist);
			real dist  = sqrt( dist2 );

			if( ( dist < (A.Radius + B.Radius)/2 ) && ( dist2 > 0 ) )
			{
				real repMass = Elastic_collisionConstant * B.Mass * 1.2;
				real sectLength = (A.Radius+B.Radius/2) - dist;
				real unitX = xDist / dist;
				real unitY = yDist / dist;

				A.XAcceleration = A.NextXAcceleration -
					( repMass ) * ( unitX ) / ( dist2 );

				A.YAcceleration = A.NextYAcceleration -
					( repMass ) * ( unitY ) / ( dist2 );

				if( dist == (A.Radius+B.Radius/2) )
				{
					real theta = atan2( yDist, xDist );
					real dir1 = atan2( A.YVelocity, A.XVelocity );
					real dir2 = atan2( B.YVelocity, B.XVelocity );
					real nYV1 = A.Speed * sin( dir1 - theta );
					real fXV1 = ( ( A.Mass - B.Mass ) * ( A.Speed * cos( dir1 - theta ) ) + 2 *
								B.Mass * ( B.Speed * cos( dir2 - theta ) ) ) / ( A.Mass + B.Mass );

					real nYV2 = B.Speed * sin( dir1 - theta );
					A.XVelocity = cos(theta) * fXV1 + cos(theta+PI_2) * nYV1;
					A.YVelocity = sin(theta) * fXV1 + sin(theta+PI_2) * nYV1;
				}
			}
		} //}}}

		/// {G,S}etter m_Elastic_collisionConstant
		real Elastic_collisionConstant() //{{{
		{
			return m_Elastic_collisionConstant;
		}
		void Elastic_collisionConstant( real nR )
		{
			m_Elastic_collisionConstant = nR;
		} //}}}

	protected:
		this( real iR )
		{
			m_Elastic_collisionConstant = iR;
		}

		static Elastic_collision m_Instance;

		real m_Elastic_collisionConstant;

	private:

}
