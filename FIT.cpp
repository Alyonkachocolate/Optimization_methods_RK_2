#include "FIT.h"

static double int_to_double(unsigned int u, Range r) {
    return r.Min + (static_cast<double>(r.Max - r.Min) * u / UINT32_MAX);
}

static unsigned int double_to_int(double d, Range r) {
    return UINT32_MAX * (d - r.Min) / (r.Max - r.Min);
}

FIT::FIT(double x, double y, Range r_x, Range r_y) : x_(x), y_(y), r_x_(r_x), r_y_(r_y) {
    if (x_ < r_x.Min || x_ > r_x.Max || y_ < r_y.Min || y_ > r_y.Max) throw std::invalid_argument("");
}

double FIT::function() const {
    return -log(1 + x_ * x_ + y_ * y_);
}

double FIT::get_x() const {
    return x_;
}

double FIT::get_y() const {
    return y_;
}

void FIT::set_x(double new_x) {
    x_ = new_x;
}

void FIT::set_y(double new_y) {
    y_ = new_y;
}

void FIT::info() const {
    std::cout << std::fixed << std::setprecision(7) << "Dot: x = " << x_ << ", y = " << y_;
    std::cout << ". FIT = " << function() << std::endl;
}

bool FIT::operator<(const FIT &l) const {
    return function() < l.function();
}

FIT &FIT::operator=(const FIT &l) {
    x_ = l.x_;
    y_ = l.y_;
    return *this;
}
void FIT::mutation() {
    x_ = int_to_double(double_to_int(x_, r_x_) ^ (1u << (rand() % 24 + 8)), r_x_);
    y_ = int_to_double(double_to_int(y_, r_y_) ^ (1u << (rand() % 24 + 8)), r_y_);
}
