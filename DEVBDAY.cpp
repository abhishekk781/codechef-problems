#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int n;
vector <int> G[100005];
int visited[100005]={0};
lli ar[100005]={0};
lli ans=0,mx=0,flag=0;
lli dfs(int i){
    if(visited[i]==1){ flag=i; return 0; }
    visited[i]=1;
    lli ret=(ar[i]+dfs(G[i][0]));
    if(flag>0){ 
        if(flag==i){ flag=0; }
        //cout<<ret<<" ";
        mx=ret;
        return mx;
    }
    return mx=max(mx,ret);
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        ans=0;
        cin>>n;
        for(int i=0;i<=n+4;i++){ G[i].clear(); visited[i]=0; }
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            G[i].push_back(x);
        }
        for(int i=1;i<=n;i++){ 
            cin>>ar[i];
        }
        lli ans=0;
        for(int i=1;i<=n;i++){
            mx=0; flag=0;
            if(visited[i]==1){ continue; }
            lli sum=dfs(i);
            if(mx>0){ ans+=mx; }
        }
        cout<<ans<<endl;
    }
    return 0;
}
