#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>       // For std::mt19937, std::uniform_int_distribution
#include <chrono>       // For seeding random number generator
#include <cmath>        // For std::pow, std::sqrt (though we'll use squared distances)
#include <algorithm>    // For std::min, std::max if needed

// Modern C++ random number generation
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

long long random_long(long long min_val, long long max_val) {
    if (min_val > max_val) {
        std::swap(min_val, max_val);
    }
    std::uniform_int_distribution<long long> dist(min_val, max_val);
    return dist(rng);
}

struct Point {
    long long x, y;
};

// Calculates squared Euclidean distance
long long distSq(Point p1, Point p2) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

// Checks if three points are collinear
// (y2-y1)*(x3-x2) == (y3-y2)*(x2-x1)
bool are_collinear(Point p1, Point p2, Point p3) {
    // To avoid overflow with large coordinates, ensure intermediate products fit long long
    // (p2.y - p1.y) * (p3.x - p2.x) - (p3.y - p2.y) * (p2.x - p1.x) == 0
    // This can be written as: p1.x(p2.y-p3.y) + p2.x(p3.y-p1.y) + p3.x(p1.y-p2.y) == 0 (Area formula)
    // Max value of a term like p1.x * (p2.y - p3.y) is 10^9 * 2*10^9 = 2*10^18. Sum of 3 such terms can be 6*10^18. Fits in long long.
    return (p2.y - p1.y) * (p3.x - p2.x) == (p3.y - p2.y) * (p2.x - p1.x);
}


void generate_distinct_points(Point& p1, Point& p2, Point& p3, long long min_coord = -1000000000LL, long long max_coord = 1000000000LL) {
    p1.x = random_long(min_coord, max_coord);
    p1.y = random_long(min_coord, max_coord);
    do {
        p2.x = random_long(min_coord, max_coord);
        p2.y = random_long(min_coord, max_coord);
    } while (p1.x == p2.x && p1.y == p2.y);
    do {
        p3.x = random_long(min_coord, max_coord);
        p3.y = random_long(min_coord, max_coord);
    } while ((p1.x == p3.x && p1.y == p3.y) || (p2.x == p3.x && p2.y == p3.y));
}

void test_case_maker(int test_number) {
    std::string filename_base = "input";
    std::string filename = filename_base + (test_number < 10 ? "0" : "") + std::to_string(test_number) + ".txt";
    std::ofstream fout(filename);

    if (!fout.is_open()) {
        std::cerr << "Error: Failed to open file for writing: " << filename << std::endl;
        return;
    }

    Point a, b, c;
    long long R_coord_limit = 1000000000LL;
    long long small_coord_limit = 100LL;
    long long mid_coord_limit = 500000000LL;


    if (test_number == 0) { // Example 1: Yes
        a = {0, 1}; b = {1, 1}; c = {1, 0};
    } else if (test_number == 1) { // Example 2: No (collinear)
        a = {1, 1}; b = {0, 0}; c = {1000, 1000};
    } else if (test_number == 2) { // Yes: 90-degree rotation around origin
        long long R = random_long(1, small_coord_limit);
        a = {R, 0}; b = {0, R}; c = {-R, 0};
    } else if (test_number == 3) { // No: Collinear, dist(AB) == dist(BC)
        a = {random_long(-small_coord_limit, small_coord_limit), random_long(-small_coord_limit, small_coord_limit)};
        b = {a.x + random_long(1, small_coord_limit), a.y + random_long(1, small_coord_limit)};
        c = {b.x + (b.x - a.x), b.y + (b.y - a.y)}; // c = 2b - a
    } else if (test_number == 4) { // No: Collinear, dist(AB) != dist(BC)
        a = {random_long(-small_coord_limit, small_coord_limit), random_long(-small_coord_limit, small_coord_limit)};
        long long dx1 = random_long(1, small_coord_limit/2); // Ensure dx1, dy1 are not both 0
        long long dy1 = random_long(0, small_coord_limit/2);
        if (dx1 == 0 && dy1 == 0) dy1 = 1;
        b = {a.x + dx1, a.y + dy1};
        long long k = random_long(2,3); // k=1 makes c=b, k=0 makes c=a (if relative to a)
                                        // Here c = a + k*(b-a). If k=2, c=2b-a (dist equal). So k=3,4...
        if (random_long(0,1)) k = random_long(-3, -1); // other side
        c = {a.x + k * dx1, a.y + k * dy1};
    } else if (test_number == 5) { // No: Non-collinear, dist(AB) != dist(BC)
        do {
            generate_distinct_points(a,b,c, -small_coord_limit, small_coord_limit);
        } while (are_collinear(a,b,c) || distSq(a,b) == distSq(b,c));
    } else if (test_number == 6) { // Yes: Non-collinear, dist(AB) == dist(BC), large coordinates
        long long px = random_long(-mid_coord_limit, mid_coord_limit);
        long long py = random_long(-mid_coord_limit, mid_coord_limit);
        long long R = random_long(1, mid_coord_limit -100); // Ensure R is not too large to overflow
        a = {px + R, py};
        b = {px, py + R};
        c = {px - R, py};
    } else if (test_number == 7) { // Yes: a=(0,0), b=(x,y), c=(x-y, y+x) or (x+y, y-x)
        a = {0,0};
        b = {random_long(1, small_coord_limit), random_long(1, small_coord_limit)};
        if(random_long(0,1)) { // Rotate (bx,by) by +90 deg to get vector bc
            c = {b.x - b.y, b.y + b.x};
        } else { // Rotate (bx,by) by -90 deg to get vector bc
            c = {b.x + b.y, b.y - b.x};
        }
    } else if (test_number == 8) { // No: Collinear, points on an axis
        long long start_x = random_long(-small_coord_limit, small_coord_limit);
        long long step_x = random_long(1, small_coord_limit/2);
        if (random_long(0,1)) step_x *= -1;
        long long common_y = random_long(-small_coord_limit, small_coord_limit);
        a = {start_x, common_y};
        b = {start_x + step_x, common_y};
        c = {start_x + 2 * step_x, common_y}; // dist(AB) == dist(BC)
    } else if (test_number == 9) { // Yes: Max coordinate values
        long long R = R_coord_limit;
        a = {R, 0}; b = {0, R}; c = {-R, 0};
        if (random_long(0,1)) { // Shift all by some offset
            long long off_x = random_long(-R_coord_limit/2, R_coord_limit/2 - R); // ensure still in bounds
            long long off_y = random_long(-R_coord_limit/2, R_coord_limit/2 - R);
             if (R > R_coord_limit/2) {off_x=0; off_y=0;} // if R is too big, no shift
            a.x += off_x; a.y += off_y;
            b.x += off_x; b.y += off_y;
            c.x += off_x; c.y += off_y;
        }
    } else if (test_number == 10) { // No: Max coordinate values, collinear
        a = {0,0};
        b = {R_coord_limit/2, R_coord_limit/2};
        c = {R_coord_limit, R_coord_limit};
    } else if (test_number == 11) { // Yes: Min coordinate values (non-zero R)
        long long R = 1;
        a = {R, 0}; b = {0, R}; c = {-R, 0};
    } else if (test_number == 12) { // No: Min coordinate values, collinear
        a = {0,0}; b = {1,1}; c = {2,2};
    } else if (test_number == 13) { // Yes: Thin triangle, dists equal
        long long L = random_long(small_coord_limit, small_coord_limit*2);
        long long eps = random_long(1,5);
        a = {0,0}; b = {L, eps}; c = {0, 2*eps};
    } else if (test_number == 14) { // No: Thin triangle, dists unequal
        long long L = random_long(small_coord_limit, small_coord_limit*2);
        long long eps1 = random_long(1,5);
        long long eps2 = random_long(eps1+1, eps1+5); // ensure different y for c
        a = {0,0}; b = {L, eps1}; c = {0, eps1 + eps2}; // c.y is different enough
    } else if (test_number == 15) { // Yes: Points on axes forming right angle at b
        long long val1 = random_long(1, small_coord_limit);
        long long val2 = random_long(1, small_coord_limit);
        a = {val1, 0}; b = {0,0}; c = {0, val2};
        // This makes distSq(a,b) = val1^2, distSq(b,c) = val2^2. Need val1=val2.
        val2 = val1;
        c = {0, val2};
    }
    // General random cases for remaining tests
    else if (test_number < 20) { // Yes, random non-collinear, equal dist
        long long px = random_long(-mid_coord_limit, mid_coord_limit);
        long long py = random_long(-mid_coord_limit, mid_coord_limit);
        long long R = random_long(1, mid_coord_limit / 2); // R not too large
        
        // Generate a random angle-like transformation for b and c from a
        // To ensure integer coords and equal dists, use rotation idea
        long long dx = random_long(-R, R);
        long long dy_abs_sq = R*R - dx*dx;
        long long dy = static_cast<long long>(std::sqrt(dy_abs_sq));
        if (dy*dy != dy_abs_sq) { // dx makes R*R - dx*dx not a perfect square, retry with simpler
            dx = R; dy = 0; // simple case if sqrt fails
            if (random_long(0,1)) { dx=0; dy=R;}
        }
        if (random_long(0,1)) dy *= -1;

        Point p_a = {px, py}; // Center of rotation
        a = {p_a.x + dx, p_a.y + dy}; // Point 'a' on circle

        // Rotate (dx, dy) by 90 deg to get (ndx, ndy) for vector AB
        long long ndx = -dy;
        long long ndy = dx;
        if (random_long(0,1)) { ndx = dy; ndy = -dx; } // other 90 deg rotation

        b = {a.x + ndx, a.y + ndy}; // This makes dist(P,a) != dist(P,b)
                                    // This construction is not P, R, theta.

        // Simpler: P is center, a,b,c on circle. Angle aPb = bPc.
        // Use the (P,R, 90deg rotation) as a template
        a = {px + R, py};
        b = {px, py + R};
        c = {px - R, py};
        // Randomly swap axes or signs to vary
        if(test_number % 3 == 1) { b = {px + R*random_long(0,1), py + R*random_long(0,1)}; /* could make b=a or b on axis*/ }
        // Ensure distinctness if modified heavily
        if ((a.x == b.x && a.y == b.y) || (b.x == c.x && b.y == c.y) || (a.x == c.x && a.y == c.y)) {
             a = {px + R, py}; b = {px, py + R}; c = {px - R, py}; // revert to safe
        }


    } else { // No, general random points, likely non-collinear and unequal distances
        do {
            generate_distinct_points(a,b,c);
        } while (are_collinear(a,b,c) && distSq(a,b) == distSq(b,c)); // Avoid accidental "Yes" for random
                                                                    // Or rather, just generate random and let the properties fall where they may
        generate_distinct_points(a,b,c); // Most random points will be "No"
    }


    fout << a.x << " " << a.y << " "
         << b.x << " " << b.y << " "
         << c.x << " " << c.y << std::endl;

    fout.close();
}

void generate_all_test_cases() {
    const int TOTAL_TEST_CASES = 31; // Generate 25 test files
    std::cout << "Generating " << TOTAL_TEST_CASES << " test files..." << std::endl;
    for (int i = 0; i < TOTAL_TEST_CASES; ++i) {
        test_case_maker(i);
        if ((i + 1) % 5 == 0 || i == TOTAL_TEST_CASES - 1) {
            std::cout << "Generated " << (i + 1) << "/" << TOTAL_TEST_CASES << " files." << std::endl;
        }
    }
    std::cout << "Test file generation complete." << std::endl;
}

int main() {
    generate_all_test_cases();
    return 0;
}
