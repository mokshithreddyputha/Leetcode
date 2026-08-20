public class Solution {
    public int[] resultArray(int[] nums) {
        int []arr1 = new int[nums.length];
        int []arr2 = new int[nums.length];

        int j=1,k=1;
        arr1[0] = nums[0];
        arr2[0] = nums[1];

        for(int i=2;i<nums.length;i++){
            if(arr1[j-1] > arr2[k-1]){
                arr1[j++] = nums[i];
            }else{
                arr2[k++] = nums[i];
            }
        }

        int count = j+k;

        int[] result = new int[j+k];

        for(int q=0;q<j;q++){
            result[q] = arr1[q];
        }

        for(int w=0;w<k;w++){
            result[j+w] = arr2[w];
        }

        return result;

    }
} {
    
}
