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
module vector;

/// 3 Dimensional vector class template, T is the type of component
class Vector( T )
{
	public:
		/// Default constructor, X and Y components default to T's default
		this()
		{ //{{{
		} //}}}

		/// Constructs a Vector with initial X and Y values
		this( T iX, T iY, T iZ )
		{ //{{{
			this.x = iX;
			this.y = iY;
			this.z = iZ;
		} //}}}

		/// Overloaded + operator
		Vector opAdd( Vector r )
		{ //{{{
			return new Vector( x + r.x, y + r.y, z + r.z );
		} //}}}

		/// Overloaded += operator
		Vector opAddAssign( Vector r )
		{ //{{{
			x += r.x;
			y += r.y;
			z += r.z;
			return this;
		} //}}}

		/// Overloaded - operator
		Vector opSub( Vector r )
		{ //{{{
			return new Vector( x - r.x, y - r.y, z - r.z );
		} //}}}

		/// Overloaded -= operator
		Vector opSubAssign( Vector r )
		{ //{{{
			x -= r.x;
			y -= r.y;
			z -= r.z;
			return this;
		} //}}}

		/// Dot product of this and r
		T Dot( Vector r )
		{ //{{{
			return ( x * r.x ) + ( y * r.y ) + ( z * r.z );
		} //}}}

		/// Cross product of this and r
		Vector Cross( Vector r )
		{ //{{{
			return new Vector( y * r.z - z * r.y,
							   z * r.x - x * r.z,
							   x * r.y - y * r.x );
		} //}}}

		/// X component
		T x;
		/// Y component
		T y;
		/// Z component
		T z;

	protected:

	private:

}
