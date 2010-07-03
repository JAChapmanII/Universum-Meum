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
#ifndef KEYPRESS_CPP
#define KEYPRESS_CPP

/// Holds information about an SDL_Event that is a keyboard key press
class Keypress
{
	public:
		/// Construct with some values
		Keypress( unsigned int iSymCode, unsigned int iCreateTime ) :
			m_SymCode( iSymCode ),
			m_CreateTime( iCreateTime )
		{
		}

		/// Return m_SymCode
		unsigned int SymCode()
		{
			return m_SymCode;
		}

		/// Return m_CreateTime
		unsigned int CreateTime()
		{
			return m_CreateTime;
		}

	private:
		// TODO Might want to make these public and not worry about getters, and
		// and assume that they might have been changed after creation TODO
		unsigned int m_SymCode;
		unsigned int m_CreateTime;

};

#endif // KEYPRESS_CPP
