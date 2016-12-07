#include "main.h"

int LCP(char *str1, char *str2)
{
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i]) {
			return i;
		}
		i++;
	}
	return i;
}


int str_cmp(char *str1, char *str2, unsigned long n)
{
	int i = 0;
	while (i<n)
	{
		if (str1[i] != str2[i]) 
			return i;
		i++;
	}
	return i;
}


int search(char *pattern, int *suffixArray, int textLength, int patternLength)
{
        int l = 0, r = textLength - 1, len = 0;  // Initilize left and right indexes
	//cout<<"Searching pattern "<<pattern<<"\n";
        int lp, rp, min, mid;
        int res;
        //txt = text;
        while (l <= r)
        {
                // See if 'pat' is prefix of middle suffix in suffix array
                mid = l + (r - l) / 2;

                //Find LCP of left and pattern, Find LCP of right and pattern, find min. start comparison of mid and pattern from min+1.
          
                res = str_cmp(pattern, txt + suffixArray[mid], patternLength);
                // If match found at the middle, print it and return
                if (res == patternLength)
                {
                        cout << "Pattern found at index " << suffixArray[mid] << "\n";
                        return mid;
                }
                // Move to left half if pattern is alphabtically less than
                // the mid suffix
                else if (pattern[res]<txt[suffixArray[mid] + res])
                {
                     
                        r = mid - 1;
                }
                // Otherwise move to right half
                else
                {
                        l = mid + 1;
                }
        }
        // We reach here if return statement in loop is not executed
        return l;
}



int search_with_LCP(char *pattern, int *suffixArray, int textLength, int patternLength)
{
        int l = 0, r = textLength - 1, len = 0;  // Initilize left and right indexes
        int lp, rp, min, mid;
        int res;
        lp = LCP(txt + suffixArray[l], pattern);
        rp = LCP(txt + suffixArray[r], pattern);
        //txt = text;
        while (l <= r)
        {
                // See if 'pat' is prefix of middle suffix in suffix array
                mid = l + (r - l) / 2;

                //Find LCP of left and pattern, Find LCP of right and pattern, find min. start comparison of mid and pattern from min+1.
                min = lp<rp ? lp : rp;
                len = patternLength - min;
                res = str_cmp(pattern + min, txt + suffixArray[mid] + min, len);
                // If match found at the middle, print it and return
                if (res == len)
                {
                        cout << "Pattern found at index " << suffixArray[mid] << "\n";
                        return mid;
                }
                // Move to left half if pattern is alphabtically less than
                // the mid suffix
                else if (pattern[min + res]<txt[suffixArray[mid] + min + res])
                {
                        rp = min + res;
                        r = mid - 1;
                }
                // Otherwise move to right half
                else
                {
                        lp = min + res;
                        l = mid + 1;
                }
        }
        // We reach here if return statement in loop is not executed
        return l;
}

/*void searchAllPatterns(char* pat, int n, int *suffixArray)
{
	int count = -1;
	int l,f;
	int pat_len = strlen(pat);
	//here we have to reduce the value of pat by 1
	cha-r* pat_left = NULL;
	//new char[pat_len];
	char* pat_right = NULL;
	//new char[pat_len];

	pat_left = (char*)malloc(sizeof(char)*pat_len);
	pat_right = (char*)malloc(sizeof(char)*pat_len);
	int start_s = 0;
        int stop_s = 0;

	strcpy(pat_left, pat);
	strcpy(pat_right, pat);
	
	pat_left[pat_len-1]--;
	pat_right[pat_len-1]++;
	strcat(pat_left,"\0");
	strcat(pat_right,"\0");
	
	start_s = clock();
	f = search(pat_left,suffixArray,n, pat_len);
	l = search(pat_right,suffixArray,n, pat_len);
	stop_s = clock();
	
	count = l-f;
	cout <<"Pattern Appeared ---> " << count << '\n';
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	outFile << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << '\n';

if(pat_left)
	free(pat_left);

if(pat_right)
	free(pat_right);

	
	//delete[] pat_left;
	//delete[] pat_right;

}


void searchAllPatternsWithLCP(char* pat, int n, int *suffixArray)
{
        int count = -1;
	int f,l;
	int pat_len = strlen(pat);
	
	//here we have to reduce the value of pat by 1

	//char* pat_left = new char[pat_len];
        //char* pat_right = new char[pat_len];

	char* pat_left = (char*)malloc(sizeof(char)*pat_len);
	char* pat_right = (char*)malloc(sizeof(char)*pat_len);
	int start_s = 0;
        int stop_s = 0;

	strcpy(pat_left, pat);
	strcpy(pat_right, pat);
	
	pat_left[pat_len-1]--;
	pat_right[pat_len-1]++;

	start_s = clock();
        f = search_with_LCP(pat_left,suffixArray,n, pat_len); 
	l = search_with_LCP(pat_right,suffixArray,n, pat_len);
	stop_s = clock();

	count = l-f;
	cout <<"Pattern Appeared ---> " << count << '\n'; 
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	outFile << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << '\n';

	
	//cout << "Occurances--->" <<count<<"\n";
                /*for(int i=0;i<count;i++)
		{
                        //cout << "Index ---> "<< suffixArray[f+i] << '\n';
			//outFile << suffixArray[f+i] << " ";
		}*/
//	delete[] pat_left;
  //      delete[] pat_right;
//}
	
/* This Function is used to obtain the LCP value */
void search(const char *pat, int *suffArr,int n)
{
	int m = strlen(pat);
	int l = 0, r = n-1;
	while (l <= r)
	{
		// Compare pat with the middle suffix in suffix array
		int mid = l + (r - l)/2;
		int res = strncmp(pat, txt+suffArr[mid], m);
		cout << "MID IS --> " << mid <<'\n';
		// If match found at the middle, print it and return
		if (res == 0)
		{
			cout << "Pattern found at index " << suffArr[mid] << '\n';
			//We have check above and below

			return;
		}
		else if (res < 0) 
		{
			r = mid - 1;
		}
		else 
		{	
			l = mid + 1;
		}
	}

	// We reach here if return statement in loop is not executed
	cout << "Pattern not found";
}

bool cmp(int a, int b)
{
	return strcmp(txt+a, txt+b) < 0? 1 : 0;
}

int *createSuffixArray(int n)
{
	int *suffix_array;
	suffix_array= new int[n];
	for (int i = 0; i < n; i++)
		suffix_array[i] = i;

	sort(suffix_array, suffix_array+n, cmp);
	return suffix_array;	
}
