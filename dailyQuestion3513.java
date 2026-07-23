class Solution {
    public int uniqueXorTriplets(int[] nums) {
        int n = nums.length;

        if (n < 3) return n;

        int bits = Integer.SIZE - Integer.numberOfLeadingZeros(n);
        return 1 << bits;
    }
}