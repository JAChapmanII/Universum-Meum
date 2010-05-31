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
import derelict.devil.il;

Logger log;
static this()
{
	log = Log.lookup( "display" );
	log.add( new AppendConsole() );
}

static char[] PROGRAM_NAME = "Universum Meum";

public class display
{
	public:
		static display Instance( uint iWidth, uint iHeight, uint iBPP )
		{ //{{{
			if( m_Instance is null )
			{
				try
				{
					m_Instance = new display( iWidth, iHeight, iBPP );
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
			glMatrixMode( GL_MODELVIEW );
			glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
		} //}}}

		void DeinitSGL()
		{
		}

		void Draw()
		{
		}

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

		void AddActor()
		{
		}

		uint GetTicks()
		{
			return SDL_GetTicks();
		}

		void WaitFor()
		{ //{{{
			uint now;
			now = GetTicks();

			if( m_NextTime > now )
			{
				SDL_Delay( m_NextTime - now );
			}
			else
			{
				char[] tlog = "Behind: " ~
					Integer.toString( cast( int )( m_NextTime - now ) );
				log.info( tlog );
			}
			m_NextTime += m_TickInterval;
		} //}}}

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
		void IsDone( bool nState ) //{{{
		{
			m_isDone = nState;
		}
		bool IsDone()
		{
			return m_isDone;
		} //}}}

		// {G,S}etter for m_isActive
		void IsActive( bool nState ) //{{{
		{
			m_isActive = nState;
		}
		bool IsActive()
		{
			return m_isActive;
		} //}}}

	protected: //{{{
		this( uint iWidth, uint iHeight, uint iBPP )
		{
			Width = iWidth;
			Height = iHeight;
			BPP = iBPP;
		}

		void loadModules()
		{
		}
		void unloadModules()
		{
		}
		void toggleModules()
		{
		}

		static display m_Instance;

		uint m_TickInterval;
		uint m_NextTime;

		bool m_isDone;
		bool m_isActive;
		bool m_ModulesLoaded;

		uint m_Width;
		uint m_Height;
		uint m_BPP;

		SDL_Event m_Event;

		//}}}

	private:
}
