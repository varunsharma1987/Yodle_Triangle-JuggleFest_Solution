/**

    Problem Name: 1 - Triangle (Yodle)
    Contributer: Varun Sharma
    Date: December, 21 2015

    dp[1][1] = mat[1][1] as cell (1,1) has no adjacent cell in upper row
    A cell (i,j) is adjacent to it's upper row. Conditions are
        (i-1,j-1)       if(i>1)
        (i-1,j)         otherwise
*/

#include<bits/stdc++.h>

using namespace std;
int mat[105][105];

int main(){
    freopen("triangle.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n=100;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++) cin>>mat[i][j];
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            int tmp=mat[i][j];
            if(j>1) tmp=max(tmp,mat[i][j]+mat[i-1][j-1]);
            tmp=max(tmp,mat[i][j]+mat[i-1][j]);
            mat[i][j]=tmp;
        }
    }
    int mx=0;
    for(int i=1;i<=n;i++) mx=max(mx,mat[n][i]);
    cout<<mx<<endl;
    cerr<<mx<<endl;
    return 0;
}
