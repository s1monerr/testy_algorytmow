#pragma once
#include<iostream>

void spc(int i) {
	for (int j = 0; j < i; j++) {
		std::cout << std::endl;
	}
}


void print_tab(int* tab, int n) {
	std::cout << "tab";

	for (int i = 0; i < n; i++)	{
		if (tab[i] != NULL)
			std::cout << " -> " << tab[i];
	}

	std::cout << std::endl;
}


void swap(int& a, int& b) {
	int buf = a;
	a = b;
	b = buf;
}


void heapify(int n, int* tab, int heapsize) {
	int left = 2 * n;
	int right = 2 * n + 1;
	int large;
	if (left <= heapsize && tab[left] > tab[n])
		large = left;
	else
		large = n;

	if (right <= heapsize && tab[right] > tab[large])
		large = right;
	if (large != n)
	{
		swap(tab[n], tab[large]);
		heapify(large, tab, heapsize);
	}
}


void heap_all(int* tab, int heapsize) {
	int n = heapsize / 2;
	while (n > 0)
	{
		heapify(n, tab, heapsize);
		n--;
	}
}


void heapsort(int* tab, int n){ // wersja dla tablicy n - elementow(wszystkie indexy wykorzystane)
	--tab; // wtedy indeks tab[1] wskazuje na tab[0]
	heap_all(tab, n);
	while (n > 1)
	{
		swap(tab[1], tab[n]);
		heapify(1, tab, --n);
	}
}



int partition(int* A, int l, int r){
	int x = A[r];
	int i = l - 1;
	for (; l < r; ++l){
		if (A[l] <= x)
			swap(A[++i], A[l]);
	}
	swap(A[i + 1], A[l]);
	return i + 1;
}


int partition_horae(int* T, int l, int r){
	int x = T[l]; // podzial wzgledem lewego elementu
	int i = l;
	int j = r + 1;

	for (;;) {
		do ++i; while (i <= r && T[i] < x);
		do --j; while (T[j] > x);
		if (j < i)
			break;
		swap(T[i], T[j]);
	}

	//swap(T[j], T[l]);
	T[l] = T[j];
	T[j] = x;
	return j;
}


int partition_mediana(int* T, int l, int r) {
	if (r - l == 1) { // jezeli tablica ma dlugosc 2
		if (T[l] > T[r]) {
			swap(T[l], T[r]);
		}
		return l;
	}

	swap(T[l], T[(l + r) >> 1]); // zamien element lewy ze srodkowym -> ustawiam element podzialu na srodek

	//WYBIERANIE ELEMENTU PODZIALU: MEDIANA Z 3

	if (T[l + 1] > T[r]) swap(T[l + 1], T[l]);
	if (T[l] > T[r]) swap(T[l], T[r]);
	if (T[l + 1] > T[l]) swap(T[l], T[l + 1]);

	// W EFEKCIE: T[l+1] <= T[l] <= T[r]

	// DZIELENIE TABLICY - WG LEWEGO ELEMENTU

	int x = T[l];

	int i = l + 1;
	int j = r;
	for (;;) {
		do ++i; while (T[i] < x);
		do --j; while (T[j] > x);

		if (i > j)
			break;

		swap(T[i], T[j]);
	}

	T[l] = T[j];
	T[j] = x;

	std::cout << "RETURNING index: " << j << std::endl;
	return j;

}


void bubble_sort_true(int* tab, int size) {
	bool swapped = true;
	for (int i = 0; i < size && swapped; ++i) {
		swapped = false;
		for (int j = 0; j < size - i; ++j) {
			if (tab[j] > tab[j + 1]) {
				swapped = true;
				swap(tab[j], tab[j + 1]);
			}
		}
	}
}


void bubble_sort(int* tab, int n) {
	int last = n;
	while(last>0) {
		int last_buf = 0;
		for (int i = 0; i < last; i++) {
			if (i+1<n&&tab[i] > tab[i + 1]) {
				swap(tab[i], tab[i + 1]);
				last_buf = i;
			}
		}
		last = last_buf;
	}
}


void quicksort(int* tab, int l, int r) {
	if (l >= r)
		return;
	int r_2 = partition(tab, l, r);
	quicksort(tab, l, r_2 - 1);
	quicksort(tab, r_2 + 1, r);
}


void quicksort_mediana(int* tab, int l, int r) {
	if (l >= r)
		return;
	int r_2 = partition_mediana(tab, l, r);
	quicksort_mediana(tab, l, r_2 - 1);
	quicksort_mediana(tab, r_2 + 1, r);
}


void quicksort_horae(int* tab, int l, int r) {
	if (l >= r)
		return;
	int r_2 = partition_horae(tab, l, r);
	quicksort_horae(tab, l, r_2 - 1);
	quicksort_horae(tab, r_2 + 1, r);
}


void hybrid_quicksort(int* tab, int l, int r) {
	if (r - l < 10) {
		bubble_sort(tab, (r-l));
		return;
	}
	else {
		int r_2 = partition_mediana(tab, l, r);
		hybrid_quicksort(tab, l, r_2 - 1);
		hybrid_quicksort(tab, r_2 + 1, r);
	}
}
void copy(int* tab, int l, int r, int* tab_2) {
	int i = 0;
	while (l < r) {
		tab_2[i] = tab[l];
		i++;
		l++;
	}
}


void merge(int *tab, int *tab1,int *tab2, int a, int b)
{
	int i = 0, j = 0, p = 0;
	while (i < a && j < b){//zawsze musza istniec elementy w obu tabilcach
		if (tab1[i] < tab2[j])
			tab[p++] = tab1[i++];
		else
			tab[p++] = tab2[j++];
	}
	while (i < a)//pozostale elementy z i oraz j trzeba dorzucic do tab
		tab[p++] = tab1[i++];

	while (j < b)
		tab[p++] = tab2[j++];
}
void merge_sort(int* tab, int n) {
	if (n > 1) {
		const int g = n / 2, h = n - g;
		int* tab_1 = new int[g];
		int* tab_2 = new int[h];
		copy(tab, 0, g, tab_1);
		copy(tab, g, n, tab_2);
		merge_sort(tab_1, g);
		merge_sort(tab_2, h);
		merge(tab, tab_1, tab_2, g, h);
	}
	else
		return;
}
void merge_hybrid(int* tab, int n) {
	if (n <= 10) {
		bubble_sort(tab, n);
		return;
	}
	const int g = n / 2, h = n - g;
	int* tab_1 = new int[g];
	int* tab_2 = new int[h];
	copy(tab, 0, g, tab_1);
	copy(tab, g, n, tab_2);
	merge_hybrid(tab_1, g);
	merge_hybrid(tab_2, h);
	merge(tab, tab_1, tab_2, g, h);
}


void insert_sort(int* tab, int size) {
	for (int i = 1; i < size; i++) {
		int x = tab[i];	// ostatni analizowany element posortowanej czesci
			int j = i-1;	// j -> itrator wstawianego elementu
			while (tab[j] > x && j>=0) {
				tab[j + 1] = tab[j];
				--j;
			}
			tab[j+1] = x;
	}
}

void select_sort(int* tab, int size) {
	for (int i = 0; i < size-1; i++) {
		int min = tab[i];
		int index = i; // index min elementu
		for (int j = i+1; j < size; j++) { // znajdz min element
			if (tab[j] < min) {
				min = tab[j];
				index = j;
			}
		}
		swap(tab[i], tab[index]);

	}
}
