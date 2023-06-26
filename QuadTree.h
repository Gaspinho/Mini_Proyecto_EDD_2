#include<bits/stdc++.h> 
#include "Point.h"
#include "Node.h"
#ifndef QUADTREE
#define QUADTREE
using namespace std;

class QuadTree{
    // Hold details of the boundary of this node
	Point topLeft;
	Point botRight;

	// Contains details of node
	Node* n;

	// Children of this tree
	QuadTree* topLeftTree;
	QuadTree* topRightTree;
	QuadTree* botLeftTree;
	QuadTree* botRightTree;

    public:
    QuadTree();
    QuadTree(Point topL, Point botR);
    void insert(Node*);
    Node* search(Point);
    bool inBoundary(Point);
    int totalPoints();
    int totalNodes();
    std::list<Node> list();
    void insert(Point p, int data);
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
    void _printQuadTree(QuadTree* p, int d);
    void printQuadTree();
};

#endif