class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        string first = "";
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            first.append(freq[i] / 2, 'a' + i);
            if (freq[i] % 2)
                middle = 'a' + i;
        }

        string second = first;
        reverse(second.begin(), second.end());

        if (middle)
            return first + middle + second;
        return first + second;
    }
};