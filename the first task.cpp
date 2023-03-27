//first task(distinct strings)
#include <iostream>
#include <string>
using namespace std;

int main()
{
  int n,k;
  string arr[50];
  string s;
  
  cout<<"ENTER n (THE NUMBERS OF STRINGS):"<<endl;
  cin>>n;
  
  cout<<"arr=";
  for(int i=0; i<n; i++)
  {
    cin>>s;
    arr[i]=s;
  }
  
  cout<<"ENTER k (THE RANK OF THE DISTANCT STRING):"<<endl;
  cin>>k;
  
  cout<<"THE"<<" "<<k<<"TH"<<" "<<"DISTANCT STRING IS:"<<endl;
  
  int count = 0; //counter for the rank k
  for(int i=0; i<n; i++)
  {
    int fr = 0; //frequency of the string
    for(int j=0; j<n; j++)
  {
      if(arr[i]==arr[j])
        fr++;
    }
      if(fr==1)//the string is distinct
    { 
        count++;
      if(count==k)
        cout<<arr[i];
      }  
  }
  cout<<"";
  return 0;
}
