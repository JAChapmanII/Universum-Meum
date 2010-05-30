/* {{{
	Copyright 2010 Jeff Chapman

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

import derelict.opengl.gl;
import derelict.sdl.sdl;
import derelict.devil.il;

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
		{
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
		}

		alias Instance opCall;

		void InitSGL( uint iWidth, uint iHeight, uint iBPP )
		{
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

			ilInit();
			if( ilGetError() != IL_NO_ERROR )
			{
				log.warn( "DevIL has had an error." );
				throw new Exception( "DevIL had an error." );
			}

			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable( GL_POINT_SMOOTH );
			glEnable( GL_DEPTH_TEST );
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( 0, Width, Height, 0, -10, 10 );
			glMatrixMode( GL_MODLEVIEW );
			glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
		}

		void DeinitSGL();

		void Draw();

		void Width( uint nWidth );
		uint Width();

		void Height( uint nHeight );
		uint Height();

		void AddActor();

		uint GetTicks();
		void WaitFor();

		void TickInterval( uint nTickInterval );
		uint TickInterval();

		void IsDone( bool nState );
		bool IsDone()

		void IsActive( bool nState );
		bool IsActive();

	protected:
		this();
		void loadModules();
		void unloadModules();
		void toggleModules();

		static Display m_Instance;

		uint m_TickInterval;
		uint m_NextTime;

		bool m_isDone;
		bool m_isActive;
		bool m_ModulesLoaded;

		SDL_Event m_Event;

	private:
}

