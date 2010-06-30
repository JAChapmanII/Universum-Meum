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
#ifndef GRAVITY_CPP
#define GRAVITY_CPP

#include <math.h>

#include "../../particle.cpp"

/// Alters particle A by applying an acceleration equal to that of a force like gravity over deltaTime
template< int gravConst >
void Gravity( Particle* A, Particle* B, long double deltaTime )
{ //{{{
	/**
	 * Formula for universal gravitation:
	 * \f[
	 *   \vec{F}=\left\{
	 *       \frac{Gm_1m_2}{r^2}
	 *       \right\}
	 * \f]
	 */
	Vector< long double > distance = B->position - A->position;
	long double dist = distance.Magnitude();

	if( dist > 0 )
	{
		long double dist3 = pow( dist, 3 );

		A->impulses.push_back( distance * ( gravConst * B->mass / dist3 ) );

		B->impulses.push_back( distance * -( gravConst * A->mass / dist3 ) );
	}
} //}}}

Particle::Force DefaultGravity = &Gravity< 0 >;

#endif // GRAVITY_CPP
