#include<math.h>
#include "main.h"

/**************************************************EYTZINGER********************************************************/

int* getKeys(int i, int j, int t, int* key_size){
        int count = 0, extra = 0;
	int* keys;
        int range = j-i+1;
        int prev = 0, curr = 0, level = 0;
	int max_extra = 0;
	int max_extra_each = 0;
        int extra_orj = 0;
	level = (int)((float)log(range+1)/(float)log(2*t));
	max_extra = (2*t - 1)*(pow(2*t, level));
	max_extra_each = max_extra/(2*t);
        extra = range - pow(2*t, level) + 1;
	cout << "\n i = " << i << " j = " << j << " extra = " << extra << " level = " << level <<  endl;
	 if(extra == 0){
		keys = new int[2*t - 1];
		for(int it = 1; it <= 2*t - 1; it++){
			keys[it-1] = i + it*(range +1)/(2*t) -1;
			cout << keys[it-1] << ",  "; 	
		}
//		cout << "\n returning here" << endl;	
		*key_size = 2*t -1;
	}
	else if(extra < 0){
		keys = new int[range];
		for(int it = 1; it <=range; it++){
                        keys[it-1] = i + it*(range +1)/(2*t) -1;
                        cout << keys[it-1] << ",  ";
                }	

	}
	else{
		if(range < (2*t -1)){
			keys = new int[range];
			for(int it = 1; it <=range; it++){
                 	       keys[it-1] = i + it*(range +1)/(2*t) -1;
                        	cout << keys[it-1] << ",  ";
                	}
			*key_size = range;
		}
		else{
			keys = new int[2*t - 1];
			extra_orj = extra;
			for(int it = 1; it <= 2*t - 1; it++){
				if(extra > 0 && extra > max_extra_each){
					keys[it-1] = i + it*(range +1)/(2*t) -1 + it*max_extra_each;
					extra -= max_extra_each;
					
				}
				if(extra > 0 && extra <= max_extra_each){
                        		keys[it-1] = i + it*(range +1)/(2*t) -1 + extra;
					extra -= max_extra_each;
				}
				else{
					keys[it-1] = i + it*(range +1)/(2*t) -1 + extra_orj;
				}
                        	cout << keys[it-1] << ",  ";
                	}
                	*key_size = 2*t -1;		
		}
	
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
	int key_size = 0;
	int* pkey_size = &key_size;
	
	int* keys = getKeys(i,j,t, pkey_size);
	cout << "\nI AM HERE KEYS ARE  i_new" << i_new << endl; 
	int s = i;
	int it = 0;
	for(it = 0; it < key_size; it++)
                cout << arr[keys[it]] << ",  "; 
	
	for(it = 0; it < key_size; it++){
		arr_new[i_new + it] = arr[keys[it]];
		cout << "Calling for " << " i = "<< s << " j = " << keys[it] - 1 << " newi = " << i_new*(2*t) + (it+1)*(2*t-1) << endl;
		btreeHelper(arr,arr_new, s, keys[it] - 1, i_new*(2*t) + (it+1)*(2*t-1) ,t);
		s = keys[it] + 1;
	}


	if(key_size > 0 ){	
		cout << "Calling for " << " i = "<< s << " j = " << j << " newi = " << i_new*(2*t) + (it+1)*(2*t-1) << endl;
		btreeHelper(arr,arr_new, s, j , i_new*(2*t) + (it+1)*(2*t-1) ,t);
		
	}
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

//        sort(suffix_array, suffix_array+n, cmp);
//	return suffix_array_btree;
	for(int x = 0; x < n; x++)
		cout << suffix_array[x] << " ";
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


