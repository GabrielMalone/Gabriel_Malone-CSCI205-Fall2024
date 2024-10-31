#ifndef NTHER
#define NTHER

#include <vector>
#include <algorithm>
#include "median_of_three.hpp"
#include "../../backend/bubblesort.hpp"


using namespace std;
// no swapping median finder
int MO3t (vector<int>& v, int a,  int c, sortData& s){
	int b = v[(a+c)/2];
	a = v[a];
	c = v[c];
	if ((a <= b) && (b <= c)) {s.comparisons ++ ;return b;}
	if ((a <= c) && (c <= b)) {s.comparisons ++ ;return c;}
	if ((b <= a) && (a <= c)) {s.comparisons ++ ;return a;}
	if ((b <= c) && (c <= a)) {s.comparisons ++ ;return c;}
	if ((c <= a) && (a <= b)) {s.comparisons ++ ;return a;}
	s.comparisons ++ ;
	return b;
}

int tukeys(vector<int>& v, int first, int last, sortData& s){
	if (last > 3){								
		int m1Last = (last / 3);
		int m2Last = (last * 2 / 3);

		int a =  MO3t(v, first, m1Last, s);   	   // median of 3 on first 1/3 of vector
		int b =  MO3t(v, m1Last+1, m2Last, s);	   // median of 3 on middle 1/3 of vector
		int c =  MO3t(v, m2Last+1, last, s);       // median of 3 on last 1/3 of vector

		int median = 0;

		if ((a <= b) && (b <= c)) median = b;		// get median of those medians
		if ((a <= c) && (c <= b)) median = c;
		if ((b <= a) && (a <= c)) median = a;
		if ((b <= c) && (c <= a)) median = c;
		if ((c <= a) && (a <= b)) median = a;
		median = b;

		s.comparisons +=5;

		int index = 0;							 	// get index of that median
		for (int i = first ; i < last ; i ++){
			s.comparisons ++ ;
			if (v[i] == median){
				index = i;
				break;
			}
		}
		if (index == 0){
			index = ( first + last ) / 2;
		}
		return index;							// return the index to be able to swap to right side
	}
	return last;
}
#endif 