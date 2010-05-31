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
module display;

import tango.util.log.Log;
import tango.util.log.AppendConsole;
import Integer = tango.text.convert.Integer;

import derelict.opengl.gl;
import derelict.sdl.sdl;

import entity;

Logger log;
static this()
{
	log = Log.lookup( "display" );
	log.add( new AppendConsole() );
}

static char[] PROGRAM_NAME = "Universum Meum";

public class Display
{
	public:
		static Display Instance( uint iWidth, uint iHeight, uint iBPP )
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new Display( iWidth, iHeight, iBPP );
				}
				catch( Exception e )
				{
					log.fatal( "Display could not be instantiated." );
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

			SDL_WM_SetCaption( cast( char* )PROGRAM_NAME, null );

			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable( GL_POINT_SMOOTH );
			glEnable( GL_DEPTH_TEST );
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( 0, Width, Height, 0, -10, 10 );
			glMatrixMode( GL_MODELVIEW );
			glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		void DeinitSGL()
		{ //{{{
			SDL_Quit();
			unloadModules();
		} //}}}

		void Draw()
		{
			foreach( i; m_Entities )
			{
				if( i is null )
				{
					log.warn( "Tried to Draw null object" );
				}
				else
				{
					i.Draw();
				}
			}
			SDL_GL_SwapBuffers();
		}

		void ProcessInput()
		{ //{{{
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
						if( m_Event.key.keysym.sym == 27 )
						{
							isDone = true;
						}
						break;
					} //}}}

					// A key was released
					case SDL_KEYUP:
					{ //{{{
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

		// {G,S}etter for m_Width
		void Width( uint nWidth ) //{{{
		{
			m_Width = nWidth;
		}
		uint Width()
		{
			return m_Width;
		} //}}}

		// {G,S}etter for m_Height
		void Height( uint nHeight ) //{{{
		{
			m_Height = nHeight;
		}
		uint Height()
		{
			return m_Height;
		} //}}}

		// {G,S}etter for m_BPP
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
				m_Entities.length = m_Entities.length + 1;
				m_Entities[ $-1 ] = nEntity;
			}
			else
			{
				log.warn( "Tried to add a null entity" );
			}
		} //}}}

		uint GetTicks()
		{
			return SDL_GetTicks();
		}

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
		{
			SDL_Delay( microSeconds );
		}

		// {G,S}etter for m_TickInterval
		void TickInterval( uint nTickInterval ) //{{{
		{
			m_TickInterval = nTickInterval;
		}
		uint TickInterval()
		{
			return m_TickInterval;
		} //}}}

		// {G,S}etter for m_isDone
		void isDone( bool nState ) //{{{
		{
			m_isDone = nState;
		}
		bool isDone()
		{
			return m_isDone;
		} //}}}

		// {G,S}etter for m_isActive
		void isActive( bool nState ) //{{{
		{
			m_isActive = nState;
		}
		bool isActive()
		{
			return m_isActive;
		} //}}}

	protected: //{{{
		this( uint iWidth, uint iHeight, uint iBPP )
		{
			InitSGL( iWidth, iHeight, iBPP );
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

		static Display m_Instance;

		uint m_TickInterval;
		uint m_NextTime;

		bool m_isDone;
		bool m_isActive;
		bool m_ModulesLoaded;

		uint m_Width;
		uint m_Height;
		uint m_BPP;

		SDL_Event m_Event;

		Entity[] m_Entities;

		//}}}

	private:
}
