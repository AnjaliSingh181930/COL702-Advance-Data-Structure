#include<bits/stdc++.h>
#define pr pair<int, int>
#define pb push_back
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;

vector<pr> countSort(int n, vector<int> &arr) {
    vector<int> freq(n + 1, 0);

    for (int i = 0; i < n; i++)
        freq[arr[i]]++;

    for (int i = 1; i <= n; i++)
        freq[i] += freq[i - 1];

    vector<pair<int, int>> ans(n);

    for (int i = 0; i < n; i++)
    {
        ans[n - freq[arr[i]]] = make_pair(arr[i], i);
        freq[arr[i]]--;
    }

    return ans;
}

void solve(vector<int> &outdeg, vector<int> &indeg, int n)
{
    ofstream output("output.txt");
    int maxoutdeg = indeg[0], maxindeg = indeg[0];
    int sumoutdeg = 0, sumindeg = 0;
    for (int i = 0; i < n; i++)
    {
        maxoutdeg = max(maxoutdeg, outdeg[i]);
        maxindeg = max(maxindeg, indeg[i]);
        sumoutdeg += outdeg[i];
        sumindeg += indeg[i];
    }
    if (maxoutdeg > n - 1 || maxindeg > n - 1 || sumoutdeg != sumindeg)
    {
        output << to_string(0);
        output.close();
        return;
    }
    int adj[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
    vector<pr> out = countSort(n, outdeg);
    vector<pr> in;
    for (int i = n - 1; i >= 0; i--)
    {
        in = countSort(n, indeg);
        int j = 0;
        while (j < n && out[i].first > 0)
        {
            if (in[j].first && (in[j].second != out[i].second))
            {
                adj[out[i].second][in[j].second] = 1;
                out[i].first --;
                in[j].first--;
                indeg[in[j].second] = in[j].first;
            }
            j++;
        }
    }
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (out[i].first || in[i].first)
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        output << to_string(0);
        output.close();
        return;
    }
    else
    {
        output << to_string(1) << "\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                output << to_string(adj[i][j]);
                if (j != n - 1) output << ",";
            }
            if (i != n - 1)
                output << "\n";
        }
        output.close();
    }
}

int main()
{
    fast_io;
    ifstream input("input.txt");
    int n;
    input >> n;
    vector<int> outdeg(n), indeg(n);
    string str;
    input >> str;
    int i = 0;
    for (int j = 0; j < str.length(); j++)
    {
        if (str[j] >= '0'  && str[j] <= '9')
        {
            string digit = "";
            while (str[j] >= '0'  && str[j] <= '9')
                digit += str[j++];
            outdeg[i++] = stoi(digit);
        }
    }
    i = 0;
    str.clear();
    input >> str;
    for (int j = 0; j < str.length(); j++)
    {
        if (str[j] >= '0'  && str[j] <= '9')
        {
            string digit = "";
            while (str[j] >= '0'  && str[j] <= '9')
                digit += str[j++];
            indeg[i++] = stoi(digit);
        }
    }
    input.close();
    solve(outdeg, indeg, n);
    return 0;
}                   // TC = O(n^2) SC = O(n)
