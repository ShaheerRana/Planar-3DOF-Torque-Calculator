#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;

// Search Parameters:
const double MAX_LENGTH = 1.0;
const double INCREMENT_LENGTH = 0.1;
const double START_LENGTH = 0.2;

// Position 1:
const int q3_1 = -M_PI/3;
const double cx1 = 0.75;
const double cy1 = 0.1;
// Position 2:
const int q3_2 = 0;
const double cx2 = 0.5;
const double cy2 = 0.5;
// Position 3:
const int q3_3 = M_PI/4;
const double cx3 = 0.2;
const double cy3 = 0.6;

// Set Position (1, 2, or 3)
const double cx = cx2;
const double cy = cy2;
const double q3 = q3_2;

// store max torque:
double min_torque = 100;
double min_l1 = 0;
double min_l2 = 0;
double min_l3 = 0;
double min_q1 = 0;
double min_q2 = 0;
double min_ax = 0;
double min_ay = 0;
double min_bx = 0;
double min_by = 0;

double rad(double deg) {
    return deg * M_PI / 180;
}

double get_hypoteneus(double a, double b) {
    return sqrt(a * a + b * b);
}

double angle_cosLaw(double a, double b, double c) {
    return acos((a*a+b*b-c*c)/(2*a*b));
}

double get_q1(double angle_o, double by, double bx) {
    return atan2(by, bx) + angle_o;
}

double get_q2(double angle_b, double by, double bx) {
    return atan2(by, bx) - angle_b;
}

double get_ax(double l1, double q1) {
    return l1 * cos(q1); // note that q1 is in rad
}

double get_ay(double l1, double q1) {
    return l1 * sin(q1); // note that q1 is in rad
}

double get_bx(double l3) {
    return cx - l3 * cos(rad(q3));
}

double get_by(double l3) {
    return cy - l3 * sin(rad(q3));
}

int main() {
    // iterate for values of l1, l2, and l3
    for (double l1 = START_LENGTH; l1 <= MAX_LENGTH; l1 += INCREMENT_LENGTH) {
        for (double l2 = START_LENGTH; l2 <= MAX_LENGTH; l2 += INCREMENT_LENGTH) {
            for (double l3 = START_LENGTH; l3 <= MAX_LENGTH; l3 += INCREMENT_LENGTH)
            {
                if (l1 + l2 + l3 >= 1) {
                    // determine all unknowns
                    double bx = get_bx(l3);
                    double by = get_by(l3);
                    double hyp = get_hypoteneus(bx, by);
                    double q1 = get_q1(angle_cosLaw(l1, hyp, l2), by, bx);
                    double q2 = get_q2(angle_cosLaw(l2, hyp, l1), by, bx);
                    double ax = get_ax(l1, q1);
                    double ay = get_ay(l1, q1);

                    // determine moment on origin:
                    double torque = 9.81*((4*l1)*(0.5*ax) + (2*l2)*(ax+(0.5*(bx-ax))) + (1*l3)*(ax+bx+0.5*(cx-bx)) + 5*cx);

                    // print results
                    cout << "l1 = " << l1 << ", l2 = " << l2 << ", l3 = " << l3
                         << ", q1 = " << q1 << ", q2 = " << q2;
                    cout << ", ax = " << ax << ", ay = " << ay
                         << ", bx = " << bx << ", by = " << by << ", hyp = " << hyp;
                    cout << ": M = " << torque << endl;
                    if (abs(torque) < abs(min_torque))
                    {
                        min_torque = torque;
                        min_l1 = l1;
                        min_l2 = l2;
                        min_l3 = l3;
                        min_q1 = q1;
                        min_q2 = q2;
                        min_ax = ax;
                        min_ay = ay;
                        min_bx = bx;
                        min_by = by;
                    }
                }
            }
        }
    }
    cout << endl
         << "Min Torque: " << min_torque << endl;
    cout << "l1 = " << min_l1 << ", l2 = " << min_l2 << ", l3 = " << min_l3
         << ", q1 = " << min_q1 << ", q2 = " << min_q2;
    cout << ", ax = " << min_ax << ", ay = " << min_ay
         << ", bx = " << min_bx << ", by = " << min_by;
}