#include <iostream>
#include <cmath>

using namespace std;

const int q3a = -M_PI/3;
const int q3b = 0;
const int q3c = M_PI/4;
const double x1 = 0.75;
const double yo = 0.1;
const double x2 = 0.5;
const double y2 = 0.5;
const double x3 = 0.2;
const double y3 = 0.6;
const double MAX_LENGTH = 1.4;
const double MAX_TORQUE = 0.5;

double getL2 (int q1, int q2, double l3)
{
    double cy = y2 - l3*sin(q3b);
    double cx = x2 - l3*cos(q3b);
    return (cy-cx*tan(q1))/(-tan(q1)*cos(q2)+sin(q2));
}
double getL1 (int q1, int q2, double l2, double l3)
{
    double cx = x2 - l3*cos(q3b);
    return (cx-l2*cos(q2))/cos(q1);
}
double getTorque (int q1, int q2, double l1, double l2, double l3)
{
    return 5*x2 + l3/2*cos(q3b) + l2*cos(q2) + l1/2*cos(q1)*4;
}

int main()
{
    //if ( l1cosq1 + l2cosq1 + l3cosq3) == ltx);
    //if ( (ly1 + ly2 + ly3) == lty);

    double l1, l2, torque;
    for (int q1 = 0; q1 <= 360; q1++)
    {
        for (int q2 = 0; q2 <= 360; q2++)
        {
            for (double l3 = 0.01; l3 < MAX_LENGTH; l3+= 0.01)
            {
                l2 = getL2 (q1/180*M_PI, q2/180*M_PI, l3);
                l1 = getL1 (q1, q2/180*M_PI/180*M_PI, l2, l3);
                torque = getTorque (q1/180*M_PI, q2/180*M_PI, l1, l2, l3);
                if (l2*sin(q2/180*M_PI) - l1*sin(q1/180*M_PI) >= 0
                    && l1 <= MAX_LENGTH && l2 <= MAX_LENGTH && l3 <= MAX_LENGTH
                    && l1 >= -MAX_LENGTH && l2 >= -MAX_LENGTH && l3 >= -MAX_LENGTH
                    && l1 != 0 && l2 != 0 && l3 != 0
                    && torque < MAX_TORQUE)
                   // {
                
                        cout << l1 << " Q1: " << q1 << " L2: " << l2 << " Q2: " << q2 << " L3: " << l3 << " T: " << torque;
                    //}
                if (l2*sin(q2/180*M_PI) - l1*sin(q1/180*M_PI) >= 0
                    && l1 <= MAX_LENGTH && l2 <= MAX_LENGTH && l3 <= MAX_LENGTH
                    && l1 >= -MAX_LENGTH && l2 >= -MAX_LENGTH && l3 >= -MAX_LENGTH
                    && l1 != 0 && l2 != 0 && l3 != 0
                    && torque < MAX_TORQUE)
                    cout <<"\n______\n";
            }
        }
    }

    return 0;
}
               // if ((l1*cos(q1) + l2*cos(q1) + l3*cos(q3a)) == x1
                 //   && (l1*sin(q1) + l2*sin(q1) + l3*sin(q3a)) == ya)