#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "darts.h"
#include <iomanip>
#include <sstream>

counter::result counter::checkout_test(int countdown_p, std::map<std::string, double> current_targets, std::string ct, int i_p, int j_p){
    if (i_p == 0){
        countdown_p -= 50;
        current_targets["Bull  "] = 129.032;
        ct += "Bull  ";
    }
    else if (i_p == -1){
        countdown_p -= 25;
        current_targets["Outer Bull  "] = 677.418;
        ct += "Outer Bull  ";
    }
    else {
        countdown_p -= j_p * i_p;
        current_targets[h[j_p - 1] + std::to_string(i_p) + "  "] = diff[j_p-1];
        ct += h[j_p - 1] + std::to_string(i_p) + "  ";
    }
    return {countdown_p, current_targets, ct};
}

double counter::diffSum(std::map<std::string, double> current_targets_p){
     double diff_sum = 0;
     for (auto it = current_targets_p.begin(); it != current_targets_p.end(); it++){
        diff_sum += it->second;
     }
     return diff_sum;
}

void counter::insertion(std::map<std::string, double> current_targets, std::string ct){
      if (std::find(finish.begin(), finish.end(), current_targets) == finish.end()){
            int order_index = 0;
                for (int t = finish.size()-1; t >= 0; t--){
                    if (diffSum(finish[t]) == diffSum(current_targets)){
                        if (finish_v[t].at(finish_v[t].length()-5) == 'D'){
                            if (std::find(std::begin(prio), std::end(prio), finish_v[t].substr(finish_v[t].length()-4, 2)) != std::end(prio) && \
                               (std::find(std::begin(prio), std::end(prio), ct.substr(ct.length()-4, 2)) == std::end(prio))){
                                std::cout<< "\nneu: "<< ct.substr(ct.length()-4, 2) << '\n';
                                std::cout<< "\nbestand: "<< finish_v[t].substr(finish_v[t].length()-4, 2)<< '\n';
                                    continue;
                            }
                            else{
                                order_index = t;
                                break;
                            }
                        }
                    }
                    if (diffSum(finish[t]) > diffSum(current_targets)){   // && finish[t].size() <= current_targets.size()
                        order_index = t+1;
                        break;
                    }
                }
            finish_v.insert(finish_v.begin() + order_index, ct);
            finish.insert(finish.begin() + order_index, current_targets);
        }
}

void counter::insertion_checkout(std::map<std::string, double> current_targets, std::string ct){
      if (std::find(checkout.begin(), checkout.end(), current_targets) == checkout.end()){
            int order_index = 0;
                for (int t = checkout.size()-1; t >= 0; t--){
                    if (diffSum(checkout[t]) > diffSum(current_targets)){   // && checkout[t].size() <= current_targets.size()
                        order_index = t+1;
                        break;
                    }
                }
            checkout_v.insert(checkout_v.begin() + order_index, ct);
            checkout.insert(checkout.begin() + order_index, current_targets);
      }
}








