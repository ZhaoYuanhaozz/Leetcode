1）硕士香港理工大学没有offer？无法确认开学时间

2）出入境记录时间囊括全部留学经历，需更新



如遇网课学习经历，需一次性完整补充：校方官方发布的强制回国通知、停飞证明、关闭国境、每学期网课通知、能确认每学期网课开始（明确日期）及最后一门课结

束（明确日期）、每学期课表、论文准备、答辩、与老师交流沟通等材料（原件关键日期信息等记号笔标记），并在备注处注明网课学习起止时间，共XXX天（哪段硕士涉

及，写哪段）



3）根据已有材料，标红信息为修改信息，请确认，如无问题请自行取消颜色标记

#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;
   
#define MAXS 10003
   
struct Node{
    int num, depth, par, cnt, child[11], del;
    void init(){
        num = depth = par = cnt = del = child[0] = 0;
    }
}node[MAXS];
int n;
    
   
struct CMP{
bool operator()(int id1, int id2){
    if(node[id1].num != node[id2].num)
        return node[id1].num < node[id2].num;
    return id1 > id2;
}
};

unordered_map <string , int> hmap;
set<int ,CMP> pool;
   
void init(int mNum)
{
    n = 1;
    hmap.clear();
    node[n].init();
    node[n].num = mNum;  
    hmap["root"] = n++;   
   
}
   
void destroy()
{
   
}
   
int addDept(char mUpperDept[], char mNewDept[], int mNum)
{
    int a = hmap[mUpperDept];
    int b = hmap[mNewDept];
    if( a == 0 || b != 0 || node[a].depth >= 5 || node[a].cnt >= 10 || node[a].num <= mNum){
        return -1;
    }
    node[a].num -= mNum;  
    node[a].child[node[a].cnt++] = n;
   
    node[n].init();
    node[n].num = mNum;
    node[n].par = a;
    node[n].depth = node[a].depth + 1;
   
    hmap[mNewDept] = n++;
    return node[a].num;
}
   
bool ischild(int p , int c){
    while (p != 0)
    {
        if(node[p].par == c)return true;
        p = node[p].par;
    }
    return false;
}
void remocechild(int p, int c){
    for(int i = 0 ; i < node[p].cnt; i++){
        if(node[p].child[i] == c){
            node[p].cnt--;
            node[p].child[i] = node[p].child[node[p].cnt];
            node[p].child[node[p].cnt] = 0;
        }
    }
}
   
int tempDepth, res;
void checkDepth(int id){
    res ++;
    if(res > tempDepth) tempDepth = res;
    for(int i = 0; i < node[id].cnt; i ++)
        checkDepth(node[id].child[i]);
    res--;
}
   
void setDepth(int id, int depth){
    node[id].depth = depth;
    for(int i = 0 ; i < node [id].cnt ; i ++)
        setDepth(node[id].child[i], depth + 1);
}
   
int mergeDept(char mDept1[], char mDept2[])
{
    int a = hmap[mDept1];
    int b = hmap[mDept2];
   
    if(a == 0 || b == 0)return -1;
   
    if(ischild(a,b)==true) return -1;
   
     
    if(node[b].par != a && node[a].cnt + node[b].cnt > 10) return -1;
   
    tempDepth = res = 0;
    checkDepth(b);
    if(node[a].depth + (tempDepth - 1) > 5) return -1;
   
   
    setDepth(b, node[a].depth);
    remocechild(node[b].par, b);
    node[a].num += node[b].num;
   
    for(int i = 0 ; i < node[b].cnt ; i++){
        node[a].child[node[a].cnt++] = node[b].child[i];
        node[node[b].child[i]].par = a;
    }
    node[b].del = 1;
    hmap[mDept2] = 0;
    return node[a].num;
       
}
   
int moveMen(int id, int k, int mDepth, int mNum){
    int res = 0;
    if(k <= mDepth){
        if(node[id].num > mNum){
            node[id].num -= mNum;
            res += mNum;
        }
        else{
            res += node[id].num - 1;
            node[id].num = 1;
        }
    }
    for(int i = 0 ; i < node[id].cnt ; i ++)
        res += moveMen(node[id].child[i], k + 1, mDepth, mNum);
    return res;
}
   
int moveEmployee(char mDept[], int mDepth, int mNum)
{
    int id = hmap[mDept];
    if(id == 0)return -1;
    for(int i = 0 ; i < node[id].cnt ; i ++){
        node[id].num += moveMen(node[id].child[i],1, mDepth, mNum);
    }
    return node[id].num;
}
  
   
void recruit(int mDeptNum, int mNum)
{
    pool.clear();  
    for(int i = 1 ; i < n; i ++){
        if(!node[i].del)   
            pool.insert(i); 
    }
      auto itr=pool.begin();
    for(int i = 0 ; i < mDeptNum && i < pool.size(); i ++){
        
        node[(*itr)].num += mNum;
        itr++;
    }
}
