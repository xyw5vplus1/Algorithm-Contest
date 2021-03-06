#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int oldrk[maxn],id[maxn],cnt[maxn],px[maxn];
int sa[maxn],ht[maxn],rk[maxn];
vector<int> v;
char s[maxn],s0[10];
int T;
bool cmp(int x,int y,int w)
{
    return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];
}
void SA(char s[],int n)
{
    int m=300,p;
    memset(cnt,0,sizeof(cnt));
    for (int i=1;i<=n;i++) ++cnt[rk[i]=s[i]];
    for (int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
    for (int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
    for (int w=1;w<n;w<<=1,m=p) {  // m=p 就是优化计数排序值域
        p=0;
        for (int i=n;i>n-w;i--) id[++p]=i;
        for (int i=1;i<=n;i++)
            if (sa[i]>w) id[++p]=sa[i]-w;
        memset(cnt,0,sizeof(cnt));
        for (int i=1;i<=n;i++) ++cnt[px[i]=rk[id[i]]];
        for (int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        for (int i=n;i>=1;i--) sa[cnt[px[i]]--]=id[i];
        memcpy(oldrk,rk,sizeof(rk));
        for (int p=0,i=1;i<=n;i++)
            rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
    }
}
void calcH(char a[],int n)
{
    for (int i=1,j=0;i<=n;i++) {
        if (j) --j;
        while (a[i+j]==a[sa[rk[i]-1]+j]) ++j;
        ht[rk[i]]=j;
    }
}
int getF(int pos)
{
    return lower_bound(v.begin(),v.end(),pos)-v.begin();
}
int main()
{
    scanf("%d",&T);
    for (int kase=1;kase<=T;kase++){
        scanf("%s",s0);
        scanf("%s",s+1);
        int n=strlen(s+1);
        SA(s,n);
        calcH(s,n);
        v.clear();
        for (int i=1;i<=n;i++)
            if (s[i]==s0[0]) v.push_back(i);
        ll ans=0;
        for (int i=1;i<=n;i++) {
            int pos=sa[i]+ht[i];
            int t=getF(sa[i]);
            if (t!=v.size()) {
                pos=max(pos,v[t]);
                ans=ans+n-pos+1;
            }
            else continue;
        }
        printf("Case #%d: %lld\n",kase,ans);
    }
    return 0;
}
