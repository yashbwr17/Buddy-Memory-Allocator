#include<iostream>
#include <unordered_map>
#include<vector>
using namespace std;
 void deallocate(int s,vector<pair<int,int > > arr[],unordered_map<int,int>& um)
    {
        // Invalid reference, as this was never allocated
        if (um.find(s)==um.end()) {
           
            return;
        }
 
        // Get the list which will track free blocks  
        // of this size
        int x = (int)ceil(log2(um[s]));
        int i, buddyNumber, buddyAddress;
 
        // Add it to the free list
        arr[x].push_back(make_pair(s, s + pow(2,x) - 1));
        // Calculte it's buddy number and buddyAddress. The
        // base address is implicitly 0 in this program, so no
        // subtraction is necessary for calculating buddyNumber
        buddyNumber = s / um[s];
     
        if (buddyNumber % 2 != 0) {
            buddyAddress = s -pow(2,x) ;
        }
         
        else {
            buddyAddress = s + pow(2,x) ;
        }
         
         
        // Search in the free list for buddy
        for (i = 0; i < arr[x].size(); i++) {
             
             
            // This indicates the buddy is also free
            if (arr[x][i].first == buddyAddress) {
                 
                // Buddy is the block after block  
                // with this base address
                if (buddyNumber % 2 == 0) {
                     
                    // Add to appropriate free list
arr[x+1].push_back(make_pair(s, s +2* (pow(2,x) - 1)));
                   
                }
                 
                // Buddy is the block before block  
                // with this base address
                else {
                     
                    // Add to appropriate free list
arr[x+1].push_back(make_pair(buddyAddress, buddyAddress +2* (pow(2,x))));
                   
                }
 
                // Remove the individual segements  
                // as they have coalesced
arr[x].erase(arr[x].begin()+i);
                arr[x].erase(arr[x].end()-1);
               
                break;
            }
        }
  um.erase(s);
        // Remove entry from HashMapm.remove(s)
    }
void allocate(vector<pair<int,int > > v[],int r,int e,unordered_map<int,int>& um)
{
int x=ceil(log2(r));

if(v[x].size()!=0)
{
um.insert({v[x][0].first,v[x][0].second-v[x][0].first+1});
v[x].erase(v[x].begin());

return;
}
int i;
for( i=x+1;i<e;i++)
{
if(v[i].size()!=0)
{
break;
}
}
if(i==e)
return;
i--;
for(;i>=x;i--)
{
pair<int,int>a=make_pair(v[i+1][0].first,(v[i+1][0].first+v[i+1][0].second)/2);
pair<int,int>b=make_pair((v[i+1][0].first+v[i+1][0].second)/2+1,v[i+1][0].second);
v[i+1].erase(v[i+1].begin());
v[i].push_back(a);
v[i].push_back(b);

}

um.insert({v[x][0].first,v[x][0].second-v[x][0].first+1});
v[x].erase(v[x].begin());

}
int main()
{
    unordered_map<int,int> um;
    int m;
    cin>>m;
    int x=ceil(log2(m));
    vector<pair<int,int > > v[x+1];
    v[x].push_back(make_pair(0,m-1));
    int t=5;
    while(t--)
{int r,y;
cin>>r>>y;
allocate(v,r,x+1,um);
deallocate(y,v,um);
vector<int>q(m,1);
for(int i=0;i<x+1;i++){
for(int j=0;j<v[i].size();j++){
for(int k=v[i][j].first;k<=v[i][j].second;k++){
q[k]=0;
}
}
}
for(int i=0;i<m;i++){
cout<<q[i]<<" ";

}
cout<<endl;}
return 0;
}
