#include <iostream>
#include <fstream>
#include <vector>
#include "Polynomial.h"

using namespace std;

int main() {
    ifstream test_file("testnew.txt");
    ofstream output_file("output.txt");

    // Check if files are successfully opened
    if (!test_file) {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    if (!output_file) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    int test_index = 0;
    while (true) {
        int degree;
        if (!(test_file >> degree) || degree < 0) break; // Read the degree of the first polynomial

        vector<double> coeffs1(degree + 1);
        for (int i = 0; i <= degree; ++i) {
            test_file >> coeffs1[i]; // Read coefficients from constant to highest degree
        }
        Polynomial p1(coeffs1);

        // Read the degree of the second polynomial
        if (!(test_file >> degree)) break;

        vector<double> coeffs2(degree + 1);
        for (int i = 0; i <= degree; ++i) {
            test_file >> coeffs2[i]; // Read coefficients from constant to highest degree
        }
        Polynomial p2(coeffs2);

        // Perform operations
        Polynomial sum = p1 + p2;
        Polynomial diff = p1 - p2;
        Polynomial prod = p1 * p2;

        // Evaluate the first polynomial at x = 2
        double evaluation = p1.evaluate(2);

        // Test derivative and integral
        Polynomial deriv = p1.derivative();
        Polynomial integ = p1.integral();
        double definiteInteg = p1.integral(0, 1);

        // Find up to 2 real roots
        vector<double> roots = p1.findRoots();

        // Write results to output file
        output_file << "Test number " << ++test_index << ":\n";
        output_file << "p1: " << p1 << "\n";
        output_file << "p2: " << p2 << "\n";
        output_file << "Sum: " << sum << "\n";
        output_file << "Difference: " << diff << "\n";
        output_file << "Product: " << prod << "\n";
        output_file << "p1 evaluated at x = 2: " << evaluation << "\n";
        output_file << "Derivative of p1: " << deriv << "\n";
        output_file << "Integral of p1: " << integ << "\n";
        output_file << "Definite integral of p1 from 0 to 1: " << definiteInteg << "\n";
        output_file << "Roots of p1: ";
        for (double root : roots) {
            output_file << root << " ";
        }
        output_file << "\n\n";
    }

    // Close files
    test_file.close();
    output_file.close();

    return 0;
}
