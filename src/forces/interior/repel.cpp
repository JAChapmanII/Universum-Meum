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
#ifndef REPEL_CPP
#define REPEL_CPP

#include <math.h>

#include "../../particle.cpp"

/// Alters particle A by applying an acceleration equal to that of a force like antigravity over deltaTime
template< int repConst >
void Repel( Particle* A, Particle* B, long double deltaTime )
{ //{{{
	long double xDist = B->XPosition() - A->XPosition();
	long double yDist = B->YPosition() - A->YPosition();
	long double dist2 = (xDist * xDist) + (yDist * yDist);
	long double dist  = sqrt( dist2 );

	if( ( dist < (A->radius + B->radius) ) && ( dist2 > 0 ) )
	{
		long double unitX = xDist / dist;
		long double unitY = yDist / dist;

		A->XAcceleration( A->NextXAcceleration() -
			( repConst * 2.0 * B->mass ) * ( unitX ) / ( dist2 ) );

		A->YAcceleration( A->NextYAcceleration() -
			( repConst * 2.0 * B->mass ) * ( unitY ) / ( dist2 ) );

		B->XAcceleration( B->NextXAcceleration() +
			( repConst * 2.0 * A->mass ) * ( unitX ) / ( dist2 ) );

		B->YAcceleration( B->NextYAcceleration() +
			( repConst * 2.0 * A->mass ) * ( unitY ) / ( dist2 ) );
	}
} //}}}

Particle::Force DefaultRepel = &Repel< 0 >;

#endif // REPEL_CPP
