#include <bits/stdc++.h>
using namespace std;

// Find shortest path from source node to destination node
// Also track the path

int Djiskstra(vector<vector<pair<int, long long int>>>&g,int src,int dest)
{
    vector<int> vis(100 + 1, 0);
    map<int, int> via;
    vector<long long int> dist(100 + 1, LLONG_MAX);

    priority_queue<pair<long long int, int>, vector<pair<long long int, int>>, greater<pair<long long int, int>>> q;
    q.emplace(0LL, src);
    dist[src] = 0LL;

    while (!q.empty())
    {
        auto it = q.top();
        q.pop();
        int node = it.second;
        long long int d = it.first;
        if (vis[node])
            continue;
        vis[node] = 1;

        for (auto nbr : g[node])
        {
            int nd = nbr.first;
            long long int wt = nbr.second;
            if (d + wt < dist[nd])
            {
                dist[nd] = d + wt;
                via[nd] = node;
                q.emplace(dist[nd], nd);
            }
        }
    }
    return dist[dest];
}
vector<int>give_path(vector<vector<pair<int, long long int>>>&g,int src,int dest)
{
    vector<int> vis(100 + 1, 0);
    map<int, int> via;
    vector<long long int> dist(100 + 1, LLONG_MAX);

    priority_queue<pair<long long int, int>, vector<pair<long long int, int>>, greater<pair<long long int, int>>> q;
    q.emplace(0LL, src);
    dist[src] = 0LL;

    while (!q.empty())
    {
        auto it = q.top();
        q.pop();
        int node = it.second;
        long long int d = it.first;
        if (vis[node])
            continue;
        vis[node] = 1;

        for (auto nbr : g[node])
        {
            int nd = nbr.first;
            long long int wt = nbr.second;
            if (d + wt < dist[nd])
            {
                dist[nd] = d + wt;
                via[nd] = node;
                q.emplace(dist[nd], nd);
            }
        }
    }
    vector<int> path;
    for (int at = dest; at != src; at = via[at])
    {
        path.push_back(at);
    }
    path.push_back(src);
    reverse(path.begin(), path.end());    
    
    return path;
}

int main()
{
    vector<vector<pair<int, long long int>>> g(100 + 1);
    map<int, string> m_node_names;

    // Storing Locations as Nodes
    m_node_names[1] = "Aryabhatta_Hostel";
    m_node_names[2] = "Satish_Dhawan_Hostel";
    m_node_names[3] = "DG_Corner";
    m_node_names[4] = "SAC";
    m_node_names[7] = "LC_Corner";
    m_node_names[8] = "Vivekanand_Hostel";
    m_node_names[9] = "Vivekanand_Corner";
    m_node_names[10] = "Vishvakarma_Hostel";
    m_node_names[11] = "Gymkhana_Grounds";
    m_node_names[12] = "NCC_Corner";
    m_node_names[13] = "Srinivas_Deshpande_Library";
    m_node_names[14] = "IIT_Stone";
    m_node_names[15] = "Annie_Besant_Lecture_Theatre";

    
    // Storing distances between adjacent nodes
    g[1].push_back({2,10});g[2].push_back({1,10});
    g[2].push_back({3,190});g[3].push_back({2,190});
    g[3].push_back({15,190});g[15].push_back({3,190});
    g[15].push_back({14,50});g[14].push_back({15,50});
    g[14].push_back({13,80});g[13].push_back({14,80});
    g[13].push_back({12,30});g[12].push_back({13,30});
    g[12].push_back({7,310});g[7].push_back({12,310});
    g[7].push_back({8,60});g[8].push_back({7,60});
    g[9].push_back({11,100});g[11].push_back({9,100});
    g[9].push_back({10,150}); g[10].push_back({9,150});
    g[9].push_back({8,50});g[8].push_back({9,50});
    g[7].push_back({4,70});g[4].push_back({7,70});
    g[4].push_back({3,50}); g[3].push_back({4,50});
    int src1, dest1;
    int src2, dest2;
    // Input for pickup and destination
    string pickup1;string destination1;
    string pickup2;string destination2;
    cin>>pickup1>>destination1;
    cin>>pickup2>>destination2;
    for(auto it:m_node_names)
    {
        if(it.second==pickup1)
        { src1=it.first;break;}
    }
    for(auto it:m_node_names)
    {
        if(it.second==destination1)
        {dest1=it.first;break;}
    }
    for(auto it:m_node_names)
    {
        if(it.second==pickup1)
        { src2=it.first;break;}
    }
    for(auto it:m_node_names)
    {
        if(it.second==destination2)
        {dest2=it.first;break;}
    }

    int p1= Djiskstra(g,src1,src2)+Djiskstra(g,src2,dest1)+Djiskstra(g,dest1,dest2); 
    int p2= Djiskstra(g,src1,dest1)+Djiskstra(g,dest1,src2)+Djiskstra(g,src2,dest2);
    int p3= Djiskstra(g,src1,src2)+Djiskstra(g,src2,dest2)+Djiskstra(g,dest2,dest1); 

    int mn=min(p1,min(p2,p3));
    vector<int> path;
    
    if(mn==p1)
    {
        vector<int>d1=give_path(g,src1,src2); d1.pop_back();
        vector<int>d2=give_path(g,src2,dest1); d2.pop_back();
        vector<int>d3=give_path(g,dest1,dest2);
        for(auto it:d1)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        for(auto it:d2)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        for(auto it:d3)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        
    }
    else
    if(mn==p2)
    {
        vector<int>d1=give_path(g,src1,src2); d1.pop_back();
        vector<int>d2=give_path(g,src2,dest1); d2.pop_back();
        vector<int>d3=give_path(g,dest1,dest2);
        for(auto it:d1)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        for(auto it:d2)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        for(auto it:d3)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        
    }
    else
    {
        vector<int>d1=give_path(g,src1,src2); d1.pop_back();
        vector<int>d2=give_path(g,src2,dest2); d2.pop_back();
        vector<int>d3=give_path(g,dest2,dest1);
        for(auto it:d1)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        for(auto it:d2)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        for(auto it:d3)
        cout<<m_node_names[it]<<"-->";
        cout<<endl;
        
    }

    // vector<int> path;
    // for (int at = dest; at != src; at = via[at])
    // {
    //     path.push_back(at);
    // }
    // path.push_back(src);
    // reverse(path.begin(), path.end());    
    // for(int i=0;i<path.size()-1;i++)
    // cout<<m_node_names[path[i]]<<" --> ";cout<<m_node_names[path[path.size()-1]]<<endl;

    return 0;
}
