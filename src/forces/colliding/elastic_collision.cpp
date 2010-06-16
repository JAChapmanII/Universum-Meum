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

#include <SDL/SDL.h>

#include "../../force.cpp"
#include "../../particle.cpp"

Logger log;
static this()
{
	log = Log.lookup( "forces.elastic_collision" );
	log.add( new AppendConsole() );
}

/// Alters particle A by applying an force resulting from a elastic collision between A and B
void ElasticCollision( long double elasticityConst )( Particle A, Particle B, ref long double deltaTime )
{ //{{{

	int sgn( long double input )
	{
		if (input >= 0)
		{
			return 1;
		}
		return -1;
	}

if( A != B)
{
	long double xDist = A.XPosition - B.XPosition;
	long double yDist = A.YPosition - B.YPosition;
	long double dist2 = (xDist * xDist) + (yDist * yDist);
	long double dist  = sqrt( dist2 );

	if( dist < (A.Radius + B.Radius))
	{
		if( xDist  < (A.Radius + B.Radius))
		{
			Stdout.formatln("A.XPosition is {}", A.XPosition);
			A.XPosition = A.XPosition + ((0.5 * (sgn(xDist)))*((A.Radius + B.Radius) - (abs(xDist))));
		}

		Stdout.formatln("A.XPosition is {}", A.XPosition);
		Stdout.formatln("A.XPosition Dif is {}", ((0.5 * (sgn(xDist)))*((A.Radius + B.Radius) - (abs(xDist)))));

//SDL_Delay(10000);


		if( yDist  < (A.Radius + B.Radius))
		{
			A.YPosition = A.YPosition + ((0.5 * (sgn(yDist)))*((A.Radius + B.Radius) - (abs(yDist))));
		}



		/*long double xDist = B.XPosition - A.XPosition;
		long double yDist = B.YPosition - A.YPosition;
		long double dist2 = (xDist * xDist) + (yDist * yDist);
		long double dist  = sqrt( dist2 );*/

		long double theta = atan2( yDist, xDist );
		long double dir1 = atan2( A.YVelocity, A.XVelocity );
		long double dir2 = atan2( B.YVelocity, B.XVelocity );
		long double nYV1 = A.Speed * sin( dir1 - theta );
		long double fXV1 = ( ( A.Mass - B.Mass ) * ( A.Speed * cos( dir1 - theta ) ) + 2 *
					B.Mass * ( B.Speed * cos( dir2 - theta ) ) ) / ( A.Mass + B.Mass );

		long double nYV2 = B.Speed * sin( dir1 - theta );
		A.XVelocity = (cos(theta) * fXV1 + cos(theta+PI_2) * nYV1) * 0.5 ;
		A.YVelocity = (sin(theta) * fXV1 + sin(theta+PI_2) * nYV1) * 0.5 ;
		}
	}
}//}}}

Force DefaultElasticCollision = &ElasticCollision!( 0.0 );
