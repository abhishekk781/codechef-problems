#include <bits/stdc++.h>
using namespace std;
#define lli long long int 
#define MOD 1000000007
vector <int> G[100005];
int depth[100005]={0};
int parent[100005]={0};
int visited[100005]={0};
int subtree_size[100005]={0};
int pos_in_base[100005]={0};
int chain_ind[100005];
int chain_head[100005];
int base_ar[100005];
int segtree[1000005];
int dp[18][100005];
lli ar[100005];
int n;
int cn=1,pib=1;
//int pos_of_id[100005]={0};
void dfs(int root,int pre,int dep){
    dp[0][root]=pre;
    parent[root]=pre;
    depth[root]=dep;
    subtree_size[root]=1;
    visited[root]=1;
    for(int i=0;i<G[root].size();i++){
        int u=G[root][i];
        if(visited[u]==1){ continue; }
        dfs(u,root,dep+1);
        subtree_size[root]+=subtree_size[u];
    }
}
 
int hld(int cur_node){
    if(chain_head[cn]==-1){ chain_head[cn]=cur_node; }
    chain_ind[cur_node]=cn;
    pos_in_base[cur_node]=pib;
    if(ar[cur_node]%3==0){ base_ar[pib]=1; }
    else{ base_ar[pib]=0; }
    pib++;
    int sp=-1,sp_ind=-1;
    for(int i=0;i<G[cur_node].size();i++){
        int u=G[cur_node][i];
        if(u!=parent[cur_node] && sp<subtree_size[u]){
            sp=subtree_size[u];
            sp_ind=u;
        }
    }
    if(sp!=-1){
        hld(sp_ind);
    }
    
    for(int i=0;i<G[cur_node].size();i++){
        int u=G[cur_node][i];
        if(u!=parent[cur_node] && u!=sp_ind){
            //cout<<u<<" -- ";
            cn++;
            hld(u);
        }
    }
}
 
void build_tree(int node,int start,int end){
    if(start==end){
        segtree[node]=base_ar[start];
    }
    else{
        int mid=(start+end)/2;
        build_tree(2*node,start,mid);
        build_tree(2*node+1,mid+1,end);
        segtree[node]=(segtree[2*node]+segtree[2*node+1]);
    }
}
 
/*void update(int node,int start,int end,int ind,int val){
    if(start==end){
        base_ar[ind]=val;
        segtree[node]=base_ar[start];
    }
    else{
        int mid=(start+end)/2;
        if(ind<=mid){ update(2*node,start,mid,ind,val); }
        else{ update(2*node+1,mid+1,end,ind,val); }
        segtree[node]=max(segtree[2*node],segtree[2*node+1]);
    }
}*/
 
long long int getans(int node,int start,int end,int l,int r){
    if(l>end || r<start){ return 0; }
    if(l<=start && end<=r){ return segtree[node]; }
    else{
        int mid=(start+end)/2;
        long long int p1=getans(2*node,start,mid,l,r);
        long long int p2=getans(2*node+1,mid+1,end,l,r);
        return (p1+p2);
    }
}
 
int LCA(int l,int r){
    if(depth[l]<depth[r]){
        swap(l,r);
    }
    int dif=depth[l]-depth[r];
    for(int i=0;i<18;i++){
        if((dif>>i)&1){
            l=dp[i][l];
        }
    }
    if(l==r) return l;
    for(int i=18-1;i>=0;i--){
        if(dp[i][l]!=dp[i][r]){
            l=dp[i][l];
            r=dp[i][r];
        }
    }
    return dp[0][l];
}
 
long long int findmax(int x,int lca){
    long long int ret=0;
    while(1){
        if(x==lca){ return ret; }
        if(chain_ind[x]==chain_ind[lca]){ ret=(ret+getans(1,1,n,pos_in_base[lca]+1,pos_in_base[x])); break; }
        ret=(ret+getans(1,1,n,pos_in_base[chain_head[chain_ind[x]]],pos_in_base[x]));
        x=parent[chain_head[chain_ind[x]]];
    }
    return ret;
}
 
void initialiser(){
    for(int i=0;i<n+5;i++){
        for(int j=0;j<18;j++){
                dp[j][i]=-1;
            }
        visited[i]=0;
        depth[i]=0;
        parent[i]=0;
        chain_head[i]=-1;
        G[i].clear();
        cn=1;
        pib=1;
    }
}
 
int main() {
    //std::ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    ar[0]=1; ar[1]=1;
    for(int i=2;i<100005;i++){
        ar[i]=ar[i-1]*i;
        ar[i]%=MOD;
    }
        scanf("%d",&n);
        initialiser();
        for(int i=1;i<=n-1;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        parent[0]=-1;
        dfs(0,-1,0);
        for(int j=1;j<18;j++){
            for(int i=0;i<n;i++){
                if(dp[j-1][i]!=-1){
                    dp[j][i]=dp[j-1][dp[j-1][i]];
                }
            }
        }
        hld(0);
        build_tree(1,1,n);
        int q; cin>>q;
        while(q--){
            int x,y;
            scanf("%d%d",&x,&y);
            //cin>>x>>y;
            
            int lca=LCA(x,y);
            //cout<<lca<<" ";
            long long int p1=findmax(x,lca);
            long long int p2=findmax(y,lca);
            long long int ans=(p1+p2);
            if(ar[lca]%3==0){ ans++; }
            printf("%lli\n",ans);
            //cout<<ans<<endl;
        }
}
