#include <iostream>
#include <numeric> 
#include <sstream>
#include <string>
using namespace std;

class Rational {
public:
    Rational() {
        numer = 0;
        denom = 1;
    }

    Rational(int numerator, int denominator) {
        int gcd;
        int num_tmp = abs(numerator);
        int den_tmp = abs(denominator);
        while (num_tmp > 0 && den_tmp > 0) {

            if (num_tmp > den_tmp) {
                num_tmp %= den_tmp;
            }
            else {
                den_tmp %= num_tmp;
            }

        }

        gcd = num_tmp + den_tmp;
        if (gcd != 0) {
            numerator = numerator / gcd;
            denominator = denominator / gcd;
        }

        double res = 0;
        if (denominator != 0) {
            res = (double)numerator / (double)denominator;
        } else {           
            throw invalid_argument("Invalid argument");
        }
        if (res < 0) {
            numerator = 0 - abs(numerator);
            denominator = abs(denominator);
        }
        else if (res > 0) {
            numerator = abs(numerator);
            denominator = abs(denominator);
        }
        if (numerator == 0) {
            denominator = 1;
        }
        numer = numerator;
        denom = denominator;
    }

    int Numerator() const {
        return numer;
    }

    int Denominator() const {
        return denom;
    }

private:
    int numer;
    int denom;
};




bool operator==(const Rational& r1, const Rational& r2) {
    return ((r1.Numerator() == r2.Numerator()) && (r1.Denominator() == r2.Denominator()));

}

Rational operator+(const Rational& r1, const Rational& r2) {
    return  { r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator(), r1.Denominator() * r2.Denominator() };
}

Rational operator-(const Rational& r1, const Rational& r2) {
    return  { r1.Numerator() * r2.Denominator() - r2.Numerator() * r1.Denominator(), r1.Denominator() * r2.Denominator() };
}

Rational operator* (const Rational& r1, const Rational& r2) {
    return { r1.Numerator() * r2.Numerator(), r1.Denominator() * r2.Denominator() };
}

Rational operator/ (const Rational& r1, const Rational& r2) {
    if (r2.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    return { r1.Numerator() * r2.Denominator(), r1.Denominator() * r2.Numerator() };
}

istream& operator>> (istream& stream, Rational& r) {
    int num = 0;
    int den = 0;
    char razdelitel;
    if (stream >> num && stream >> razdelitel && stream >> den) {
        if (razdelitel == '/') { r = { num, den }; }
    }
    else {
        throw invalid_argument("Invalid argument");
    }
    return stream;
}

ostream& operator<< (ostream& stream, const Rational& r) {
    stream << r.Numerator() << '/' << r.Denominator();
    return stream;
}

bool operator< (const Rational& r1, const Rational& r2) {
    if (r1.Numerator() * r2.Denominator() - r1.Denominator() * r2.Numerator() < 0) {
        return true;
    }
    return false;
}

bool operator> (const Rational& r1, const Rational& r2) {
    if (r1.Numerator() * r2.Denominator() - r1.Denominator() * r2.Numerator() > 0) {
        return true;
    }
    return false;
}


bool operator!= (const Rational& r1, const Rational& r2) {
    return !(r1 == r2);
}

Rational execute(istream& element_operation_element) {
    Rational lhs, rhs;
    char operation;
    element_operation_element >> lhs;
    element_operation_element >> operation;
    element_operation_element >> rhs;
    if (operation == '+') {
        return lhs + rhs;
    }
    else if (operation == '-') {
        return lhs - rhs;
    }
    else if (operation == '*') {
        return lhs * rhs;
    }
    else { //if (operation == '/') 
        return lhs / rhs;
    }
    
}

int main() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    try {
        cout << execute(ss);
    }
    catch (exception& ex) {
        cout << ex.what();
    }
    return 0;
}