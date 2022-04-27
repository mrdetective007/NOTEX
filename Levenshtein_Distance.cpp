// #include <iostream>
// #include <math.h>
// #include <string.h>
// using namespace std;
// #define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values
// int main() {
//    int i,j,l1,l2,t,track;
//    int dist[50][50];
//    //take the strings as input
//    char s1[] = "darshan";
//    char s2[] = "jeet";
//    //stores the lenght of strings s1 and s2
//    l1 = strlen(s1);
//    l2= strlen(s2);
//    for(i=0;i<=l1;i++) {
//       dist[0][i] = i;
//    }
//    for(j=0;j<=l2;j++) {
//       dist[j][0] = j;
//    }
//    for (j=1;j<=l1;j++) {
//       for(i=1;i<=l2;i++) {
//          if(s1[i-1] == s2[j-1]) {
//             track= 0;
//          } else {
//             track = 1;
//          }
//          t = MIN((dist[i-1][j]+1),(dist[i][j-1]+1));
//          dist[i][j] = MIN(t,(dist[i-1][j-1]+track));
//       }
//    }
//    cout<<"The Levinstein distance is:"<<dist[l2][l1];
//    return 0;
// }



#include <bits/stdc++.h>
using namespace std;


int min(int x, int y, int z) { return min(min(x, y), z); }

int editDist(string str1, string str2, int m, int n)
{
	
	if (m == 0)
		return n;

	
	if (n == 0)
		return m;

	
	if (str1[m - 1] == str2[n - 1])
		return editDist(str1, str2, m - 1, n - 1);

	
	return 1
		+ min(editDist(str1, str2, m, n - 1), // Insert
				editDist(str1, str2, m - 1, n), // Remove
				editDist(str1, str2, m - 1,
						n - 1) // Replace
			);
}

int Insertfun(string s1, string s2, int m, int n){
   if(m==0){
      return n;
   }
   if(n==0){
      return m;
   }
   if(s1[m-1] == s2[n-1]){
      return Insertfun(s1,s2,m-1,n-1);
   }
   return  Insertfun(s1,s2,m,n-1);
}

int deletefun(string s1, string s2, int m, int n){
   if(m==0){
      return n;
   }
   if(n==0){
      return m;
   }
   if(s1[m-1] == s2[n-1]){
      return deletefun(s1,s2,m-1,n-1);
   }
   return deletefun(s1,s2,m-1,n);
}

int replacefun(string s1, string s2, int m, int n){
   if(m==0){
      return n;
   }
   if(n==0){
      return m;
   }
   if(s1[m-1] == s2[n-1]){
      return replacefun(s1,s2,m-1,n-1);
   }
   return  replacefun(s1,s2,m-1,n-1);
}


// Driver code
int main()
{
	// your code goes here
	string str1 = "jeet";
	string str2 = "jeete";

	cout << editDist(str1, str2, str1.length(),str2.length())<<endl;
   cout<<Insertfun(str1,str2,str1.size(),str2.size())<<endl;
   cout<<deletefun(str1,str2,str1.size(),str2.size())<<endl;
   cout<<replacefun(str1,str2,str1.size(),str2.size())<<endl;

	return 0;
}


