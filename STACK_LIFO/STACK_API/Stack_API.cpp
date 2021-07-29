#include<iostream>
#include<stack>
#include"Stack_API.hpp"
#include<string>

int main(){
    std::stack<int> my_stack;
    my_stack.push(10);
    my_stack.push(20);
    Print(my_stack);
    std::string string("10,5,-,15,+");
    int result = 0;
    RPN_Calculation(string, result);
    std::cout << "RESULT: " << result << std::endl;
    return 0;
}