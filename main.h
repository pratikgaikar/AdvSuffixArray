#ifndef _main_H 
#define _main_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

extern const char* txt; 
void printArr(int arr[], int n, const char *txt);
bool cmp(int a, int b);
int *createSuffixArray(int n);
void searchAllPatternsWithLCP(char* pat, int n, int *suffixArray);
void searchAllPatterns(char* pat, int n, int *suffixArray);
#endif 
