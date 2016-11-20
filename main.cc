#include "main.h"
<<<<<<< HEAD
=======
#include<math.h>
>>>>>>> be8ec199778f2a69f0a75c14040ab052977a63e0

/* A suffix array based search function to search a given pattern
   'pat' in given text 'txt' using suffix array suffArr[] */

const char *txt ="";
string inputString;
void parseInputFile()
{
<<<<<<< HEAD
	/* code to read the content of input file */
	string line;
	string skip_char = ">";
	ifstream myfile ("/home/megatron/AdvSuffixArray/test_data.fa");
=======
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
>>>>>>> be8ec199778f2a69f0a75c14040ab052977a63e0
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			if (strncmp (line.c_str(),skip_char.c_str(),1) != 0)
			{
				inputString.append(line);
				inputString.append("$"); 
			}
		}
		cout <<"Length of string is ---- >" << inputString.length() <<'\n';
		txt = inputString.c_str();
		
		myfile.close();	
	}
	else
	{
		 cout << "Unable to open file";
		 exit(0); 
	}	
}

int main()
{
	int *suffixArray;
	parseInputFile();
	int n = strlen(txt);
<<<<<<< HEAD
	int choice;
	char pat[100];
	suffixArray = createSuffixArray(n);
	while(1)
	{
		cout<<"1.Vanilla SERACH"<<endl;
		cout<<"2.Vanilla LCP SEARACH"<<endl;
		cout<<"3.EYTZINGER SERACH"<<endl;
		cout<<"4.EYTZINGER LCP SEARACH"<<endl;
		cout<<"5.EXIT"<<endl;
		cout<<"ENTER YOUR CHOICE :";
		cin>>choice;
		switch(choice)
		{
			case 1:
			cout<<"Enter the pattern "<<endl;
			cin>>pat;
			searchAllPatterns(pat,n,suffixArray);
			break;
=======
	
//	suffixArray = createSuffixArray(n);

	suffixArray = createSuffixArrayEytzinger(n);
	//printArr(suffixArray,n);

	char pat[] = "PRATIK";
	cout << "Pattern -->" << pat << '\n';
>>>>>>> be8ec199778f2a69f0a75c14040ab052977a63e0

			case 2: 
			cout<<"Enter the pattern"<<endl;
			cin>>pat;
			searchAllPatternsWithLCP(pat,n,suffixArray);
			break;

			case 3:
			cout<<"Enter the pattern "<<endl;
			cin>>pat;
			break;

<<<<<<< HEAD
			case 4: 
			cout<<"Enter the pattern"<<endl;
			cin>>pat;
			break;
=======
	/* Search All the Occurance with LCP */
	searchEytzinger(pat,n,suffixArray,0);	
//searchAllPatternsWithLCP(pat,n,suffixArray);
>>>>>>> be8ec199778f2a69f0a75c14040ab052977a63e0

			case 5: exit(0);
			break;
		}
	}
	return 0;
}
