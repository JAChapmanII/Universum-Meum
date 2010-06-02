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
module click;

class Click
{
	public:
		this( uint iX, uint iY, uint iButton, uint cTime )
		{
			m_Position[ 0 ] = iX;
			m_Position[ 1 ] = iY;
			m_CreateTime = cTime;
			m_Button = iButton;
		}

		uint XPosition()
		{
			return m_Position[ 0 ];
		}
		uint YPosition()
		{
			return m_Position[ 1 ];
		}

		uint CreateTime()
		{
			return m_CreateTime;
		}

		uint Button()
		{
			return m_Button;
		}

	protected:
		uint[ 2 ] m_Position;
		uint m_CreateTime;
		uint m_Button;

	private:

}
