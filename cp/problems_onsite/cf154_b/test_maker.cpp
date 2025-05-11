#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> // For std::shuffle
#include <random>    // For std::mt19937, std::uniform_int_distribution
#include <chrono>    // For seeding random number generator

// Modern C++ random number generation
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int random_int(int min_val, int max_val) {
    if (min_val > max_val) { // Ensure min_val <= max_val
        std::swap(min_val, max_val);
    }
    std::uniform_int_distribution<int> dist(min_val, max_val);
    return dist(rng);
}

// Generates a vector of random measurement values
std::vector<int> generate_random_measurements(int n, int min_val, int max_val) {
    std::vector<int> measurements(n);
    for (int i = 0; i < n; ++i) {
        measurements[i] = random_int(min_val, max_val);
    }
    return measurements;
}

// Writes the generated test case to the output file stream
void write_test_case_to_file(std::ofstream& fout, int n, const std::vector<int>& measurements) {
    fout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        fout << measurements[i] << (i == n - 1 ? "" : " ");
    }
    fout << std::endl;
}

// Creates a single test case file
void test_case_maker(int test_number) {
    std::string filename_base = "input";
    std::string filename = filename_base + (test_number < 10 ? "0" : "") + std::to_string(test_number) + ".txt";
    std::ofstream fout(filename);

    if (!fout.is_open()) {
        std::cerr << "Error: Failed to open file for writing: " << filename << std::endl;
        return; // Skip this test case if file cannot be opened
    }

    int n;
    std::vector<int> c;
    const int MIN_C_VAL = 1;
    const int MAX_C_VAL = 5000;
    const int MIN_N_VAL = 2;
    const int MAX_N_VAL = 100000;

    // Specific Test Cases
    if (test_number == 0) { // Example 1 from problem
        n = 6;
        c = {4, 5, 3, 8, 3, 7};
    } else if (test_number == 1) { // Example 2 from problem
        n = 4;
        c = {4, 3, 2, 4};
    } else if (test_number == 2) { // Min N (2), no removal needed
        n = MIN_N_VAL;
        c = {100, 150}; // 150 <= 2*100
    } else if (test_number == 3) { // Min N (2), 1 removal needed
        n = MIN_N_VAL;
        c = {100, 201}; // 201 > 2*100
    } else if (test_number == 4) { // All elements are the same
        n = random_int(5, 20);
        int val = random_int(MIN_C_VAL, MAX_C_VAL);
        c.assign(n, val);
    } else if (test_number == 5) { // Sorted, all fit criteria
        n = random_int(10, 30);
        c.resize(n);
        c[0] = random_int(MIN_C_VAL, MAX_C_VAL / 2 - 10); // Ensure space for growth
        for(int i = 1; i < n; ++i) {
            c[i] = random_int(c[i-1], std::min(MAX_C_VAL, c[0] * 2));
        }
        std::sort(c.begin(), c.end()); // Ensure sorted for this specific case logic
         // Verify all fit: max_val <= 2 * min_val
        if (!c.empty() && c.back() > 2 * c.front()) { // If not, regenerate a simple fitting case
            c.clear();
            int start_val = random_int(100,200);
            for(int i=0; i<n; ++i) c.push_back(start_val + i);
        }

    } else if (test_number == 6) { // Sorted, requires removal from the end
        n = random_int(10, 30);
        c.resize(n);
        int start_val = random_int(MIN_C_VAL, MAX_C_VAL / 3);
        for(int i = 0; i < n / 2; ++i) c[i] = start_val + i * random_int(1,5);
        for(int i = n / 2; i < n; ++i) c[i] = start_val * 2 + 50 + i * random_int(1,5); // Values likely too large
        std::sort(c.begin(), c.end());
    } else if (test_number == 7) { // Sorted, requires removal from the start
        n = random_int(10, 30);
        c.resize(n);
        int end_val = random_int(MAX_C_VAL / 2 + 10, MAX_C_VAL);
        for(int i = 0; i < n / 2; ++i) c[i] = end_val / 2 - 50 - (n/2 - i) * random_int(1,5); // Values likely too small
        for(int i = n / 2; i < n; ++i) c[i] = end_val - (n-i-1) * random_int(1,5);
        std::sort(c.begin(), c.end());
    } else if (test_number == 8) { // Max N, completely random values
        n = MAX_N_VAL;
        c = generate_random_measurements(n, MIN_C_VAL, MAX_C_VAL);
    } else if (test_number == 9) { // Max N, all values are small
        n = MAX_N_VAL;
        c = generate_random_measurements(n, MIN_C_VAL, MIN_C_VAL + 20);
    } else if (test_number == 10) { // Max N, all values are large
        n = MAX_N_VAL;
        c = generate_random_measurements(n, MAX_C_VAL - 20, MAX_C_VAL);
    } else if (test_number == 11) { // Max N, two distinct tight clusters
        n = MAX_N_VAL;
        c.clear();
        int mid_n = n / 2;
        for(int i = 0; i < mid_n; ++i) c.push_back(random_int(100, 150));
        for(int i = 0; i < n - mid_n; ++i) c.push_back(random_int(400, 450));
        std::shuffle(c.begin(), c.end(), rng);
    } else if (test_number == 12) { // Values that are close to the 2x boundary
        n = random_int(MAX_N_VAL / 2, MAX_N_VAL);
        c.clear();
        int base = random_int(MIN_C_VAL, MAX_C_VAL / 2 - 5); // Ensure base*2 is within MAX_C_VAL
        for(int i = 0; i < n; ++i) {
            if (i % 4 == 0) c.push_back(base);
            else if (i % 4 == 1) c.push_back(base * 2);
            else if (i % 4 == 2) c.push_back(random_int(base, std::min(MAX_C_VAL, base * 2 + 1))); // slightly over or at limit
            else c.push_back(random_int(std::max(MIN_C_VAL, base -1), base * 2)); // general vicinity
        }
        std::shuffle(c.begin(), c.end(), rng);
    }
    // General Random Cases
    else {
        if (test_number % 6 == 0 && test_number < 25) { // Occasional large N for general cases
             n = random_int(MAX_N_VAL / 2, MAX_N_VAL);
        } else if (test_number < 20) { // Medium N
             n = random_int(100, 2000);
        } else { // Smaller N
             n = random_int(MIN_N_VAL, 200);
        }
        c = generate_random_measurements(n, MIN_C_VAL, MAX_C_VAL);

        // Introduce a potentially optimal tight band of numbers
        if (n > 20 && test_number % 3 == 1) {
            int band_size = random_int(std::min(n, n / 4 + 5) , std::min(n, n / 2 + 5)); // Ensure band_size <= n
            int band_start_val = random_int(MIN_C_VAL, MAX_C_VAL - 100);
            int band_end_val = std::min(MAX_C_VAL, band_start_val + random_int(10, 50));
            for(int k=0; k < band_size; ++k) {
                if (!c.empty()) { // Ensure c is not empty before trying to access an element
                     c[random_int(0, c.size()-1)] = random_int(band_start_val, band_end_val);
                } else { // If c was empty (e.g. n was 0, though constraints say n>=2)
                    c.push_back(random_int(band_start_val, band_end_val));
                }
            }
        }
        std::shuffle(c.begin(), c.end(), rng);
    }

    write_test_case_to_file(fout, n, c);
    fout.close();
}

// Generates all test case files
void generate_all_test_cases(){
    const int TOTAL_TEST_CASES = 30; // Generate 30 test files (input00.txt to input29.txt)
    std::cout << "Generating " << TOTAL_TEST_CASES << " test files..." << std::endl;
    for(int i = 0; i < TOTAL_TEST_CASES; ++i){
        test_case_maker(i);
        if ((i + 1) % 5 == 0) {
            std::cout << "Generated " << (i + 1) << "/" << TOTAL_TEST_CASES << " files." << std::endl;
        }
    }
    std::cout << "Test file generation complete." << std::endl;
}

int main() {
    // The random number generator 'rng' is seeded globally when declared.
    generate_all_test_cases();
    return 0;
}
