#ifndef _main_H 
#define _main_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

extern ofstream outFile;

extern const char* txt; 
void printArr(int arr[], int n, const char *txt);
bool cmp(int a, int b);
int *createSuffixArray(int n);
void searchAllPatternsWithLCP(const char* pat, int n, int *suffixArray);
void searchAllPatterns(const char* pat, int n, int *suffixArray);
int* createSuffixArrayEytzinger(int* suffixArrayEytzinger, int n);
void searchEytzinger(const char* pat, int n, int *suffixArray, int i, int* count);
void write_output(char *data);

#endif 
