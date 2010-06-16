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

/// 2 Dimensional vector class
class Vector
{
	public:
		/// Default constructor, X and Y components default to real.nan
		this()
		{ //{{{
		} //}}}

		/// Constructs a Vector with initial X and Y values
		this( real iX, real iY, real iZ )
		{ //{{{
			x = iX;
			y = iY;
			z = iZ;
		} //}}}

		/// Overloaded + operator
		Vector opAdd( const ref Vector r )
		{ //{{{
			return Vector( x + r.x, y + r.y, z + r.z );
		} //}}}

		/// Overloaded += operator
		Vector opAddAssign( const ref Vector r )
		{ //{{{
			x += r.x;
			y += r.y;
			z += r.z;
			return this;
		} //}}}

		/// Overloaded - operator
		Vector opSub( const ref Vector r )
		{ //{{{
			return Vector( x - r.x, y - r.y, z - r.z );
		} //}}}

		/// Overloaded -= operator
		Vector opSubAssign( const ref Vector )
		{ //{{{
			x -= r.x;
			y -= r.y;
			z -= r.z;
			return this;
		} //}}}

		/// Dot product of this and r
		real Dot( const ref Vector r )
		{ //{{{
			return ( x * r.x ) + ( y * r.y ) + ( z * r.z );
		} //}}}

		/// Cross product of this and r
		Vector Cross( const ref Vector r )
		{ //{{{
			return Vector( y * r.z - z * r.y,
						   z * r.x - x * r.z,
						   x * r.y - y * r.x );
		} //}}}

		/// X component
		real x;
		/// Y component
		real y;

	protected:

	private:

}
