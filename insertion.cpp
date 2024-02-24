#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "darts.h"
#include <iomanip>
#include <sstream>

void counter::insertion(std::map<std::string, double> current_targets, std::vector<std::pair<int,int>> ct){   // improvement: sort vector after calculation of ALL options. -> how to reduce calculation time? Setting breaks?
      if (std::find(finish.begin(), finish.end(), current_targets) == finish.end()){
            int order_index = 0;
                for (int t = finish.size()-1; t >= 0; t--){

                    if (bull_count(ct) < bull_count(finish_v[t])){
                          continue;
                       }
                        else if (bull_count(finish_v[t]) < bull_count(ct)){
                            order_index = t+1;
                            break;
                        }

                    else if (ct.size() < finish_v[t].size()){
                        continue;
                    }
                    else if (finish_v[t].size() < ct.size()){
                        order_index = t+1;
                        break;
                    }

                    else if ( (ct.back().second & (ct.back().second - 1)) == 0 && (finish_v[t].back().second & (finish_v[t].back().second - 1)) != 0 ){  // ist Double 2er Potenz ?
                        continue;
                        }
                        else if ((finish_v[t].back().second & (finish_v[t].back().second - 1)) == 0 && (ct.back().second & (ct.back().second - 1)) != 0){  // ist Double 2er Potenz ?
                             order_index = t+1;
                             break;
                        }



                    else if ( ct.back().second % 2 == 0 && finish_v[t].back().second % 2 != 0 ){   // ist Double durch 2 teilbar?
                        continue;
                            }
                    else if (finish_v[t].back().second % 2 == 0 && ct.back().second % 2 != 0){
                         order_index = t+1;
                         break;
                    }

                    else if ( (ct.back().second / 2) % 2 == 0 && (finish_v[t].back().second / 2) % 2 != 0 ){   // ist der Double durch 2 durch 2 teilbar?
                        continue;
                            }
                    else if ((finish_v[t].back().second / 2) % 2 == 0 && (ct.back().second / 2) % 2 != 0){
                         order_index = t+1;
                         break;
                    }

                    else if (diffSum(ct) > diffSum(finish_v[t])){
                        continue;
                    }
                    else if (diffSum(finish_v[t]) > diffSum(ct)){
                        order_index = t+1;
                        break;
                    }

                    else if (maxSingle(finish_v[t], ct)){
                        order_index = t+1;
                        break;
                    }
                    else if ( scoreSumSingle_finish(ct) > scoreSumSingle_finish(finish_v[t]) ){
                        continue;
                    }
                    else if (scoreSumSingle_finish(finish_v[t]) > scoreSumSingle_finish(ct)){
                        order_index = t+1;
                        break;
                    }
                    else if (double_bull_count(finish_v[t]) < double_bull_count(ct)){
                        order_index = t+1;
                        break;
                    }

                }
            finish_v.insert(finish_v.begin() + order_index, ct);
            finish.insert(finish.begin() + order_index, current_targets);
      }
}

void counter::insertion_checkout(std::map<std::string, double> current_targets, std::vector<std::pair<int,int>> ct){
      if (std::find(checkout_v.begin(), checkout_v.end(), ct) == checkout_v.end()){
            int order_index = 0;
                for (int t = checkout.size()-1; t >= 0; t--){
                    if (double_bull_count(ct) < double_bull_count(checkout_v[t])){
                        continue;
                    }
                    else if (double_bull_count(checkout_v[t]) < double_bull_count(ct)){
                        order_index = t+1;
                        break;
                    }

                    else if (scoreSum(checkout_v[t]) > scoreSum(ct)){   // && checkout[t].size() <= current_targets.size()       double_bull_count(checkout_v[t]) < double_bull_count(ct)
                        order_index = t+1;
                        break;
                    }
                    else if (scoreSum(checkout_v[t]) == scoreSum(ct)){
                             if (diffSum(checkout_v[t]) > diffSum(ct)){
                                 order_index = t+1;
                                 break;
                             }
                    }
                }
            checkout_v.insert(checkout_v.begin() + order_index, ct);
            checkout.insert(checkout.begin() + order_index, current_targets);
      }
}
