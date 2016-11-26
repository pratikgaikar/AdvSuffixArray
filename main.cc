#include "main.h"

const char *txt ="";
string inputString;
ofstream outFile; 

void parseInputFile()
{
	string line;
	string skip_char = ">";
	//ifstream myfile ("/home/apoorv30/AdvSuffixArray/test_data.fa");
	ifstream myfile ("/home/apoorv30/test/test_data.fa");

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


void parsePatFile(int n, int *suffixArray, int choice)
{

	const char *pat;
	string line;
	int count = 0;
	int start_s = 0;
        int stop_s = 0;
	//ifstream patFile ("/home/apoorv30/AdvSuffixArray/test_pattern.fa");
	ifstream patFile ("/home/apoorv30/test/ramin_250_400.fa");
	if (patFile.is_open())
	{
		while ( getline (patFile,line) )
		{
			pat = line.c_str();
			//cout << "PATTERN ---> " << pat << '\n';

			outFile << pat;
			outFile << " ";

			start_s = clock();
			if(choice == 1)
				searchAllPatterns(pat,n,suffixArray);
			if(choice == 2)
				searchAllPatternsWithLCP(pat,n,suffixArray);
			if(choice == 3)
			{
				count = 0;
                                searchEytzinger(pat, n, suffixArray, 0, &count);
				outFile << count << " ";
			}
			stop_s = clock();
			//cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
			
			outFile << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << '\n';

		}
		patFile.close();
		outFile.close();
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
	int* suffixArrayEytzinger;
	parseInputFile();
	int n = strlen(txt);
	int choice;
	outFile.open ("/home/apoorv30/AdvSuffixArray/test_output.fa");
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
				cout<<" VANILLA "<<endl;
				parsePatFile(n, suffixArray, choice);
				break;
			
			case 2:
				cout<<" VANILLA WITH LCP "<<endl;
                                parsePatFile(n, suffixArray, choice);
                                break;
			
			case 3:
				cout << " EYTZINGER " << endl;
				suffixArrayEytzinger = createSuffixArrayEytzinger(suffixArray, n);
				parsePatFile(n, suffixArrayEytzinger, choice);
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
