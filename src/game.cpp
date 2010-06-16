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
#ifndef GAME_CPP
#define GAME_CPP

#include <vector>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "entity.cpp"

#include "vector.cpp"
#include "keypress.cpp"
#include "click.cpp"

static char PROGRAM_NAME[ 15 ] = "Universum Meum";

class Game : public Entity
{
	static Game *m_Instance;

	public:
		static Game *Instance()
		{
			if( !m_Instance )
			{
				m_Instance = new Game;
			}
			return m_Instance;
		}

		static Game *Instance( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP )
		{ //{{{
			// TODO not well
			if( !m_Instance )
			{
				m_Instance = new Game( iWidth, iHeight, iBPP );
			}
			return m_Instance;
			/*
			if( m_Instance == 0 )
			{
				// TODO Error handling C++ style
					m_Instance = new Game( iWidth, iHeight, iBPP );
			}
			return m_Instance;
			*/
		} //}}}

		void InitSGL( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP )
		{ //{{{
			loadModules();

			if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
			{
				// TODO used to throw exception
			}
			SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
			SDL_SetVideoMode( iWidth, iHeight, iBPP, SDL_OPENGL );

			Width( iWidth );
			Height( iHeight );
			BPP( iBPP );
			ResizeViewport( iWidth, iHeight );

			SDL_WM_SetCaption( PROGRAM_NAME, 0 );

			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
			glEnable( GL_POINT_SMOOTH );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable( GL_POINT_SMOOTH );
			glEnable( GL_DEPTH_TEST );
			glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		void DeinitSGL()
		{ //{{{
			SDL_Quit();
			unloadModules();
		} //}}}

		void ResizeViewport( long double nWidth, long double nHeight )
		{ //{{{
			m_ViewWidth = nWidth;
			m_ViewHeight = nHeight;
			ResizeViewport();
		} //}}}

		void ResizeViewport()
		{ //{{{
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( 0, ViewWidth(), 0, ViewHeight(), -10, 10 );
			glMatrixMode( GL_MODELVIEW );
			Zoom( Width() / ViewWidth() );
		} //}}}

		/// Iterates through each actor that has been registered and calls its Draw function
		void Draw( long double magZoom = 1 )
		{ //{{{
			glPushMatrix();
			glTranslatef( -this->position.x, -this->position.y, 0 );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			for( std::vector< Entity >::iterator i = m_Entities.begin(); i != m_Entities.end(); i++ )
			{
				// TODO null i?
					i->Draw( Zoom() * magZoom );
			}
			glPopMatrix();
			SDL_GL_SwapBuffers();
		} //}}}

		void ProcessInput()
		{ //{{{
			/// Ditch old mousewheel events
			/// TODO look into a better way to do this, as currently we're throwing away potentially
			/// valid data. This is because each mouse wheel "click" is actually a press and release
			/// at the same time.
			for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ ) //{{{
			{
				if( ( i->button == SDL_BUTTON_WHEELUP ) || ( i->button == SDL_BUTTON_WHEELDOWN ) )
				{
					m_Clicks.erase( i );
					break;
				}
			} //}}}
			// handle all SDL events that we might've received in this loop
			// iteration TODO can this SDL_Poll... error?
			while( SDL_PollEvent( &m_Event ) )
			{
				switch( m_Event.type )
				{
					// user has clicked on the window's close button
					case SDL_QUIT:
					{ //{{{
						// set the done flag
						isDone( true );
						return;
					} //}}}

					// window has gained/lost attention
					case SDL_ACTIVEEVENT:
					{ //{{{
						if( m_Event.active.gain == 0 )
						{
							// lost focus
							isActive( false );
						}
						else
						{
							// gained focus
							isActive( true );
						}
						break;
					} //}}}

					// A key was pressed
					case SDL_KEYDOWN:
					{ //{{{
						m_Keypresses.push_back( Keypress( m_Event.key.keysym.sym, GetTicks() ) );
						break;
					} //}}}

					// A key was released
					case SDL_KEYUP:
					{ //{{{
						for( std::vector< Keypress >::iterator i = m_Keypresses.begin();
								i != m_Keypresses.end(); ++i )
						{
							if( i->SymCode() == m_Event.key.keysym.sym )
							{
								m_Keypresses.erase( i );
								break;
							}
						}
						break;
					} //}}}

					case SDL_MOUSEMOTION:
					{ //{{{
						m_Cursor.x = m_Event.motion.x;
						m_Cursor.y = m_Event.motion.y;
						break;
					} //}}}

					case SDL_MOUSEBUTTONDOWN:
					{ //{{{
						m_Clicks.push_back( Click( m_Event.button.x, m_Event.button.y,
											m_Event.button.button, GetTicks() ) );
						break;
					} //}}}

					case SDL_MOUSEBUTTONUP:
					{ //{{{
						if( ( m_Event.button.button == SDL_BUTTON_WHEELUP ) ||
							( m_Event.button.button == SDL_BUTTON_WHEELDOWN ) )
						{
							break;
						}
						for( std::vector< Click >::iterator i = m_Clicks.begin();
								i != m_Clicks.end(); i++ )
						{
							if( i->button == m_Event.button.button )
							{
								m_Clicks.erase( i );
								break;
							}
						}
						break;
					} //}}}

					// by default, we do nothing => break from the switch
					default:
					{ //{{{
						break;
					} //}}}
				}
			}

			return;
		} //}}}

		bool isClicked( int toCheckFor = SDL_BUTTON_LEFT )
		{ //{{{
			for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
			{
				if( i->button == toCheckFor )
				{
					return true;
				}
			}
			return false;
		} //}}}

		unsigned int ClickX( int button )
		{ //{{{
			for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
			{
				if( i->button == button )
				{
					return i->position.x;
				}
			}
			// TODO throw something
		} //}}}

		unsigned int ClickY( int button )
		{ //{{{
			for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
			{
				if( i->button == button )
				{
					return i->position.x;
				}
			}
			// TODO throw something
		} //}}}

		unsigned int ClickCreateTime( int button )
		{ //{{{
			for( std::vector< Click >::iterator i = m_Clicks.begin(); i != m_Clicks.end(); i++ )
			{
				if( i->button == button )
				{
					return i->createTime;
				}
			}
			// TODO throw something
		} //}}}

		void WarpMouse( unsigned int nX, unsigned int nY )
		{ //{{{
			m_Cursor.x = nX;
			m_Cursor.y = nY;
			SDL_WarpMouse( nX, nY);
		} //}}}

		bool isPressed( int toCheckFor = 27 )
		{ //{{{
			for( std::vector< Keypress >::iterator i = m_Keypresses.begin(); i != m_Keypresses.end(); i++ )
			{
				if( i->SymCode() == toCheckFor )
				{
					return true;
				}
			}
			return false;
		} //}}}

		/// {G,S}etter for m_Width
		void Width( unsigned int nWidth ) //{{{
		{
			m_Width = nWidth;
		}
		unsigned int Width()
		{
			return m_Width;
		} //}}}

		/// {G,S}etter for m_Height
		void Height( unsigned int nHeight ) //{{{
		{
			m_Height = nHeight;
		}
		unsigned int Height()
		{
			return m_Height;
		} //}}}

		/// {G,S}etter for m_BPP
		void BPP( unsigned int nBPP ) //{{{
		{
			m_BPP = nBPP;
		}
		unsigned int BPP()
		{
			return m_BPP;
		} //}}}

		void AddEntity( Entity *nEntity )
		{ //{{{
			if( nEntity != 0 )
			{
				m_Entities.push_back( *nEntity );
			}
			else
			{
				// TODO Error
			}
		} //}}}

		void RemoveEntity( Entity *toRemove )
		{ //{{{
			for( std::vector< Entity >::iterator i = m_Entities.begin(); i != m_Entities.end(); ++i )
			{
				// TODO WTF?
				/*
				if( (*i) == (*toRemove) )
				{
					m_Entities.erase( i );
				}
				*/
			}
		} //}}}

		unsigned int GetTicks()
		{ //{{{
			return SDL_GetTicks();
		} //}}}

		void WaitFor()
		{ //{{{
			static unsigned int now;
			now = GetTicks();

			if( m_NextTime > now )
			{
				SDL_Delay( m_NextTime - now );
			}
			else
			{
				/*
				char[] tlog = "Behind: " ~
					Integer.toString( cast( int )( m_NextTime - now ) );
				log.info( tlog );
				*/
			}
			m_NextTime += m_TickInterval;
		} //}}}

		void sleep( unsigned int microSeconds = 1000 )
		{ //{{{
			SDL_Delay( microSeconds );
		} //}}}

		/// {G,S}etter for m_TickInterval
		void TickInterval( unsigned int nTickInterval ) //{{{
		{
			m_TickInterval = nTickInterval;
		}
		unsigned int TickInterval()
		{
			return m_TickInterval;
		} //}}}

		/// {G,S}etter for m_isDone
		void isDone( bool nState ) //{{{
		{
			m_isDone = nState;
		}
		bool isDone()
		{
			return m_isDone;
		} //}}}

		/// {G,S}etter for m_isActive
		void isActive( bool nState ) //{{{
		{
			m_isActive = nState;
		}
		bool isActive()
		{
			return m_isActive;
		} //}}}

		/// Getter for m_ViewWidth
		/*void ViewWidth( long double nViewWidth ) //{{{
		{
			m_ViewWidth = nViewWidth;
		}*/
		long double ViewWidth()
		{
			return m_ViewWidth;
		} //}}}

		/// Getter for m_ViewHeight
		/*void ViewHeight( long double nViewHeight ) //{{{
		{
			m_ViewHeight = nViewHeight;
		}*/
		long double ViewHeight()
		{
			return m_ViewHeight;
		} //}}}

		/// Setter for both X/Y centers
		void Centers( long double nXC, long double nYC ) //{{{
		{
			this->position.x = nXC - ViewWidth() / 2;
			this->position.y = nYC - ViewHeight() / 2;
		} //}}}

		/// {G,S}etter for the X center
		long double XCenter() //{{{
		{
			return ViewWidth() / 2 + this->position.x;
		}
		void XCenter( long double nXC )
		{
			this->position.x = nXC - ViewWidth() / 2;
		} //}}}

		/// {G,S}etter for the Y center
		long double YCenter() //{{{
		{
			return ViewHeight() / 2 + this->position.y;
		}
		void YCenter( long double nYC )
		{
			this->position.y = nYC - ViewHeight() / 2;
		} //}}}

		/// {G,S}etter for the Cursor X
		unsigned int CursorX() //{{{
		{
			return m_Cursor.x;
		}
		void CursorX( unsigned int nCX )
		{
			WarpMouse( nCX, m_Cursor.y );
		} //}}}

		/// {G,S}etter for the Cursor Y
		unsigned int CursorY() //{{{
		{
			return m_Cursor.y;
		}
		void CursorY( unsigned int nCY )
		{
			WarpMouse( m_Cursor.x, nCY );
		} //}}}

		/// {G,S}etter for the Zoom
		void Zoom( long double nZoom ) //{{{
		{
			m_Zoom = nZoom;
		}
		long double Zoom()
		{
			return m_Zoom;
		} //}}}

	private: //{{{
		Game()
		{
		}

		Game( unsigned int iWidth, unsigned int iHeight, unsigned int iBPP )
		{
			InitSGL( iWidth, iHeight, iBPP );
		}

		Game( Game const& )
		{
		}

		Game& operator=( Game const& )
		{
		}

		// load modules needed to interface with C libs SDL, GL, IL
		void loadModules()
		{ //{{{
			if( ! m_ModulesLoaded )
			{
				// TODO Uhh......
				m_ModulesLoaded = true;
			}
			else
			{
				// TODO Error
			}
		} //}}}

		// unload modules needed to interface with C libs SDL, GL, IL
		void unloadModules()
		{ //{{{
			if( m_ModulesLoaded )
			{
				// TODO Uhm???
				m_ModulesLoaded = false;
			}
			else
			{
				// TODO something...
			}
		} //}}}

		// toggle {un}loaded state of modules
		void toggleModules()
		{ //{{{
			if( m_ModulesLoaded )
			{
				unloadModules();
			}
			else
			{
				loadModules();
			}
		} //}}}

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

		std::vector< Entity > m_Entities;

		SDL_Event m_Event;
		std::vector< Keypress > m_Keypresses;
		std::vector< Click > m_Clicks;
		Vector< unsigned int > m_Cursor;

		long double m_Zoom;

		//}}}
};

Game *Game::m_Instance = 0;

#endif // GAME_CPP
