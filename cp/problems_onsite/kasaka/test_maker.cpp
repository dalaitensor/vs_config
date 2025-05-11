#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <cstdlib> // for system()
using namespace std;

// Initialize random engine
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int random_int(int min_val, int max_val) {
    if(min_val > max_val) swap(min_val, max_val);
    std::uniform_int_distribution<int> dist(min_val, max_val);
    return dist(rng);
}

long long random_ll(long long min_val, long long max_val) {
    if(min_val > max_val) swap(min_val, max_val);
    std::uniform_int_distribution<long long> dist(min_val, max_val);
    return dist(rng);
}

// Generate a random string of given length that does not start or end with 'a'
string generate_body(int len) {
    string s;
    s.resize(len);
    for(int i = 0; i < len; i++) {
        // letters from 'b' to 'z'
        s[i] = 'b' + random_int(0, 24);
    }
    return s;
}

// Construct S = (prefix_a) + (body) + (suffix_a)
// The counts satisfy: For Yes-case, suffix >= prefix; for No-case, suffix < prefix.
string construct_string(int prefixCount, int bodyLen, int suffixCount) {
    string s;
    s.append(prefixCount, 'a');
    s += generate_body(bodyLen);
    s.append(suffixCount, 'a');
    return s;
}

void test_case_maker(int test_number) {
    // Write file to testcase/input folder in the current directory.
    string folder = "testcase/input/";
    string filename = folder + "input" + (test_number < 10 ? "0" : "") + to_string(test_number) + ".txt";
    ofstream fout(filename);
    if(!fout.is_open()){
        cerr << "Error: Failed to open file for writing: " << filename << endl;
        return;
    }
    
    string S;
    // Fixed small test cases.
    if(test_number == 0) {
        // Sample Input 1: "kasaka" -> Yes (adding one 'a' forms "akasaka")
        S = "kasaka";
    } else if(test_number == 1) {
        // Sample Input 2: "atcoder" -> No
        S = "atcoder";
    } else if(test_number == 2) {
        // Sample Input 3: "php" -> Yes (already a palindrome)
        S = "php";
    } else if(test_number == 3) {
        // Single letter
        S = "b";
    } else if(test_number == 4) {
        // Already palindrome (no extra a needed)
        S = "racecar";
    }
    // For further test cases, alternate between Yes and No.
    else {
        // Decide length (body length + prefix + suffix).
        // For larger test cases, use up to 10^6 characters.
        int totalLength;
        if(test_number >= 11)
            totalLength = random_int(500000, 1000000);
        else
            totalLength = random_int(10, 100);
            
        // Determine body length.
        // Ensure body length is at least 1.
        int minBody = 1;
        int bodyLen = random_int(minBody, max( minBody, totalLength/3 ));
        int remaining = totalLength - bodyLen;
        // Split remaining between prefix and suffix.
        // For a "Yes" case (even test_number): suffixCount >= prefixCount.
        // For a "No" case (odd test_number): suffixCount < prefixCount.
        int prefixCount, suffixCount;
        if(test_number % 2 == 0) {
            // Yes-case: pick prefixCount between 0 and remaining/2
            prefixCount = random_int(0, remaining/2);
            suffixCount = remaining - prefixCount; // will be >= prefixCount
        } else {
            // No-case: force more a's at front.
            if(remaining > 0) {
                // choose prefixCount greater than half of remaining
                prefixCount = random_int(remaining/2 + 1, remaining);
                suffixCount = remaining - prefixCount; // then suffix < prefix
            } else {
                prefixCount = 0;
                suffixCount = 0;
            }
        }
        S = construct_string(prefixCount, bodyLen, suffixCount);
    }
    
    fout << S;
    fout.close();
}

void generate_all_test_cases(){
    // Ensure the output folder exists (Mac command)
    system("mkdir -p testcase/input");
    
    const int TOTAL_TEST_CASES = 25;
    cout << "Generating " << TOTAL_TEST_CASES << " test files..." << endl;
    for(int i = 0; i < TOTAL_TEST_CASES; i++){
        test_case_maker(i);
        if ((i+1) % 5 == 0 || i == TOTAL_TEST_CASES - 1)
            cout << "Generated " << (i+1) << "/" << TOTAL_TEST_CASES << " files." << endl;
    }
    cout << "Test file generation complete." << endl;
}

int main(){
    generate_all_test_cases();
    return 0;
}