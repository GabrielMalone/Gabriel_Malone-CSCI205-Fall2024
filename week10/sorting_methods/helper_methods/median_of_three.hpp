#ifndef MEDIANOFTHREE
#define MEDIANOFTHREE

#include <vector>

using namespace std;

int MO3(vector<int>& v, int left, int right){
    int center = (left + right) / 2;	// find center
	//swap(v[left], v[center]);			// get ready to sort the three
	if( v[left] > v[right] )			// look at left and right
		swap(v[left], v[right]);		// swap if necessary
	if(v[center] > v[right] )			// look at center and right
		swap(v[center], v[right]);		// swap if necessary
	//swap(v[center], v[right]);			// put pivot on right
	return v[right];					// return pivot value
}

#endif 