#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<set>
using namespace std;

vector<int> friends[1001];
unordered_map<int,pair<int,int>> packages;  // pid  <area, price>
int userAndArea[1001][11];
set<pair<int,int>> location[11];
int m, n;

   
void init(int N, int M)
{   
    // N = users;
    // M = areas
    m = M;
    n = N;
    packages.clear();
   
    for (int i = 1; i <= m; i++) {
        location[i].clear();
        for (int j = 1; j <= n; j++) {
            userAndArea[j][i] = 0;
            friends[j].resize(0);
   
        }
    }
}
void befriend(int uid1, int uid2)
{ 
    friends[uid1].push_back(uid2);
    friends[uid2].push_back(uid1);
}
   
void add(int pid, int area, int price)
{   
    packages.insert({pid,{area,price}});
    location[area].insert({price,pid});
}
   
void reserve(int uid, int pid)
{
    int reservedArea = packages[pid].first;
    userAndArea[uid][reservedArea] ++;
    location[reservedArea].erase({packages[pid].second, pid});
    packages.erase(pid);
}
   
int recommend(int uid)
{   
    int cur = -1;
    int price = 1e9 +7;
    int pid;
    for(int i = 1; i<= m; i ++)
    {
        int ans = userAndArea[uid][i]; // int ans = 0
        for (auto el: friends[uid])
        {   
            ans += userAndArea[el][i];
        }
        
        if (location[i].size())
        {
            if (cur < ans)
            {
                cur = ans;
                price = location[i].begin() ->first;
                pid = location[i].begin() -> second;
            }
            else if (ans == cur)
            {
                if(location[i].begin()->first < price)
                {
                    price = location[i].begin() ->first;
                    pid = location[i].begin() -> second;
                }
                else if (location[i].begin()->first == price)
                {
                    pid = min(pid, location[i].begin()->second);
                }
            }
        }
    }
    return pid;
}
