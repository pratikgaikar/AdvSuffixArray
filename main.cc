#include "main.h"

char *txt = NULL;
string inputString;
ofstream outFile;
vector<int> pattern_vector_e;  
vector<int> pattern_vector_b; 

char *parseInputFile()
{
	string line;
	const char *text = NULL;
	string skip_char = ">";
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
		cout <<"Length of input text string ->" << inputString.length() <<'\n';
		text = inputString.c_str();
		myfile.close();	
	}
	else
	{
		cout << "Unable to open test_data.fa";
		exit(0); 
	}	
	return (char *)text;
}

void parsePatFile(int n, int *suffixArray, int choice, int t)
{
	string str;
	int f, l, pat_len;
	int start_s, stop_s;
	int count;
  	std::ifstream pattern_file("/home/warlock/AdvSuffixArray/present.fa", std::ios::binary | std::ios::ate); 
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
			outFile <<"\t"<<l-f<<"\t"<< (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
			for(int j=f;j<l;j++)
			{
                        	outFile<<"\t"<<suffixArray[j];				
			}
			outFile<<'\n';  		 
			
    		} 
		if(choice == 2)
		{
			start_s = clock();
			f = search_with_LCP((char*)pattern_vector1[i].c_str(),suffixArray,n, pat_len);
			l = search_with_LCP((char*)pattern_vector2[i].c_str(),suffixArray,n, pat_len);
			stop_s = clock();
			outFile <<"\t"<<l-f<<"\t"<< (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;	
			for(int j=f;j<l;j++)
			{
                        	outFile<<"\t"<<suffixArray[j];				
			}
			outFile<<'\n';		
		}
		if(choice == 3)
		{
			count = 0;
			pattern_vector_e.clear();
			start_s = clock();
                        searchEytzinger((char*)pattern_vector[i].c_str(), n, suffixArray, 0, pat_len,&count);
			stop_s = clock();                        
                        outFile <<"\t"<<count<<"\t"<< (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
			for(int j=0;j<pattern_vector_e.size();j++)
			{
				outFile<<"\t"<<pattern_vector_e[j];	
			}
			outFile<<'\n';
		}
		if(choice == 4)
                {			
                        count = 0;
			pattern_vector_b.clear();
                        start_s = clock();
                        searchBtree((char* )pattern_vector[i].c_str(), n, suffixArray, 0, t, pat_len, &count);
                        stop_s = clock();
                        outFile <<"\t"<<count<<"\t"<< (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
			for(int j=0;j<pattern_vector_b.size();j++)
			{
				outFile<<"\t"<<pattern_vector_b[j];	
			}
			outFile<<'\n';
                }

	}    
}

int main()
{
	int *suffixArray;
	int* suffixArrayEytzinger, *suffixArrayBtree;
	txt = parseInputFile();
	int n = strlen(txt);
	int choice;
	int t = 3;
	outFile.open ("/home/warlock/AdvSuffixArray/test_output.fa");
	suffixArray = createSuffixArray(n);

	while(1)
	{
		cout<<"1.Vanilla SERACH"<<endl;
		cout<<"2.Vanilla LCP SEARACH"<<endl;
		cout<<"3.EYTZINGER SERACH"<<endl;
		cout<<"4.BTREE SEARACH"<<endl;
		cout<<"5.EXIT"<<endl;
		cout<<"ENTER YOUR CHOICE :";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"VANILLA SERACH "<<endl;
				system("sync; echo 3 > /proc/sys/vm/drop_caches");				
				parsePatFile(n, suffixArray, choice, t);
				cout <<"Check outfile test_output.fa\n" << endl;
				break;
			
			case 2:
				cout<<" VANILLA SEARCH WITH LCP "<<endl;
				system("sync; echo 3 > /proc/sys/vm/drop_caches");
                                parsePatFile(n, suffixArray, choice, t);
				cout <<"Check outfile test_output.fa\n"<< endl;
                                break;
			
			case 3:
				cout <<"EYTZINGER SERACH" << endl;
				system("sync; echo 3 > /proc/sys/vm/drop_caches");
				suffixArrayEytzinger = createSuffixArrayEytzinger(suffixArray, n);
				parsePatFile(n, suffixArrayEytzinger, choice,t);
				cout <<"Check outfile test_output.fa\n" << endl;
				break;
			case 4:
				cout <<"BTREE SERACH"<< endl;
				system("sync; echo 3 > /proc/sys/vm/drop_caches");
				suffixArrayBtree = createSuffixArrayBtree(suffixArray, n, t);
                                parsePatFile(n, suffixArrayBtree, choice,t);
				cout <<"Check outfile test_output.fa\n" << endl;
				break;

			case 5: exit(0);
				break;

			default: 
				cout <<"Please select among the options provided."<< '\n';
				break;
		}
	}
	return 0;
}
