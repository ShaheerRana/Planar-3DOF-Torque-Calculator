# Planar-3DOF-Torque-Calculator
This program was developed for design project 2 in MTE 119 at the Univeristy of Waterloo to optimize a planar 3 DOF robot for three positions.
It does so by iterating through each length configuration and calculating the link angles and torque generated around the base.

The precision of this program can be controlled by varying the length incrementation, however, doing so will increase the run time of the program.
The number of iterations can be calculated as: ((MAX_LENGTH - MIN_LENGTH)/INCREMENTATION)^3

This value can then be divided by the number of iterations your computer completes in a period of time to estimate the run time of the program.

Authors: Shaheer Rana, Ethan Kim, Patrick Kim
