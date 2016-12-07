#ifndef _main_H 
#define _main_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

extern ofstream outFile;

extern char *txt;
//void printArr(int arr[], int n, const char *txt);
bool cmp(int a, int b);
int *createSuffixArray(int n);
//void searchAllPatternsWithLCP(char* pat, int n, int *suffixArray);
//void searchAllPatterns(char* pat, int n, int *suffixArray);
int search_with_LCP(char *pattern, int *suffixArray, int textLength, int patternLength);
int search(char *pattern, int *suffixArray, int textLength, int patternLength);
//int search(char *pattern, int *suffixArray, int textLength, int patternLength);
/*int* createSuffixArrayEytzinger(int* suffixArrayEytzinger, int n);
void searchEytzinger(const char* pat, int n, int *suffixArray, int i, int* count);*/
void write_output(char *data);

#endif 
