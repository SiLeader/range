/*
    Range test code.
    Licensed under the Mozilla Public License 2.0 (See LICENSE or https://opensource.org/licenses/MPL-2.0).
    Copyright (C) 2017 SiLeader. All rights reserved.
*/

#include <iostream>
#include <string>
#include <chrono>

#include <range.hpp>

int main() {
    std::cout<<"std::initializer_list"<<std::endl;
    for(auto&& str : range::range<std::string>({"a", "b", "c", "d", "e", "f"})) {
        std::cout<<str<<std::endl;
    }

    std::cout<<"std::initializer_list(to_reverse)"<<std::endl;
    for(auto&& str : range::range<std::string>({"a", "b", "c", "d", "e", "f"}).to_reverse()) {
        std::cout<<str<<std::endl;
    }

    std::cout<<"reverse container"<<std::endl;
    range::range<std::string> r({"a", "b", "c", "d", "e", "f"});
    r.reverse();
    for(auto&& str : r) {
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
    .map<std::string>([](int num){
        return std::to_string(num*num);
    })
    .reduce<std::string>([](range::range<std::string> r){
        std::string sum;
        r.for_each([&](std::string& str) {
            sum+=str;
        });
        return sum;
    });
    std::cout<<result<<std::endl;

    std::cout<<"async_for_each"<<std::endl;
    range::range<int>(num_vector).async_for_each([](int v) {
        std::cout<<v<<std::endl;
    });
}
