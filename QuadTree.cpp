#include<bits/stdc++.h>
#include "Point.h"
#include "Node.h"
#include "QuadTree.h"
using namespace std;

QuadTree::QuadTree(){
    topLeft = Point(0, 0);
	botRight = Point(0, 0);
	n = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;
}

QuadTree::QuadTree(Point topL, Point botR){
    n = NULL;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;
	topLeft = topL;
	botRight = botR;
}

void QuadTree::insert(Node* node){

    if (node == NULL)
		return;

	// Current quad cannot contain it
	if (!inBoundary(node->pos))
		return;

	// We are at a quad of unit area
	// We cannot subdivide this quad further
	if (abs(topLeft.x - botRight.x) <= 1
		&& abs(topLeft.y - botRight.y) <= 1) {
		if (n == NULL)
			n = node;
		return;
	}

	if ((topLeft.x + botRight.x) / 2 >= node->pos.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topLeftTree == NULL)
				topLeftTree = new QuadTree(
					Point(topLeft.x, topLeft.y),
					Point((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2));
			topLeftTree->insert(node);
		}

		// Indicates botLeftTree
		else {
			if (botLeftTree == NULL)
				botLeftTree = new QuadTree(
					Point(topLeft.x,
						(topLeft.y + botRight.y) / 2),
					Point((topLeft.x + botRight.x) / 2,
						botRight.y));
			botLeftTree->insert(node);
		}
	}
	else {
		// Indicates topRightTree
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topRightTree == NULL)
				topRightTree = new QuadTree(
					Point((topLeft.x + botRight.x) / 2,
						topLeft.y),
					Point(botRight.x,
						(topLeft.y + botRight.y) / 2));
			topRightTree->insert(node);
		}

		// Indicates botRightTree
		else {
			if (botRightTree == NULL)
				botRightTree = new QuadTree(
					Point((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2),
					Point(botRight.x, botRight.y));
			botRightTree->insert(node);
		}
	}
}

Node* QuadTree::search(Point p){
    // Current quad cannot contain it
	if (!inBoundary(p))
		return NULL;

	// We are at a quad of unit length
	// We cannot subdivide this quad further
	if (n != NULL)
		return n;

	if ((topLeft.x + botRight.x) / 2 >= p.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topLeftTree == NULL)
				return NULL;
			return topLeftTree->search(p);
		}

		// Indicates botLeftTree
		else {
			if (botLeftTree == NULL)
				return NULL;
			return botLeftTree->search(p);
		}
	}
	else {
		// Indicates topRightTree
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topRightTree == NULL)
				return NULL;
			return topRightTree->search(p);
		}

		// Indicates botRightTree
		else {
			if (botRightTree == NULL)
				return NULL;
			return botRightTree->search(p);
		}
	}
}

bool QuadTree::inBoundary(Point p){
    return (p.x >= topLeft.x && p.x <= botRight.x && p.y >= topLeft.y && p.y <= botRight.y);
}

int QuadTree::totalPoints(){

    if (n != NULL)
		return 1;

	int count = 0;

	if (topLeftTree != NULL)
		count += topLeftTree->totalPoints();
	if (topRightTree != NULL)
		count += topRightTree->totalPoints();
	if (botLeftTree != NULL)
		count += botLeftTree->totalPoints();
	if (botRightTree != NULL)
		count += botRightTree->totalPoints();

	return count;
    
}

int QuadTree::totalNodes(){

    int count = 1; // Count the current node

	if (topLeftTree != NULL)
		count += topLeftTree->totalNodes();
	if (topRightTree != NULL)
		count += topRightTree->totalNodes();
	if (botLeftTree != NULL)
		count += botLeftTree->totalNodes();
	if (botRightTree != NULL)
		count += botRightTree->totalNodes();

	return count;

}

void QuadTree::insert(Point p, int data){
    Node* newNode = new Node(p, data);
	insert(newNode);
}

list<Node> QuadTree::list(){

    std::list<Node> result;

	if (n != NULL)
		result.push_back(*n);

	if (topLeftTree != NULL) {
		std::list<Node> topLeftList = topLeftTree->list();
		result.insert(result.end(), topLeftList.begin(), topLeftList.end());
	}
	if (topRightTree != NULL) {
		std::list<Node> topRightList = topRightTree->list();
		result.insert(result.end(), topRightList.begin(), topRightList.end());
	}
	if (botLeftTree != NULL) {
		std::list<Node> botLeftList = botLeftTree->list();
		result.insert(result.end(), botLeftList.begin(), botLeftList.end());
	}
	if (botRightTree != NULL) {
		std::list<Node> botRightList = botRightTree->list();
		result.insert(result.end(), botRightList.begin(), botRightList.end());
	}

	return result;
}

int QuadTree::countRegion(Point p, int d){

    int count = 0;

	if (inBoundary(p)) {
		if (n != NULL) {
			count = 1;
		} else {
			if (topLeftTree != NULL)
				count += topLeftTree->countRegion(p, d);
			if (topRightTree != NULL)
				count += topRightTree->countRegion(p, d);
			if (botLeftTree != NULL)
				count += botLeftTree->countRegion(p, d);
			if (botRightTree != NULL)
				count += botRightTree->countRegion(p, d);
		}
	}

	return count;

}

int QuadTree::agreggateRegion(Point p, int d){
    int aggregate = 0;

	if (inBoundary(p)) {
		if (n != NULL) {
			aggregate = n->data;
		} else {
			if (topLeftTree != NULL)
				aggregate += topLeftTree->agreggateRegion(p, d);
			if (topRightTree != NULL)
				aggregate += topRightTree->agreggateRegion(p, d);
			if (botLeftTree != NULL)
				aggregate += botLeftTree->agreggateRegion(p, d);
			if (botRightTree != NULL)
				aggregate += botRightTree->agreggateRegion(p, d);
		}
	}

	return aggregate;
}





