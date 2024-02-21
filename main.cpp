#include <iostream>
#include "darts.h"
#include <typeinfo>
#include <fstream>

int main(){
    counter c;
    std::cout<< c.countdown<<'\n';

    while (c.countdown != 0){
        std::cout << "enter score: ";
        std::cin>> c.score;
        if (c.countdown - c.score >= 2){
            c.countdown -= c.score;
            std::cout<< "-> -> -> "<< c.countdown;

            c.checkout_loop(c.countdown);

            if (c.countdown <= 350){
                if (c.countdown > 170) {
                    std::cout<< "\t\t\t\tto get to checkout hit\n\n";
//                    std::string out;
                    for (auto ch : c.checkout_v){
//                        out += ch + "\n";
                        std::cout<< ch << '\n';
                    }
//                    std::ofstream outfile;
//                    outfile.open("/home/moritz/Nextcloud2/C++/darts_alt_string/darts/box1.json");
//                    outfile << out;
                }
                else if (c.finish_v.size() == 1){
                            std::cout<< "\t\tfinish:\n" << c.finish_v[0] <<'\n';
                }
                else{
                    std::cout<< "\t\tfinishes:\n";
                    for (std::string f : c.finish_v){
                            std::cout<< f << '\n';
                    }
                }
            }
            else {
                std::cout<< "\t\t\tcan't finish\n";
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
