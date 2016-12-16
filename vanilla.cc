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
	
        int lp, rp, min, mid;
        int res;
       
        while (l <= r)
        {
                // See if 'pat' is prefix of middle suffix in suffix array
                mid = l + (r - l) / 2;

                //Find LCP of left and pattern, Find LCP of right and pattern, find min. start comparison of mid and pattern from min+1.
          
                res = str_cmp(pattern, txt + suffixArray[mid], patternLength);
                // If match found at the middle, print it and return
                if (res == patternLength)
                {
                        //cout << "Pattern found at index " << suffixArray[mid] << "\n";
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
                        //cout << "Pattern found at index " << suffixArray[mid] << "\n";
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
