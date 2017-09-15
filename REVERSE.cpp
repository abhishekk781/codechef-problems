#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <deque> 
using namespace std;
vector < pair<int,int> > G[100005];

int main() {
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        G[x].push_back(make_pair(y,0));
        G[y].push_back(make_pair(x,1));
    }
    int dis[100007];
    for(int i=0;i<n+5;i++){ dis[i]=100000000; }
    queue <int> q;
    q.push(1);
    dis[1]=0;
    while(!q.empty()){
        int x=q.front();
        //cout<<x<<" ";
        q.pop();
        for(int i=0;i<G[x].size();i++){
            int u=G[x][i].first;
            int v=G[x][i].second;
            if(dis[x]+v<dis[u]){
                dis[u]=dis[x]+v;
                q.push(u);
            }
        }
    }
    if(dis[n]==100000000){ cout<<-1; }
    else{ cout<<dis[n]; }
    return 0;
}
