#include <iostream>
#include "darts.h"
#include <typeinfo>
#include <fstream>
#include <iterator>
#include <algorithm>

int main(){
    counter c;
    std::cout<< c.countdown<<'\n';

    while (c.countdown != 0){
        std::cout << "enter score: ";
        std::cin>> c.score;
        if (c.countdown - c.score >= 2){
            c.countdown -= c.score;
            std::cout<< "-> -> -> "<< c.countdown;

            if (c.countdown <= 350){
                if (c.countdown > 170 || std::find(std::begin(c.no_checkout), std::end(c.no_checkout), c.countdown) != std::end(c.no_checkout)) {
                    c.checkout_loop(c.countdown);
                    std::cout<< "\t\nto get to checkout hit: (Dart 1, Dart 2, Dart 3, total target area)\n\n";
                    for (auto ch : c.checkout_v){
                        std::cout<< ch << '\n';
                    }
                }
                else {c.finish_loop(c.countdown);
                    if (c.finish_v.size() == 1){
                                std::cout<< "\nfinish: (Dart 1, Dart 2, Dart 3, total target area)\n\n" << c.finish_v[0] <<'\n';
                    }
                    else{
                        std::cout<< "\nfinishes: (Dart 1, Dart 2, Dart 3, total target area)\n\n";
                        for (std::string f : c.finish_v){
                                std::cout<< f << '\n';
                        }
                    }
                }
                std::cout<< "\v";
            }
            else {
                std::cout<< "\t\t\tcan't finish\n\n";
            }
        }
        else {
            std::cout<< "\t\t\tno score\n";
        }
        c.finish_v = {};
        c.checkout_v = {};
        c.finish = {};
        c.checkout = {};
    }

    return 0;
}
