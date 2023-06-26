#include <bits/stdc++.h>
#include "Point.h"
#include "Node.h"
#include "QuadTree.h"
using namespace std;


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

	if ((topLeft.x + botRight.x) / 2 > node->pos.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
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
		if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
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

	if ((topLeft.x + botRight.x) / 2 > p.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 > p.y) {
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
		if ((topLeft.y + botRight.y) / 2 > p.y) {
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

bool QuadTree::inBoundary(Point p) {
    return (p.x >= topLeft.x && p.x <= botRight.x && p.y >= topLeft.y && p.y <= botRight.y);
}

int QuadTree::totalPoints() {
    int count = 0;

    if (n != NULL) {
        count++;
    }

    if (topLeftTree != NULL) {
        count += topLeftTree->totalPoints();
    }

    if (topRightTree != NULL) {
        count += topRightTree->totalPoints();
    }

    if (botLeftTree != NULL) {
        count += botLeftTree->totalPoints();
    }

    if (botRightTree != NULL) {
        count += botRightTree->totalPoints();
    }

    return count;
}

int QuadTree::totalNodes() {
    int count = 1;

    if (topLeftTree != NULL) {
        count += topLeftTree->totalNodes();
    }

    if (topRightTree != NULL) {
        count += topRightTree->totalNodes();
    }

    if (botLeftTree != NULL) {
        count += botLeftTree->totalNodes();
    }

    if (botRightTree != NULL) {
        count += botRightTree->totalNodes();
    }

    return count;
}

void QuadTree::insert(Point p, int data){
    Node* newNode = new Node(p, data);
	insert(newNode);
}

std::list<Node> QuadTree::list(){

    std::list<Node> result;

	if (n != NULL)
		result.push_back(*n);

	if (topLeftTree != NULL) {
		std::list<Node> topLeftList = topLeftTree->list();
		result.insert(result.end(), topLeftList.begin(), topLeftList.end());
		result.clear();
	}
	if (topRightTree != NULL) {
		std::list<Node> topRightList = topRightTree->list();
		result.insert(result.end(), topRightList.begin(), topRightList.end());
		result.clear();
	}
	if (botLeftTree != NULL) {
		std::list<Node> botLeftList = botLeftTree->list();
		result.insert(result.end(), botLeftList.begin(), botLeftList.end());
		result.clear();
	}
	if (botRightTree != NULL) {
		std::list<Node> botRightList = botRightTree->list();
		result.insert(result.end(), botRightList.begin(), botRightList.end());
		result.clear();
	}

	return result;
}


int QuadTree::countRegion(Point p, int d) {
    int count = 0;

    if (n != NULL) {
        if (abs(p.x - n->pos.x) <= d && abs(p.y - n->pos.y) <= d) {
            count++;
        }
    }

    if (topLeftTree != NULL) {
        count += topLeftTree->countRegion(p, d);
    }

    if (topRightTree != NULL) {
        count += topRightTree->countRegion(p, d);
    }

    if (botLeftTree != NULL) {
        count += botLeftTree->countRegion(p, d);
    }

    if (botRightTree != NULL) {
        count += botRightTree->countRegion(p, d);
    }

    return count;
}

int QuadTree::aggregateRegion(Point p, int d) {
    int aggregate = 0;

    if (n != NULL) {
        if (abs(p.x - n->pos.x) <= d && abs(p.y - n->pos.y) <= d) {
            aggregate += n->data;
        }
    }

    if (topLeftTree != NULL) {
        aggregate += topLeftTree->aggregateRegion(p, d);
    }

    if (topRightTree != NULL) {
        aggregate += topRightTree->aggregateRegion(p, d);
    }

    if (botLeftTree != NULL) {
        aggregate += botLeftTree->aggregateRegion(p, d);
    }

    if (botRightTree != NULL) {
        aggregate += botRightTree->aggregateRegion(p, d);
    }

    return aggregate;
}


void QuadTree::_printQuadTree(QuadTree* t, int indent)
{
  for(int i=0; i < indent; i++)
    std::cout << "--";

  if(t != NULL && t->n != NULL)
    std::cout << " " << t->n->data << std::endl;
  else if(t == NULL)
    std::cout << " NULL" << std::endl;
  else {
    std::cout << " X " << std::endl;
  
    _printQuadTree(t->topLeftTree, indent+1);
    _printQuadTree(t->topRightTree, indent+1);
    _printQuadTree(t->botLeftTree, indent+1);
    _printQuadTree(t->botRightTree, indent+1);
  }
}

void QuadTree::printQuadTree()
{
  _printQuadTree(this->topLeftTree, 1);
  _printQuadTree(this->topRightTree, 1);
  _printQuadTree(this->botLeftTree, 1);
  _printQuadTree(this->botRightTree, 1);
}

