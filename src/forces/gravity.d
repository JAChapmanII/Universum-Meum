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
module gravity;

class Gravity
{
	public:
		this()
		{
		}

		override void Work( Particle A, Particle B )
		{
			uint distX = A.XPosition - B.XPositon;
			uint distY = A.YPosition - B.YPosition;

			A.XAcceleration = A.XAcceleration + distX;
			A.YAcceleration = A.YAcceleration + distY;

			B.XAcceleration = B.XAcceleration - distX;
			B.XAcceleration = B.XAcceleration - distX;
		}

	protected:

	private:

}
