#include <bits/stdc++.h>
using namespace std;

void solve(int v, vector<int> adj[], int target, set<int> &ans)
{
    int count = 0;
    queue<int> q;
    bool vis[v] = {false};
    q.push(target);
    ans.insert(target);
    vis[target] = true; 
    while (!q.empty())
    {
        int size = q.size();
        count++;
        while (size--)
        {
            int temp = q.front();
            q.pop();
            if ((count-1)%3==0)
                ans.insert(temp);
            vis[temp] = false;
            for (int &ele : adj[temp])
            {
                if (!vis[ele])
                {
                    q.push(ele);
                    vis[ele] = true;
                }
            }
        }
    }
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n;
    input >> n;

    vector<int> adj[n + 1];

    for (int i = 1; i <= n; i++)
    {
        string str;
        input >> str;
        for (int j = 0; j < str.length(); j++)
        {
            if (str[j] >= '0' && str[j] <= '9')
            {
                string vertex = "";
                while (str[j] >= '0' && str[j] <= '9')
                {
                    vertex += str[j];
                    j++;
                }
                int node = stoi(vertex);
                if (node != i)
                    adj[node].push_back(i);
            }
        }
        sort(adj[i].begin(), adj[i].end());
    }
    
    string u;
    input >> u;
    int target = stoi(u.substr(1));

    set<int> ans;
    
    solve(n+1, adj, target, ans);

    output << ans.size() << endl;

    bool first = true;
    for (auto it = ans.begin(); it != ans.end(); it++)
    {
        if (!first)
            output << ",";
        output << "v" << *it;
        first = false;
    }

    input.close();
    output.close();

    return 0;
}
