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
#ifndef ELASTIC_COLLISOIN_CPP
#define ELASTIC_COLLISOIN_CPP

#include <math.h>
#include <iostream>

#include <SDL/SDL.h>

#include "../../particle.cpp"

int sgn( long double input )
{
	if (input >= 0)
	{
		return 1;
	}
	return -1;
}

/// Alters particle A by applying an force resulting from a elastic collision between A and B
template< int elasticityConst >
void ElasticCollision( Particle* A, Particle* B, long double deltaTime )
{ //{{{
	// TODO, uhm...
	//if( A != B)
	//{
		long double xDist = A->XPosition() - B->XPosition();
		long double yDist = A->YPosition() - B->YPosition();
		long double dist2 = (xDist * xDist) + (yDist * yDist);
		long double dist  = sqrt( dist2 );
		long double sumR = A->radius + B->radius;

		if( ( dist < sumR ) && ( dist > 0 ) )
		{
			long double sectLength = (A->radius+B->radius) - dist;
			long double unitX = xDist / dist;
			long double unitY = yDist / dist;

			A->XPosition( A->XPosition() + ( unitX * sectLength ) / 2 );
			A->YPosition( A->YPosition() + ( unitY * sectLength ) / 2 );

			/*long double xDist = B.XPosition - A.XPosition;
			long double yDist = B.YPosition - A.YPosition;
			long double dist2 = (xDist * xDist) + (yDist * yDist);
			long double dist  = sqrt( dist2 );*/

			long double theta = atan2( yDist, xDist );
			long double dir1 = atan2( A->YVelocity(), A->XVelocity() );
			long double dir2 = atan2( B->YVelocity(), B->XVelocity() );
			long double nYV1 = A->speed * sin( dir1 - theta );
			long double fXV1 = ( ( A->mass - B->mass ) * ( A->speed * cos( dir1 - theta ) ) + 2 *
						B->mass * ( B->speed * cos( dir2 - theta ) ) ) / ( A->mass + B->mass );

			long double nYV2 = B->speed * sin( dir1 - theta );
			A->XVelocity( (cos(theta) * fXV1 + cos(theta+PI_2) * nYV1));
			A->YVelocity( (sin(theta) * fXV1 + sin(theta+PI_2) * nYV1));
		}
	//}
}//}}}

Particle::Force DefaultElasticCollision = &ElasticCollision< 0 >;

#endif // ELASTIC_COLLISOIN_CPP
