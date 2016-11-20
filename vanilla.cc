#include "main.h"

/* This Function is used to obtain the LCP value */
int getLCP(char *pat, int index, int oldLCP, int *res, int *suffixArray)
{
	int count = 0;
	int m = strlen(pat);

	for(int i = 0; i < m-oldLCP; i++)
	{
		if(pat[i+oldLCP] == txt[suffixArray[index]+i+oldLCP])
		{
			*res = 0;
			count++;
		}
		else
		{
			if(pat[i+oldLCP] < txt[suffixArray[index]+i+oldLCP])
				*res = -1;
			else
				*res = 1;
			break;
		}
	}
	return count;
}

int getMIN(int LCP1, int LCP2)
{
	return LCP1>LCP2?LCP2:LCP1;
}

int firstLCP(char *pat, int n, int *suffixArray)
{
        int m = strlen(pat); // get length of pattern, needed for strncmp()
	int low = 0;
	int high = n-1;
	int res = 0;
	int LCP1 = getLCP(pat, low, 0, &res, suffixArray);
	int LCP2 = getLCP(pat, high, 0, &res, suffixArray);
	int mid = 0;
	int midLCP = 0;


        while(low <= high)
        {
                mid = low + (high-low)/2;

		midLCP = getMIN(LCP1, LCP2);
		midLCP = midLCP+ getLCP(pat,mid, midLCP, &res, suffixArray);

		if( ( mid == 0 || strncmp(pat + getMIN(LCP1,midLCP), txt+suffixArray[mid-1], m)>0) && res == 0)
                {
                        cout << "First Occurance Index ----> " << mid << " Index in text ---> "<< suffixArray[mid] <<'\n';
                        return mid;
                }
                else if(res > 0)
		{
                        low = mid + 1;
			LCP1 = midLCP;
		}	
                else
		{
			high = mid -1;
                        LCP2 = midLCP;
        	}
	}
        return -1;
}

int lastLCP(char *pat, int n, int *suffixArray)
{
        int m = strlen(pat);
        int low = 0;
        int high = n-1;
        int res = 0;
        int LCP1 = getLCP(pat, low, 0, &res, suffixArray);
        int LCP2 = getLCP(pat, high, 0, &res, suffixArray);
        int mid = 0;
        int midLCP = 0;


        while(low <= high)
        {
                mid = low + (high-low)/2;

                midLCP = getMIN(LCP1, LCP2);
                midLCP = midLCP+ getLCP(pat,mid, midLCP, &res, suffixArray);

                if( ( mid == n-1 || strncmp(pat + getMIN(LCP2,midLCP), txt+suffixArray[mid+1] + getMIN(LCP2,midLCP) , m)<0) && res == 0)
                {
                        cout << "last Occurance Index ----> " << mid << " Index in text ---> "<< suffixArray[mid] <<'\n';
                        return mid;
                }
                else if(res < 0)
                {
                        high = mid - 1;
                        LCP2 = midLCP;
                }
                else
                {
                        low = mid +1;
                        LCP1 = midLCP;
                }
        }
        return -1;
}

/* This function will return the first occurance of pattern */
int first(char *pat,int *suffixArray,int n)
{
	int m = strlen(pat);
	int high = n-1;
	int low = 0;
	int mid = 0;
	int res = 0;

	while(low <= high)
	{
		mid = low + (high-low)/2;
		res = strncmp(pat, txt+suffixArray[mid], m);

		if( ( mid == 0 || strncmp(pat, txt+suffixArray[mid-1], m)>0) && res == 0)
		{
			cout << "First Occurance Index ----> " << mid << " Index in text ---> "<< suffixArray[mid] <<'\n';
			return mid;
		}
		else if(res > 0)
		{
			low = mid +1;
		}			
		else
			high =mid -1;
	}
	return -1;
}

/* This function will retrun the last occurance of Pattern */
int last(char *pat,int *suffixArray,int n)
{
        int m = strlen(pat);
	int high = n-1;
	int low = 0;
	int mid = 0;
	int res = 0;
        while(low <= high)
        {
                mid = low + (high-low)/2;
                res = strncmp(pat, txt+suffixArray[mid], m);

                if( ( mid == n-1 || strncmp(pat, txt+suffixArray[mid+1], m)<0) && res == 0)
                {
                        cout << "Last Occurance Index ----> " << mid << " Index in text ---> "<< suffixArray[mid] <<'\n';
                        return mid;
                }
                else if(res < 0)
                        high = mid -1;
                else
			low = mid + 1;
        }
        return -1;
}

void search(char *pat, int *suffArr,int n)
{
	int m = strlen(pat); // get length of pattern, needed for strncmp()
	int l = 0, r = n-1;  // Initilize left and right indexes
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


void searchAllPatterns(char* pat, int n, int *suffixArray)
{
	int count = -1;
	int l,f;
	
	f = first(pat,suffixArray, n); 
	if(f!=-1)
	{	
		l = last(pat, suffixArray, n);
		count = l-f+1;
		cout <<"Pattern Appeared ---> " << count << '\n';
		for(int i=0;i<count;i++)
			cout << "Index ---> "<< suffixArray[f+i] << '\n';
	}
	else
		cout <<"Pattern Not Found" << '\n';	
}

void searchAllPatternsWithLCP(char* pat, int n, int *suffixArray)
{
        int count = -1;
	int f,l;

        f = firstLCP(pat,n,suffixArray);
	if(f!=-1)
	{        
	    	l = lastLCP(pat,n,suffixArray);
		count = l-f+1;
                cout <<"Pattern Appeared ---> " << count << '\n';
                for(int i=0;i<count;i++)
                        cout << "Index ---> "<< suffixArray[f+i] << '\n';
	}        
	else
                cout <<"Pattern Not Found" << '\n';
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
