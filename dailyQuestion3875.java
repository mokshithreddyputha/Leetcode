class Solution {
    public boolean uniformArray(int[] nums1) {
        return true;
    }
}class Solution {
    public boolean uniformArray(int[] nums1) {

        int min = nums1[0];
        boolean hasOdd = false;

        for (int num : nums1) {

            min = Math.min(min, num);

            if (num % 2 == 1) {
                hasOdd = true;
            }
        }

        // If minimum is even and there is an odd number,
        // the minimum cannot change to odd.
        if (min % 2 == 0 && hasOdd) {
            return false;
        }

        return true;
    }
}