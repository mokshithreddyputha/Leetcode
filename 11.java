class Solution {
    public int maxArea(int[] height) {
        
        int len = height.length;

        int i=0;
        int j=len-1;
        int h,w;
        int max = 0;
        int area;
        boolean s;

        while(i<j){
            if(height[i] > height[j]){
                h = height[j];
                s = true;
            }else{
                h = height[i];
                s = false;
            }
            w = j-i;

            area = h * w;

            if(max < area){
                max = area;
            }
            
            if(s){
                j--;
            }else{
                i++;
            }
        }
        
        return max;
    }
}