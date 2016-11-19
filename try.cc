#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;
int *suffixArray;

const char* txt = ""; 
/* A suffix array based search function to search a given pattern
   'pat' in given text 'txt' using suffix array suffArr[] */

/* This function will return the first occurance of pattern */

int first(char *pat, int low, int high, int n)
{
	int m = strlen(pat); // get length of pattern, needed for strncmp()

	if(low <= high)
	{
		int mid = low + (high-low)/2;
		int res = strncmp(pat, txt+suffixArray[mid], m);

		if( ( mid == 0 || strncmp(pat, txt+suffixArray[mid-1], m)>0) && res == 0)
		{
			cout << "First Occurance Index ----> " << mid << " Index in text ---> "<< suffixArray[mid] <<'\n';
			return mid;
		}
		else if(res > 0)
		{
			return first(pat, (mid + 1), high, n);
		}
		else
		{		
			return first(pat, low, (mid -1), n);
		}
	}
	return -1;
}


int last(char *pat, int low, int high, int n)
{
        int m = strlen(pat); // get length of pattern, needed for strncmp()

        if(low <= high)
        {
                int mid = low + (high-low)/2;
                int res = strncmp(pat, txt+suffixArray[mid], m);

                if( ( mid == n-1 || strncmp(pat, txt+suffixArray[mid+1], m)<0) && res == 0)
                {
                        cout << "Last Occurance Index ----> " << mid << " Index in text ---> "<< suffixArray[mid] <<'\n';
                        return mid;
                }
                else if(res < 0)
                {
                        return last(pat, low, (mid -1), n);
                }
                else
                {
			return last(pat, (mid + 1), high, n);
                }
        }
        return -1;
}


void search(char *pat, int *suffArr, int n)
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


bool cmp(int a, int b)
{
	return strcmp(txt+a, txt +b) < 0? 1 : 0;
}


void  createSuffixArray(int n)
{

	for (int i = 0; i < n; i++)
	{
		suffixArray[i] = i;
	}
	sort(suffixArray, suffixArray+n, cmp);

}


void printArr(int arr[], int n,const char *txt)
{
	for(int i = 0; i < n; i++)
		cout << i << "--> " <<txt+arr[i] << "---->" << arr[i] << '\n';
	cout << endl;
}


void searchAllPatterns(char* pat, int n)
{
	int count = -1;
	int l = last(pat, 0, n-1, n);
	int f = first(pat, 0, n-1, n);
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


int main()
{

	/* code to read the content of input file */

	string line;
	string inputString;
	string a = ">";
	ifstream myfile ("/home/apoorv30/test_data_small.fa");
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
	else cout << "Unable to open file"; 

	txt = inputString.c_str();

	int n = strlen(txt);
	suffixArray = new int[n];
	createSuffixArray(n);
	printArr(suffixArray, n, txt);

	/* Search the string in suffix array */
	char pat[] = "APOORV";   // pattern to be searched in text
	cout << "Pattern -->" << pat << '\n';
	//search(pat, suffixArray, n);

	searchAllPatterns(pat,n);
	//cout << "Pattern Appeared--->" << num << '\n';	
	return 0;
}

