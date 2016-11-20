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
	ifstream myfile ("/home/megatron/AdvSuffixArray/test_data.fa");
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

			case 2: 
			cout<<"Enter the pattern"<<endl;
			cin>>pat;
			searchAllPatternsWithLCP(pat,n,suffixArray);
			break;

			case 3:
			cout<<"Enter the pattern "<<endl;
			cin>>pat;
			break;

			case 4: 
			cout<<"Enter the pattern"<<endl;
			cin>>pat;
			break;

			case 5: exit(0);
			break;
		}
	}
	return 0;
}
