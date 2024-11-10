#include "Polynomial.h"

// Constructors
Polynomial::Polynomial() : coeffs(1, 0.0) {}

Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {
    // Remove trailing zeros to ensure correct degree
    while (coeffs.size() > 1 && coeffs.back() == 0.0) {
        coeffs.pop_back();
    }
}

Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

// Destructor
Polynomial::~Polynomial() {}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Arithmetic operators
Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] += other.coeffs[i];
    }
    return Polynomial(result);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
    }
    return Polynomial(result);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream& operator<<(ostream& out, const Polynomial& poly) {
    if (poly.coeffs.empty() || (poly.coeffs.size() == 1 && poly.coeffs[0] == 0.0)) {
        out << "0";
        return out;
    }
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0) out << "+";
            out << poly.coeffs[i];
            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;
            out << " ";
        }
    }
    return out;
}

// Utility functions
int Polynomial::degree() const {
    return coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    if (coeffs.empty()) return 0.0;
    double result = 0.0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i]; // Horner's method
    }
    return result;
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * q + Polynomial(vector<double>{coeffs[i]});
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial(vector<double>{0.0});
    vector<double> deriv(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        deriv[i - 1] = coeffs[i] * i;
    }
    return Polynomial(deriv);
}

Polynomial Polynomial::integral() const {
    vector<double> integ(coeffs.size() + 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        integ[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(integ);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial integ = integral();
    return integ.evaluate(x2) - integ.evaluate(x1);
}

vector<double> Polynomial::findRoots(double tolerance, int maxIter, double rangeMin, double rangeMax, double step) {
    vector<double> roots;
    if (degree() == 0 && coeffs[0] == 0.0) {
        return roots; // No roots for the zero polynomial
    }
    for (double guess = rangeMin; guess <= rangeMax; guess += step) {
        double x = guess;
        for (int i = 0; i < maxIter; ++i) {
            double fx = evaluate(x);
            double fpx = derivative().evaluate(x);
            if (abs(fx) < tolerance) break;
            if (fpx == 0) break; // Avoid division by zero
            x = x - fx / fpx;
        }
        bool isNewRoot = true;
        for (double root : roots) {
            if (abs(root - x) < tolerance) {
                isNewRoot = false;
                break;
            }
        }
        if (isNewRoot && abs(evaluate(x)) < tolerance) {
            roots.push_back(x);
        }
    }
    sort(roots.begin(), roots.end());
    return roots;
}

void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
    // Remove trailing zeros to ensure correct degree
    while (coeffs.size() > 1 && coeffs.back() == 0.0) {
        coeffs.pop_back();
    }
}

double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) return 0.0;
    return coeffs[degree];
}
