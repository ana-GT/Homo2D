/**
 * @file Vertex.h
 */


#ifndef _HP2D_VERTEX_H_
#define _HP2D_VERTEX_H_

#include <vector>
#include <stdio.h>

/**
 * @class Vertex
 */
struct Pos {
	int x;
	int y;
};

class Vertex {

private:
	Pos p;
	int index;
	int dist;
	std::vector<int> Adj;

public:
	/// Common constants
	static int minX;
	static int maxX;
	static int minY;
	static int maxY;
	static const int NX[];
	static const int NY[]; 	

	/// Functions
	Vertex( int _x, int y_, int _dist = 0, int _index = 0 );	
	~Vertex();
	std::vector<Pos> Neighbors();
	void AddAdjacent( int _ind );

	/// Getters
	int GetIndex() const;
	int GetDist() const;
	Pos GetPos() const;
	std::vector<int> GetAdjacent() const;

	/// Setters
	void SetIndex( int _index );

	/// Utility
	void PrintInfo();
};



/////////// INLINE FUNCTIONS //////////////////////
inline int Vertex::GetIndex() const{
	return index;
}

inline int Vertex::GetDist() const{
	return dist;
}

inline Pos Vertex::GetPos() const{
	return p;
}

inline std::vector<int> Vertex::GetAdjacent() const {
	return Adj;
}

inline void Vertex::SetIndex( int _index ) {
	index = _index;
}

#endif /** _HP2D_VERTEX_H */


