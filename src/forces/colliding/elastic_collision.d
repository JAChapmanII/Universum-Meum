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

/// Alters particle A by applying an force resulting from a elastic collision between A and B
void ElasticCollision( real elasticityConst )( Particle A, Particle B, ref real deltaTime )
{ //{{{

	int sgn( real input )
	{
		if (input >= 0)
		{
			return 1;
		}
		return -1;
	}


	real NextxDist = B.NextXPosition - A.NextXPosition;
	real NextyDist = B.NextYPosition - A.NextYPosition;
	real Nextdist2 = (NextxDist * NextxDist) + (NextyDist * NextyDist);
	real Nextdist  = sqrt( Nextdist2 );

	if( Nextdist < (A.Radius + B.Radius))
	{
		if( NextxDist  < (A.Radius + B.Radius))
		{
			A.XPosition = A.XPosition + ((0.5 * (sgn(A.NextXPosition - B.NextXPosition)))*((A.Radius + B.Radius) - (A.NextXPosition - B.NextXPosition)));
		}
		if( NextyDist  < (A.Radius + B.Radius))
		{
			A.YPosition = A.YPosition + ((0.5 * (sgn(A.NextYPosition - B.NextYPosition)))*((A.Radius + B.Radius) - (A.NextYPosition - B.NextYPosition)));
		}
	}
		real xDist = B.XPosition - A.XPosition;
		real yDist = B.YPosition - A.YPosition;
		real dist2 = (xDist * xDist) + (yDist * yDist);
		real dist  = sqrt( dist2 );

		real theta = atan2( yDist, xDist );
		real dir1 = atan2( A.YVelocity, A.XVelocity );
		real dir2 = atan2( B.YVelocity, B.XVelocity );
		real nYV1 = A.Speed * sin( dir1 - theta );
		real fXV1 = ( ( A.Mass - B.Mass ) * ( A.Speed * cos( dir1 - theta ) ) + 2 *
					B.Mass * ( B.Speed * cos( dir2 - theta ) ) ) / ( A.Mass + B.Mass );

		real nYV2 = B.Speed * sin( dir1 - theta );
		A.XVelocity = cos(theta) * fXV1 + cos(theta+PI_2) * nYV1;
		A.YVelocity = sin(theta) * fXV1 + sin(theta+PI_2) * nYV1;

		}//}}}

Force DefaultElasticCollision = &ElasticCollision!( 0.0 );
