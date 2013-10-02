/*****
 * Author   : brinkmwj
 * Date     : 2009-10-15
 * Sources  : All code is original
 * Purpose  : The purpose of this file is to do some VERY rudimentary timing of your getNearest
 *            method, as well as a very small sampling to measure accuracy
 */
#include <iostream>
#include <fstream>
#include <cmath>

#include "brinkmwjStarbucks.h"

#define PI 3.14159265
//This code is based on http://www.movable-type.co.uk/scripts/latlong.html
double distance(Entry& e1, Entry& e2){
  double R = 6371; // radius of earth, in km
  double dLat = (e2.y-e1.y)*PI/180;
  double dLon = (e2.x-e1.x)*PI/180;
  double lat1 = e1.y*PI/180;
  double lat2 = e2.y*PI/180;

  double a = sin(dLat/2) * sin(dLat/2) +
    sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
  double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  double d = R * c;

  return d;
}

double distance(double long1, double lat1, double long2, double lat2){
  double R = 6371; // radius of earth, in km
  double dLat = (lat2-lat1)*PI/180;
  double dLon = (long2-long1)*PI/180;
  lat1 = lat1*PI/180;
  lat2 = lat2*PI/180;

  double a = sin(dLat/2) * sin(dLat/2) +
    sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
  double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  double d = R * c;

  return d;
}


/*
 * This is a helper function that reads in the Starbucks.csv file. If you modified your Starbucks.csv,
 *  or if Starbucks.csv is not in the project's folder, then this might blow up on you.
 */
void readEntryList(Entry** entryList, int* n){
  std::ifstream inFile("starbucks.csv");

  if(!inFile){
    std::cout << "Error opening file" << std::endl;
    exit(0);
  }

  //The first line is just an integer that tells us what n is
  inFile >> *n;

  char buffer[1024];
  //Next, consume the line of labels
  inFile.getline(buffer,1024,'\r');
  inFile.getline(buffer,1024,'\r');

  *entryList = new Entry[*n];
  for(int i=0; i<*n; i++){
    inFile.getline(buffer, 256, ',');//Getline reads up until the first occurence of ',', and consumes the ',' for me
    (*entryList)[i].city = buffer;
    inFile.getline(buffer,256,',');
    (*entryList)[i].address = buffer;
    inFile >> (*entryList)[i].x;
    char c;
    inFile.get(c); //consume the comma, because >> does not do so
    inFile >> (*entryList)[i].y; //Don't need to worry about consuming the \n, because getline handles this
    while(isspace(inFile.peek())){
      inFile.get(c);
    }
  }
}

int main(){
  {
    brinkmwjStarbucks sS;

    int n;
    Entry* entryList;
    readEntryList(&entryList, &n); //Helper function

    //randomly scramble the entryList
    srand(5);
    for(int i=0; i<n; i++){
      int j = i + rand()%(n-i);
      Entry t = entryList[i];
      entryList[i] = entryList[j];
      entryList[j] = t;
    }

    /*
     * With my solution building the data structure takes less than 100ms, so the timing is not very accurate. I 
     * get numbers anywhere from 0ms to 60ms.
     */
    clock_t startb = clock();
    sS.build(entryList, n);
    clock_t endb = clock();
    std::cout << "Building the data structure took: " << 1000.0*(endb-startb)/CLOCKS_PER_SEC << " milliseconds" << std::endl;

    /* 
     * TEST FOR SPEED
     * Do many searches, and compute the average time per search. -- This should take between
     * 5 and 50 seconds.
     */
    clock_t start = clock();
    int numTrials = 1000;
    for(int i=0; i<numTrials; i++){
      double x = ((double)rand())/RAND_MAX;
      double y = ((double)rand())/RAND_MAX;
      Entry* tmp = sS.getNearest(x, y);
    }
    clock_t end = clock();

    if((end - start)/CLOCKS_PER_SEC < 5){ //If less than 5 seconds
      start = clock();
      numTrials = 10000;
      for(int i=0; i<numTrials; i++){
	double x = ((double)rand())/RAND_MAX;
	double y = ((double)rand())/RAND_MAX;
	Entry* tmp = sS.getNearest(x, y);
      }
      end = clock();
    }

    if((end - start)/CLOCKS_PER_SEC < 5){ //If less than 5 seconds
      start = clock();
      numTrials = 100000;
      for(int i=0; i<numTrials; i++){
	double x = ((double)rand())/RAND_MAX;
	double y = ((double)rand())/RAND_MAX;
	Entry* tmp = sS.getNearest(x, y);
      }
      end = clock();
    }

    if((end - start)/CLOCKS_PER_SEC < 5){ //If less than 5 seconds
      start = clock();
      numTrials = 1000000;
      for(int i=0; i<numTrials; i++){
	double x = ((double)rand())/RAND_MAX;
	double y = ((double)rand())/RAND_MAX;
	Entry* tmp = sS.getNearest(x, y);
      }
      end = clock();
    }

    std::cout << "Time: " << ((1000.0*(end - start)/CLOCKS_PER_SEC)/numTrials) << " ms per search, " <<numTrials << " trials" << std::endl;
		
		
    /* 
     * TEST FOR ACCURACY
     * I used Excel to double-check these answers
     */
    double studentTotal = 0.0;
    double optTotal = 0.0;

    //I used Excel to compute these test points
    Entry* testS = sS.getNearest(-86.295369,32.35012); //Should be the "Zelda Rd  Carter Hill Rd"
    optTotal += 0.0;
    studentTotal += distance(testS->x, testS->y,-86.295369,32.35012);
  		
    testS = sS.getNearest(-79.5,43.7); //Should be the "Toronto Ontario" "Festival Hall" location
    optTotal += 1.5400761831996408;
    studentTotal += distance(testS->x, testS->y,-79.5,43.7);
		
    testS = sS.getNearest(-86.75,36.0); //Should be the "Target Brentwood T-1983" location
    optTotal += 2.3306897598873859;
    studentTotal += distance(testS->x, testS->y,-86.75,36.0);
    
    double error = studentTotal/optTotal;
    std::cout << "Error percentage is: " << 100.0*(error-1.0) << std::endl; //Note that 0.0 is the best error level

  }

  return 0;
}
