#include <bits/stdc++.h>
#include <random>

using namespace std;

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Generate a sorted array with random values
vector<int> random_sorted_array(int n) {
    vector<int> arr(n);
    
    // Start with a small random value
    arr[0] = random_int(1, 100);
    
    // For each subsequent element, add a random increment
    for (int i = 1; i < n; i++) {
        // Use smaller increments to create interesting cases
        // where elements are close together
        int increment = random_int(0, 20);
        arr[i] = arr[i-1] + increment;
    }
    
    return arr;
}

void test_case_maker(int test_number) {
    string filename = "input" + string(test_number < 10 ? "0" : "") + to_string(test_number) + ".txt";
    ofstream fout(filename);

    if (!fout.is_open()) {
        cerr << "Failed to open file: " << filename << '\n';
        exit(1);
    }
    
    // Special cases for first few test cases
    if (test_number == 0) {
        // Minimum case: n=2
        fout << "1\n2\n1 2\n";
        fout.close();
        return;
    }
    else if (test_number == 1) {
        // Array with equal elements
        fout << "1\n5\n10 10 10 10 10\n";
        fout.close();
        return;
    }
    else if (test_number == 2) {
        // Array with large gap then small gaps
        fout << "1\n5\n1 100 101 102 103\n";
        fout.close();
        return;
    }
    
    // General cases
    int max_sum = 500;
    int remaining = max_sum;
    
    vector<int> sizes;
    // Ensure we don't exceed problem constraints
    while (remaining >= 2 && sizes.size() < 100) {
        int size = random_int(2, min(remaining, 30)); // Smaller n for variety
        sizes.push_back(size);
        remaining -= size;
    }
    
    int t = sizes.size();
    fout << t << endl;
    
    for (int i = 0; i < t; i++) {
        int n = sizes[i];
        fout << n << endl;
        
        vector<int> arr = random_sorted_array(n);
        
        // For some arrays, make values much larger
        if (random_int(1, 10) > 7) {
            for (int j = 0; j < n; j++) {
                arr[j] *= random_int(1000, 1000000);
            }
        }
        
        for (int j = 0; j < n; j++) {
            fout << arr[j] << (j == n-1 ? "\n" : " ");
        }
    }

    fout.close();
}

void test_maker(){
    int TEST_CASE_NUM = 25;
    for(int i = 0; i <= TEST_CASE_NUM; i++){
        test_case_maker(i);
    }
}

signed main() {
    srand(time(nullptr));
    test_maker();
    
    return 0;
}