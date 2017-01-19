Range C++ Library
=====
Copyright (C) 2017 SiLeader. All rights reserved.  
Licensed under Mozilla Public License 2.0.
(https://opensource.org/licenses/MPL-2.0)

# Overview
Range is container for "range-based for".  
This class has std::vector and can use all functions that are in std::vector.  

## Features
+ Only one header file.
+ Extend std::vector's function.

# Supporting functions
+ std::vector functions
+ reverse sequence
+ MapReduce
+ for each
+ convert sequence (use std::function)
+ assign from generator (use std::function)
+ increment assign

# Sample Code
This sample code is in test/test.cpp
```c++
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
std::initializer_list(reverse)
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
30

```

# C++ Version
C++11 or later.
