#ifndef MSORT_H
#define MSORT_H
#include <iostream>
#include <vector>


//Could be in the mergesort_util class, I think this is better for readibility but not sure
template <typename T, typename Compare>
void Merge(T *a, int low, int high, int mid, Compare comp) {
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k; 
	std::vector<T> temp;
	i = low;
	//k = 0;
	j = mid + 1;
	// Merge the two parts into temp[].
	while (i <= mid && j <= high) {
		if (comp(a[i],a[j])) {
			temp.push_back(a[i]);
			//k++;
			i++;
		} else {
			temp.push_back(a[j]);
			//k++;
			j++;
		}
	}
	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid) {
		temp.push_back(a[i]);
		//k++;
		i++;
	}
	// Insert all the remaining values from j to high into temp[].
	while (j <= high) {
		temp.push_back(a[j]);
		//k++;
		j++;
	}
	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++) {
		a[i] = temp[i-low];
	}
}


template <typename T, typename Compare = std::less<T> >
class mergesort_util {
public:
	mergesort_util(T *_start, int _size, bool _merge_on = true) : start(_start), size(_size), merge_on(_merge_on) {
		comp = Compare();
	}
	
	void split(int low, int high) {
		int mid;
		if (low < high) {
			mid = (low+high)/2;
			split(low, mid);
			split(mid+1, high);
			
			if (merge_on) {
				Merge(start, low, high, mid, comp);
			} else {
				//Sort two element sub-arrays 
				if (high-low == 1) {
					Merge(start, low, high, mid, comp);
				}
			}
		}
	}
	
	void set_merge_on() { merge_on = true; }
	
	void sort() {
		//The commented line depends on interpretation
		//set_merge_on();
		split(0, size-1);
	}

private:
	T *start;
	int size;
	bool merge_on;
	Compare comp;
};

template <typename T>
void mergesort(T *start, int size) {
	mergesort_util<T> tmp(start, size);
	tmp.sort();
}

template <typename T, typename Compare>
void mergesort(T *start, int size, Compare comp) {
	mergesort_util<T, Compare> tmp(start, size);
	tmp.sort();
}	

#endif