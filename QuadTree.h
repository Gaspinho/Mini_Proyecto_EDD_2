#include<bits/stdc++.h> 
#include "Point.h"
#include "Node.h"
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
    void insert(Point p, int data);
    std::list<Node> list();
    int countRegion(Point p, int d);
    int agreggateRegion(Point p, int d);
};