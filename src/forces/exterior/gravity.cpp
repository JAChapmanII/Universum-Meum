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

#include <math.h>

#include "../../particle.cpp"

/// Alters particle A by applying an acceleration equal to that of a force like gravity over deltaTime
template< int gravConst >
void Gravity( Particle* A, Particle* B, long double deltaTime )
{ //{{{
	long double xDist = B->XPosition() - A->XPosition();
	long double yDist = B->YPosition() - A->YPosition();
	long double dist2 = (xDist * xDist) + (yDist * yDist);

	if( dist2 > 0 )
	{
		long double dist  = sqrt( dist2 );

		A->XAcceleration( A->NextXAcceleration() +
			( gravConst * B->mass )*(xDist/dist) / ( dist2 ) );

		A->YAcceleration( A->NextYAcceleration() +
			( gravConst * B->mass )*(yDist/dist) / ( dist2 ) );

		B->XAcceleration( B->NextXAcceleration() +
			( gravConst * A->mass )*(-xDist/dist) / ( dist2 ) );

		B->YAcceleration( B->NextYAcceleration() +
			( gravConst * A->mass )*(-yDist/dist) / ( dist2 ) );
	}
} //}}}

Particle::Force DefaultGravity = &Gravity< 0 >;
