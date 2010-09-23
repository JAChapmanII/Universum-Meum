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
#ifndef COLLAPSE_CPP
#define COLLAPSE_CPP

#include <cmath>

#include "../../particle.hpp"

template< int collConst >
void Collapse( Particle* A, Particle* B, long double deltaTime )
{ //{{{
	long double dist = Magnitude( A->position );

	if( ( dist > 0 ) && ( dist > A->radius ) )
	{
		long double dist3 = pow( dist, 3 );

		A->impulses.push_back( A->position * -( collConst / dist3 ) );
	}
} //}}}

Particle::Force DefaultCollapse = &Collapse< 0 >;

#endif // COLLAPSE_CPP
