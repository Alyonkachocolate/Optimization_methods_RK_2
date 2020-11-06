#ifndef RK_2_FIT_H
#define RK_2_FIT_H

#include <cmath>
#include <iomanip>
#include <iostream>

//структура для диапазона
struct Range {
    double Min;
    double Max;
};

// преобразования
static double int_to_double(unsigned int u, Range r);

static unsigned int double_to_int(double d, Range r);

class FIT {
private:
    double x_;
    double y_;
    Range r_x_;
    Range r_y_;

public:
    FIT() : x_(0), y_(0), r_x_({}), r_y_({}) {}

    FIT(double x, double y, Range r_x, Range r_y);

    double function() const;
    double get_x() const;
    double get_y() const;

    void set_x(double new_x);
    void set_y(double new_y);

    void info() const;

    bool operator<(const FIT &l) const;

    FIT &operator=(const FIT &l);

    // функция мутации
    void mutation();
};


#endif//RK_2_FIT_H
