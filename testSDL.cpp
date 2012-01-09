/**
 * @file testSDL.cpp
 */

#include "testSDL.h"

//////////// Extern Variables /////////////////////

//-- Surfaces
SDL_Surface *screen = NULL;
SDL_Surface *tiles = NULL;
SDL_Surface *v0 = NULL;
SDL_Surface *paths = NULL;

//-- Attributes of the screen
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
const int SCREEN_BPP = 32;

//-- Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TILE_SPRITES = 5;

//-- Sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_BLACK = 3;
const int TILE_V0 = 4;

SDL_Rect clips[TILE_SPRITES];
SDL_Rect clipsPaths[9]; // I set this 

//-- Event structure
SDL_Event event;

//-- Global variables
int SIZE_X;
int SIZE_Y;
int MOUSE_MODE;
Pos p0;
std::vector< std::vector<Pos> > gPaths;
/////////////////////////////////////////////////


/**
 * @function main  
 */
int main( int argc, char *argv[] ) {

	bool quit = false;

	//-- Initialize
	if( init() == false ) {
		return 1;
	}

	//-- Load the files
	if( load_files() == false ) {
		return 1;
	}

	//-- Clip tiles
	clip_tiles();

	//-- Create grid
    Grid2D g( SIZE_X, SIZE_Y );

	//-- Create HomoPath object
    HP2D h( &g );

	//-- Display options
	display_options();

	//-- Start SDL
	while( quit == false ) {
		while( SDL_PollEvent( &event ) ) {

			if( event.type == SDL_QUIT ) {
				quit = true;
			}
			else if( event.type == SDL_KEYDOWN ) {
				switch( event.key.keysym.sym ) {
					case 's': {
						printf("-- Starting planner \n"); 
						MOUSE_MODE = -1;
						CallPlanner( &g, &h );
						printf("--* To see options again press [q] \n");	
						break;
					}
					case 'v': {
						printf("-- Click one location to be the initial vertex \n");
						MOUSE_MODE = 0;
						break;
					}
					case 'o': {
						printf("-- Click one location to be obstacle \n");
						MOUSE_MODE = 1;
						break;
					}
					case 'x': {
						printf("-- Pick a grid to check the possible paths \n");
						MOUSE_MODE = 2;
						break;
					}
					case 'q': {
						display_options();
					}
				}
			}

			else if( event.type == SDL_MOUSEBUTTONDOWN ) {
				if( event.button.button == SDL_BUTTON_LEFT ) {

					int x = event.button.x;
					int y = event.button.y;					
					Pos p = GetMousePos( x, y );

					switch( MOUSE_MODE ) {
						case 0: {
							printf("--> V0 located at (%d, %d) \n", p.x, p.y );
							p0.x = p.x; 
							p0.y = p.y;
							printf("--* To see options again press [q] \n");	
							break;
						}
						case 1: {
							printf("--> Obstacle located at (%d, %d) \n", p.x, p.y );
							if( g.GetState(p) == false ) { 	
								g.SetState( p, true ); 
							}
							else {
								g.SetState( p, false );
							}
							printf("--* To see options again press [q] \n");			
							break;
						}
						case 2: {
							printf( "--> Locating paths for (%d %d) \n", p.x, p.y );
							gPaths = h.PrintPath(p);
							printf("--* To see options again press [q] \n");			
							break;
						}

					}

				}
			}

		//-- Draw
		DrawScene( &g );

		} // end while SDL_PollEvent
		

	} // end while quit

	clean_up();
    return 0;
	
}


/**
 * @function CallPlanner
 */
void CallPlanner( Grid2D *_g, HP2D *_h ) {
	
	// Distance of 0 because it is  the first vertex
    Vertex* v0 = new Vertex( p0.x, p0.y, 0 ); 

	//-- Build manifold
    _h->BuildManifold( v0 );

	printf("Call Planner over - back to loop \n");

}

/**
 * @function init
 */
bool init() {

	SIZE_X = 5; 
    SIZE_Y = 5;	
	Vertex::minX = 0;
	Vertex::maxX = SIZE_X - 1;
	Vertex::minY = 0;
	Vertex::maxY = SIZE_Y - 1;

	SCREEN_WIDTH = TILE_WIDTH*SIZE_X;
	SCREEN_HEIGHT = TILE_HEIGHT*SIZE_Y;

	MOUSE_MODE = -1;
	p0.x = -1; p0.y = -1;

	//-- SDL Initialization
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		return false;
	}	
	
	//-- Setup the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//-- If there was an error in setting up the screen
	if( screen == NULL ) {
		return false;
	}	

	//-- Set the window caption
	SDL_WM_SetCaption( "HP2D", NULL );

	//-- If everything initialized fine
	return true;
}


