/**
 * @file HP2D.cpp
 */

#include "HP2D.h"

int HP2D::DIST_MAX = 28;

/**
 * @function HP2D
 * @brief Constructor
 */
HP2D::HP2D( Grid2D *_g ) {
	mG = _g;
}

/**
 * @function ~HP2D
 * @brief Destructor
 */
HP2D::~HP2D() {

	/// Destroy the pointed vertices -- give back the heap, people
	for( std::vector<Vertex*>::iterator i = mV.begin(); i != mV.end(); ++i ) {
		delete *i;
	}

}

/**
 * @function BuildManifold
 */
void HP2D::BuildManifold( Vertex* _v0 ) {
	
	Vertex* va;
    std::vector<Vertex*> S;
	std::vector<Vertex*> B;

	printf("Build Manifold \n");
	AddVertex( _v0 );	
	EnQueue( _v0 );

	while( mQ.size() != 0 ) {
		va = DeQueue();
		S = Successors( va );

		for( unsigned int i = 0; i < S.size(); ++i ) {
			AddVertex( S[i] );
			AddEdge( va, S[i] );
			if( S[i]->GetDist() < DIST_MAX ) {		
				EnQueue( S[i] );
			}
			B = GetAdjacent2( va );
			for( unsigned j = 0; j < B.size(); ++j ) {
				if( CheckPosNeighbors( B[j], S[i] ) == true ) {
					AddEdge( S[i], B[j] );
				}
			}
		}		
	}
}


/**
 * @function GetPath
 */
std::vector< std::vector<Pos> > HP2D::GetPath( Pos _p ) {
	std::vector<int> iv;
	Vertex* current;
	int minIndex;
	int minDist;
	std::vector< std::vector<Pos> > paths;

	iv = mG->GetVertices( _p );	

	for( unsigned int i = 0; i < iv.size(); ++i ) {

		current = mV[ iv[i] ];
		std::vector<Pos> path;
		
		while( current->GetIndex() != 0 ) {

			std::vector<int> a;
			a = current->GetAdjacent();
			if( a.size() == 0 ) {
				printf("--(!) Uh-oh, error here. No Adjacents! GetPath Function \n");
			}

			minDist = 1000;
			minIndex = -1;

			for( unsigned int j = 0; j < a.size(); ++ j ) {
				if( mV[ a[j] ]->GetDist() < minDist ) {
					minDist = mV[ a[j] ]->GetDist();
					minIndex = mV[ a[j] ]->GetIndex();
				}	
			}
			
			path.push_back( current->GetPos() ); 		
			current = mV[minIndex];
		}

		path.push_back( mV[0]->GetPos() );
		paths.push_back( path );
	}

	return paths;
}

/**
 * @function PrintPath
 */
std::vector< std::vector<Pos> > HP2D::PrintPath( Pos _p ) {

	std::vector< std::vector<Pos> > paths = GetPath(_p);

	if( paths.size() == 0 ) {
		printf("--(!) No paths to this grid cell \n");
		return paths;
	}

	printf("\n Paths to position (%d, %d) : %d \n", _p.x, _p.y, paths.size() );
	for( int i = 0; i < paths.size(); ++i ) {
		for( unsigned j = 0; j < paths[i].size(); ++j ) {
			printf("[%d] (%d , %d) \n", i, paths[i][j].x, paths[i][j].y  );
		}
		printf("\n --------------------------\n");
	}
	
	return paths;
}

/**
 * @function Successors
 */
std::vector<Vertex*> HP2D::Successors( Vertex *_va ) {

	std::vector<Vertex*> S;
	std::vector<Pos> N = _va->Neighbors();
	S.resize(0);

	for( unsigned int i = 0; i < N.size(); ++i ) {
		if( mG->CheckCollision( N[i] ) == false && CheckPosAdj( N[i], _va ) == false  ) {
			Vertex *vi = new Vertex( N[i].x, N[i].y, _va->GetDist() + 1 );
			S.push_back( vi );
		}
	}

	return S;
}

/**
 * @function AddVertex
 */
void HP2D::AddVertex( Vertex* _v ) {

 	int ind;

    ind = mV.size();
    _v->SetIndex( ind );
	mG->InsertVertex( _v->GetPos(), ind );

	mV.push_back( _v );
}

/**
 * @function AddEdge
 */
void HP2D::AddEdge( Vertex *_va, Vertex *_vb ) {
	
	_va->AddAdjacent( _vb->GetIndex() );
	_vb->AddAdjacent( _va->GetIndex() );
	
} 

/**
 * @function EnQueue
 */
int HP2D::EnQueue( Vertex* _v ) {
	
	int ind; 
	int node; int parent;
	int n; int temp;

	ind = _v->GetIndex();

	n = mQ.size();
	mQ.push_back( ind );

	return n;
}

/**
 * @function DeQueue
 */
Vertex* HP2D::DeQueue() {

	Vertex *first;
	
	if( mQ.size() == 0 ) {
		printf("--(!) ERROR No more elements left \n");
		return first;
	}

	// Save the popped out element	
	first = mV[mQ[0]];

	mQ.erase( mQ.begin() );

	return first;
}

/**
 * @function GetAdjacent2
 */
std::vector<Vertex*> HP2D::GetAdjacent2( Vertex *_v ) {

	std::vector<int> a;
	Vertex *va;
	std::vector<Vertex*> Adj2;
	bool already = false;

	a = _v->GetAdjacent();

	for( unsigned int i = 0; i < a.size(); ++i ) {
		va = mV[a[i]];
		std::vector<int> a2;
		a2 = va->GetAdjacent();
		for( unsigned int j = 0; j < a2.size(); ++j ) {
			already = false;
			for( unsigned int k = 0; k < Adj2.size(); ++k ) {
				if( Adj2[k]->GetIndex() == mV[a2[j]]->GetIndex() ) {
					already = true; break;
				}
			}
			if( already == false ) {
				Adj2.push_back( mV[a2[j]] );
			}
		}
	}	
	return Adj2;
}


/**
 * @function CheckPosAdj
 */
bool HP2D::CheckPosAdj( Pos _p, Vertex *_v ) {
	
	std::vector<int> adj = _v->GetAdjacent();
	for( unsigned int i = 0; i < adj.size(); ++i ) {
		Pos temp = mV[ adj[i] ]->GetPos();
		if( _p.x == temp.x && _p.y == temp.y ) {
			return true;
		}
	}	

	return false;
}

/**
 * @function CheckPosNeighbors
 */
bool HP2D::CheckPosNeighbors( Vertex* _a, Vertex* _b ) {
	Pos p = _a->GetPos();
	std::vector<Pos> n = _b->Neighbors();
	
	for( unsigned int i = 0; i < n.size(); ++i ) {
		if( p.x == n[i].x && p.y == n[i].y ) {
			return true;
		}
	}

	return false;
}


/**
 * @function PrintVertices
 */
void HP2D::PrintVertices() {
	for( int i = 0; i < mV.size(); i++ ) {
		printf( "[%d] ", i ); 
        mV[i]->PrintInfo();
	}	
}

/**
 * @function PrintQueue
 */
void HP2D::PrintQueue() {
	for( int i = 0; i < mQ.size(); i++ ) {
		printf( "Q[%d]: ", i ); 
        mV[ mQ[i] ]->PrintInfo();
	}	
}

