class Solution {
    public int maxNumberOfFamilies(int n, int[][] reservedSeats) {

        HashMap<Integer, Integer> map = new HashMap<>();

        for(int[] seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            map.put(row, map.getOrDefault(row, 0) | (1 << s));
        }

        int count = (n - map.size()) * 2;

        for(int row : map.keySet()) {

            int r = map.get(row);

            boolean left = (r & (1 << 2)) == 0 &&
                           (r & (1 << 3)) == 0 &&
                           (r & (1 << 4)) == 0 &&
                           (r & (1 << 5)) == 0;

            boolean middle = (r & (1 << 4)) == 0 &&
                             (r & (1 << 5)) == 0 &&
                             (r & (1 << 6)) == 0 &&
                             (r & (1 << 7)) == 0;

            boolean right = (r & (1 << 6)) == 0 &&
                            (r & (1 << 7)) == 0 &&
                            (r & (1 << 8)) == 0 &&
                            (r & (1 << 9)) == 0;

            if(left && right) {
                count += 2;
            }
            else if(left || middle || right) {
                count++;
            }
        }

        return count;
    }
}