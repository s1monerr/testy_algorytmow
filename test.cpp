#include <iostream>
#include "algorytmy.h"
#include <time.h>
#include <chrono>

void copy_tab(int* t1, int* t2, int n) {
	for (int i = 0; i < n; i++) {
		t2[i] = t1[i];
	}
}

using namespace std::chrono;

int main() {
	int n;
	std::cout << "array size: ";
	std::cin >> n;
	const int size = n;
	srand(time(NULL));
	int* tab = new int[size];
	std::cout << "1 - inverse sort, 2 - random (-100; 100), 3 - sorted arr" << std::endl;
	int x;
	std::cin >> x;
	switch (x)
	{
	case(1):
		std::cout << "INVERSE SORT" << std::endl << std::endl;
		for (int i = 0; i < size; i++) {
			tab[i] = 10000 -  i;//odwrotnie posortowana
		}
		break;
	case(2):
		std::cout << "RANDOM SORT" << std::endl << std::endl;
		for (int i = 0; i < size; i++) {
			tab[i] = rand() % 200 - 100;//liczby losowe
		}
		break;
	case(3):
		std::cout << "SORTED ARRAY" << std::endl << std::endl;
		for (int i = 0; i < size; i++) {//posortowana
			tab[i] = i;
		}
		break;
	default:
		std::cout << "default: RANDOM SORT" << std::endl;
		for (int i = 0; i < size; i++) {
			tab[i] = rand() % 200 - 100;//liczby losowe
		}
		break;
	}
	std::cout << "array size: " << size << std::endl << std::endl;
	int max = -1, min = -1;
	auto tmax(0);
	auto tmin(5000000);

	int* tab_1 = new int[size];//hybrid_quicksort
	copy_tab(tab, tab_1, size);
	auto start = high_resolution_clock::now();
	hybrid_quicksort(tab_1, 0,size-1);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "1. hybrid_quicksort time = " << duration.count() << " micros" << std::endl;
	delete[] tab_1;
	tmax = duration.count();
	tmin = duration.count();
	max = 1;
	min = 1;

	if (size < 10000||x!=1) {
		int* tab_2 = new int[size];//quicksort (zwykly partition)
		copy_tab(tab, tab_2, size);
		auto start_1 = high_resolution_clock::now();
		quicksort(tab_2, 0, size - 1);
		auto stop_1 = high_resolution_clock::now();
		auto duration_1 = duration_cast<microseconds>(stop_1 - start_1);
		std::cout << "2. quicksort time = " << duration_1.count() << " micros" << std::endl;
		delete[] tab_2;
		if (duration_1.count() < tmin) {
			tmin = duration_1.count();
			min = 2;
		}
		else if (duration_1.count() > tmax) {
			tmax = duration_1.count();
			max = 2;
		}

		int* tab_5 = new int[size];//quicksort_horae
		copy_tab(tab, tab_5, size);
		auto start10 = high_resolution_clock::now();
		quicksort_horae(tab_5, 0, size - 1);
		auto stop10 = high_resolution_clock::now();
		auto duration10 = duration_cast<microseconds>(stop10 - start10);
		std::cout << "3. quicksort hoare time = " << duration10.count() << " micros" << std::endl;
		delete[] tab_5;
		if (duration10.count() < tmin) {
			tmin = duration10.count();
			min = 3;
		}
		else if (duration10.count() > tmax) {
			tmax = duration10.count();
			max = 3;
		}
	}

	if (size < 26000 || x != 1) {
		int* tab_3 = new int[size];//quicksort_mediana
		copy_tab(tab, tab_3, size);
		auto start_15 = high_resolution_clock::now();
		quicksort_mediana(tab_3, 0, size - 1);
		auto stop_15 = high_resolution_clock::now();
		auto duration_15 = duration_cast<microseconds>(stop_15 - start_15);
		std::cout << "4. quicksort mediana time = " << duration_15.count() << " micros" << std::endl;
		delete[] tab_3;
		if (duration_15.count() < tmin) {
			tmin = duration_15.count();
			min = 4;
		}
		else if (duration_15.count() > tmax) {
			tmax = duration_15.count();
			max = 4;
		}
	}

	int* tab_4 = new int[size];//heapsort
	copy_tab(tab, tab_4, size);
	auto start3 = high_resolution_clock::now();
	heapsort(tab_4, size);
	auto stop3 = high_resolution_clock::now();
	auto duration3 = duration_cast<microseconds>(stop3 - start3);
	std::cout << "5. heapsort time = " << duration3.count() << " micros" << std::endl;
	delete[] tab_4;
	if (duration3.count() < tmin) {
		tmin = duration3.count();
		min = 5;
	}
	else if (duration3.count() > tmax) {
		tmax = duration3.count();
		max = 5;
	}

	int* tab_6 = new int[size];//merge_sort
	copy_tab(tab, tab_6, size);
	auto start5 = high_resolution_clock::now();
	merge_sort(tab_6, size);
	auto stop5 = high_resolution_clock::now();
	auto duration5 = duration_cast<microseconds>(stop5 - start5);
	std::cout << "6. merge_sort time = " << duration5.count() << " micros" << std::endl;
	delete[] tab_6;
	if (duration5.count() < tmin) {
		tmin = duration5.count();
		min = 6;
	}
	else if (duration5.count() > tmax) {
		tmax = duration5.count();
		max = 6;
	}

	int* tab_7 = new int[size];//merge_hybrid
	copy_tab(tab, tab_7, size);
	auto start6 = high_resolution_clock::now();
	merge_hybrid(tab_7, size);
	auto stop6 = high_resolution_clock::now();
	auto duration6 = duration_cast<microseconds>(stop6 - start6);
	std::cout << "7. merge_hybrid time = " << duration6.count() << " micros" << std::endl;
	delete[] tab_7;
	if (duration6.count() < tmin) {
		tmin = duration6.count();
		min = 7;
	}
	else if (duration6.count() > tmax) {
		tmax = duration6.count();
		max = 7;
	}

	//bubble_sort(tab, size);
	//bubble_sort_true(tab, size);
	spc(1);
	std::cout << "***";
	spc(2);
	std::cout << "Best time = " << tmin << " microseconds, index: " << min << std::endl;
	std::cout << "Worst time = " << tmax << " microseconds, index: " << max;
	spc(1);

	system("pause");

	return 0;
}
