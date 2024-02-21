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
    void insertion(std::map<std::string, double>, std::string, std::vector<std::map<std::string, double>>&, std::vector<std::string>&);
    void insertion_checkout(std::map<std::string, double>, std::string, std::vector<std::map<std::string, double>>&, std::vector<std::string>&);


    std::map<std::string, double> current_targets;
    std::string ct;
    std::vector<std::map<std::string, double>> finish, checkout;
    std::vector<std::string> finish_v, checkout_v;

    int countdown = 501, score=20;
    std::string prio[3] = {"12", "16", "20"};

    double diff[3] = {2322.576, 419.354, 258.064};
    std::string h[3] = {"", "D", "T"};

    std::vector<int> a = {170, 167, 164, 161, 160, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135,\
                   134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106,\
                   105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71,\
                   70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40};
    int no_checkout[8] = {170, 169, 168, 166, 165, 163, 162, 159};
};

#endif // DARTS_H_INCLUDED
