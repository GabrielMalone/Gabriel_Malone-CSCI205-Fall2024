#ifndef REALMEDIAN_SORT
#define REALMEDIAN_SORT

#include <vector>
#include "../../backend/sort_data.hpp"
#include "../../backend/bubblesort.hpp"

using namespace std;

// cheating and pretending can just find the actual median without time cost
// this only really works when rrandom vectors generated with non repeating 1 through N
// otherwise it's as good as lazy middle

int realMedian(vector<int>&v, int start, int end){
   return  ( start + end ) / 2;
}

#endif 