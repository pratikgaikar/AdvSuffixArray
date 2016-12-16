#ifndef _main_H 
#define _main_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

/*extern variable */
extern ofstream outFile;
extern char *txt;

extern vector<int> pattern_vector_e;     
extern vector<int> pattern_vector_b; 

//void printArr(int arr[], int n, const char *txt);
bool cmp(int a, int b);
int *createSuffixArray(int n);
//void searchAllPatternsWithLCP(char* pat, int n, int *suffixArray);
//void searchAllPatterns(char* pat, int n, int *suffixArray);
/*vanilla search functions prototype */
int search_with_LCP(char *pattern, int *suffixArray, int textLength, int patternLength);
int search(char *pattern, int *suffixArray, int textLength, int patternLength);
//int search(char *pattern, int *suffixArray, int textLength, int patternLength);

/*Eytzinger functions prototype*/
int* createSuffixArrayEytzinger(int* suffixArrayEytzinger, int n);
void searchEytzinger(char* pat, int n, int *suffixArray, int i, int pat_len,int* count);

/*Btree functions prototype*/
void searchBtree(char* pat, int n, int *suffixArray, int i, int t, int pat_len, int* count);
int* createSuffixArrayBtree(int *suffix_array, int n, int t);

#endif 
