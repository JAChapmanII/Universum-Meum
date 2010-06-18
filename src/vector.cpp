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
#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "vector.hpp"

/// Default constructor, X and Y components default to T's default
template< class T >
Vector< T >::Vector() :
	x( 0 ), //{{{
	y( 0 ),
	z( 0 )
{
} //}}}

/// Constructs a Vector with initial X, Y and Z values
template< class T >
Vector< T >::Vector( T iX, T iY, T iZ ) :
	x( iX ), //{{{
	y( iY ),
	z( iZ )
{
} //}}}

/// Copy consructs a Vector with initial X, Y and Z values
template< class T >
Vector< T >::Vector( Vector< T > const& r ) :
	x( r.x ), //{{{
	y( r.y ),
	z( r.z )
{
} //}}}

/// Set all members at once
template< class T >
Vector< T > Vector< T >::Set( T nX, T nY, T nZ )
{ //{{{
	x = nX;
	y = nY;
	z = nZ;
} //}}}

/// Set all members to zero, return zero vector
template< class T >
Vector< T > Vector< T >::Zero()
{ //{{{
	x = 0;
	y = 0;
	z = 0;
	return *this;
} //}}}

/// Overloaded + operator
template< class T >
Vector< T > Vector< T >::opAdd( Vector r )
{ //{{{
	return new Vector< T >( x + r.x, y + r.y, z + r.z );
} //}}}

/// Overloaded += operator
template< class T >
Vector< T > Vector< T >::opAddAssign( Vector r )
{ //{{{
	x += r.x;
	y += r.y;
	z += r.z;
	return this;
} //}}}

/// Overloaded - operator
template< class T >
Vector< T > Vector< T >::opSub( Vector r )
{ //{{{
	return new Vector< T >( x - r.x, y - r.y, z - r.z );
} //}}}

/// Overloaded -= operator
template< class T >
Vector< T > Vector< T >::opSubAssign( Vector r )
{ //{{{
	x -= r.x;
	y -= r.y;
	z -= r.z;
	return this;
} //}}}

/// Dot product of this and r
template< class T >
T Vector< T >::Dot( Vector r )
{ //{{{
	return ( x * r.x ) + ( y * r.y ) + ( z * r.z );
} //}}}

/// Cross product of this and r
template< class T >
Vector< T > Vector< T >::Cross( Vector r )
{ //{{{
	return new Vector< T >( y * r.z - z * r.y,
							z * r.x - x * r.z,
							x * r.y - y * r.x );
} //}}}

#endif // VECTOR_CPP
