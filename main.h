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
int* createSuffixArrayEytzinger(int* suffixArrayEytzinger, int n);
void searchEytzinger(char* pat, int n, int *suffixArray, int i, int pat_len,int* count);
void write_output(char *data);
void searchBtree(char* pat, int n, int *suffixArray, int i, int t, int pat_len, int* count);
int* createSuffixArrayBtree(int *suffix_array, int n, int t);
#
#endif 
