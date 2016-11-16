#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;


vector<int> build_suffix_array(string text)
{
	vector<int> suffix_array;
	map<string,int> hash_map;
    	for(int i =0 ;i< text.length();i++)
    	{	
       		hash_map.insert (pair<string,int>(text.substr(i),i));
    	}
       	map<string,int>:: iterator it = hash_map.begin();
    	for (it=hash_map.begin(); it!=hash_map.end(); ++it)
    	{
        	cout << it->first << " => " << it->second << '\n';
        	suffix_array.push_back(it->second);
    	}

	return suffix_array;
}

vector<int> find_pattern(vector<int> sa, string search_str,string str)
{
	vector<int> pattern_index;
	int len = strlen(search_str.c_str());
	int low = 0 , high = sa.size() - 1;
    	while(low <= high)
    	{
        	int mid = low + (high - low)/2;
        	string mid_str = str.substr(sa.at(mid));
        	string i_str;
        	if(strncmp(search_str.c_str(),mid_str.c_str(),len) == 0)
        	{ 
            		int i = mid-1;
            		cout<<"\nFound at "<<mid_str<<"Index -->"<<sa.at(mid);
			pattern_index.push_back(sa.at(mid));
            		while(i >= low)
            		{
                		i_str = str.substr(sa.at(i));
                		if(strncmp(search_str.c_str(),i_str.c_str(),len) == 0)
				{
					pattern_index.push_back(sa.at(i));
                    			cout<<"\nFound at "<<i_str<<"Index -->"<<sa.at(i);
				}                		
				else
                    			break;
                		i--;    
                
            		}
            		i = mid +1;
            		while(i <= high)
            		{
                		i_str = str.substr(sa.at(i));
                		if(strncmp(search_str.c_str(),i_str.c_str(),len) == 0)
				{
					pattern_index.push_back(sa.at(i));
                    			cout<<"\nFound at "<<i_str<<"Index -->"<<sa.at(i);
				}
                		else
                    			break;
                		i++;  
                
            		}
           	 break;
              	}
        	else if(strncmp(search_str.c_str(),mid_str.c_str(),len) < 0)
        	{
          		high = mid-1;
        	}
        	else if(strncmp(search_str.c_str(),mid_str.c_str(),len) > 0)
        	{
            		low = mid+1;
        	}  
    	}       
	return pattern_index;
}
int main()
{
	string str = "aba$babbb$";
	vector<int> suffix_array; 
	suffix_array = build_suffix_array(str); 
	string search_str = "ba"; 
	find_pattern(suffix_array,search_str,str);	
    	return 0;
}


