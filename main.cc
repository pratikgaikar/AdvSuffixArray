#include "main.h"
#include<math.h>

/* A suffix array based search function to search a given pattern
   'pat' in given text 'txt' using suffix array suffArr[] */
const char* txt = ""; 

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



/* This function will return the first occurance of pattern */

/*int first(char *pat, int n)
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
}*/


/* This function will retrun the last occurance of Pattern */

/*int last(char *pat, int n)
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
}*/

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

/*void search(char *pat, int *suffArr, int n)
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
}*/


bool cmp(int a, int b)
{
	return strcmp(txt+a, txt+b) < 0? 1 : 0;
}


int * createSuffixArray(int n)
{
	int *suffix_array;
	suffix_array= new int[n];
	for (int i = 0; i < n; i++)
		suffix_array[i] = i;

	sort(suffix_array, suffix_array+n, cmp);
	return suffix_array;	
}





void printArr(int arr[], int n)
{
	for(int i = 0; i < n; i++)
		cout << i << "--> " <<txt+arr[i] << "---->" << arr[i] << '\n';
	cout << endl;
}


/*void searchAllPatterns(char* pat, int n)
{
	int count = -1;
	int l = last(pat,n);
	int f = first(pat,n);
	if(l!=-1 && f!=-1)
		count = l-f+1;
	if(count>0)
	{
		cout <<"Pattern Appeared ---> " << count << '\n';
		for(int i=0;i<count;i++)
			cout << "Index ---> "<< suffixArray[f+i] << '\n';
	}
	else
		cout <<"Pattern Not Found" << '\n';	
}*/



void searchAllPatternsWithLCP(char* pat, int n, int *suffixArray)
{
        int count = -1;
	
        int l = lastLCP(pat,n,suffixArray);
        int f = firstLCP(pat,n,suffixArray);
        if(l!=-1 && f!=-1)
                count = l-f+1;
        if(count>0)
        {
                cout <<"Pattern Appeared ---> " << count << '\n';
                for(int i=0;i<count;i++)
                        cout << "Index ---> "<< suffixArray[f+i] << '\n';
        }
        else
                cout <<"Pattern Not Found" << '\n';
}

/**************************************************EYTZINGER********************************************************/

int getMid(int i, int j){
	int count = 0, extra = 0;
	int range = j-i+1;
	int prev = 0, curr = 0, level = 0;
//	cout << "mid for " <<i << " " << j << endl;
	while(curr < range){
		curr += pow(2, level);  
		if(curr > range){
			break;
		}
		level++;
		prev = curr;
	}
	extra = range - prev;
//	cout << "extra " << extra << " level " << level << " prev " << prev << " curr " << curr << endl;  
	
	if(extra == 0)
		return (j+i)/2;
	if((curr - prev)/2 < extra)
		return(i + prev/2 + pow(2, level-1));
	return	(i + prev/2 + extra);
		
}



void eytzingerHelper(int arr[],int arr_new[], int i, int j, int i_new){
	int mid = 0; int l = 2*i_new + 1; int r = 2*i_new + 2;
	//cout << "\n NEW for "<< i_new<< endl;
	if(i > j)
		return;
	mid = getMid(i,j);	
	
//	cout << "i = "<< i << ", mid = " << mid << ", j = " << j << ", i_new = "<< i_new << endl;
	arr_new[i_new] = arr[mid];
	eytzingerHelper(arr,arr_new, i, mid-1, l);
	eytzingerHelper(arr,arr_new, mid+1,j, r);
	
}


int * createSuffixArrayEytzinger(int n)
{
        int *suffix_array; int * suffix_array_eytzinger;
	suffix_array_eytzinger = new int[n];
        suffix_array= new int[n];
        for (int i = 0; i < n; i++)
                suffix_array[i] = i;

        sort(suffix_array, suffix_array+n, cmp);
	eytzingerHelper(suffix_array, suffix_array_eytzinger, 0, n-1, 0);
        delete(suffix_array);
	return suffix_array_eytzinger;
	
}



void searchEytzinger(char* pat, int n, int *suffixArray, int i)
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
			//cout << (txt + suffixArray[i]).c_str().substr(0,6) << endl;
			cout << "FOUND AT " << i <<  "  " << suffixArray[i] << endl;
			searchEytzinger(pat, n, suffixArray, 2*i + 1);
			searchEytzinger(pat, n, suffixArray, 2*i + 2);
			return;
		}
	

	}
//	cout << "Pattern Not Found" << endl;

}


/*******************************************************************************************************************/








int main()
{

	/* code to read the content of input file */
	string line;
	string inputString;
	string a = ">";
	ifstream myfile ("/home/asmita/AdvSuffixArray/test_data.fa");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			if (strncmp (line.c_str(),a.c_str(),1) != 0)
			{
				inputString.append(line);
				inputString.append("$"); 
			}
		}
		cout <<"Length of string is ---- >" << inputString.length() <<'\n';
		myfile.close();
	}
	else
	{
		 cout << "Unable to open file";
		 exit(0); 
	}

	int *suffixArray;
	
	txt = inputString.c_str();

	int n = strlen(txt);
	
//	suffixArray = createSuffixArray(n);

	suffixArray = createSuffixArrayEytzinger(n);
	//printArr(suffixArray,n);

	char pat[] = "PRATIK";
	cout << "Pattern -->" << pat << '\n';

	/* Search one Occurance */
	//search(pat, suffixArray, n);

	/* Search All the Occurance*/
	//searchAllPatterns(pat,n);

	/* Search All the Occurance with LCP */
	searchEytzinger(pat,n,suffixArray,0);	
//searchAllPatternsWithLCP(pat,n,suffixArray);

	return 0;
}

