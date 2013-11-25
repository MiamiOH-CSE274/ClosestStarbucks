//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/10/01

template <class Key, class T>
class SSet {
 public:
  //Return the number of items currently in the SSet
  virtual unsigned long size() = 0;

  //Add a new item, x, with Key k.
  // If an item with Key k already exists, overwrite it
  virtual void add(Key lat, Key lon, T x) = 0;

  //Remove the item with Key lat, Key lon. If there is no such item, do nothing.
  virtual void remove() = 0;

  //If there is a key in the set that is > k,
  // return the first such key. If not, return k
  virtual T* next(Key lat, Key lon) = 0;

};
