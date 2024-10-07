#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <random> // for std::default_random_engine and std::shuffle
#include <ctime> // for std::time
using namespace std;

// Function to solve Cryptarithmetic puzzle
bool solveCryptarithmetic(const vector<string>& expressions, const string& resultExpression, unordered_map<char, int>& mapping) {
    vector<char> letters;
    
    // Collect all unique letters from the expressions and result expression
    for (const string& expression : expressions) {
        for (char c : expression) {
            if (find(letters.begin(), letters.end(), c) == letters.end()) {
                letters.push_back(c);
            }
        }
    }
    for (char c : resultExpression) {
        if (find(letters.begin(), letters.end(), c) == letters.end()) {
            letters.push_back(c);
        }
    }

    if (letters.size() > 10) {
        return false;  // More than 10 unique letters, no solution possible
    }

    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Shuffle the digits vector randomly
    unsigned seed = std::time(0);
    std::default_random_engine rng(seed);
    std::shuffle(digits.begin(), digits.end(), rng);

    do {
        unordered_map<char, int> currentMapping;
        for (size_t i = 0; i < letters.size(); ++i) {
            currentMapping[letters[i]] = digits[i];
        }

        int result = 0;
        for (const string& expression : expressions) {
            int num = 0;
            for (char c : expression) {
                num = num * 10 + currentMapping[c];
            }
            result += num;
        }

        int expectedResult = 0;
        for (char c : resultExpression) {
            expectedResult = expectedResult * 10 + currentMapping[c];
        }

        if (result == expectedResult) {
            mapping = currentMapping;
            return true;
        }
    } while (next_permutation(digits.begin(), digits.end()));

    return false;  // No solution found
}

int main() {
    int n;
    cout << "Enter the number of expressions: ";
    cin >> n;
    cout<<n<<endl;
    vector<string> expressions(n);

    for (int i = 0; i < n; ++i) {
        cout << "Enter expression " << i + 1 << ": ";
        cin >> expressions[i];
        cout<<expressions[i]<<endl;
    }

    string resultExpression;
    cout << "Enter result expression: ";
    cin >> resultExpression;
    cout<<resultExpression<<endl;
    unordered_map<char, int> solutionMapping;
    
    if (solveCryptarithmetic(expressions, resultExpression, solutionMapping)) {
        cout << "Solution found:" << endl;
        for (const auto& pair : solutionMapping) {
            cout << pair.first << " = " << pair.second << endl;
        }
    } else {
        cout << "No solution found." << endl;
    }
    
    return 0;
}
