class Solution {
    public String smallestNumber(String numStr, long t) {
        int a=0,b=0,c=0,d=0;
        while(t%2==0){t/=2;a++;}
        while(t%3==0){t/=3;b++;}
        while(t%5==0){t/=5;c++;}
        while(t%7==0){t/=7;d++;}
        if(t!=1) return "-1";

        int A=a+1,B=b+1,C=c+1,D=d+1;
        int[] e2={0,0,1,0,2,0,1,0,3,0};
        int[] e3={0,0,0,1,0,0,1,0,0,2};
        int[] e5={0,0,0,0,0,1,0,0,0,0};
        int[] e7={0,0,0,0,0,0,0,1,0,0};

        int total=A*B*C*D;
        int[] f=new int[total];
        Arrays.fill(f,-1);
        List<List<Integer>> buckets=new ArrayList<>();
        for(int s=0;s<=a+b+c+d;s++) buckets.add(new ArrayList<>());
        for(int n2=0;n2<A;n2++) for(int n3=0;n3<B;n3++)
         for(int n5=0;n5<C;n5++) for(int n7=0;n7<D;n7++)
            buckets.get(n2+n3+n5+n7).add(((n2*B+n3)*C+n5)*D+n7);

        f[0]=0;
        for(int s=1;s<buckets.size();s++){
            for(int st: buckets.get(s)){
                int n2=st/(B*C*D), rem=st%(B*C*D);
                int n3=rem/(C*D); rem%=(C*D);
                int n5=rem/D, n7=rem%D;
                int best=Integer.MAX_VALUE;
                for(int dig=2; dig<=9; dig++){
                    int m2=Math.max(0,n2-e2[dig]), m3=Math.max(0,n3-e3[dig]);
                    int m5=Math.max(0,n5-e5[dig]), m7=Math.max(0,n7-e7[dig]);
                    int ni=((m2*B+m3)*C+m5)*D+m7;
                    if(ni==st) continue;
                    best=Math.min(best, f[ni]+1);
                }
                f[st]=best;
            }
        }

        char[] num=numStr.toCharArray();
        int n=num.length;
        int zeroPos=n;
        for(int i=0;i<n;i++) if(num[i]=='0'){zeroPos=i;break;}

        int[][] pref=new int[zeroPos+1][4];
        pref[0]=new int[]{a,b,c,d};
        for(int i=0;i<zeroPos;i++){
            int dig=num[i]-'0';
            pref[i+1]=new int[]{
                Math.max(0,pref[i][0]-e2[dig]), Math.max(0,pref[i][1]-e3[dig]),
                Math.max(0,pref[i][2]-e5[dig]), Math.max(0,pref[i][3]-e7[dig])};
        }

        if(zeroPos==n){
            int[] st=pref[n];
            if(st[0]==0&&st[1]==0&&st[2]==0&&st[3]==0) return numStr;
        }

        int A_=A, B_=B, C_=C, D_=D;

        java.util.function.BiFunction<int[],Integer,String> greedyFill = (state, length) -> {
            char[] res=new char[length];
            Arrays.fill(res,'1');
            int[] cur=state.clone();
            for(int pos=0; pos<length; pos++){
                int remain=length-pos-1;
                for(int dig=1; dig<=9; dig++){
                    int m2=Math.max(0,cur[0]-e2[dig]), m3=Math.max(0,cur[1]-e3[dig]);
                    int m5=Math.max(0,cur[2]-e5[dig]), m7=Math.max(0,cur[3]-e7[dig]);
                    int idx=((m2*B_+m3)*C_+m5)*D_+m7;
                    if(f[idx]<=remain){
                        res[pos]=(char)('0'+dig);
                        cur=new int[]{m2,m3,m5,m7};
                        break;
                    }
                }
            }
            return new String(res);
        };

        int limit=Math.min(zeroPos,n-1);
        for(int i=limit;i>=0;i--){
            int startD=(num[i]-'0')+1;
            for(int dig=startD; dig<=9; dig++){
                int m2=Math.max(0,pref[i][0]-e2[dig]), m3=Math.max(0,pref[i][1]-e3[dig]);
                int m5=Math.max(0,pref[i][2]-e5[dig]), m7=Math.max(0,pref[i][3]-e7[dig]);
                int need=f[((m2*B+m3)*C+m5)*D+m7];
                if(need<=n-1-i){
                    String prefix=new String(num,0,i);
                    return prefix+(char)('0'+dig)+greedyFill.apply(new int[]{m2,m3,m5,m7}, n-1-i);
                }
            }
        }

        int M=f[((a*B+b)*C+c)*D+d];
        int L=Math.max(n+1,M);
        return greedyFill.apply(new int[]{a,b,c,d}, L);
    }
}