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
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "entity.cpp"

#include "vector.cpp"
#include "keypress.cpp"
#include "click.cpp"

class Game : public Entity
{
	static Game *m_Instance;

	public:
		static Game *Instance();
		static Game *Instance( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP );

		void InitSGL( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP );
		void DeinitSGL();

		void ResizeViewport( long double nWidth, long double nHeight );
		void ResizeViewport();

		/// Iterates through each actor that has been registered and calls its Draw function
		void Draw( long double magZoom = 1 );

		void ProcessInput();

		bool isClicked( unsigned int toCheckFor = SDL_BUTTON_LEFT );
		unsigned int ClickX( unsigned int button );
		unsigned int ClickY( unsigned int button );
		unsigned int ClickCreateTime( unsigned int button );
		void WarpMouse( unsigned int nX, unsigned int nY );

		bool isPressed( unsigned int toCheckFor = 27 );
		unsigned int PressCreateTime( unsigned int button );

		/// {G,S}etter for m_Width
		void Width( unsigned int nWidth ); //{{{
		unsigned int Width();  //}}}

		/// {G,S}etter for m_Height
		void Height( unsigned int nHeight ); //{{{
		unsigned int Height(); //}}}

		/// {G,S}etter for m_BPP
		void BPP( unsigned int nBPP ); //{{{
		unsigned int BPP(); //}}}

		void AddEntity( Entity* nEntity );
		void RemoveEntity( Entity* toRemove );

		unsigned int GetTicks();
		void WaitFor();
		void sleep( unsigned int microSeconds = 1000 );

		/// {G,S}etter for m_TickInterval
		void TickInterval( unsigned int nTickInterval ); //{{{
		unsigned int TickInterval(); //}}}

		/// {G,S}etter for m_isDone
		void isDone( bool nState ); //{{{
		bool isDone(); //}}}

		/// {G,S}etter for m_isActive
		void isActive( bool nState ); //{{{
		bool isActive(); //}}}

		/// Getter for m_ViewWidth
		//void ViewWidth( long double nViewWidth ); //{{{
		long double ViewWidth(); //}}}

		/// Getter for m_ViewHeight
		//void ViewHeight( long double nViewHeight ); //{{{
		long double ViewHeight(); //}}}

		/// Setter for both X/Y centers
		void Centers( long double nXC, long double nYC );

		/// {G,S}etter for the X center
		long double XCenter(); //{{{
		void XCenter( long double nXC ); //}}}

		/// {G,S}etter for the Y center
		long double YCenter(); //{{{
		void YCenter( long double nYC ); //}}}

		/// {G,S}etter for the Cursor X
		unsigned int CursorX(); //{{{
		void CursorX( unsigned int nCX ); //}}}

		/// {G,S}etter for the Cursor Y
		unsigned int CursorY(); //{{{
		void CursorY( unsigned int nCY ); //}}}

		/// {G,S}etter for the Zoom
		void Zoom( long double nZoom ); //{{{
		long double Zoom(); //}}}

	private:
		//{{{
		Game();
		Game( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP );
		Game( Game const& );
		Game& operator=( Game const& );

		// load modules needed to interface with C libs SDL, GL, IL
		void loadModules();
		// unload modules needed to interface with C libs SDL, GL, IL
		void unloadModules();
		// toggle {un}loaded state of modules
		void toggleModules();

		unsigned int m_TickInterval;
		unsigned int m_NextTime;

		bool m_isDone;
		bool m_isActive;
		bool m_ModulesLoaded;

		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_BPP;

		long double m_ViewWidth;
		long double m_ViewHeight;

		std::vector< Entity* > m_Entities;

		SDL_Event m_Event;
		std::vector< Keypress > m_Keypresses;
		std::vector< Click > m_Clicks;
		Vector< unsigned int > m_Cursor;

		long double m_Zoom;

		//}}}
};

#endif // GAME_HPP
