#include "main.h"

/* A suffix array based search function to search a given pattern
   'pat' in given text 'txt' using suffix array suffArr[] */

const char *txt ="";
string inputString;
void parseInputFile()
{
	/* code to read the content of input file */
	string line;
	string skip_char = ">";
	ifstream myfile ("/home/apoorv30/AdvSuffixArray/test_data.fa");
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
	int *suffixArray, *suffixArrayEytzinger;
	parseInputFile();
	int n = strlen(txt);
	int choice;
	char pat[100];
	int start_s = 0;
	int stop_s = 0;
	cout << "Creating Suffix Array..." << '\n';
	suffixArray = createSuffixArray(n);
	cout << "Suffix Array Created !!" << '\n';
	
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
			start_s = clock();
			searchAllPatterns(pat,n,suffixArray);
			stop_s = clock();
			cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;			
			break;

			case 2: 
			cout<<"Enter the pattern"<<endl;
			cin>>pat;
			start_s = clock();			
			searchAllPatternsWithLCP(pat,n,suffixArray);
			stop_s = clock();
			cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
			break;

			case 3:
			cout<<"Enter the pattern "<<endl;
			cin>>pat;
			suffixArrayEytzinger = createSuffixArrayEytzinger(suffixArray, n);
			start_s = clock();
			searchEytzinger(pat, n, suffixArrayEytzinger, 0);		
			stop_s = clock();
			cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
			break;

			case 4: 
			cout<<"Enter the pattern"<<endl;
			cin>>pat;
			break;

			case 5: exit(0);
			break;

			default: 
			cout << "Please select among the options" << '\n';
			break;
		}
	}
	return 0;
}
