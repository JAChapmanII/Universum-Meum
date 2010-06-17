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
#ifndef VECTOR_HPP
#define VECTOR_HPP

// 3 Dimensional vector class template, T is the type of component
template< class T >
class Vector
{
	public:
		/// Default constructor, X and Y components default to T's default
		Vector();

		/// Constructs a Vector with initial X and Y values
		Vector( T iX, T iY, T iZ );

		/// Set all members at once
		Vector< T > Set( T nX, T nY, T nZ );

		/// Set all members to zero, return zero vector
		Vector< T > Zero();

		/// Overloaded + operator
		Vector< T > opAdd( Vector r );
		/// Overloaded += operator
		Vector< T > opAddAssign( Vector r );

		/// Overloaded - operator
		Vector< T > opSub( Vector r );
		/// Overloaded -= operator
		Vector< T > opSubAssign( Vector r );

		/// Dot product of this and r
		T Dot( Vector r );
		/// Cross product of this and r
		Vector< T > Cross( Vector r );

		/// X component
		T x;
		/// Y component
		T y;
		/// Z component
		T z;

	private:

};

#endif // VECTOR_CPP
