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
module game;

import tango.util.container.LinkedList;
import tango.util.log.Log;
import tango.util.log.AppendConsole;
import Integer = tango.text.convert.Integer;

import derelict.opengl.gl;
import derelict.sdl.sdl;

import entity;

import vector;
import keypress;
import click;

// Set up logging
Logger log; //{{{
static this()
{
	log = Log.lookup( "game" );
	log.add( new AppendConsole() );
}
// }}}

static char[] PROGRAM_NAME = "Universum Meum";

public class Game : Entity
{
	public:
		static Game Instance( uint iWidth, uint iHeight, uint iBPP )
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new Game( iWidth, iHeight, iBPP );
				}
				catch( Exception e )
				{
					log.fatal( "Game could not be instantiated." );
					throw e;
				}
			}
			return m_Instance;
		} //}}}

		alias Instance opCall;

		void InitSGL( uint iWidth, uint iHeight, uint iBPP )
		{ //{{{
			loadModules();

			if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
			{
				log.fatal( "SDL could not initialize." );
				throw new Exception( "SDL failed to initialize." );
			}
			SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
			SDL_SetVideoMode( iWidth, iHeight, iBPP, SDL_OPENGL );

			Width = iWidth;
			Height = iHeight;
			BPP = iBPP;
			ResizeViewport( iWidth, iHeight );

			SDL_WM_SetCaption( cast( char* )PROGRAM_NAME, null );


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

		void ResizeViewport( real nWidth, real nHeight )
		{ //{{{
			m_ViewWidth = nWidth;
			m_ViewHeight = nHeight;
			ResizeViewport();
		} //}}}

		void ResizeViewport()
		{ //{{{
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( 0, ViewWidth, 0, ViewHeight, -10, 10 );
			glMatrixMode( GL_MODELVIEW );
			Zoom = Width() / ViewWidth();
		} //}}}

		/// Iterates through each actor that has been registered and calls its Draw function
		override void Draw( real magZoom = 1 )
		{ //{{{
			glPushMatrix();
			glTranslatef( -this.position.x, -this.position.y, 0 );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			foreach( i; m_Entities )
			{
				if( i is null )
				{
					log.warn( "Tried to Draw null object" );
				}
				else
				{
					i.Draw( Zoom * magZoom );
				}
			}
			glPopMatrix();
			SDL_GL_SwapBuffers();
		} //}}}

		void ProcessInput()
		{ //{{{
			/// Ditch old mousewheel events
			/// TODO look into a better way to do this, as currently we're throwing away potentially
			/// valid data. This is because each mouse wheel "click" is actually a press and release
			/// at the same time. /TODO
			foreach( i; m_Clicks ) //{{{
			{
				if( ( i.Button == SDL_BUTTON_WHEELUP ) || ( i.Button == SDL_BUTTON_WHEELDOWN ) )
				{
					m_Clicks.remove( i );
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
						isDone = true;
						return;
					} //}}}

					// window has gained/lost attention
					case SDL_ACTIVEEVENT:
					{ //{{{
						if( m_Event.active.gain == 0 )
						{
							// lost focus
							isActive = false;
						}
						else
						{
							// gained focus
							isActive = true;
						}
						break;
					} //}}}

					// A key was pressed
					case SDL_KEYDOWN:
					{ //{{{
						m_Keypresses.add( new Keypress( m_Event.key.keysym.sym, GetTicks ) );
						break;
					} //}}}

					// A key was released
					case SDL_KEYUP:
					{ //{{{
						foreach( i; m_Keypresses )
						{
							if( i.SymCode == m_Event.key.keysym.sym )
							{
								m_Keypresses.remove( i );
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
						m_Clicks.add( new Click( m_Event.button.x, m_Event.button.y,
									m_Event.button.button, GetTicks ) );
						break;
					} //}}}

					case SDL_MOUSEBUTTONUP:
					{ //{{{
						if( ( m_Event.button.button == SDL_BUTTON_WHEELUP ) ||
							( m_Event.button.button == SDL_BUTTON_WHEELDOWN ) )
						{
							break;
						}
						foreach( i; m_Clicks )
						{
							if( i.Button == m_Event.button.button )
							{
								m_Clicks.remove( i );
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
			foreach( i; m_Clicks )
			{
				if( i.Button == toCheckFor )
				{
					return true;
				}
			}
			return false;
		} //}}}

		uint ClickX( int button )
		{ //{{{
			foreach( i; m_Clicks )
			{
				if( i.Button == button )
				{
					return i.XPosition;
				}
			}
			throw new Exception( "Button is not pressed" );
		} //}}}

		uint ClickY( int button )
		{ //{{{
			foreach( i; m_Clicks )
			{
				if( i.Button == button )
				{
					return i.YPosition;
				}
			}
			throw new Exception( "Button is not pressed" );
		} //}}}

		uint ClickCreateTime( int button )
		{ //{{{
			foreach( i; m_Clicks )
			{
				if( i.Button == button )
				{
					return i.CreateTime;
				}
			}
			throw new Exception( "Button is not pressed" );
		} //}}}

		void WarpMouse( uint nX, uint nY )
		{ //{{{
			m_Cursor.x = nX;
			m_Cursor.y = nY;
			SDL_WarpMouse( nX, nY);
		} //}}}

		bool isPressed( int toCheckFor = 27 )
		{ //{{{
			foreach( i; m_Keypresses )
			{
				if( i.SymCode == toCheckFor )
				{
					return true;
				}
			}
			return false;
		} //}}}

		/// {G,S}etter for m_Width
		void Width( uint nWidth ) //{{{
		{
			m_Width = nWidth;
		}
		uint Width()
		{
			return m_Width;
		} //}}}

		/// {G,S}etter for m_Height
		void Height( uint nHeight ) //{{{
		{
			m_Height = nHeight;
		}
		uint Height()
		{
			return m_Height;
		} //}}}

		/// {G,S}etter for m_BPP
		void BPP( uint nBPP ) //{{{
		{
			m_BPP = nBPP;
		}
		uint BPP()
		{
			return m_BPP;
		} //}}}

		void AddEntity( Entity nEntity )
		{ //{{{
			if( !( nEntity is null ) )
			{
				m_Entities.add( nEntity );
			}
			else
			{
				log.warn( "Tried to add a null entity" );
			}
		} //}}}

		void RemoveEntity( Entity toRemove )
		{ //{{{
			if( m_Entities.contains( toRemove ) )
			{
				m_Entities.remove( toRemove, true );
			}
		} //}}}

		uint GetTicks()
		{ //{{{
			return SDL_GetTicks();
		} //}}}

		void WaitFor()
		{ //{{{
			static uint now;
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

		void sleep( uint microSeconds = 1000 )
		{ //{{{
			SDL_Delay( microSeconds );
		} //}}}

		/// {G,S}etter for m_TickInterval
		void TickInterval( uint nTickInterval ) //{{{
		{
			m_TickInterval = nTickInterval;
		}
		uint TickInterval()
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
		/*void ViewWidth( real nViewWidth ) //{{{
		{
			m_ViewWidth = nViewWidth;
		}*/
		real ViewWidth()
		{
			return m_ViewWidth;
		} //}}}

		/// Getter for m_ViewHeight
		/*void ViewHeight( real nViewHeight ) //{{{
		{
			m_ViewHeight = nViewHeight;
		}*/
		real ViewHeight()
		{
			return m_ViewHeight;
		} //}}}

		/// Setter for both X/Y centers
		void Centers( real nXC, real nYC ) //{{{
		{
			this.position.x = nXC - ViewWidth / 2;
			this.position.y = nYC - ViewHeight / 2;
		} //}}}

		/// {G,S}etter for the X center
		real XCenter() //{{{
		{
			return ViewWidth / 2 + this.position.x;
		}
		void XCenter( real nXC )
		{
			this.position.x = nXC - ViewWidth / 2;
		} //}}}

		/// {G,S}etter for the Y center
		real YCenter() //{{{
		{
			return ViewHeight / 2 + this.position.y;
		}
		void YCenter( real nYC )
		{
			this.position.y = nYC - ViewHeight / 2;
		} //}}}

		/// {G,S}etter for the Cursor X
		uint CursorX() //{{{
		{
			return m_Cursor.x;
		}
		void CursorX( uint nCX )
		{
			WarpMouse( nCX, m_Cursor.y );
		} //}}}

		/// {G,S}etter for the Cursor Y
		uint CursorY() //{{{
		{
			return m_Cursor.y;
		}
		void CursorY( uint nCY )
		{
			WarpMouse( m_Cursor.x, nCY );
		} //}}}

		/// {G,S}etter for the Zoom
		void Zoom( real nZoom ) //{{{
		{
			m_Zoom = nZoom;
		}
		real Zoom()
		{
			return m_Zoom;
		} //}}}

	protected : //{{{
		this( uint iWidth, uint iHeight, uint iBPP )
		{
			super();
			InitSGL( iWidth, iHeight, iBPP );
			m_Keypresses = new LinkedList!( Keypress );
			m_Clicks = new LinkedList!( Click );
			m_Entities = new LinkedList!( Entity );
			m_Cursor = new Vector!( uint );
		}

		// load modules needed to interface with C libs SDL, GL, IL
		void loadModules()
		{ //{{{
			if( ! m_ModulesLoaded )
			{
				// Try to load SDL module
				try //{{{
				{
					DerelictSDL.load();
				}
				catch( Exception e )
				{
					log.fatal( "Could not load SDL module" );
					throw e;
				} //}}}

				// Try to load OpenGL module
				try //{{{
				{
					DerelictGL.load();
				}
				catch( Exception e )
				{
					log.fatal( "Could not load OpenGL module" );
					throw e;
				} //}}}

				m_ModulesLoaded = true;
			}
			else
			{
				log.warn( "Attempted to re-load modules" );
			}
		} //}}}

		// unload modules needed to interface with C libs SDL, GL, IL
		void unloadModules()
		{ //{{{
			if( m_ModulesLoaded )
			{
				// Try to unload all modules
				// since this is less important, one try block
				try //{{{
				{
					DerelictSDL.unload();
					DerelictGL.unload();
				}
				catch( Exception e )
				{
					log.error( "One or more modules could not be unloaded" );
					throw e;
				} //}}}

				m_ModulesLoaded = false;
			}
			else
			{
				log.warn( "Attempted to re-unload modules" );
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

		static Game m_Instance;

		uint m_TickInterval;
		uint m_NextTime;

		bool m_isDone;
		bool m_isActive;
		bool m_ModulesLoaded;

		uint m_Width;
		uint m_Height;
		uint m_BPP;

		real m_ViewWidth;
		real m_ViewHeight;

		LinkedList!( Entity ) m_Entities;

		SDL_Event m_Event;
		LinkedList!( Keypress ) m_Keypresses;
		LinkedList!( Click ) m_Clicks;
		Vector!( uint ) m_Cursor;

		real m_Zoom;

		//}}}

	private:
}
