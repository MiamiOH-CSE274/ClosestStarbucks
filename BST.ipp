#define dNULL 0
#include <string>

template <class Key, class T>
BST<Key,T>::BST(){
    root = dNULL;
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
    if (r==dNULL){
        return numItems;
    }
    else numItems++;
    if (r->left==dNULL) {
        numItems += size(r->right);
    }
    
    else if (r->right==dNULL) {
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
T BST<Key,T>::find(Key lat, Key lon){
    Node<Key, T>* data = find(lat, lon, root,0);
    if (data==dNULL) {
        throw (std::string)"This key does not exist in the tree.";
    }
    return data->data;
}
//Return true if there is an item with Key lat, Key lon in the table. If not,
// return false
template <class Key, class T>
bool BST<Key,T>::keyExists(Key lat, Key lon){
    Node<Key,T>* data = find(lat, lon, root,0);
    
    if (data==dNULL) {
        return false;
    }
    else return true;
}

//If there is a key in the set that is > k,
// return the first such key. If not, return k
template <class Key, class T>
T* BST<Key,T>::next(Key lat, Key lon){
   
   Node<Key, T>* toReturn = next(lat, lon, root,0);
    T* place;
    
//    if (toReturn==dNULL) {
//        return k;
//    }
    place = &toReturn->data;
    return place;

}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::next(Key lat, Key lon, Node<Key,T>* r, int level){
    
    Node<Key,T>* curPtr;
    Key k;
    
    if(level%2==0)
        k = lon;
    else k = lat;
    
    if(r==NULL){
        return NULL;
    }
    
    if (r->k >k){
        curPtr= next(lat, lon, r->left, ++level);
    }
    
    else if(r->k <k){
        curPtr= next(lat, lon, r->right, ++level);
    }
    
    else{
        if(r->right !=NULL)
            curPtr= next(lat, lon, r->right, ++level);
        else curPtr= dNULL;
    }
    
//    while (curPtr !=dNULL) {
//        if (curPtr->k > k) {
//            previousPtr = curPtr;
//            curPtr = curPtr->left;
//        }
//        else if (curPtr->k < k){
//            curPtr = curPtr->right;
//        }
//        else{
//            curPtr = curPtr->right;
//        }
//    }
//    
//    if (previousPtr->k <k) {
//        return dNULL;
//    }
    
    if(curPtr==dNULL && r->k>k)
        return r;
    
    else if (curPtr ==NULL)
        return r;
    
    else return curPtr;
   }

//If there is a key in the set that is < k,
// return the first such key. If not, return k
template <class Key, class T>
T* BST<Key,T>::prev(Key lat, Key lon){
    T* place;
    Node<Key, T>* toReturn=prev(lat, lon, root, 0);
    
//    if (toReturn==dNULL) {
//        return k;
//    }
     place = &toReturn->data;
    return place;
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::prev(Key lat, Key lon, Node<Key,T>* r, int level){
    Node<Key,T>* curPtr;
        Key k;
    if(level%2==0)
        k = lon;
    else k = lat;

    if(r==NULL){
        return NULL;
    }
    
    if (r->k >k){
        curPtr= next(lat, lon, r->right, ++level);
    }
    
    else if(r->k <k){
        curPtr= next(lat, lon, r->left, ++level);
    }
    
    else{
        if(r->left !=NULL)
            curPtr= next(lat, lon, r->left, ++level);
        else curPtr= dNULL;
    }
    
    
    //    while (curPtr !=dNULL) {
//        if (curPtr->k < k) {
//            previousPtr = curPtr;
//            curPtr = curPtr->right;
//        }
//        else if (curPtr->k > k){
//            previousPtr = curPtr;
//            curPtr = curPtr->left;
//        }
//        else{
//            curPtr = curPtr->left;
//        }
//    }
    
    if(curPtr==dNULL && r->k>k)
        return r;
    else if (curPtr==NULL)
        return r;
    
    else return curPtr;
}




template <class Key, class T>
Node<Key,T>* BST<Key,T>::add(Key lat, Key lon, T x, Node<Key,T>* r,int level){
        Key k;
    if(level%2==0)
        k = lon;
    else k = lat;
    
    if (r==dNULL) {
        Node<Key,T>* toAdd = new Node<Key, T>;
        toAdd->k = k;
        toAdd->data = x;
        return toAdd;
    }
    else if (r->k==k){
        r->data = x;
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
    if (r == dNULL) {
        return dNULL;
    }
    else if (r->k==k){
        if (r->left==dNULL && r->right==dNULL) {
            delete r;
            return dNULL;
        }
        else if (r->left==dNULL || r->right==dNULL){
            Node<Key, T>* newR = r->left;
            if (newR==dNULL) {
                newR = r->right;
            }
            delete r;
            return newR;
        }
        else{
            Node<Key, T>* maxR = max(r->left);
            Key temp = maxR->k;

            maxR->k = r->k;
            r->k = temp;
            T dataTemp = r->data;
            r->data = maxR->data;
            maxR->data = dataTemp;
            //FIGURE OUT WHICH LEVEL THIS NEEDS TO BE
            r->left = remove(lat, lon, r->left, ++level);
            return r;
        }
    }
    
    else if (r->k >k){
       return r = remove(lat, lon, r->left, ++level);
    }
    
    else return r= remove(lat, lon, r->right, ++level);
    
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
