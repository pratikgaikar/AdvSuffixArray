#include<math.h>
#include "main.h"

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

	if(extra == 0){
		keys = new int[2*t - 1];
		for(int it = 1; it <= 2*t - 1; it++){
			keys[it-1] = i + it*(range +1)/(2*t) -1;
		}
		*key_size = 2*t -1;
	}
	else if(extra < 0){
		keys = new int[range];
		for(int it = 1; it <=range; it++){
                        keys[it-1] = i + it*(range +1)/(2*t) -1;
                }	

	}
	else{
		if(range < (2*t -1)){
			keys = new int[range];
			for(int it = 1; it <=range; it++){
                 	       keys[it-1] = i + it -1;

                	}
			*key_size = range;
		}
		else{
			keys = new int[2*t - 1];
			extra_orj = extra;
			for(int it = 1; it <= 2*t - 1; it++){
					
				if(extra > 0 && extra > max_extra_each){	
					keys[it-1] = i + it*(range + 1 - extra_orj)/(2*t) -1 + it*max_extra_each;
					extra -= max_extra_each;
			
				}
				else if(extra > 0 && extra <= max_extra_each){
                        		keys[it-1] = i + it*(range + 1- extra_orj)/(2*t) -1 + extra_orj;
					extra = 0;

				}
				else{
					keys[it-1] = i + it*(range +1 - extra_orj)/(2*t) -1 + extra_orj;

				}
                	}
                	*key_size = 2*t -1;		
		}
	
	}

	return keys;
}


void btreeHelper(int arr[],int arr_new[], int i, int j, int i_new, int t){
        if(i > j)
                return;
	int key_size = 0;
	int* pkey_size = &key_size;
	
	int* keys = getKeys(i,j,t, pkey_size);
	int s = i;
	int it = 0;

	for(it = 0; it < key_size; it++){
		arr_new[i_new + it] = arr[keys[it]];
		btreeHelper(arr,arr_new, s, keys[it] - 1, i_new*(2*t) + (it+1)*(2*t-1) ,t);
		s = keys[it] + 1;
	}


	if(key_size > 0 ){	

		btreeHelper(arr,arr_new, s, j , i_new*(2*t) + (it+1)*(2*t-1) ,t);
		
	}
}


int* createSuffixArrayBtree(int *suffix_array, int n, int t)
{
	int * suffix_array_btree;
        suffix_array_btree = new int[n];	
        btreeHelper(suffix_array, suffix_array_btree, 0, n-1, 0, t);	
        return suffix_array_btree;

}

void print_recursively(int* suffixArray, int n, int s, int t, int* count){
	int x = 0;
	
	while(x < 2*t-1 && s+x < n){
		pattern_vector_b.push_back(suffixArray[s+x]); 
		*count += 1;
                print_recursively(suffixArray, n, s*(2*t) + (x+1)*(2*t-1), t, count);
		x++;
        }
	if(s+x < n)
		print_recursively(suffixArray, n, s*(2*t) + (x+1)*(2*t-1), t, count);
	
}

void handel_equal_case(int* suffixArray, int n, int s, int j, int t, int* count){
      int curr = s*(2*t) + (j+1)*(2*t-1);
      if(curr < n)
                print_recursively(suffixArray, n, curr, t, count);

}



void searchBtree(char* pat, int n, int *suffixArray, int i, int t,int pat_len, int *count)
{
	int j = 0;
	int comp_val;
	int i_new = i;
	bool flag = true;
  	
        while(i < n){
		j = 0;
		flag = true;
		while(i+j < n && j < (2*t)-1 ){
			comp_val = strncmp(pat, txt + suffixArray[i+j],pat_len);
			
			if(comp_val < 0){

				i_new = i*(2*t) + (j+1)*(2*t-1);
				break;
			}
			else if(comp_val > 0){

				j++;

				i_new = i*(2*t) + (j+1)*(2*t-1);
			}
			else{

				*count += 1;
				pattern_vector_b.push_back(suffixArray[i+j]); 
				if(flag == true){ // First OCCOURANCE OF EQUAL SO SEARCH LEFT
					searchBtree(pat, n, suffixArray, i*(2*t) + (j+1)*(2*t-1),t, pat_len,count);
					flag = false;	
				}
				else{
					handel_equal_case(suffixArray, n, i, j, t, count); // WIL PriNT EVERYTHING BETWEEN (i+j)-1 AND (i+j)
				}
				j++;
				i_new = i*(2*t) + (j+1)*(2*t-1);
				flag = false;
			}
		}
		i = i_new;
        }
}




