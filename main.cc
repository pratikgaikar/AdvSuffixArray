#include "main.h"

char *txt = NULL;

string inputString;
ofstream outFile; 

char *parseInputFile()
{
	string line;
	const char *text = NULL;
	string skip_char = ">";
	//ifstream myfile ("/home/apoorv30/AdvSuffixArray/test_data.fa");
	ifstream myfile ("/home/warlock/AdvSuffixArray/test_data.fa");

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
		text = inputString.c_str();
		myfile.close();	
	}
	else
	{
		cout << "Unable to open file1";
		exit(0); 
	}	
	return (char *)text;
}


void parsePatFile(int n, int *suffixArray, int choice)
{
	string str;
	system("sync; echo 1 > /proc/sys/vm/drop_caches");
	int f, l, pat_len;
	int start_s, stop_s;
  	std::ifstream pattern_file("/home/warlock/AdvSuffixArray/test_inputs/dtmin_250_400.fa", std::ios::binary | std::ios::ate); 
    	std::streamsize pattern_size = pattern_file.tellg(); 
    	pattern_file.seekg(0, std::ios::beg); 
    	std::vector<std::string> pattern_vector; 
    	std::vector<std::string> pattern_vector1; 
    	std::vector<std::string> pattern_vector2; 
    	while (getline(pattern_file, str)) 
    	{ 
        	pattern_vector.push_back(str); 
        	str[str.size() - 1]--; 
        	pattern_vector1.push_back(str); 
        	str[str.size() - 1]++; 
        	str[str.size() - 1]++; 
        	pattern_vector2.push_back(str);
	}
 
	
	for (int i = 0; i < pattern_vector.size(); i++) 
	{   	
		pat_len =  strlen((char*)pattern_vector1[i].c_str());
		if(choice == 1)
		{
			start_s = clock();
			f = search((char*)pattern_vector1[i].c_str(),suffixArray,n, pat_len);
			l = search((char*)pattern_vector2[i].c_str(),suffixArray,n, pat_len);
			stop_s = clock();
			//cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
				
			outFile <<" "<<l-f<<" "<< (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << '\n';
        		//cout << "Number of occurences :" << l - f << "\n"; 
			
    		} 
		if(choice == 2)
		{
			start_s = clock();
			f = search_with_LCP((char*)pattern_vector1[i].c_str(),suffixArray,n, pat_len);
			l = search_with_LCP((char*)pattern_vector2[i].c_str(),suffixArray,n, pat_len);
			stop_s = clock();
			//cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
			outFile <<" "<<l-f<<" "<< (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << '\n';
			//cout << "Number of occurences :" << l - f << "\n"; 
		}
	}    
}

int main()
{
	int *suffixArray;
	int* suffixArrayEytzinger;
	txt = parseInputFile();
	int n = strlen(txt);
	int choice;
	outFile.open ("/home/warlock/AdvSuffixArray/test_output.fa");
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
				//suffixArrayEytzinger = createSuffixArrayEytzinger(suffixArray, n);
				//parsePatFile(n, suffixArrayEytzinger, choice);
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
