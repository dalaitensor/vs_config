#include <bits/stdc++.h>
#include <random>

using namespace std;

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

vector<int> random_permutation(int n) {
    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        perm[i] = i + 1;
    }
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(perm.begin(), perm.end(), g);
    
    return perm;
}

void test_case_maker(int test_number) {
    string filename = "input" + string(test_number < 10 ? "0" : "") + to_string(test_number) + ".txt";
    ofstream fout(filename);

    if (!fout.is_open()) {
        cerr << "Failed to open file: " << filename << '\n';
        exit(1);
    }
    int max_sum = 5000;
    int remaining = max_sum;
    
    vector<int> sizes;
    while (remaining >= 4 && sizes.size() < 1000) {
        int size = random_int(4, min(remaining, 5000));
        sizes.push_back(size);
        remaining -= size;
    }
    
    int t = sizes.size();
    fout << t << endl;
    
    for (int i = 0; i < t; i++) {
        int n = sizes[i];
        fout << n << endl;
        
        vector<int> perm = random_permutation(n);
        for (int j = 0; j < n; j++) {
            fout << perm[j] << (j == n-1 ? "\n" : " ");
        }
    }

    fout.close();
}

void test_maker(){
    int TEST_CASE_NUM = 32;
    for(int i = 0; i <= TEST_CASE_NUM; i++){
        test_case_maker(i);
    }
}

signed main() {
    srand(time(nullptr));
    test_maker();
    
    return 0;
}