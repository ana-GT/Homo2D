/**
 * @file HP2D.h
 */

#ifndef _HP2D_H_
#define _HP2D_H_

#include "Grid2D.h"
#include "Vertex.h"

/**
 * @class HP2D
 */
class HP2D {

public:
	std::vector<Vertex*> mV;
	std::vector<int> mQ;
	Grid2D *mG;

	static int DIST_MAX;
	
	/** FUNCTIONS */
	HP2D( Grid2D *_g );
	~HP2D();
	void AddVertex( Vertex* _v );
	void AddEdge( Vertex *_va, Vertex *_vb );
    std::vector<Vertex*> Successors( Vertex *_v );
    std::vector< std::vector<Pos> > GetPath( Pos _p );
    std::vector< std::vector<Pos> > PrintPath( Pos _p );

	/// Queue functions
	int EnQueue( Vertex* _v );
    Vertex* DeQueue();
	void BuildManifold( Vertex *_v0 );

	/// Auxiliar
    bool CheckPosAdj( Pos _p, Vertex *_v );
    bool CheckPosNeighbors( Vertex* _a, Vertex* _b );
	std::vector<Vertex*> GetAdjacent2( Vertex *_v );
	void PrintVertices();
    void PrintQueue();
};


#endif /** _HP2D_H_ */





