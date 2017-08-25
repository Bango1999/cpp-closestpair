#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <float.h>

using namespace std;

class Point {
public:
float x,y;

Point() {
	x = y = 0;
}
};

int cmpX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int cmpY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}

class Pair {
private:
	Point a, b;
	float dist;
	
	public:
	Pair(Point pOne, Point pTwo) {
		a = pOne;
		b = pTwo;
		dist = getDistance();
	}
	
	Pair bruteForce(Point arr[], int n) {
	//cout << "\tBRUTE FORCE ARRAY DUMP:" << endl;
	//for (int i = 0; i < n; i++)
	//	cout << "\t" << arr[i].x << " " << arr[i].y << endl;
	Point a,b;
	Pair pair(a,b);
			
		if (n < 2) {
			cout << "failed brute force, n=" << n << endl;
			return pair;
		} else {
			Pair minPts(arr[0],arr[1]);
			float min = abs(minPts.getDistance());
		//	cout << "\t\tinit minDist=" << min << " when minpts=";
		//	minPts.print();
			
			for (int i = 1; i < n-1; ++i) {
				for (int j = i+1; j < n; ++j) {
					Pair p(arr[i],arr[j]);
					float newDistance = abs(p.getDistance());
				//	cout << "\tfound new distance in ";
				//	p.print();
				//	cout << "\t as " << newDistance << endl;
					if (newDistance < min) {
						min = newDistance;
						minPts = p;
					}
				}
			}
		//	cout << "\tbrute forced and found closest pair here, ";
		//	minPts.print();
			return minPts;
		}
	}
	
	//recursion algorithm for closest pair
	Pair recurse(Point X[], Point Y[], int Xlen, int Ylen) {
	//see if we need to do a brute force
	if (Xlen <= 3) {
		return bruteForce(X,Xlen);
	} 
	
	//define a pair
	Point a,b;
	Pair pair(a,b);
	
	//calculate the sizes of the split arrays, define new arrays
	int newLeftLen = Xlen/2;
	int newRightLen = Xlen/2;
	if (Xlen % 2 == 1) {
		newRightLen++;
	}
	Point xLeft[newLeftLen];
	Point xRight[newRightLen];
	//set values for the subarrays
	for (int i =0; i<Xlen;i++) {
		if (i < Xlen/2)
			xLeft[i] = X[i];
		else
			xRight[i-(Xlen/2)] = X[i];
	}
	
	//new temporary array identical to xLeft, sort it by y, perform recursion
	Point temp[newLeftLen];
	for (int i = 0; i < Xlen/2; i++) {
		temp[i] = xLeft[i];
	}
	qsort(temp,newLeftLen,sizeof(Point),cmpY);
	Pair closestLeft = recurse(xLeft,temp,newLeftLen,newLeftLen);
	
	//new temporary array identical to xRight, sort it by y, perform recursion
	Point temp2[newRightLen];
	for (int i = 0; i < newRightLen; i++) {
		temp2[i] = xRight[i];
	}
	qsort(temp2,newRightLen,sizeof(Point),cmpY);
	Pair closestRight = recurse(xRight,temp2,newRightLen,newRightLen);
	
	//get closest set of pts from 2 previous recursions
	Pair closest = getMin(closestLeft,closestRight);
		
	//define a new temp to hold values that meet the condition below
	Point temp3[Ylen];
	int temp3Ctr = 0;
	//define shortest distance as the dist in closest pair we have so far
	float shortest = closest.getDistance();
	//set x to be the initial value of xRight's x value
	float x = xRight[0].x;
	//add new points to temp3
	for (int i = 0; i < Ylen; i++) {
		if (abs(x-Y[i].x) < shortest) {
			temp3[temp3Ctr++] = Y[i];
		}
	}
	
	for (int i = 0; i < temp3Ctr-1; i++) {
		Point p1 = temp3[i];
		for (int j = i+1; j < temp3Ctr; j++) {
			Point p2 = temp3[j];
			if ((p2.y - p1.y) >= shortest) {
			//	cout << "break condition" << endl;
				break;
			}
			Pair newPair(p1,p2);
			if (newPair.getDistance() < closest.getDistance()) {
				closest = newPair;
				shortest = newPair.getDistance();
			}
		}
	}
	
	return closest;
	}
	
	//return minimum of 2 floats
Pair getMin(Pair a, Pair b) {
	if (a.getDistance() < b.getDistance())
		return a;
	else
		return b;
}
	
float getDistance() {
	float x = (getAX()- getBX());
	x = x*x;
	float y = getAY() - getBY();
	y = y*y;
	return abs(sqrt(x+y));
}

int pairCmpY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}
	
  float getAX() {return a.x;	}
	float getAY() {return a.y;}
	float getBX() {return b.x;}
	float getBY() {return b.y;}
	void setAX(float x) {a.x = x;}
	void setAY(float y) {a.y = y;}
	void setBX(float x) {b.x=x;}
	void setBY(float y) {b.y=y;}
	
	void print() {
		cout << "Pair = (" << getAX() <<","<< getAY() <<") , ("<< getBX() <<","<< getBY() <<")" << endl;
		cout << "Distance = " << getDistance() << endl;
	}
};

//closest pair algo
void findClosestPair(Point arr[], const int n, int problem) {
	Point X[n], Y[n];
	for (int i = 0; i < n; i++) {
		X[i] = arr[i];
		Y[i] = arr[i];
		//cout << arr[i].x << " & " << arr[i].y << endl;
	}
	
	//sort values by both x and y coords
	qsort(X,n,sizeof(Point),cmpX);
	qsort(Y,n,sizeof(Point),cmpY);
	//for (int i = 0; i < n; i++)
	//	cout << "X: " << X[i].x << " & " << X[i].y << "  Y: " << Y[i].x << " & " << Y[i].y << endl;
	
	Point a;
	Point b;
	Pair pair(a,b);
	pair = pair.recurse(X,Y,n,n);
	pair.print();
}

//get the points into an array of x,y
void closestPair(ifstream& pts, int problem) {
	if (pts.good()) {
		int numPoints;
		pts >> numPoints;
		cout << numPoints << endl;
		Point arr[numPoints];
		for (int i = 0; i < numPoints; i++) {
			pts >> arr[i].x >> arr[i].y;
			//cout << arr[i].x << " " << arr[i].y << endl;
		}
		//weve got the points array, do the algorithm
		findClosestPair(arr, numPoints,problem);
	}
}

int main() {
	int cases;
	ifstream pts;
	pts.open("points.txt");
	if (pts.is_open()) {
		pts >> cases;
		for (int i = 0; i < cases; i++)
			closestPair(pts,i+1);
	} else {
		cout << "could not open points.txt" << endl;
	}
	return 0;
}