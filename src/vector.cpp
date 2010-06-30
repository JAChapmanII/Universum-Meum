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

template< class T >
Vector< T >::Vector() :
	x( 0 ), //{{{
	y( 0 ),
	z( 0 )
{
} //}}}

template< class T >
Vector< T >::Vector( T iX, T iY, T iZ ) :
	x( iX ), //{{{
	y( iY ),
	z( iZ )
{
} //}}}

template< class T >
Vector< T >::Vector( Vector< T > const& r ) :
	x( r.x ), //{{{
	y( r.y ),
	z( r.z )
{
} //}}}

template< class T >
Vector< T > Vector< T >::Set( T nX, T nY, T nZ )
{ //{{{
	x = nX;
	y = nY;
	z = nZ;
} //}}}

template< class T >
Vector< T > Vector< T >::Set( Vector< T > nThis )
{ //{{{
	this->x = nThis.x;
	this->y = nThis.y;
	this->z = nThis.z;
	return *this;
} //}}}

template< class T >
Vector< T > Vector< T >::Zero()
{ //{{{
	x = 0;
	y = 0;
	z = 0;
	return *this;
} //}}}

template< class T >
T Vector< T >::Magnitude()
{ //{{{
	return sqrt( this->x*this->x + this->y*this->y + this->z*this->z );
} //}}}

template< class T >
Vector< T > Vector< T >::operator+( Vector< T > r ) const
{ //{{{
	return Vector< T >( this->x + r.x, this->y + r.y, this->z + r.z );
} //}}}

template< class T >
Vector< T > &Vector< T >::operator+=( const Vector &r )
{ //{{{
	this->x += r.x;
	this->y += r.y;
	this->z += r.z;
	return *this;
} //}}}

template< class T >
Vector< T > Vector< T >::operator-( Vector< T > r ) const
{ //{{{
	return Vector< T >( this->x - r.x, this->y - r.y, this->z - r.z );
} //}}}

template< class T >
Vector< T > &Vector< T >::operator-=( const Vector< T > &r )
{ //{{{
	this->x -= r.x;
	this->y -= r.y;
	this->z -= r.z;
	return *this;
} //}}}

template< class T >
Vector< T > &Vector< T >::operator/=( const Vector< T > &r )
{ //{{{
	this->x /= r.x;
	this->y /= r.y;
	this->z /= r.z;
	return *this;
} //}}}

template< class T >
Vector< T > Vector< T >::operator*( T r ) const
{ //{{{
	return Vector< T >( this->x * r, this->y * r, this->z * r );
} //}}}

template< class T >
Vector< T > Vector< T >::operator/( T r ) const
{ //{{{
	return Vector< T >( this->x / r, this->y / r, this->z / r );
} //}}}

template< class T >
Vector< T > Vector< T >::operator/=( T r )
{ //{{{
	this->x /= r;
	this->y /= r;
	this->z /= r;
	return *this;
} //}}}

template< class T >
T Vector< T >::Dot( Vector r )
{ //{{{
	return ( x * r.x ) + ( y * r.y ) + ( z * r.z );
} //}}}

template< class T >
Vector< T > Vector< T >::Cross( Vector r )
{ //{{{
	return new Vector< T >( y * r.z - z * r.y,
							z * r.x - x * r.z,
							x * r.y - y * r.x );
} //}}}

#endif // VECTOR_CPP
