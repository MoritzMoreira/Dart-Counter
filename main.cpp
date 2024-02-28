#include <iostream>
#include "darts.h"
#include <typeinfo>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <nlohmann/json.hpp>
#include <string>

int main(){
    counter c;
    std::cout<< c.countdown<<'\n';

//    nlohmann::json j;
//    std::vector<int> kf = {3,5,7};
//    j["test"] = kf;

    while (c.countdown != 0){
            c.enter_score();

            if (c.countdown <= 350){
                if (c.countdown > 170 || std::find(std::begin(c.no_checkout), std::end(c.no_checkout), c.countdown) != std::end(c.no_checkout)) {
                    c.checkout_loop(c.countdown);
                    std::cout<< "\t\nto get to checkout hit:\n";
                    c.print(c.checkout_v);
                }


                else {
                    c.finish_loop(c.countdown);
                    if (c.finish_v.size() == 1) { std::cout<< "\nfinish:\n\n";
                    }
                    else {std::cout<< "\nfinishes:\n";
                    }
                    c.print(c.finish_v);
                }
                std::cout<< std::string(45, '_')<<"\n\v";
            }
            else {
                std::cout<< "\t\t\tcan't finish\n\n";
            }
            c.finish_v = {};
            c.checkout_v = {};
        }
    endProgram:
    return 0;
}
