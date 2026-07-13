#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {

        vector<int> result;
        string digits = "123456789";

        for (int len = 2; len <= 9; len++) {
            for (int start = 0; start + len <= 9; start++) {

                int num = stoi(digits.substr(start, len));

                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }

        return result;
    }
};

int main() {

    int low = 100;
    int high = 13000;

    Solution obj;

    vector<int> result = obj.sequentialDigits(low, high);

    for (int num : result) {
        cout << num << " ";
    }

    cout << endl;

    return 0;
}