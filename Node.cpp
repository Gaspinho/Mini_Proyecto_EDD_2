#include<bits/stdc++.h>
#include "Point.h"
#include "Node.h"
using namespace std;

Node::Node(Point _pos, int _data){
    pos = _pos;
    data = _data;
}

Node::Node(){
    data = 0;
}
