#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    string str = "aba$babbb$";
    vector<int> sa;
    map<string,int> m;
    int i=0;
    for(i =0 ;i< str.length();i++)
    {
       m.insert (pair<string,int>(str.substr(i),i));
    }
    
    map<string,int>:: iterator it = m.begin();
    for (it=m.begin(); it!=m.end(); ++it)
    {
        cout << it->first << " => " << it->second << '\n';
        sa.push_back(it->second);
    }
    
    string search_str = "ba";
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
            while(i >= low)
            {
                i_str = str.substr(sa.at(i));
                if(strncmp(search_str.c_str(),i_str.c_str(),len) == 0)
                    cout<<"\nFound at "<<i_str<<"Index -->"<<sa.at(i);
                else
                    break;
                i--;    
                
            }
            i = mid +1;
            while(i <= high)
            {
                i_str = str.substr(sa.at(i));
                if(strncmp(search_str.c_str(),i_str.c_str(),len) == 0)
                    cout<<"\nFound at "<<i_str<<"Index -->"<<sa.at(i);
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
    return 0;
}


