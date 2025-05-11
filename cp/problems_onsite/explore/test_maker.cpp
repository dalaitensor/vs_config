#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <cstdlib> // for system()

using namespace std;

// Modern C++ random number generation
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

void test_case_maker(int test_number) {
    // Write files to testcase/input folder in the current directory.
    string folder = "testcase/input/";
    string filename = folder + "input" + (test_number < 10 ? "0" : "") + to_string(test_number) + ".txt";
    ofstream fout(filename);
    if(!fout.is_open()){
        cerr << "Error: Failed to open file for writing: " << filename << endl;
        return;
    }
    
    // Variables for input
    int N, M;
    long long T;
    vector<long long> A; // movement times from room i to i+1 (size = N-1)
    // bonus rooms: each pair (X, Y); with 1 < X < N, sorted by X.
    vector<int> bonusX;
    vector<long long> bonusY;
    
    // Specific small test cases:
    if(test_number == 0) {
        // Sample Input 1: Yes case
        // N=4, M=1, T=10; A: 5 7 5; bonus: (2,10)
        N = 4; M = 1; T = 10;
        A = {5, 7, 5};
        bonusX.push_back(2); bonusY.push_back(10);
    } else if(test_number == 1) {
        // Sample Input 2: No case
        N = 4; M = 1; T = 10;
        A = {10, 7, 5};
        bonusX.push_back(2); bonusY.push_back(10);
    } else if(test_number == 2) {
        // Minimal yes: 2 rooms, no bonus.
        N = 2; M = 0; T = 10;
        A = {5};
    } else if(test_number == 3) {
        // Minimal no: 2 rooms, T too small.
        N = 2; M = 0; T = 4;
        A = {5};
    } else if(test_number == 4) {
        // 5-room cave with one bonus making it possible.
        N = 5; M = 1; T = 10;
        A = {5, 7, 5, 5};
        bonusX.push_back(2); bonusY.push_back(10);
    } else if(test_number == 5) {
        // 5-room cave, no bonus, T exactly equals route cost.
        N = 5; M = 0;
        A = {3, 4, 5, 6};
        T = 3 + 4 + 5 + 6;
    } else if(test_number == 6) {
        // 7-room cave, two bonus rooms => Yes scenario.
        N = 7; M = 2; T = 15;
        A = {5, 6, 7, 8, 3, 4};
        bonusX = {3, 5};
        bonusY = {10, 5};
    } else if(test_number == 7) {
        // 7-room cave, two bonus rooms but still not enough time.
        N = 7; M = 2; T = 10;
        A = {5, 6, 7, 8, 3, 4};
        bonusX = {3, 5};
        bonusY = {3, 2};
    } else if(test_number == 8) {
        // Random small case: N between 5 and 8, maybe 1 bonus.
        N = random_int(5, 8);
        M = random_int(0, 1);
        T = random_ll(10, 50);
        A.resize(N-1);
        for (int i = 0; i < N-1; i++) {
            A[i] = random_ll(3, 15);
        }
        if(M > 0) {
            int room = random_int(2, N-1);
            bonusX.push_back(room);
            bonusY.push_back(random_ll(5, 20));
        }
    } else if(test_number == 9) {
        // Random small case where bonuses nearly compensate cost.
        N = random_int(6, 10);
        M = random_int(1, 2);
        T = random_ll(10, 30);
        A.resize(N-1);
        for (int i = 0; i < N-1; i++) {
            A[i] = random_ll(5, 15);
        }
        vector<int> rooms;
        for (int r = 2; r < N; r++) rooms.push_back(r);
        std::shuffle(rooms.begin(), rooms.end(), rng);
        for (int i = 0; i < M; i++) {
            bonusX.push_back(rooms[i]);
            bonusY.push_back(random_ll(5, 15));
        }
        sort(bonusX.begin(), bonusX.end());
    } 
    // Big N test cases
    else if(test_number == 15) {
        // Big N test: N near 10^5, no bonuses.
        N = random_int(50000, 100000);
        M = 0;
        A.resize(N-1);
        long long totalCost = 0;
        for (int i = 0; i < N-1; i++) {
            A[i] = random_ll(1, 1000);
            totalCost += A[i];
        }
        // Set T to be totalCost + a random extra time (so Takahashi can reach room N)
        T = totalCost + random_ll(0, 1000);
    } else {
        // Big N test with several bonuses inserted.
        N = random_int(50000, 100000);
        // Choose M between 0 and, say, 100 (but not exceeding N-2)
        M = random_int(0, min(100, N-2));
        A.resize(N-1);
        long long totalCost = 0;
        for (int i = 0; i < N-1; i++) {
            A[i] = random_ll(1, 1000);
            totalCost += A[i];
        }
        // Set T so that without bonuses it might not suffice.
        T = totalCost - random_ll(0, 5000);
        // Choose M distinct bonus indices in 2..N-1.
        vector<int> roomIndices;
        for (int i = 2; i < N; i++) roomIndices.push_back(i);
        std::shuffle(roomIndices.begin(), roomIndices.end(), rng);
        for (int i = 0; i < M; i++) {
            bonusX.push_back(roomIndices[i]);
            bonusY.push_back(random_ll(1, 10000));
        }
        sort(bonusX.begin(), bonusX.end());
    } 
    
    // Write output:
    fout << N << " " << M << " " << T << "\n";
    for (int i = 0; i < (int)A.size(); i++) {
        fout << A[i] << (i + 1 == A.size() ? "\n" : " ");
    }
    for (int i = 0; i < M; i++) {
        fout << bonusX[i] << " " << bonusY[i] << "\n";
    }
    
    fout.close();
}

void generate_all_test_cases(){
    // Ensure the output folder exists (Mac command)
    system("mkdir -p testcase/input");
    
    const int TOTAL_TEST_CASES = 20;
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