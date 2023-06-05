#include<bits/stdc++.h> //Biblioteca donde se encuentra la función cout
#include "Point.h"
#include "Node.h"
using namespace std;  //uso del espacio de nombre 

Node::Node(Point _pos, int _data){
    pos = _pos;
    data = _data;
}

Node::Node(){
    data = 0;
}