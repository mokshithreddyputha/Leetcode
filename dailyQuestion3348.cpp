class Solution {
public:
    string smallestNumber(string num, long long t) {
        int a=0,b=0,c=0,d=0;
        while(t%2==0){t/=2;a++;}
        while(t%3==0){t/=3;b++;}
        while(t%5==0){t/=5;c++;}
        while(t%7==0){t/=7;d++;}
        if(t!=1) return "-1";

        int A=a+1,B=b+1,C=c+1,D=d+1;
        int e2[10]={0,0,1,0,2,0,1,0,3,0};
        int e3[10]={0,0,0,1,0,0,1,0,0,2};
        int e5[10]={0,0,0,0,0,1,0,0,0,0};
        int e7[10]={0,0,0,0,0,0,0,1,0,0};

        auto idx=[&](int n2,int n3,int n5,int n7){ return ((n2*B+n3)*C+n5)*D+n7; };
        vector<int> f(A*B*C*D, -1);

        vector<vector<int>> buckets(a+b+c+d+1);
        for(int n2=0;n2<A;n2++) for(int n3=0;n3<B;n3++)
         for(int n5=0;n5<C;n5++) for(int n7=0;n7<D;n7++)
            buckets[n2+n3+n5+n7].push_back(idx(n2,n3,n5,n7));

        f[idx(0,0,0,0)]=0;
        for(size_t s=1;s<buckets.size();s++){
            for(int st: buckets[s]){
                int n2=st/(B*C*D), rem=st%(B*C*D);
                int n3=rem/(C*D); rem%=(C*D);
                int n5=rem/D, n7=rem%D;
                int best=INT_MAX;
                for(int dig=2; dig<=9; dig++){
                    int m2=max(0,n2-e2[dig]), m3=max(0,n3-e3[dig]);
                    int m5=max(0,n5-e5[dig]), m7=max(0,n7-e7[dig]);
                    int ni=idx(m2,m3,m5,m7);
                    if(ni==st) continue;
                    best=min(best, f[ni]+1);
                }
                f[st]=best;
            }
        }

        auto reduce=[&](array<int,4> s,int dig){
            return array<int,4>{max(0,s[0]-e2[dig]),max(0,s[1]-e3[dig]),
                                 max(0,s[2]-e5[dig]),max(0,s[3]-e7[dig])};
        };

        int n=num.size();
        int zeroPos=n;
        for(int i=0;i<n;i++) if(num[i]=='0'){zeroPos=i;break;}

        vector<array<int,4>> pref(zeroPos+1);
        pref[0]={a,b,c,d};
        for(int i=0;i<zeroPos;i++) pref[i+1]=reduce(pref[i], num[i]-'0');

        if(zeroPos==n){
            auto&st=pref[n];
            if(st[0]==0&&st[1]==0&&st[2]==0&&st[3]==0) return num;
        }

        auto greedyFill=[&](array<int,4> state,int length){
            string res(length,'1');
            for(int pos=0; pos<length; pos++){
                int remain=length-pos-1;
                for(int dig=1; dig<=9; dig++){
                    auto ns=reduce(state,dig);
                    if(f[idx(ns[0],ns[1],ns[2],ns[3])]<=remain){
                        res[pos]='0'+dig; state=ns; break;
                    }
                }
            }
            return res;
        };

        int limit=min(zeroPos,n-1);
        for(int i=limit;i>=0;i--){
            int startD=(num[i]-'0')+1;
            for(int dig=startD; dig<=9; dig++){
                auto ns=reduce(pref[i],dig);
                int need=f[idx(ns[0],ns[1],ns[2],ns[3])];
                if(need<=n-1-i)
                    return num.substr(0,i)+char('0'+dig)+greedyFill(ns,n-1-i);
            }
        }

        int M=f[idx(a,b,c,d)];
        int L=max(n+1,M);
        return greedyFill({a,b,c,d}, L);
    }
};