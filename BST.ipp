#define dNULL 0
#include <string>



template <class Key, class T>
BST<Key,T>::BST(){
    root = NULL;
}

template <class Key, class T>
BST<Key,T>::~BST(){
    while (size()>0) {
        remove(root->data.x, root->data.y);
    }
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
void BST<Key,T>::remove(Key lat, Key lon){
    root = remove(lat, lon, root,0);
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
   Node<Key, T>* toReturnLeft = next(lat, lon, root->left, root->left,true, dist);
   Node<Key, T>* toReturnRight = next(lat, lon, root->right, root->right, true, dist);
    T* place;
    
//    if (toReturn==dNULL) {
//        return k;
//   }
    place = &toReturnLeft->data;
    return place;

}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::next(Key lat, Key lon, Node<Key,T>* r,Node<Key,T>* recordHolder, bool hasGottenCloser, double recordDist){
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
        //recordHolder = r->left->left;
        llCloser = next(lat, lon, r->left->left, r->left->left, true, distLL);
    }
    else if (hasGottenCloser)
        llCloser = next(lat, lon, r->left->left, recordHolder, false, recordDist);
    
    else llCloser = r;
    
    if (distLR<recordDist) {
        lrCloser = next(lat, lon, r->left->right, r->left->right, true, distLR);
    }
    
    else if (hasGottenCloser)
        lrCloser = next(lat, lon, r->left->right, recordHolder, false, recordDist);
    
    else lrCloser = r;
    
    //Continue down the right -> L/R track
    Node<Key,T>* rlCloser;
    Node<Key,T>* rrCloser;
    if(distRL<recordDist){
        //recordHolder = r->left->left;
        rlCloser = next(lat, lon, r->right->left, r->right->left, true, distLL);
    }
    else if (distRL>=recordDist && hasGottenCloser)
        rlCloser = next(lat, lon, r->right->left, recordHolder, false, recordDist);
    
    else rlCloser = r;
    
    if (distRR<recordDist) {
        rrCloser = next(lat, lon, r->right->right, r->right->right, true, distLR);
    }
    
    else if (distRR>=recordDist && hasGottenCloser)
        rrCloser = next(lat, lon, r->right->right, recordHolder, false, recordDist);
    
    else rrCloser = r;
    
    Node<Key,T>* lClosest;
    Node<Key,T>* rClosest;
    
    
    if (distL< distance(lrCloser->data, lon, lat) && distL < distance(llCloser->data, lon, lat)) {
        lClosest = r->left;
    }
    
    else if (distance(lrCloser->data, lon, lat) < distance(llCloser->data, lon, lat))
        lClosest = lrCloser;
    else lClosest = llCloser;
    
    if (distR< distance(rlCloser->data, lon, lat) && distR< distance(rrCloser->data, lon, lat)) {
        rClosest = r->right;
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
        return r;
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
Node<Key,T>* BST<Key,T>::remove(Key lat, Key lon, Node<Key,T>* r,int level){
        Key k;
    if(level%2==0)
        k = lon;
    else k = lat;
    if (r == NULL) {
        return NULL;
    }
    else if (r->k==k){
        if (r->left==NULL && r->right==NULL) {
            delete r;
            return NULL;
        }
        else if  (r->left!=NULL && r->right!=NULL){
            Node<Key, T>* newR = min(r->right);
            Key temp = r->k;
            T tempData = r->data;
            r->data = newR->data;
            r->k = newR->k;
            newR->k =temp;
            newR->data = tempData;
            r->right = remove(lat, lon, r->right, ++level);
            return r;
            
            
        }
        
        else{
            Node<Key, T>* newR = r->right;
            if (newR==NULL) {
                newR = r->left;
                delete r;
                return newR;
            }
            delete r;
            return newR;
            
        }
    }
    
    else if (r->k >k){
        r->left = remove(lat, lon, r->left, ++level);
    }
    
    else  r->right= remove(lat, lon, r->right, ++level);
    
    return r;
    
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
