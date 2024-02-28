#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "darts.h"
#include <iomanip>
#include <sstream>
#include <nlohmann/json.hpp>

int counter::MINi(size_t a, size_t b) {if (a < b) {return a;} else {return b;}}

counter::counter(){
    char pBuf[256];
    size_t len = sizeof(pBuf);
    int bytes = MINi(readlink("/proc/self/exe", pBuf, len), len - 1);
    if (bytes >= 0)
        pBuf[bytes] = '\0';
    const char* fileN= "/highscore.json";
    for (int i = std::strlen(pBuf)-1; ; i--){
        if (pBuf[i] == '/'){
            pBuf[i] = '\0'; break;
        }
        else {pBuf[i] = '\0';}
    }
    pfad = (char*) malloc(std::strlen(pBuf) + std::strlen(fileN)+1);
    strcpy(pfad, pBuf );
    strcat(pfad, fileN);
            std::ifstream file(pfad);
            if (file.good()){
                hisc_json = nlohmann::json::parse(pfad);
            }
}

void counter::enter_score(){
        std::string name;
        char repeat;
        std::cout << "enter score: ";
        std::cin>> score;
        if (countdown - score >= 0 && countdown - score != 1){
            countdown -= score;
            std::cout<< "-> -> -> " << countdown<<"\n";
            hisc_map_crt[std::to_string(hisc_map_crt.size()+1)] = score;                                           //"\"" + std::to_string(score) + "\"";
            if (countdown == 0){
                std::cout<< "\t\t\tnfinished!" << "with " << hisc_map_crt.size() << " darts\n";
                for (auto it = hisc_json.begin(); it != hisc_json.end(); it++){
                    if (hisc_map_crt.size() < it.value().size()-1 || it.key() == ""){
                        std::cout<< "\t\t\tnew highscore! (place " << it.key() << ")\n Enter name:";
                        std::cin >> name;
                        hisc_map_crt["name"] = 2;
                        it.value() = hisc_map_crt;
                    }
                }
                std::cout<< "\t\t\tplay again? (y/n)\n";
                std::cin>>repeat;
                if (repeat == 'y'){
                    countdown = 501; std::cout<< countdown << '\n';
                }
                else {exit(0);}
            }
        }
        else {
            std::cout<< "\t\t\tno score\n";
            hisc_map_crt[std::to_string(hisc_map_crt.size()+1)] = 0;
        }
}

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
        current_targets[bed_names[j_p - 1] + std::to_string(i_p) + "  "] = diff[j_p-1];
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
    std::cout << std::string(45, '-')<< '\n' << "Dart 1\t" << "Dart 2\tDart 3\t";
    if (checkout_v.size() > 0){std::cout << "for\t";}
    std::cout<< "target area (mm2)"  <<'\n';

    for (auto i : ct_vec){
        if (count >= print_limit){break;}
            for (auto el : i){
                if (el.second == 50 || el.second == 25){
                    std::cout<< bed_names[el.first-1] << "\t";
                }
                else {std::cout<< bed_names[el.first-1] << el.second << "\t";}
            }
            if(checkout_v.size() > 0){ std::cout<< countdown - scoreSum(i) << '\t';}

            std::cout << std::string((2 - (i.size()-1)), '\t') << diffSum(i) << "\n";
            count++;
    }
}

counter::~counter(){
//    hiscore = "{";
//    for (auto it = hisc_map.begin(); it != hisc_map.end(); it++){
//        hiscore += std::to_string(it.key()) + ":{";
//        for (i : it->value){
//            if (i == *(it->second.end()-1)){
//                hiscore += std::to_string(i) +"}";
//            }
//            else{ hiscore += std::to_string(i) + ","; }
//        }
//        hiscore += "}";
//    }

    std::ofstream outfile;
    outfile.open(pfad);
    outfile << hisc_json;
}








