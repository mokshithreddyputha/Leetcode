class Solution {
    public long sumAndMultiply(int n) {
        
        int i = n;
        int x = 0;
        long f = 0;
        int d = String.valueOf(n).length();
        int[] digits = new int[d];
        int k = 0;

        while(i > 0){
            if(i % 10 == 0){
                i = i/10;
            } 
            else{
                digits[k] = i%10;
                i = i/10;
                k++;
            }
        }

        for(int j = 0;j<k;j++){
            x += digits[j];
        }
        
        for(int q=k-1;q> -1 ;q++){
            f = f*10 + digits[q];
        }
        long m = x * f;

        if(n == 0) return 0;

        return m;
    }
}