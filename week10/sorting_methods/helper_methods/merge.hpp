#ifndef MERGE_HELPER
#define MERGE_HELPER

#include <vector>
#include "../../backend/sort_data.hpp"

using namespace std;

void merge(vector<int> &avector, vector<int> left, vector<int> right, sortData& s, bool print){
	unsigned i = 0;	// left vector index
	unsigned l = 0;	// right vector index
	unsigned r = 0;	// merged vector index
	// while there are elements in both sub vectors
	while (l < left.size() && r < right.size()){
        s.comparisons ++ ;
		if (left[l] < right[r]){
			avector[i] = left[l];		// copy from left
            i ++ ;
			l ++ ;
			s.array_accesses ++;
			if (print){
				printTowers(avector, avector[l]);
			}
        }
		else {
			avector[i] = right[r];	// copy from right
			if (print){
				printTowers(avector, avector[r]);
			}
			s.array_accesses ++;
			i ++ ;
			r ++ ;
		}
	}
	// one of the vectors is exhausted. Can unconditionally copy from here
	while (l < left.size()) {
		s.comparisons++;
		s.array_accesses++;
		avector[i] = left[l];        // copy from left
		if (print){
			printTowers(avector, avector[l]);
		}
		i ++ ;
		l ++ ;
	}

	while (r < right.size()) {
		s.comparisons++;
		s.array_accesses++;
		avector[i] = right[r];
		if (print){
			printTowers(avector, avector[r]);
		}
		i ++ ;
		r ++ ;      // copy from right
	}
}

#endif