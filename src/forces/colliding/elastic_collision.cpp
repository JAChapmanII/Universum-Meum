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

/// Alters particle A by applying an force resulting from a elastic collision between A and B
template< int elasticityConst >
void ElasticCollision( Particle* A, Particle* B, long double deltaTime )
{ //{{{
	Vector< long double > distance = A->position - B->position;
	long double dist = distance.Magnitude();
	long double sumR = A->radius + B->radius;

	if( ( dist < sumR ) && ( dist > 0 ) )
	{
		long double sectLength = (A->radius+B->radius) - dist;
		distance /= dist;
		//long double unitX = xDist / dist;
		//long double unitY = yDist / dist;

		A->movers.push_back( distance * ( sectLength / 2 ) );
		B->movers.push_back( distance * -( sectLength / 2 ) );

		long double theta = atan2( distance.y, distance.x );
		long double theta2 = atan2( -distance.y, -distance.x );
		long double dir1 = atan2( A->velocity.y, A->velocity.x );
		long double dir2 = atan2( B->velocity.y, B->velocity.x );

		long double nYV1 = A->speed * sin( dir1 - theta );
		long double fXV1 = ( ( A->mass - B->mass ) * ( A->speed * cos( dir1 - theta ) ) + 2 *
					B->mass * ( B->speed * cos( dir2 - theta ) ) ) / ( A->mass + B->mass );

		A->impulses.push_back( Vector< long double >(
						(cos( theta ) * fXV1 + cos( theta + M_PI_2 ) * nYV1 ) - A->velocity.x,
						(sin( theta ) * fXV1 + sin( theta + M_PI_2 ) * nYV1 ) - B->velocity.y, 0 ) );

		long double nYV2 = B->speed * sin( dir2 - theta2 );
		long double fXV2 = ( ( B->mass - A->mass ) * ( B->speed * cos( dir2 - theta2 ) ) + 2 *
					A->mass * ( A->speed * cos( dir1 - theta2 ) ) ) / ( B->mass + A->mass );

		B->impulses.push_back( Vector< long double >(
						(cos( theta2 ) * fXV2 + cos( theta2 + M_PI_2 ) * nYV2 ) - B->velocity.x,
						(sin( theta2 ) * fXV2 + sin( theta2 + M_PI_2 ) * nYV2 ) - B->velocity.y, 0 ) );
	}
}//}}}

Particle::Force DefaultElasticCollision = &ElasticCollision< 0 >;

#endif // ELASTIC_COLLISOIN_CPP
