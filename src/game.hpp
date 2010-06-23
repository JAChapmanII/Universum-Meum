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

/** \brief Game is used to manage rendering and input.
 *
 * Game maintains a std::vector of actors to draw everytime Game::Draw is called. It inherits form
 * Entity and uses it's properties much as how you would expect any Entity to. Input is handled
 * using std::vector's of Keypress and Click classes.
 * \note Game is a singleton!
 */
class Game : public Entity
{
	static Game *m_Instance;

	public:
		/// Create/Return a pointer to the single allowed instance of the Game class.
		static Game *Instance();
		/// Create/Return pointer to singleton, using these window properties if creating one
		static Game *Instance( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP );

		/// Create an SDL_Surface for the Window and set some OpenGL properties
		void InitSGL( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP );
		/// Undo stuff InitSGL does to get ready to die
		void DeinitSGL();

		/// Change the size of the OpenGL space to the values passed in
		void ResizeViewport( long double nWidth, long double nHeight );
		/// Change the size of the OpenGL space to m_ViewWidth, m_ViewHeight
		void ResizeViewport();

		/// Iterates through each actor that has been registered and calls its Draw function
		void Draw( long double magZoom = 1 );

		/// Iterate through all SDL events and handle them accordingly
		void ProcessInput();

		/// Check to see if some mouse button is currently pressed
		bool isClicked( unsigned int toCheckFor = SDL_BUTTON_LEFT );
		/// Find out the x position of a mouse button click
		unsigned int ClickX( unsigned int button );
		/// Find out the y position of a mouse button click
		unsigned int ClickY( unsigned int button );
		/// Find out the creation time of a mouse button click
		unsigned int ClickCreateTime( unsigned int button );
		/// Move the Cursor to a new location based on arguments
		void WarpMouse( unsigned int nX, unsigned int nY );

		/// Check to see if some key is pressed
		bool isPressed( unsigned int toCheckFor = 27 );
		/// Find out when a key was pressed
		unsigned int PressCreateTime( unsigned int button );

		/// Setter for m_Width
		void Width( unsigned int nWidth );
		/// Getter for m_Width
		unsigned int Width();

		/// Setter for m_Height
		void Height( unsigned int nHeight );
		/// Getter for m_Height
		unsigned int Height();

		/// Setter for m_BPP
		void BPP( unsigned int nBPP );
		/// Getter for m_BPP
		unsigned int BPP();

		/// Add an entity to be tracked/drawn/updated by Game
		void AddEntity( Entity* nEntity );
		/// Find toRemove in the vector of entities and remove it
		void RemoveEntity( Entity* toRemove );

		/// Return the result of SDL_GetTicks()
		unsigned int GetTicks();
		/// Block until m_NextTime
		void WaitFor();
		/// Block for microSeconds number of microSeconds
		void sleep( unsigned int microSeconds = 1000 );

		/// Setter for m_TickInterval
		void TickInterval( unsigned int nTickInterval );
		/// Getter for m_TickInterval
		unsigned int TickInterval();

		/// Getter for m_isDone
		void isDone( bool nState );
		/// Getter for m_isDone
		bool isDone();

		/// Setter for m_isActive
		void isActive( bool nState );
		/// Getter for m_isActive
		bool isActive();

		/// Getter for m_ViewWidth
		//void ViewWidth( long double nViewWidth );
		long double ViewWidth();

		/// Getter for m_ViewHeight
		//void ViewHeight( long double nViewHeight );
		long double ViewHeight();

		/// Setter for both X/Y centers
		void Centers( long double nXC, long double nYC );

		/// Getter for the X center
		long double XCenter();
		/// Setter for the X center
		void XCenter( long double nXC );

		/// Getter for the Y center
		long double YCenter();
		/// Setter for the Y center
		void YCenter( long double nYC );

		/// Getter for the Cursor X
		unsigned int CursorX();
		/// Setter for the Cursor X
		void CursorX( unsigned int nCX );

		/// Getter for the Cursor Y
		unsigned int CursorY();
		/// Setter for the Cursor Y
		void CursorY( unsigned int nCY );

		/// Setter for the Zoom
		void Zoom( long double nZoom );
		/// Getter for the Zoom
		long double Zoom();

	private:
		//{{{
		/// Internal default constructor
		Game();
		/// Internal constructor to also call InitSGL
		Game( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP );
		/// Copy constructor (not needed because Game is a singleton)
		Game( Game const& );
		/// Equals operator (not needed because Game is a singleton)
		Game& operator=( Game const& );

		/// Amount of time to wait on WaitFor
		unsigned int m_TickInterval;
		/// Time to wait for when WaitFor is called
		unsigned int m_NextTime;

		/// Set to true if the program recieves a quit request
		bool m_isDone;
		/// Set to false when the WM of the user unfocuses/minimizes the window
		bool m_isActive;

		/// Width of window
		unsigned int m_Width;
		/// Height of window
		unsigned int m_Height;
		/// Bits per pixel of window
		unsigned int m_BPP;

		/// Width of OpenGL space
		long double m_ViewWidth;
		/// Height of OpenGL space
		long double m_ViewHeight;

		/// List of entities to be manipulated/controlled by Game
		std::vector< Entity* > m_Entities;

		/// SDL_Event for input event gathering
		SDL_Event m_Event;
		/// List of all keys that have been pressed, and when
		std::vector< Keypress > m_Keypresses;
		/// List of how, when, and where a mouse button has been pressed
		std::vector< Click > m_Clicks;
		/// Position of Cursor in window (not OpenGL) coordinates
		Vector< unsigned int > m_Cursor;

		/// "Zoom" level (Widow Width/OpenGL context Width)
		long double m_Zoom;

		//}}}
};

#endif // GAME_HPP
