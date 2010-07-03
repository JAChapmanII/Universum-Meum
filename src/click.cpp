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
#ifndef CLICK_CPP
#define CLICK_CPP

#include "vector.cpp"

/// Holds information about the location and type of a mouse click
class Click
{
	public:
		/// Construct with a position, time, and mouse button
		Click( unsigned int iX, unsigned int iY,
				unsigned int iButton, unsigned int cTime ) :
			position( iX, iY, 0 ),
			createTime( cTime ),
			button( iButton )
		{
		}

		/// Coordinates of click in pixels
		Vector< unsigned int > position;
		/// Time of click in ticks since SDL has been initialized
		unsigned int createTime;
		/// Which mouse button was clicked
		unsigned int button;

	private:

};

#endif // CLICK_CPP
