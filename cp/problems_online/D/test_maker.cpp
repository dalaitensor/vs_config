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
    
    int n = random_int(1, 1000);
    fout << n << endl;
    
    fout.close();
}

void test_maker(){
    int TEST_CASE_NUM = 56;
    for(int i = 0; i <= TEST_CASE_NUM; i++){
        test_case_maker(i);
    }
}

signed main() {
    srand(time(nullptr));
    test_maker();
    
    return 0;
}