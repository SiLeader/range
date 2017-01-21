Range C++ Container
=====
Copyright (C) 2017 SiLeader. All rights reserved.  
Licensed under Mozilla Public License 2.0.
(https://opensource.org/licenses/MPL-2.0)  
[![Build Status](https://travis-ci.org/SiLeader/range.svg?branch=master)](https://travis-ci.org/SiLeader/range)
# Overview
Range is container for "range-based for".  
This class has std::vector and can use all functions that are in std::vector.  

## Features
+ Only one header file.
+ Extend std::vector's function.
+ Have Thread Pool

# Supporting functions
+ std::vector functions
+ reverse sequence
+ MapReduce
+ for each
+ convert sequence (use std::function)
+ assign from generator (use std::function)
+ increment assign
+ async for each (use std::thread, std::function)
    + use range::thread_pool

# Sample Code
This sample code is in test/test.cpp
```c++
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
```
Execution result
```
std::initializer_list
a
b
c
d
e
f
std::initializer_list(to_reverse)
f
e
d
c
b
a
reverse container
f
e
d
c
b
a
generate from lambda
0
2
4
6
8
construct from vector -> convert -> for_each
0
1
4
9
16
construct from vector -> map -> reduce(for_each)
014916
async_for_each
0
1
2
3
4
```

# Range::Thread Pool
Thread pool class is for support range's async functions.  
This class is based on std::thread.

# C++ Version
C++11 or later.
