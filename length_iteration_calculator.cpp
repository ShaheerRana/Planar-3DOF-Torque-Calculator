#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;

// Search Parameters:
const double MAX_LENGTH = 1.0;
const double MIN_LENGTH = 0.3;
const double INCREMENT_LENGTH = 0.1;

// Position 1:
const double q3_1 = -M_PI/3;
const double cx1 = 0.75;
const double cy1 = 0.1;
// Position 2:
const double q3_2 = 0;
const double cx2 = 0.5;
const double cy2 = 0.5;
// Position 3:
const double q3_3 = M_PI/4;
const double cx3 = 0.2;
const double cy3 = 0.6;

// store max torque:
double min_t = 100000;
double min_l1 = 0;
double min_l2 = 0;
double min_l3 = 0;
double min_q1[3] = {0};
double min_q2[3] = {0};
double min_ax[3] = {0};
double min_ay[3] = {0};
double min_bx[3] = {0};
double min_by[3] = {0};
double min_torque[3] = {0};

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

double get_bx(double l3, double cx, double q3) {
    return cx - l3 * cos(q3);
}

double get_by(double l3, double cy, double q3) {
    return cy - l3 * sin(q3);
}

double get_ax(double l1, double q1) {
    return l1 * cos(q1); // note that q1 is in rad
}

double get_ay(double l1, double q1) {
    return l1 * sin(q1); // note that q1 is in rad
}

int main() {
    // iterate for values of l1, l2, and l3
    for (double l1 = MIN_LENGTH; l1 <= MAX_LENGTH; l1 += INCREMENT_LENGTH) {
        for (double l2 = MIN_LENGTH; l2 <= MAX_LENGTH; l2 += INCREMENT_LENGTH) {
            for (double l3 = MIN_LENGTH; l3 <= MAX_LENGTH; l3 += INCREMENT_LENGTH) {
                if (l1 + l2 + l3 >= 1) {
                    
                    double t_total = 0;  // store T value (T = sqrt(T1^2+T2^2+T3^2))
                    std::cout << "l1 = " << l1 << ", l2 = " << l2 << ", l3 = " << l3 << ":" << endl; // print length values

                    double bx[3] = {0};
                    double by[3] = {0};
                    double hyp[3] = {0};
                    double q1[3] = {0};
                    double q2[3] = {0};
                    double ax[3] = {0};
                    double ay[3] = {0};
                    double torque[3] = {0};

                    // iterate for the three positions
                    for (int i = 0; i < 3; i++) {
                        // Set Position (1, 2, or 3)
                        double cx = 0, cy = 0, q3 = 0; 
                        switch (i)
                        {
                        case 0: // position 1
                            cx = cx1;
                            cy = cy1;
                            q3 = q3_1;
                            break;                        
                        case 1: // position 2
                            cx = cx2;
                            cy = cy2;
                            q3 = q3_2;
                            break;
                        case 2: // position 3
                            cx = cx3;
                            cy = cy3;
                            q3 = q3_3;
                            break;
                        default:
                            cx = cx2;
                            cy = cy2;
                            q3 = q3_2;
                            break;
                        }
                        // determine all unknowns
                        bx[i] = get_bx(l3, cx, q3);
                        by[i] = get_by(l3, cx, q3);
                        hyp[i] = get_hypoteneus(bx[i], by[i]);
                        q1[i] = get_q1(angle_cosLaw(l1, hyp[i], l2), by[i], bx[i]);
                        q2[i] = get_q2(angle_cosLaw(l2, hyp[i], l1), by[i], bx[i]);
                        ax[i] = get_ax(l1, q1[i]);
                        ay[i] = get_ay(l1, q1[i]);

                        // determine moment on origin:
                        torque[i] = 9.81*((4*l1)*(0.5*ax[i]) + (2*l2)*(ax[i]+0.5*l2*cos(q2[i])) + (1*l3)*(cx-0.5*l3*cos(q3)) + 5*cx);
                        // store for T value:
                        t_total += torque[i] * torque[i];

                        // print more details
                        std::cout << "Position " << i << ": ";
                        std::cout << "q1 = " << q1[i] << ", q2 = " << q2[i];
                        std::cout << ", ax = " << ax[i] << ", ay = " << ay[i] << ", bx = " << bx[i] << ", by = " << by[i];
                        std::cout << ", T" << i << " = " << torque[i] << endl;
                    }
                    
                    // finalize T value:
                    t_total = sqrt(t_total);
                    std::cout << "T_total = " << t_total << endl;
                    // select smallest T:
                    if (abs(t_total) < abs(min_t))
                    {
                        min_t = t_total;
                        min_l1 = l1;
                        min_l2 = l2;
                        min_l3 = l3;
                        for (int i = 0; i < 3; i++) {
                            min_q1[i] = q1[i];
                            min_q2[i] = q2[i];
                            min_ax[i] = ax[i];
                            min_ay[i] = ay[i];
                            min_bx[i] = bx[i];
                            min_by[i] = by[i];
                            min_torque[i] = torque[i];
                        }
                    }
                }
            }
        }
    }
    std::cout << endl
              << "Search Parameters: " << MIN_LENGTH << " < L < " << MAX_LENGTH << ", delta l = " << INCREMENT_LENGTH
              << endl
              << "Min T value: " << min_t << endl;
    std::cout << "l1 = " << min_l1 << ", l2 = " << min_l2 << ", l3 = " << min_l3 << endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "Position " << i+1 << ": ";
        std::cout << "q1 = " << min_q1[i] << ", q2 = " << min_q2[i];
        std::cout << ", ax = " << min_ax[i] << ", ay = " << min_ay[i] << ", bx = " << min_bx[i] << ", by = " << min_by[i];
        std::cout << ", T" << i+1 << " = " << min_torque[i] << endl;
    }
}