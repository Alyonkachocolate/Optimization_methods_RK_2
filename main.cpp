#include "FIT.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <vector>

// случайное дробное число
double Random() {
    std ::random_device rd;
    std ::mt19937 gen(rd());
    std ::uniform_real_distribution<> dis(-2.0, std ::nextafter(2, std ::numeric_limits<double>::max()));
    return dis(gen);
}

int main() {
    srand(time(0));
    // Задаём изначальную популяцию
    // Из условия D = [-2,2] x [-2,2]

    std::cout << "Изначальная популяция (№0)" << std::endl;
    Range r = {-2, 2};
    std::vector<FIT> dots;
    for (size_t i = 0; i < 4; i++) {
        FIT dot(Random(), Random(), r, r);
        dots.push_back(dot);
        dot.info();
    }
    std::cout << "_______________________________________________" << std::endl;

    size_t N = 100;
    for (size_t i = 0; i < N; ++i) {
        std::cout << "Полученная популяция №" << i + 1 << ":" << std::endl;

        // селекция
        sort(dots.begin(), dots.end());// по возрастанию

        // скрещивание
        FIT best = dots.at(3);
        FIT crossover_1(best.get_x(), dots.at(2).get_y(), r, r),
                crossover_2(dots.at(2).get_x(), best.get_y(), r, r),
                crossover_3(best.get_x(), dots.at(1).get_y(), r, r),
                crossover_4(dots.at(1).get_x(), best.get_y(), r, r);

        // мутация (вероятность - 20%)
        size_t t = rand() % 100;
        if (t < 20)
            crossover_1.mutation();
        t = rand() % 100;
        if (t < 20)
            crossover_2.mutation();
        t = rand() % 100;
        if (t < 20)
            crossover_3.mutation();
        t = rand() % 100;
        if (t < 20)
            crossover_4.mutation();

        if (i < 10 || i == N - 1) {
            crossover_1.info();
            crossover_2.info();
            crossover_3.info();
            crossover_4.info();
        }

        double F_max = (std::max(std::max(crossover_1, crossover_2), std::max(crossover_1, crossover_2))).function();

        double F_sr = (crossover_1.function() + crossover_2.function() + crossover_3.function() + crossover_4.function()) / 4.0;

        std::cout << "FIT наибольшее = " << F_max << std::endl;
        std::cout << "FIT среднее = " << F_sr << std::endl;

        if (F_sr == F_max) std::cout << "@@@FIT наибольшее = FIT среднее" << std::endl;

        // записываем новую популяцию
        dots.clear();
        dots.push_back(crossover_1);
        dots.push_back(crossover_2);
        dots.push_back(crossover_3);
        dots.push_back(crossover_4);
        std::cout << "_______________________________________________" << std::endl;
    }

    return 0;
}