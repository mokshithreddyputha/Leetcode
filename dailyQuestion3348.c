#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int e2[10] = {0,0,1,0,2,0,1,0,3,0};
static int e3[10] = {0,0,0,1,0,0,1,0,0,2};
static int e5[10] = {0,0,0,0,0,1,0,0,0,0};
static int e7[10] = {0,0,0,0,0,0,0,1,0,0};

static int A,B,C,D;
static int *f;

static inline int idxOf(int n2,int n3,int n5,int n7){
    return ((n2*B+n3)*C+n5)*D+n7;
}

static void greedyFill(int n2,int n3,int n5,int n7,int length,char *res){
    for(int pos=0; pos<length; pos++){
        int remain = length-pos-1;
        for(int dig=1; dig<=9; dig++){
            int m2 = n2-e2[dig]; if(m2<0) m2=0;
            int m3 = n3-e3[dig]; if(m3<0) m3=0;
            int m5 = n5-e5[dig]; if(m5<0) m5=0;
            int m7 = n7-e7[dig]; if(m7<0) m7=0;
            int id = idxOf(m2,m3,m5,m7);
            if(f[id] <= remain){
                res[pos] = (char)('0'+dig);
                n2=m2; n3=m3; n5=m5; n7=m7;
                break;
            }
        }
    }
}

char* smallestNumber(char* num, long long t) {
    int a=0,b=0,c=0,d=0;
    while(t%2==0){ t/=2; a++; }
    while(t%3==0){ t/=3; b++; }
    while(t%5==0){ t/=5; c++; }
    while(t%7==0){ t/=7; d++; }
    if(t != 1){
        char *res = (char*)malloc(2);
        strcpy(res, "-1");
        return res;
    }

    A=a+1; B=b+1; C=c+1; D=d+1;
    int total = A*B*C*D;
    f = (int*)malloc(sizeof(int)*total);
    for(int i=0;i<total;i++) f[i] = -1;

    int maxSum = a+b+c+d;
    int *bucketCount = (int*)calloc(maxSum+1, sizeof(int));
    int **buckets = (int**)malloc(sizeof(int*)*(maxSum+1));

    for(int n2=0;n2<A;n2++)
     for(int n3=0;n3<B;n3++)
      for(int n5=0;n5<C;n5++)
       for(int n7=0;n7<D;n7++)
          bucketCount[n2+n3+n5+n7]++;

    for(int s=0;s<=maxSum;s++)
        buckets[s] = (int*)malloc(sizeof(int)*bucketCount[s]);

    int *fillPos = (int*)calloc(maxSum+1, sizeof(int));
    for(int n2=0;n2<A;n2++)
     for(int n3=0;n3<B;n3++)
      for(int n5=0;n5<C;n5++)
       for(int n7=0;n7<D;n7++){
          int s=n2+n3+n5+n7;
          buckets[s][fillPos[s]++] = idxOf(n2,n3,n5,n7);
       }
    free(fillPos);

    f[idxOf(0,0,0,0)] = 0;

    for(int s=1; s<=maxSum; s++){
        for(int k=0;k<bucketCount[s];k++){
            int st = buckets[s][k];
            int n2 = st/(B*C*D);
            int rem = st%(B*C*D);
            int n3 = rem/(C*D);
            rem %= (C*D);
            int n5 = rem/D;
            int n7 = rem%D;

            int best = INT_MAX;
            for(int dig=2; dig<=9; dig++){
                int m2 = n2-e2[dig]; if(m2<0) m2=0;
                int m3 = n3-e3[dig]; if(m3<0) m3=0;
                int m5 = n5-e5[dig]; if(m5<0) m5=0;
                int m7 = n7-e7[dig]; if(m7<0) m7=0;
                int ni = idxOf(m2,m3,m5,m7);
                if(ni == st) continue;
                if(f[ni] != -1 && f[ni]+1 < best) best = f[ni]+1;
            }
            f[st] = best;
        }
    }

    for(int s=0;s<=maxSum;s++) free(buckets[s]);
    free(buckets);
    free(bucketCount);

    int n = (int)strlen(num);

    int zeroPos = n;
    for(int i=0;i<n;i++){
        if(num[i]=='0'){ zeroPos=i; break; }
    }

    int (*pref)[4] = (int(*)[4])malloc(sizeof(int)*4*(zeroPos+1));
    pref[0][0]=a; pref[0][1]=b; pref[0][2]=c; pref[0][3]=d;
    for(int i=0;i<zeroPos;i++){
        int dig = num[i]-'0';
        int m2 = pref[i][0]-e2[dig]; if(m2<0) m2=0;
        int m3 = pref[i][1]-e3[dig]; if(m3<0) m3=0;
        int m5 = pref[i][2]-e5[dig]; if(m5<0) m5=0;
        int m7 = pref[i][3]-e7[dig]; if(m7<0) m7=0;
        pref[i+1][0]=m2; pref[i+1][1]=m3; pref[i+1][2]=m5; pref[i+1][3]=m7;
    }

    if(zeroPos == n){
        if(pref[n][0]==0 && pref[n][1]==0 && pref[n][2]==0 && pref[n][3]==0){
            char *res = (char*)malloc(n+1);
            strcpy(res, num);
            free(pref); free(f);
            return res;
        }
    }

    int limit = zeroPos < n-1 ? zeroPos : n-1;

    for(int i=limit; i>=0; i--){
        int startD = (num[i]-'0') + 1;
        for(int dig=startD; dig<=9; dig++){
            int m2 = pref[i][0]-e2[dig]; if(m2<0) m2=0;
            int m3 = pref[i][1]-e3[dig]; if(m3<0) m3=0;
            int m5 = pref[i][2]-e5[dig]; if(m5<0) m5=0;
            int m7 = pref[i][3]-e7[dig]; if(m7<0) m7=0;
            int need = f[idxOf(m2,m3,m5,m7)];
            if(need != -1 && need <= n-1-i){
                int tailLen = n-1-i;
                char *res = (char*)malloc(n+1);
                memcpy(res, num, i);
                res[i] = (char)('0'+dig);
                greedyFill(m2,m3,m5,m7, tailLen, res+i+1);
                res[n] = '\0';
                free(pref); free(f);
                return res;
            }
        }
    }

    free(pref);

    int M = f[idxOf(a,b,c,d)];
    int L = (n+1 > M) ? (n+1) : M;

    char *res = (char*)malloc(L+1);
    greedyFill(a,b,c,d, L, res);
    res[L] = '\0';

    free(f);
    return res;
}