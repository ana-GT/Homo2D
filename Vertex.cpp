/**
 * @file Vertex.cpp
 */
#include "Vertex.h"

/** Static class variables */
int const Vertex::NX[4] = {-1, 0, 1,  0};
int const Vertex::NY[4] = { 0, 1, 0, -1};
int Vertex::minX = 0; int Vertex::maxX = 0;
int Vertex::minY = 0; int Vertex::maxY = 0;

/**
 * @function Vertex
 * @brief Constructor	
 */
Vertex::Vertex( int _x, int _y, int _dist, int _index ) {

	if ( _x < minX || _x > maxX || _y < minY || _y > maxY ) { 
	  printf( "--(!) Vertex (%d, %d) out of range \n", _x, _y );
	}

	p.x = _x;
	p.y = _y;
	index = _index;
	dist = _dist;	
}

/**
 * @function ~Vertex
 * @brief Destructor	
 */
Vertex::~Vertex() {
}

/**
 * @function Neighbors
 */
std::vector<Pos> Vertex::Neighbors() {

	std::vector<Pos> N;

	int nx; int ny;
	for( unsigned int i = 0; i < 4; i++ ) {
		nx = p.x + NX[i];
		ny = p.y + NY[i];
		if ( nx < minX || nx > maxX || ny < minY || ny > maxY ) { 
		  //printf( "No created vertex with pos (%d, %d) -- Out of range \n", nx, ny );
		  continue; 
		}
		Pos temp; 
		temp.x = nx; temp.y = ny;					
		N.push_back( temp );	
	}		

	return N;
}

/**
 * @function AddAdjacent
 */
void Vertex::AddAdjacent( int _ind ) {
	Adj.push_back( _ind );
}


/**
 * @function PrintInfo
 */
void Vertex::PrintInfo() {
   printf(" V(%d, %d) - index: %d \n", p.x, p.y, index );
}
