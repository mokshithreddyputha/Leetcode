class Solution {
    public boolean[] pathExistenceQueries(int n, int[] nums, int maxDiff, int[][] queries) {
        int [] neighbour = new int[nums.length];
        boolean []output = new boolean[queries.length];
        int component = 1;
        
        neighbour[0] = component;

        for(int i=1;i<nums.length;i++){
            if(nums[i] - nums[i-1] > maxDiff){
                component++;
            }
            neighbour[i] = component;
        }
       
        for(int j=0;j<queries.length;j++){
            int a = queries[j][0];
            int b = queries[j][1];
            
            if(neighbour[a] == neighbour[b]){
                output[j] = true;
            }else{
                output[j] = false;
            }
        }
        return output;
    }
}