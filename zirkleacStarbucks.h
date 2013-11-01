#pragma once
#include "starbucks.h"
//template <class Entry>
class Node {
public:
  Entry* data;
  Node* firQuad;
  Node* secQuad;
  Node* triQuad;
  Node* quadQuad;
};
//#include "Starbucks.h";
//template <class Key, class T>
class zirkleacStarbucks// : public Starbucks<Key, Entry> //:
	//public Starbucks
{

public:
	
	zirkleacStarbucks(void);
	virtual ~zirkleacStarbucks(void);
	Entry* getNearest(double x, double y);
	//void build();
	void build(Entry* c, int n);
	void add(std::string s,std::string adr,double x, double y);
private:
	void add(Entry r);
	
	Node* getNearestr(double x, double y, Node* r);
	Node* addr(std::string s,std::string adr,double x, double y, Node*  r);
	//Node<Entry>* root;
};

