Author
==========
"Luo, Yu", luoy6
ClosestStarbucks
================

Find the nearest Starbucks location

Background info
---------------
Imagine that you need to find the closes Starbucks store to your current location. Google maps makes this very easy – Simply searching for your current address + “starbucks” will work (http://maps.google.com/maps?q=starbucks%2045056). This kind of problem is called the “nearest neighbor problem.” In the nearest neighbor problem we start with a large but seldom changing list of locations (that is, we get the x and y coordinates of all Starbucks locations), and build a data structure. This data structure’s goal is to make it very efficient to find the closest Starbucks to a given pair of x and y coordinates. In this assignment you will design a data structure that solves the nearest-neighbor problem. 

Your data structure will support two operations:

1. `void build(Entry* c, int n)` – My skeleton code will read in a file that contains the locations of all US Starbucks locations. c is a pointer to an array of “Entry” objects, and n is the length of c. The entry class has four member variables: City (string), Address (string), x (the longitude, which is a float between -360 and +360) and y (the latitude, which is a float between -360 and +360). Your build function is expected to store the data and build whatever data structure you want using that data. The running time of build is not important, as long as it finishes in a reasonable period of time (say less than 10 minutes). Note: I may delete the array that c points to, so you should not depend on it existing after build() finishes! You need to copy the data into your own data structure!
2.	`Entry* getNearest(double x, double y)` – There is probably not a Starbucks location at position (x,y), so your job is to find the nearest location to it, and return a pointer to the appropriate entry in your data structure. I have provided two functions for computing distance: They are declared in Starbucks.h, and implemented in Controller.cpp.

Goals/requirements
------------------
There is an inherent trade-off between the speed of getNearest, the accuracy of getNearest, and the complexity of the resulting data structure and code. If you want getNearest to be both fast and accurate you are going to need a sophisticated data structure (http://en.wikipedia.org/wiki/K-d_tree would be a good place to start).

If you are willing to sacrifice accuracy, your BST from lab 06 might be useful. If you are willing to sacrifice speed there are a lot of simple approaches you could use.

1. getNearest() should be as fast as possible
2. getNearest() should be as accurate as possible

Suggested steps
-----

1. Download the starter code (Starbucks.h and Controller.cpp) from the site. Do NOT modify Starbucks.h (you may modify Controller.cpp if you wish).
2. Create your own Starbucks class (mine was called brinkmwjStarbucks, and it was implemented in brinkmwjStarbucks.h and brinkmwjStarbucks.cpp) which inherits from the Starbucks class. Note, your class declaration should look something like this: `class brinkmwjStarbucks : public Starbucks { 
/* member variables and methods declared here */ 
}`
3. Implement all methods of your Starbucks class. Don’t forget the constructor and destructor, as well as the methods inherited from Starbucks.

Questions
=========

#### 1. Which type of data structure did you choose? Explain, in English, the main ideas behind your data structure.

TODO

#### 2. Explain, in English, the worst-case running time of each of your methods, along with a justification of your claims.

TODO

Portfolio Video
=========

Explain your code, as you would to a boss or colleague in the workplace. You will most likely want to use a screen-capture software. You should, at minimum, do the following:

1. Show your program running.
2. Show your code, briefly explaining what it is meant to do. You do NOT need to explain any of the provided code, unless you made some meaningful change you want to describe.
3. If something is not working (or if you aren't sure), explain that part carefully.
4. Explain the expected running times of your getNearest method.

The video should certainly be less than 2 minutes long. I (or the grading assistant) ought to be able to grade your program based solely on your video, so be sure that we can see your code style, and can accurately assess what works, or doesn't work, in your program. The "Questions" above might also be things you want to talk about in your video: The video should be able to be understood even by someone that isn't in the class, and hasn't read your question answers.

#### 1. Give the link to your portfolio video on YouTube.

TODO