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

template< int collConst >
void Collapse( Particle* A, Particle* B, long double deltaTime )
{ //{{{
	long double dist2 = (A->XPosition()*A->XPosition()) + (A->YPosition()*A->YPosition());

	if( ( dist2 > 0 ) && ( dist2 > 400 ) )
	{
		long double dist3 = pow( dist2, 1.5 );

		A->XAcceleration( A->NextXAcceleration() +
			( collConst )*(-A->XPosition()) / ( dist3 ) );

		A->YAcceleration( A->NextYAcceleration() +
			( collConst )*(-A->YPosition()) / ( dist3 ) );
	}
} //}}}

Particle::Force DefaultCollapse = &Collapse< 0 >;
