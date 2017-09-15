#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int n;
lli arr[19][19]={0};
lli ans=0;
struct node{
    node *left=NULL;
    node *right=NULL;
}*trie[20];
void insert(node *root,int val){
    int level=30;
    while(level>=0){
        if(val&(1<<level)){
            if(root->right==NULL){ root->right=new node; }
            root=root->right;
        }
        else{
            if(root->left==NULL){ root->left=new node; }
            root=root->left;
        }
        level--;
    }
}
lli query(node *root,int val,int level){
        if(level==-1){ return 0; }
        if((1<<level)&val){
            if(root->left==NULL){ return query(root->right,val,level-1); }
            else{ return (1<<level)|query(root->left,val,level-1); }
        }
        else{
            if(root->right==NULL){ return query(root->left,val,level-1); }
            else{ return (1<<level)|query(root->right,val,level-1); }
        }
}
void solvedown(int i,int j,int val){
    val=val^arr[i][j];
    if(i+j==n+1){
        insert(trie[i],val);
        return;
    }
    solvedown(i,j+1,val);
    solvedown(i+1,j,val);
}
void solveup(int i,int j,int val){
    if(i+j==n+1){
        ans=max(ans,query(trie[i],val,30));
        return;
    }
    val^=arr[i][j];
    solveup(i,j-1,val);
    solveup(i-1,j,val);
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>arr[i][j];
        }
        trie[i]=new node;
    }
    solvedown(1,1,0);
    solveup(n,n,0);
    cout<<ans;
    return 0;
}
