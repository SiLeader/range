/*
    Range test code.
    Licensed under the Mozilla Public License 2.0 (See LICENSE or https://opensource.org/licenses/MPL-2.0).
    Copyright (C) 2017 SiLeader. All rights reserved.
*/

#include <iostream>
#include <string>

#include <range.hpp>

int main() {
    std::cout<<"std::initializer_list"<<std::endl;
    for(auto&& str : range::range<std::string>({"a", "b", "c", "d", "e", "f"})) {
        std::cout<<str<<std::endl;
    }
    std::cout<<"std::initializer_list(reverse)"<<std::endl;
    for(auto&& str : range::range<std::string>({"a", "b", "c", "d", "e", "f"}).reverse()) {
        std::cout<<str<<std::endl;
    }

    std::vector<int> num_vector={0, 1, 2, 3, 4};
    std::cout<<"generate from lambda"<<std::endl;
    for(auto&& num : range::range<int>(5, [&](std::size_t idx){return num_vector[idx]+idx;})) {
        std::cout<<num<<std::endl;
    }

    std::cout<<"construct from vector -> convert -> for_each"<<std::endl;
    range::range<int>(num_vector).convert([](int num){return num*num;}).for_each([](int& num){
        std::cout<<num<<std::endl;
    });

    std::cout<<"construct from vector -> map -> reduce(for_each)"<<std::endl;
    auto result=range::range<int>(num_vector)
    .map([](int num){
        return num*num;
    })
    .reduce<int>([](range::range<int> r){
        int sum=0;
        r.for_each([&](int& num) {
            sum+=num;
        });
        return sum;
    });
    std::cout<<result<<std::endl;
}
