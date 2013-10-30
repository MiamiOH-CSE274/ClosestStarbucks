#include "zirkleacStarbucks.h"

//#define NULL 0;
Node* root;
//zirkleacStarbucks::zirkleacStarbucks():Starbucks<class Key, class T>(){}
template <class Key, class T>
zirkleacStarbucks<Key,T>::zirkleacStarbucks(void)
{
	root = NULL;
}

template <class Key, class T>
zirkleacStarbucks<Key,T>::~zirkleacStarbucks(void)
{
}

Node* addr(std::string s,std::string adr,double x, double y, Node* r){
	if(r==0){
		Node* n= new Node;
		Entry* e= new Entry();
		e->city=s;
		e->address=adr;
		e->x=x;
		e->y=y;
		n->data=e;
		return n;
	}
	else{ 
		if(abs(r->data->x - x) <=.00001)
			return NULL;
		else{ 
			if(abs(r->data->y- y)<=.00001)
				return NULL;
			else{ 
				if(r->data->x<x){
					if(r->data->y<y)
						return addr(s,adr,x,y,r->firQuad);
					else
						return addr(s,adr,x,y,r->quadQuad);
				}
				else {
					if(r->data->y<y)
						return addr(s,adr,x,y,r->secQuad);
					else
						return addr(s,adr,x,y,r->triQuad);
				}
			}
		}
	}
}

Node* getNearestr(double x, double y, Node* r){
	if(r==0)
		return r;
	if(abs(r->data->x-x)<=.00001 && abs(r->data->y-y)<=.00001)
		return r;
	if(r->data->x<x){
		if(r->data->y<y){
			if(r->firQuad==0)
				return r;
			else
				return getNearestr(x,y,r->firQuad);
		}
		else{
			if(r->quadQuad==0)
				return r;
			else
				return getNearestr(x,y,r->quadQuad);
		}
	}
	else {
		if(r->data->y<y){
			if(r->secQuad==0)
				return r;
			else
				return getNearestr(x,y,r->secQuad);
		}
		else{
			if(r->triQuad==0)
				return r;
			else
				return getNearestr(x,y,r->triQuad);
		}
	}
}

void build(Entry* c, int n){
	//for (int i=0; ;i++){
	//	add(c[i]);
	//}
}
Entry* getNearest(double x, double y){
	return getNearestr(x,y,root)->data;

}
void add(std::string s,std::string adr,double x, double y){
	addr(s,adr,x,y,root);

}