 #include <bits/stdc++.h>
#include <cmath>
using namespace std;
#define MAX 100
int n,x[MAX],y[MAX],cnt=0;
double dist[MAX][MAX];
bool vst[MAX];
vector<int> path;
double mindis=INFINITY;

double calc_dis(int a,int b)
{
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])); //distance
}

void tsp(int cur,double dis, int visited)
{
    if(visited == n)
    {
        if(dis+dist[cur][0]<mindis)
        {
            mindis=dis+dist[cur][0];
            cnt=n;
            path[cnt++]=0;
        }
        return;
    }
    for(int i=1;i<n;i++)
    {
        if(!vst[i])
        {
            vst[i]=true;
            path[cnt++]=i;
            tsp(i,dis+calc_dis(cur,i), visited + 1);
            vst[i]=false;
            cnt--;
        }
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x[i]>>y[i];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            dist[i][j]=calc_dis(i,j);
        }
    }
    path.resize(n);
    tsp(0,0,1);
	
	cout<<"Path: "<<endl;
    for(int i=0;i<cnt;i++)
    {
        cout<<x[path[i]]<<" "<<y[path[i]]<<endl;
    }

    
    cout<<endl<<"Total Distance: "<<fixed<<setprecision(2)<<mindis<<endl;
    return 0;
}