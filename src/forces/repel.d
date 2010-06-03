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

		override void Work( Particle A, Particle B, ref real deltaTime )
		{ //{{{
			real xDist = B.XPosition - A.XPosition;
			real yDist = B.YPosition - A.YPosition;
			real dist2 = (xDist * xDist) + (yDist * yDist);
			real dist  = sqrt( dist2 );

			if( ( dist < (A.Radius + B.Radius)/2 ) && ( dist2 > 0 ) )
			{
				real repMass = RepelConstant * B.Mass * 2;
				real sectLength = (A.Radius+B.Radius/2) - dist;
				real unitX = xDist / dist;
				real unitY = yDist / dist;

				A.XAcceleration = A.NextXAcceleration -
					( repMass ) * ( unitX ) / ( dist2 );

				A.YAcceleration = A.NextYAcceleration -
					( repMass ) * ( unitY ) / ( dist2 );

				//A.XVelocity = A.XVelocity - unitX * B.Mass;
				//A.YVelocity = A.YVelocity - unitY * B.Mass;

				if( dist == (A.Radius+B.Radius/2) )
				{
					real theta = atan2( yDist, xDist );
					real mag1 = A.Speed;
					real mag2 = B.Speed;
					real dir1 = atan2( A.YVelocity, A.XVelocity );
					real dir2 = atan2( B.YVelocity, B.XVelocity );
					real nXV1 = mag1*cos( dir1 - theta );
					real nYV1 = mag1*sin( dir1 - theta );
					real nXV2 = mag2*cos( dir2 - theta );
					real nYV2 = mag2*sin( dir1 - theta );
					real fXV1 = ((A.Mass-B.Mass)*nXV1 + (B.Mass+B.Mass)*nXV2)/(A.Mass+B.Mass);
					real fXV2 = ((A.Mass+A.Mass)*nXV1 + (B.Mass-A.Mass)*nXV2)/(A.Mass+B.Mass);
					real fYV1 = nYV1;
					real fYV2 = nYV2;

					A.XVelocity = cos(theta)*fXV1 + cos(theta+PI_2)*fYV1;
					A.YVelocity = sin(theta)*fXV1 + sin(theta+PI_2)*fYV1;
				}

				//A.Positions( A.XPosition - sectLength * unitX,
				//			 A.YPosition - sectLength * unitY );
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
