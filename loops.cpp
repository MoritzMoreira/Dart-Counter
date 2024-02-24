#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "darts.h"
#include <iomanip>
#include <sstream>
#include <bits/stdc++.h>

template<typename T>
std::string to_string_with_precision(const T a_value, const int n)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

void counter::checkout_loop(int countdown_p){
     for (int j=3; j!=0; j-=2){
            for (int i = 20; i >-2; --i) {
                std::map<std::string, double> ct_m = {}; std::vector<std::pair<int,int>> ct_s = {};
                  result test_result = checkout_test(countdown_p, ct_m, ct_s, i, j);
                  int cd_afterDart1 = test_result.countdown_i;
                  std::map<std::string, double> ct_afterD1_m = test_result.current_targets_p;
                  std::vector<std::pair<int,int>> ct_afterD1_s = test_result.ct_p;
                  if (cd_afterDart1 < 2 || checkout.size() > limit) {break;}

                  for (int k=3; k!=0; k -= 2){
                         for (int l = 20; l >-2; --l) {
                              result test_result2 = checkout_test(cd_afterDart1, ct_afterD1_m, ct_afterD1_s, l, k);
                              int cd_afterDart2 = test_result2.countdown_i;
                              std::map<std::string, double> ct_afterD2_m = test_result2.current_targets_p;
                              std::vector<std::pair<int,int>> ct_afterD2_s = test_result2.ct_p;
                              if (cd_afterDart2 < 2 || checkout.size() > limit) {break;}

                              for (int u=3; u!=0; u -= 2){
                                  for (int m = 20; m >-2; --m) {
                                       result test_result3 = checkout_test(cd_afterDart2, ct_afterD2_m, ct_afterD2_s, m, u);
                                       int cd_afterD3 = test_result3.countdown_i;
                                       std::map<std::string, double> ct_afterD3_m = test_result3.current_targets_p;
                                       std::vector<std::pair<int,int>> ct_afterD3_s = test_result3.ct_p;
                                       if (cd_afterD3 <=170 && std::find(std::begin(no_checkout), std::end(no_checkout), cd_afterD3) == std::end(no_checkout)){
                                            std::sort(ct_afterD3_s.begin(), ct_afterD3_s.end());
                                            insertion_checkout(ct_afterD3_m, ct_afterD3_s);
                                       }
                                         if (cd_afterD3 < 2 || checkout.size() > limit) {break;}
                                  }
                                  if (u == 1) {
                                       u += 3;
                                  }
                               }
                          }
                          if (k == 1) {
                               k += 3;
                          }
                   }
             }
             if (j == 1) {
                 j += 3;
             }
     }
}

void counter::finish_loop(int countdown_p){
     for (int j=3; j!=0; j-=2){
            for (int i = 20; i >-2; --i) {
                std::map<std::string, double> ct_m = {}; std::vector<std::pair<int,int>> ct_s = {};
                  result test_result = checkout_test(countdown_p, ct_m, ct_s, i, j);
                  int cd_afterDart1 = test_result.countdown_i;
                  std::map<std::string, double> ct_afterD1_m = test_result.current_targets_p;
                  std::vector<std::pair<int,int>> ct_afterD1_s = test_result.ct_p;

                  if (cd_afterDart1 == 0 && (j == 2 || i == 0)){
                      if (std::find(finish_v.begin(), finish_v.end(), ct_afterD1_s) == finish_v.end()){
                            insertion(ct_afterD1_m, ct_afterD1_s);
                            break;
                      }
                  }
                  else if (finish.size() > limit) {break;}

                  for (int k=3; k!=0; k-=2){
                         for (int l = 20; l >-2; --l) {
                              result test_result2 = checkout_test(cd_afterDart1, ct_afterD1_m, ct_afterD1_s, l, k);
                              int cd_afterDart2 = test_result2.countdown_i;
                              std::map<std::string, double> ct_afterD2_m = test_result2.current_targets_p;
                              std::vector<std::pair<int,int>> ct_afterD2_s = test_result2.ct_p;
                              if (cd_afterDart2 == 0 && (k == 2 || l == 0)){
                                  std::vector<std::pair<int,int>> ct_afterD2_s_swapped = ct_afterD2_s;
                                 ct_afterD2_s_swapped[0] = ct_afterD2_s[1]; ct_afterD2_s_swapped[1] = ct_afterD2_s[0];
                                  if (std::find(finish_v.begin(), finish_v.end(), ct_afterD2_s) == finish_v.end() && \
                                      std::find(finish_v.begin(), finish_v.end(), ct_afterD2_s_swapped) == finish_v.end()){
                                      insertion(ct_afterD2_m, ct_afterD2_s);
                                      break;
                                  }
                              }
                              else if (finish.size() > limit) {break;}

                              for (int m = 20; m >-1; --m) {

                                   result test_result3 = checkout_test(cd_afterDart2, ct_afterD2_m, ct_afterD2_s, m, 2);
                                   int cd_afterDart3 = test_result3.countdown_i;
                                   std::map<std::string, double> ct_afterD3_m = test_result3.current_targets_p;
                                   std::vector<std::pair<int,int>> ct_afterD3_s = test_result3.ct_p;
                                   if (cd_afterDart3 == 0){
                                       std::vector<std::pair<int, int>> ct_afterD3_s_ordered = ct_afterD3_s;
                                       std::sort(ct_afterD3_s_ordered.begin(), ct_afterD3_s_ordered.end()-1);                 //toDo: Duplikate bei Doublen und Bulls in D1 und D2 aussortieren
                                       if (std::find(finish_v_ordered.begin(), finish_v_ordered.end(), ct_afterD3_s_ordered) == finish_v_ordered.end()){
                                           insertion(ct_afterD3_m, ct_afterD3_s);
                                           break;
                                       }
                                       finish_v_ordered.push_back(ct_afterD3_s_ordered);
                                   }
                                   else if (finish.size() > limit) {break;}
                               }
                           }
                           if (k == 1) {
                                k += 3;
                           }
                    }
            }
            if (j == 1) {
                  j += 3;
            }
     }
}
