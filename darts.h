#include <vector>
#include <iostream>
#include <map>

#ifndef DARTS_H_INCLUDED
#define DARTS_H_INCLUDED

class counter{
public:
    struct result{
        int countdown_i;
        std::map<std::string, double> current_targets_p;
        std::string ct_p;
    };
    result checkout_test(int, std::map<std::string, double>, std::string, int, int);
    void checkout_loop(int);
    void finish_loop(int);
    double diffSum(std::map<std::string, double>);
    void insertion(std::map<std::string, double>, std::string);
    void insertion_checkout(std::map<std::string, double>, std::string);


    std::map<std::string, double> current_targets;
    std::string ct;
    std::vector<std::map<std::string, double>> finish, checkout;
    std::vector<std::string> finish_v, checkout_v;

    int countdown = 501, score=20;
    std::string prio[3] = {"12", "16", "20"};

    double diff[3] = {2322.576, 419.354, 258.064};
    std::string h[3] = {"", "D", "T"};

    int no_checkout[8] = {170, 169, 168, 166, 165, 163, 162, 159};
    unsigned int limit = 10;

};

#endif // DARTS_H_INCLUDED
