class Solution {
    public boolean isPalindrome(int x) {
        if(x < 0){
            return false;
        }
        if(x%10 == 0 && x != 0){
            return false;
        }
        if(x == 0){
            return true;
        }
        int rev = 0;
        int original = x;

        while(x > 0){
            int digit = x%10;
            rev = rev*10 + digit;
            x = x/10;
        }

        if( original == rev){
            return true;
        }
        else{
            return false;
        }
    }
}