//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/10/01

#include "SSet.h"
#define MAX_TIMES_TO_GET_CLOSER 4

template <class Key, class T>
class Node {
public:
  Key k;
  T data;
  Node* left;
  Node* right;
};

template <class Key, class T>
class BST : public SSet <Key,T> {
 public:
  BST();
  ~BST();
  
  //Return the number of items currently in the SSet
  virtual unsigned long size();

  //Add a new item, x, with Key k.
  // If an item with Key k already exists, overwrite it
  virtual void add(Key lat, Key lon, T x);

  //Remove the item with Key k. If there is no such item, do nothing.
  virtual void remove();

  //Return the item with Key k. 
  // If there is no such item, throw an exception.
  virtual T* find(Key lat, Key lon);
  //Return true if there is an item with Key k in the table. If not,
  // return false
  virtual bool keyExists(Key lat, Key lon);

  //If there is a key in the set that is > k,
  // return the first such key. If not, return k
  virtual T* next(Key lat, Key lon);
  //If there is a key in the set that is < k,
  // return the first such key. If not, return k
  virtual T* prev(Key lat, Key lon);

private:
  Node<Key,T>* root;

  virtual unsigned long size(Node<Key,T>* r);
  //These are the recursive versions of each of your methods.
  // You should return the address of the new root node, whether
  // or not the root node changes.
  virtual Node<Key,T>* add(Key lat, Key lon, T x, Node<Key,T>* r, int level);
  virtual void remove(Node<Key,T>* r);

  //This one returns the address of the found node, NULL
  // if not found
  virtual Node<Key,T>* find(Key lat, Key lon, Node<Key,T>* r,int level);

  //Find the item in the sub-tree rooted at r which has the smallest key
  virtual Node<Key,T>* min(Node<Key,T>* r);

  //Find the item in the sub-tree rooted at r which has the largest key
  virtual Node<Key,T>* max(Node<Key,T>* r);

  //Find the next/prev node, and return its address
  virtual Node<Key,T>* next(Key lat, Key lon, Node<Key,T>* r, Node<Key,T>* recordHolder, int timesHasGottenCloser, double recordDist);
  virtual Node<Key,T>* prev(Key lat, Key lon, Node<Key,T>* r,int level,Node<Key,T>* recordHolder);

};

#define dNULL 0
#include <string>



template <class Key, class T>
BST<Key,T>::BST(){
    root = NULL;
}

template <class Key, class T>
BST<Key,T>::~BST(){
    remove(root);
}

//Return the number of items currently in the SSet
template <class Key, class T>
unsigned long BST<Key,T>::size(){
    return size(root);
}

template <class Key, class T>
unsigned long BST<Key,T>::size(Node<Key,T>* r){
    unsigned long numItems = 0;
    if (r==NULL){
        return numItems;
    }
    else numItems++;
    if (r->left==NULL) {
        numItems += size(r->right);
    }
    
    else if (r->right==NULL) {
        numItems+= size(r->left);
    }
    
    else{
        numItems += size(r->right);
        numItems+= size(r->left);
    }
    
    return numItems;
    
}

//Add a new item, x, with Key lat, Key lon.
// If an item with Key lat, Key lon already exists, overwrite it
template <class Key, class T>
void BST<Key,T>::add(Key lat, Key lon, T x){
    root = add(lat, lon, x, root, 0);
}

//Remove the item with Key lat, Key lon. If there is no such item, do nothing.
template <class Key, class T>
void BST<Key,T>::remove(){
    remove(root);
}

//Return the item with Key lat, Key lon.
// If there is no such item, throw an exception.
template <class Key, class T>
T* BST<Key,T>::find(Key lat, Key lon){
    Node<Key, T>* data = find(lat, lon, root,0);
    if (data==NULL) {
        throw (std::string)"This key does not exist in the tree.";
    }
    T* place = &data->data;
    return place;
}
//Return true if there is an item with Key lat, Key lon in the table. If not,
// return false
template <class Key, class T>
bool BST<Key,T>::keyExists(Key lat, Key lon){
    Node<Key,T>* data = find(lat, lon, root,0);
    
    if (data==NULL) {
        return false;
    }
    else return true;
}

//If there is a key in the set that is > k,
// return the first such key. If not, return k
template <class Key, class T>
T* BST<Key,T>::next(Key lat, Key lon){
    
    double dist = distance(root->data, lon, lat);
    Node<Key, T>* toReturnRight =NULL;
    Node<Key, T>* toReturnLeft=NULL;
    if (root->k <lon) {
         toReturnRight = next(lat, lon, root->right, root->right, MAX_TIMES_TO_GET_CLOSER, dist);
    }
    else toReturnLeft = next(lat, lon, root->left, root->left,MAX_TIMES_TO_GET_CLOSER, dist);
    
    T* place;
    
    if (toReturnRight==NULL) {
        place = &toReturnLeft->data;
    }
    
    
    else place = &toReturnRight->data;
    return place;
    
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::next(Key lat, Key lon, Node<Key,T>* r,Node<Key,T>* recordHolder, int timesHasGottenCloser, double recordDist){
    //    Key k;
    //    if(level==0)
    //        k = lat;
    //    else k = lon;
    
    if (r==NULL) {
        return recordHolder;
    }
    
    double distLL, distLR, distRL, distRR, distL, distR;
    distLL = distLR = distRL = distRR = distL = distR = recordDist+1;
    if(r->left !=NULL){
        if(r->left->left!=NULL)
            distLL = distance(r->left->left->data, lon, lat);
        if (r->left->right!=NULL)
            distLR = distance(r->left->right->data, lon, lat);
        distL = distance(r->left->data, lon, lat);
    }
    if (r->right!=NULL) {
        if (r->right->left!=NULL)
            distRL = distance(r->right->left->data, lon, lat);
        if(r->right->right!=NULL)
            distRR = distance(r->right->right->data, lon, lat);
        distR = distance(r->right->data, lon, lat);
        
    }
    
    
    Node<Key,T>* llCloser;
    Node<Key,T>* lrCloser;
    //Continue down the left -> L/R track
    if(distLL<recordDist){
        if (timesHasGottenCloser<MAX_TIMES_TO_GET_CLOSER) {
            llCloser = next(lat, lon, r->left->left, r->left->left, timesHasGottenCloser+1, distLL);
        }
        else llCloser = next(lat, lon, r->left->left, r->left->left, timesHasGottenCloser, distLL);
    }
    else if (distLL!=recordDist+1&&timesHasGottenCloser>1)
        llCloser = next(lat, lon, r->left->left, recordHolder, timesHasGottenCloser-1, recordDist);
    
    else llCloser = r;
    
    if (distLR<recordDist) {
        if (timesHasGottenCloser<MAX_TIMES_TO_GET_CLOSER) {
        lrCloser = next(lat, lon, r->left->right, r->left->right, timesHasGottenCloser+1, distLR);
        }
        else lrCloser = next(lat, lon, r->left->right, r->left->right, timesHasGottenCloser, distLR);
    }
    
    else if (timesHasGottenCloser>1 && distLR!=recordDist+1)
        lrCloser = next(lat, lon, r->left->right, recordHolder, timesHasGottenCloser-1, recordDist);
    
    else lrCloser = r;
    
    //Continue down the right -> L/R track
    Node<Key,T>* rlCloser;
    Node<Key,T>* rrCloser;
    if(distRL<recordDist){
        if (timesHasGottenCloser<MAX_TIMES_TO_GET_CLOSER) {
            rlCloser = next(lat, lon, r->right->left, r->right->left, timesHasGottenCloser+1, distRL);
        }
        else rlCloser = next(lat, lon, r->right->left, r->right->left, timesHasGottenCloser, distRL);
    }
    else if (timesHasGottenCloser>1 && distRL!=recordDist+1)
        rlCloser = next(lat, lon, r->right->left, recordHolder, timesHasGottenCloser-1, recordDist);
    
    else rlCloser = r;
    
    if (distRR<recordDist) {
        if (timesHasGottenCloser<MAX_TIMES_TO_GET_CLOSER) {
        rrCloser = next(lat, lon, r->right->right, r->right->right, timesHasGottenCloser+1, distRR);
        }
        else rrCloser = next(lat, lon, r->right->right, r->right->right, timesHasGottenCloser, distRR);
    }
    
    else if (timesHasGottenCloser>1 && distRR!=recordDist+1)
        rrCloser = next(lat, lon, r->right->right, recordHolder, timesHasGottenCloser-1, recordDist);
    
    else rrCloser = r;
    
    Node<Key,T>* lClosest;
    Node<Key,T>* rClosest;
    
    
    if (distL< distance(lrCloser->data, lon, lat) && distL < distance(llCloser->data, lon, lat)) {
        if (distL==recordDist+1) {
            lClosest = r;
        }
        else lClosest = r->left;
    }
    
    else if (distance(lrCloser->data, lon, lat) < distance(llCloser->data, lon, lat))
        lClosest = lrCloser;
    else lClosest = llCloser;
    
    if (distR< distance(rlCloser->data, lon, lat) && distR< distance(rrCloser->data, lon, lat)) {
        if (distR ==recordDist+1) {
            rClosest = r;
        }
        else rClosest = r->right;
    }
    else if (distance(rrCloser->data, lon, lat) < distance(rlCloser->data, lon, lat))
        rClosest = rrCloser;
    else rClosest = rlCloser;
    
    if (distance(lClosest->data, lon, lat) < distance(rClosest->data, lon, lat)) {
        return lClosest;
    }
    else return rClosest;
    
}

//If there is a key in the set that is < k,
// return the first such key. If not, return k
template <class Key, class T>
T* BST<Key,T>::prev(Key lat, Key lon){
    T* place;
    Node<Key, T>* toReturn=prev(lat, lon, root, 0, root);
    
    //    if (toReturn==dNULL) {
    //        return k;
    //    }
    place = &toReturn->data;
    return place;
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::prev(Key lat, Key lon, Node<Key,T>* r, int level, Node<Key,T>* recordHolder){
    return r;
}




template <class Key, class T>
Node<Key,T>* BST<Key,T>::add(Key lat, Key lon, T x, Node<Key,T>* r,int level){
    Key k;
    if(level%2==0)
        k = lon;
    else k = lat;
    
    if (r==NULL) {
        Node<Key,T>* toAdd = new Node<Key, T>;
        toAdd->k = k;
        toAdd->data = x;
        toAdd->left = NULL;
        toAdd->right = NULL;
        return toAdd;
    }
    else if (r->k == k){
        if (r->data.x == lon && r->data.y==lat) {
            return r;
        }
        else r->right = add(lat, lon, x, r->right, ++level);
    }
    
    else if(r->k > k){
        r->left = add(lat, lon, x, r->left, ++level);
    }
    
    else{
        r->right = add(lat, lon, x, r->right, ++level);
    }
    
    return r;
    
}

template <class Key, class T>
void BST<Key,T>::remove(Node<Key,T>* r){
    if(r->left!=NULL)
        remove(r->left);
    if (r->right!=NULL)
        remove(r->right);
    
    if (r->left==NULL && r->right==NULL) 
        delete r;
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::find(Key lat, Key lon, Node<Key,T>* r,int level){
    Key k;
    if(level%2==0)
        k = lon;
    else k = lat;
    if (r==dNULL) {
        return dNULL;
    }
    else if (k==r->k){
        return r;
    }
    else if (k>r->k){
        return find(lat, lon, r->right, ++level);
    }
    else return find(lat, lon, r->left, ++level);
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::max(Node<Key,T>* r){
    if (r==dNULL) {
        return dNULL;
    }
    else if (r->right==dNULL){
        return r;
    }
    
    else return max(r->right);
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::min(Node<Key,T>* r){
    if (r==dNULL) {
        return dNULL;
    }
    else if (r->left==dNULL){
        return r;
    }
    
    else return min(r->left);
}
