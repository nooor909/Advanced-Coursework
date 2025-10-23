// Advanced Algorithms coursework
// Question 1

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <fstream>
using namespace std;

// Bubble Sort count
int bubble_sort_count(int arr[], int n) {
	int i, j;
	int count = 0;
	bool swapped;
	for (int i = 0; i < n - 1; i++) {
		swapped = false;
		for (int j = 0; j < n - 1 - i; j++) {
			count++;
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
	return count;
}

// Selection Sort count
int selection_sort_count(int arr[], int n) {
	int i, j, min_index;
	int count = 0;
	for (int i = 0; i < n - 1; i++) {
		min_index = i;
		for (int j = i + 1; j < n; j++) {
			count++;
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}
		}
		if (min_index != i) 
			swap(arr[min_index], arr[i]);
	}
	return count;
}

// Insertion Sort count
int insertion_sort_count(int arr[], int n) {
	int i, key, j;
	int count = 0;
	for (int i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0) {
			count++;
			if (arr[j] > key) {
				arr[j + 1] = arr[j];
				j--;
			}
			else {
				break;
			}
		}
		arr[j + 1] = key;
	}
	return count;
}

// Copy of the arrays
void copy_array(int destination[], int source[], int n) {
	for (int i = 0; i < n; i++) {
		destination[i] = source[i];
	}
}
void random(int arr[], int n, int lo = 0, int hi = 200) {
	for (int i = 0; i < n; i++) {
		arr[i] = lo + (rand() % (hi - lo + 1));
	}
}
void sorted(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}
}
void reversed(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = n - 1 - i;
	}
}

// Measure the time for each execution
void measured_time(int arr[], int n, int(*sort_fn)(int*, int), 
	int& comparison_out, double& millisec_out) {
	auto start = chrono::high_resolution_clock::now();
	comparison_out = sort_fn(arr, n);
	auto end = chrono::high_resolution_clock::now();
	// Calculate duration in milliseconds
	chrono::duration<double, milli> duration = end - start;
	millisec_out = duration.count();
}

void run_tests(const string& title, void (*filler)(int*, int),
	ofstream& comps, ofstream& times) {
	cout << "\n == " << title << " == \n";
	int base[30], a1[30], a2[30], a3[30];

	for (int i = 1; i <= 30; i++) {
		filler(base, i);

		int comp_bubble, comp_selec, comp_ins;
		double time_bubble, time_selec, time_ins;

		copy_array(a1, base, i);
		measured_time(a1, i, bubble_sort_count, comp_bubble, time_bubble);

		copy_array(a2, base, i);
		measured_time(a2, i, selection_sort_count, comp_selec, time_selec);

		copy_array(a3, base, i);
		measured_time(a3, i, insertion_sort_count, comp_ins, time_ins);

		cout << "n = " << i << "\n";
		cout << "Bubble: Comparison = " << comp_bubble << ", time taken " << time_bubble << "ms \n";
		cout << "Selection: Comparison = " << comp_selec << ", time taken " << time_selec << "ms \n";
		cout << "Insertion: Comparison = " << comp_ins << ", time taken " << time_ins << "ms \n";

		comps << i << ", " << title << ", " << comp_bubble << ", " << comp_selec << ", " << comp_ins << endl;
		times << i << ", " << title << ", " << (time_bubble / 1000.0) << ", " 
				<< (time_selec / 1000.0) << ", " << (time_ins / 1000.0) << endl;
	}
}

void random_wrapper(int arr[], int n) {
	random(arr, n, 0, 200);
}
void test_comparisons() {
	srand(time(0));
	cout << fixed << setprecision(4);

	ofstream comps("Comparisons.csv");
	ofstream times("Times_ms.csv");

	comps << "n, array_type, Bubble, Selection, Insertion\n";
	times << "n, array_type, Bubble, Selection, Insertion\n ";
	times << fixed << setprecision(4);

	run_tests("Random", random_wrapper, comps, times);
	run_tests("Sorted", sorted, comps, times);
	run_tests("Reversed", reversed, comps, times);
	
	comps.close();
	times.close();
}

int main() {
	test_comparisons();
	return 0;
}