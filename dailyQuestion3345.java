class Solution {
    public int smallestNumber(int n, int t) {

int k = 0;
        for(int i=n;i<=100;i++){
            int c = i;
            int product = 1;

            while(c >0){
                product *= c%10;
                c = c/10;
            }
            if(product % t == 0){
                k = i;
                break;
            }
        }
        return k;
    }
}