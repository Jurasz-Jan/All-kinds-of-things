#include <bits/stdc++.h>
using namespace std;
const int N=5005;
double dis[N][N];
int n,x[N],y[N],match[N];
bool vis[N];
double dist(int i,int j){return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));}
bool dfs(int u)
{
    for(int v=0;v<n;v++)
        if(dis[u][v]<1e-6&&!vis[v])
        {
            vis[v]=1;
            if(match[v]==-1||dfs(match[v]))
            {
                match[v]=u;
                return 1;
            }
        }
    return 0;
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++) cin>>x[i]>>y[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dis[i][j]=dist(i,j);
    memset(match,-1,sizeof match);
    for(int i=0;i<n;i++)
    {
        memset(vis,0,sizeof vis);
        dfs(i);
    }
    int u=0;
    double sum=0;
    vector<int>path;
    for(int i=0;i<n;i++)
        if(match[i]!=-1)
        {
            sum+=dis[match[i]][i];
            if(i<match[i])
                path.push_back(i),path.push_back(match[i]);
        }
    cout<<sum<<endl;
    for(int i=0;i<path.size();i++)
        cout<<x[path[i]]<<" "<<y[path[i]]<<endl;
    return 0;
}
