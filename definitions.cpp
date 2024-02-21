#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "darts.h"
#include <iomanip>
#include <sstream>

counter::result counter::checkout_test(int countdown_p, std::map<std::string, double> current_targets, std::string ct, int i_p, int j_p){
    if (i_p == 21){
        countdown_p -= 25;
        current_targets["Outer Bull  "] = 677.418;
        ct += "Outer Bull  ";
    }
    else if (i_p == 22){
        countdown_p -= 50;
        current_targets["Bull  "] = 129.032;
        ct += "Bull  ";
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

void counter::insertion(std::map<std::string, double> current_targets, std::string ct, std::vector<std::map<std::string, double>>& maps_p, std::vector<std::string>& strings_p){
      if (std::find(maps_p.begin(), maps_p.end(), current_targets) == maps_p.end()){
            int order_index = 0;
                for (int t = maps_p.size()-1; t >= 0; t--){
                    if (diffSum(maps_p[t]) == diffSum(current_targets)){
                        if (strings_p[t].at(strings_p[t].length()-5) == 'D'){
                            if (std::find(std::begin(prio), std::end(prio), strings_p[t].substr(strings_p[t].length()-4, 2)) != std::end(prio) && \
                               (std::find(std::begin(prio), std::end(prio), ct.substr(ct.length()-4, 2)) == std::end(prio))){
                                std::cout<< "\nneu: "<< ct.substr(ct.length()-4, 2) << '\n';
                                std::cout<< "\nbestand: "<< strings_p[t].substr(strings_p[t].length()-4, 2)<< '\n';
                                    continue;
                            }
                            else{
                                order_index = t;
                                break;
                            }
                        }
                    }
                    if (diffSum(maps_p[t]) > diffSum(current_targets)){   // && maps_p[t].size() <= current_targets.size()
                        order_index = t+1;
                        break;
                    }
                }
            strings_p.insert(strings_p.begin() + order_index, ct);
            maps_p.insert(maps_p.begin() + order_index, current_targets);
        }
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

void counter::checkout_loop(int countdown_p){

     for (int j=1; j<4; j++){
            for (int i = 1; i != 23; ++i) {
                  std::map<std::string, double> ct_m = {}; std::string ct_s = "";
                  result test_result = checkout_test(countdown_p, ct_m, ct_s, i, j);
                  int cd_afterDart1 = test_result.countdown_i;
                  std::map<std::string, double> ct_afterD1_m = test_result.current_targets_p;
                  std::string ct_afterD1_s = test_result.ct_p;
                  if (cd_afterDart1 == 0 && (ct_afterD1_s.at(ct_afterD1_s.length()-6) == 'B' || ct_afterD1_s.at(ct_afterD1_s.length()-4) == 'D' || ct_afterD1_s.at(ct_afterD1_s.length()-5) == 'D')){
                        //ct_afterD1_s += "(target area = " + to_string_with_precision(diffSum(ct_afterD1_m), 3) + ")";
                        insertion(ct_afterD1_m, ct_afterD1_s, finish, finish_v);
                        break;
                  }
                  else if (cd_afterDart1 < 2) {break;}


                  for (int k=1; k<4; k++){
                      for (int l = 1; l != 23; ++l) {
                              result test_result2 = checkout_test(cd_afterDart1, ct_afterD1_m, ct_afterD1_s, l, k);
                              int cd_afterDart2 = test_result2.countdown_i;
                              std::map<std::string, double> ct_afterD2_m = test_result2.current_targets_p;
                              std::string ct_afterD2_s = test_result2.ct_p;
                              if (cd_afterDart2 == 0 && (ct_afterD2_s.at(ct_afterD2_s.length()-6) == 'B' || ct_afterD2_s.at(ct_afterD2_s.length()-4) == 'D' || ct_afterD2_s.at(ct_afterD2_s.length()-5) == 'D')){
                                    //ct_afterD2_s += "(target area = " + to_string_with_precision(diffSum(ct_afterD2_m), 3) + ")";
                                    insertion(ct_afterD2_m, ct_afterD2_s, finish, finish_v);
                                    break;
                              }
                              else if (cd_afterDart2 < 2) {break;}


                              for (int m = 1; m != 23; ++m) {
                                   result test_result3 = checkout_test(cd_afterDart2, ct_afterD2_m, ct_afterD2_s, m, 2);
                                   int cd_afterD3 = test_result3.countdown_i;
                                   std::map<std::string, double> ct_afterD3_m = test_result3.current_targets_p;
                                   std::string ct_afterD3_s = test_result3.ct_p;
                                   if (cd_afterD3 == 0 && (ct_afterD3_s.at(ct_afterD3_s.length()-6) == 'B' || ct_afterD3_s.at(ct_afterD3_s.length()-4) == 'D' || ct_afterD3_s.at(ct_afterD3_s.length()-5) == 'D')){
                                       //ct_afterD3_s += "(target area = " + to_string_with_precision(diffSum(ct_afterD3_m), 3) + ")";
                                       insertion(ct_afterD3_m, ct_afterD3_s, finish, finish_v);
                                       break;
                                   }
                                   else if (cd_afterD3 < 2) {break;}
                                   else if (std::find(a.begin(), a.end(), cd_afterD3) != a.end()){
                                        //ct_afterD3_s += " for " + std::to_string(cd_afterD3) + " (target area = " + (to_string_with_precision(diffSum(ct_afterD3_m), 3)) + " mm2)";
                                        insertion(ct_afterD3_m, ct_afterD3_s, checkout, checkout_v);
                                   }
                             }
                       }
                   }
            }
      }
     for (int m = 0; m < finish.size(); m++){
         finish_v[m] += to_string_with_precision(diffSum(finish[m]), 3);
     }
}


