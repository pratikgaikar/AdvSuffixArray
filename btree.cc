#include<math.h>
#include "main.h"

/**************************************************EYTZINGER********************************************************/

int* getKeys(int i, int j, int t){
        int count = 0, extra = 0;
	int* keys;;
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
	level = (int)((float)log(range+1)/(float)log(2*t));
        extra = range - pow(2*t, level) + 1;
	cout << "\n i = " << i << " j = " << j << " extra = " << extra << " level = " << level <<  endl;
	 if(extra == 0){
		keys = new int[2*t - 1];
		for(int it = 1; it <= 2*t - 1; it++){
			keys[it-1] = i + it*(range +1)/(2*t) -1;
			cout << akeys[it-1] << ",  "; 	
		}
		
                return keys;
	}
/*
        if((curr - prev)/2 < extra)
                return(i + prev/2 + pow(2, level-1));
        return  (i + prev/2 + extra);
*/
	return keys;
}


void btreeHelper(int arr[],int arr_new[], int i, int j, int i_new, int t){
        if(i >= j)
                return;
	int* keys= getKeys(i,j,t);
	cout << "\nI AM HERE" << endl; 
       	int len = (sizeof(keys)/sizeof(*keys));
	cout << "I MA HERE" << endl;
	int s = i;
	int it = 0;
	cout << " len = " << len <<  endl;
	for(it = 0; it < len; it++){
                        cout << keys[it-1] << ",  "; 
	for(it = 0; it < len; it++){
		arr_new[i_new + it] = arr[keys[it]];
		cout << "\nCalling for " << " i = "<< s << " j = " << keys[it] - 1 << " newi = " << i_new*(2*t) + (it+1)*(2*t+1) << endl;
		btreeHelper(arr,arr_new, s, keys[it] - 1, i_new*(2*t) + (it+1)*(2*t+1) ,t);
		s = keys[it] + 1;
	}
	btreeHelper(arr,arr_new, i, keys[it] - 1, i_new*(2*t) + (it+1)*(2*t+1) ,t);
//        btreeHelper(arr,arr_new, i, mid-1, l);
//        btreeHelper(arr,arr_new, mid+1,j, r);

}


int* createSuffixArrayBtree(int *suffix_array, int n)
{
	int * suffix_array_btree;
	int t = 2;
        suffix_array_btree = new int[n];
        for (int i = 0; i < n; i++)
                suffix_array[i] = i;

        sort(suffix_array, suffix_array+n, cmp);
//	return suffix_array_btree;
        btreeHelper(suffix_array, suffix_array_btree, 0, n-1, 0, t);
	for (int i = 0; i < n; i++)
		cout << suffix_array_btree[i] << "  ";
        return suffix_array_btree;

}



void searchBtree(char* pat, int n, int *suffixArray, int i)
{
        int count = -1;

        int cmp_val = 0;

        while(i < n){
                cmp_val = strncmp(pat, txt + suffixArray[i],strlen(pat));
                if(cmp_val < 0){
                        i = 2*i + 1;
                }
                else if(cmp_val > 0){
                        i = 2*i + 2;
                }
                else{
                        cout << "FOUND AT " << i <<  "  " << suffixArray[i] << endl;
                        searchBtree(pat, n, suffixArray, 2*i + 1);
                        searchBtree(pat, n, suffixArray, 2*i + 2);
                        return;
                }


        }

}


/*******************************************************************************************************************/


