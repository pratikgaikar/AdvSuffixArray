#include<math.h>
#include "main.h"
/**************************************************EYTZINGER********************************************************/


int getMid(int i, int j){
        int count = 0, extra = 0;
        int range = j-i+1;
        int prev = 0, curr = 0, level = 0;
        while(curr < range){
                curr += pow(2, level);
                if(curr > range){
                        break;
                }
                level++;
                prev = curr;
        }
        extra = range - prev;
        if(extra == 0)
                return (j+i)/2;
        if((curr - prev)/2 < extra)
                return(i + prev/2 + pow(2, level-1));
        return  (i + prev/2 + extra);

}

void eytzingerHelper(int arr[],int arr_new[], int i, int j, int i_new){
        int mid = 0; int l = 2*i_new + 1; int r = 2*i_new + 2;
        if(i > j)
                return;
        mid = getMid(i,j);

        arr_new[i_new] = arr[mid];
        eytzingerHelper(arr,arr_new, i, mid-1, l);
        eytzingerHelper(arr,arr_new, mid+1,j, r);

}

int* createSuffixArrayEytzinger(int *suffix_array, int n)
{
	int * suffix_array_eytzinger;
        suffix_array_eytzinger = new int[n];
        eytzingerHelper(suffix_array, suffix_array_eytzinger, 0, n-1, 0);
        return suffix_array_eytzinger;

}

void searchEytzinger(char* pat, int n, int *suffixArray, int i, int pat_len,int* count)
{
        int cmp_val = 0;
	
        while(i < n){
                cmp_val = strncmp(pat, txt + suffixArray[i],pat_len);
                if(cmp_val < 0){
                        i = 2*i + 1;
                }
                else if(cmp_val > 0){
                        i = 2*i + 2;
                }
                else{                        
                        *count = *count + 1;
			pattern_vector_e.push_back(suffixArray[i]); 
			searchEytzinger(pat, n, suffixArray, 2*i + 1, pat_len,count);
                        searchEytzinger(pat, n, suffixArray, 2*i + 2, pat_len,count);
                        return;
                }
        }
}

/*******************************************************************************************************************/


