
This is a folder that cointains some small interview problems that I faced before.

In file print_3digit.cpp, Proving a int number input, output should be print out with comma every 3 digits from right to left. For Example: input = 1980620 => output = 1,980,620. 
Compile: g++ print_3digit.cpp -o print_3digit.out -std=c++11

In File Gcd_Amazon.cpp => find the greatest common divisor(GCD)  in the array. In C++ array can define as vector, C-array or std::array. I am included 3 solutions in this file. 
For Example: std::array <int, 5> array = {4,8,12,16 20}
4:  1 , 2 , 4
8:  1 , 2 , 4 , 8
12: 1 , 2 , 3, 4 , 6 , 12
16: 1 , 2 , 4 , 8, 16
20: 1 , 2 , 4 , 10 , 20
=> 4 is GCDs

In File Cell_Change.cpp, create an algorithm to output the state of the cells after the given number of days. One function uses std::array to pass parameter, another function uses std::vector and pass pointer array. 
