#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "darts.h"
#include <iomanip>
#include <sstream>

counter::result counter::checkout_test(int countdown_p, std::map<std::string, double> current_targets, std::vector<std::pair<int,int>> ct, int i_p, int j_p){
    if (i_p == 0){
        countdown_p -= 50;
        current_targets["Bull  "] = 129.032;
        ct.push_back({4,50});
    }
    else if (i_p == -1){
        countdown_p -= 25;
        current_targets["Outer Bull  "] = 677.418;
        ct.push_back({5, 25});
    }
    else {
        countdown_p -= j_p * i_p;
        current_targets[h[j_p - 1] + std::to_string(i_p) + "  "] = diff[j_p-1];
        ct.push_back({j_p, i_p});
    }
    return {countdown_p, current_targets, ct};
}

double counter::diffSum(std::vector<std::pair<int,int>> ct_p){
     double diff_sum = 0;
     for (auto it = ct_p.begin(); it != ct_p.end(); it++){
        diff_sum += diff[it->first-1];
     }
     return diff_sum;
}

int counter::scoreSum(std::vector<std::pair<int,int>> ct_p){
    int score_sum = 0;
    for (auto it : ct_p){
        if (it.first == 4 || it.first == 5){
            score_sum += it.second;
        }
        else{
            score_sum += it.first * it.second;
        }
    }
    return score_sum;
}

int counter::scoreSumSingle(std::vector<std::pair<int,int>> ct_p){
    int score_sum = 0;
    for (auto it : ct_p){
            if (it.first != 4 && it.first != 5){
                score_sum += it.second;
            }
    }
    return score_sum;
}

int counter::scoreSumSingle_finish(std::vector<std::pair<int,int>> ct_p){
    int score_sum = 0;
    for (auto it : ct_p){
        if (it != *(ct_p.end()-1)){
            if (it.first != 4 && it.first != 5){
                score_sum += it.second;
            }
        }
    }
    return score_sum;
}

int counter::double_bull_count(std::vector<std::pair<int,int>> ct_p){
    int db_count = 0;
    for (auto it : ct_p){
        if (it.first == 2 || it.first == 4 || it.first == 5){
            db_count += 1;
        }
    }
    return db_count;
}

int counter::bull_count(std::vector<std::pair<int,int>> ct_p){
    int db_count = 0;
    for (auto it : ct_p){
        if (it != *ct_p.end()){
            if (it.first == 4){
                db_count += 1;
            }
        }
    }
    return db_count;
}

bool counter::maxSingle(std::vector<std::pair<int,int>> finish_v_p, std::vector<std::pair<int,int>> ct_p){
    std::vector<int> f_singleVec, ct_singleVec;
    for (auto it : ct_p){
        if (it.first != 4 && it.first != 5){
            ct_singleVec.push_back(it.second);
        }
    }
    for (auto it : finish_v_p){
        f_singleVec.push_back(it.second);
    }
    std::sort(f_singleVec.begin(), f_singleVec.end());
    std::sort(ct_singleVec.begin(), ct_singleVec.end());
    for (int i = std::min(finish_v_p.size(), ct_p.size()); i >-1; i--){
        if (f_singleVec[i] > ct_singleVec[i]){
            return 1;
        }
    }
    return 0;
}

void counter::print(std::vector<std::vector<std::pair<int,int>>> ct_vec){
    int count = 0;
    std::cout << std::string(45, '-')<< '\n' << "Dart 1\t" << std::setw(15) << "Dart 2\tDart 3\ttarget area (mm2)n"  <<'\n';

    for (auto i : ct_vec){
        if (count >= print_limit){break;}
            for (auto el : i){
                if (el.second == 50 || el.second == 25){
                    std::cout<< h[el.first-1] << "\t";
                }
                else { std::cout<< h[el.first-1] << el.second << "\t";}
            }
            std::cout << std::string((2 - (i.size()-1)), '\t') << diffSum(i) << "\n";
            count++;
    }
}








