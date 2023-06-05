#include<bits/stdc++.h> //Biblioteca donde se encuentra la función cout
#include "Point.h"
using namespace std;  //uso del espacio de nombre 

struct Node{
    Point pos;
    int data;
    Node(Point _pos, int _data);
    Node();
};