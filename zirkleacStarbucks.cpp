#include "zirkleacStarbucks.h"
//#define NULL 0;

//zirkleacStarbucks::zirkleacStarbucks():Starbucks<class Key, class T>(){}
//template <class Key, class T>
zirkleacStarbucks::zirkleacStarbucks()
{
	root = NULL;
	
}

//template <class Key, class T>
zirkleacStarbucks::~zirkleacStarbucks(void)
{
}

Node* zirkleacStarbucks::addr(std::string s,std::string adr,double x, double y, Node* r){
	if(r==NULL){
		Node* n= new Node;
		Entry* e= new Entry();
		e->city=s;
		e->address=adr;
		e->x=x;
		e->y=y;
		n->data=e;
		n->firQuad=NULL;
		n->quadQuad=NULL;
		n->secQuad=NULL;
		n->triQuad=NULL;
		//r=n;
		return n;
	}
	else{ 
		if(abs(r->data->x - x) <=.00001)
			 return r;
		else{ 
			if(abs(r->data->y- y)<=.00001)
				return r;
			else{ 
				if(r->data->x<x){
					if(r->data->y<y){
						r->firQuad= addr(s,adr,x,y,r->firQuad);
						return r;
					}
					else{
						r->quadQuad= addr(s,adr,x,y,r->quadQuad);
						return r; 
					}
				}
				else {
					if(r->data->y<y){
						r->secQuad= addr(s,adr,x,y,r->secQuad);
						return r;
					}
					else{

						r->triQuad= addr(s,adr,x,y,r->triQuad);
						return r;
					}
				}
			}
		}
	}
}

Node* zirkleacStarbucks::getNearestr(double x, double y, Node* r){
	if(r==0)
		return r;
	if(abs(r->data->x-x)<=.00001 && abs(r->data->y-y)<=.00001)
		return r;
	if(r->data->x<x){
		if(r->data->y<y){
			if(r->firQuad==NULL)
				return r;
			else
				return getNearestr(x,y,r->firQuad);
		}
		else{
			if(r->quadQuad==NULL)
				return r;
			else
				return getNearestr(x,y,r->quadQuad);
		}
	}
	else {
		if(r->data->y<y){
			if(r->secQuad==NULL)
				return r;
			else
				return getNearestr(x,y,r->secQuad);
		}
		else{
			if(r->triQuad==NULL)
				return r;
			else
				return getNearestr(x,y,r->triQuad);
		}
	}
}


Entry* zirkleacStarbucks::getNearest(double x, double y){
	return getNearestr(x,y,root)->data;

}

void zirkleacStarbucks::add(std::string s,std::string adr,double x, double y){
	addr(s,adr,x,y,root);

}

void zirkleacStarbucks::add(Entry e){
	if(root==NULL){
		Node* n= new Node;
		Entry* j= new Entry();
		j->city=e.city;
		j->address=e.address;
		j->x=e.x;
		j->y=e.y;
		n->data=j;
		n->firQuad=NULL;
		n->quadQuad=NULL;
		n->secQuad=NULL;
		n->triQuad=NULL;
		root=n;
		return;
	}
	addr(e.city, e.address, e.x, e.y, root);
}

void zirkleacStarbucks::build(Entry* c, int n){
	for (int i=0;i<n ;i++){
		this->add(c[i]);
	}
}