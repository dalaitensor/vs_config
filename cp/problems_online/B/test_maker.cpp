#include <bits/stdc++.h>
#include <random>

using namespace std;

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
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
        // Minimum case: n=1, k=1
        fout << "1 1\n100\n10\n";
        fout.close();
        return;
    }
    else if (test_number == 1) {
        // Simple case with 3 engineers where all will work
        fout << "3 10\n100 100 100\n5 8 10\n";
        fout.close();
        return;
    }
    else if (test_number == 2) {
        // Case where some won't work (last engineer has b too high)
        fout << "3 10\n50 50 50\n10 20 60\n";
        fout.close();
        return;
    }
    else if (test_number == 3) {
        // Large k case
        fout << "5 1000\n1000 2000 1500 3000 2500\n1 2 3 4 5\n";
        fout.close();
        return;
    }
    else if (test_number == 4) {
        // Case where all engineers have same values
        fout << "5 100\n1000 1000 1000 1000 1000\n10 10 10 10 10\n";
        fout.close();
        return;
    }
    
    // General cases
    int n = random_int(1, 1000); // Smaller n for variety
    int k = random_int(1, 1000000);
    
    fout << n << " " << k << endl;
    
    // Generate bonuses a_i
    for (int i = 0; i < n; i++) {
        // Mix of small and large bonuses
        int bonus;
        if (random_int(1, 10) > 7) {
            bonus = random_int(10000, 1000000000);
        } else {
            bonus = random_int(10, 10000);
        }
        fout << bonus << (i == n-1 ? "\n" : " ");
    }
    
    // Generate work values b_i
    for (int i = 0; i < n; i++) {
        // Mix of engineers with different valuations
        int work_value;
        if (random_int(1, 10) > 8) {
            // Some engineers value work highly
            work_value = random_int(500, 1000);
        } else if (random_int(1, 10) > 5) {
            // Medium valued work
            work_value = random_int(50, 499);
        } else {
            // Low valued work
            work_value = random_int(1, 49);
        }
        fout << work_value << (i == n-1 ? "\n" : " ");
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