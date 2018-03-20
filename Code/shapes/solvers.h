#ifndef SOLVERS_H_
#define SOLVERS_H_

class Solvers
{
    public:
        // Solve quadratic function
        // return false if no solution
        // x0 <= x1
        // uses pass by reference (hence the &)
        static bool quadratic(double a, double b, double c,
                              double &x0, double &x1);
};

#endif
