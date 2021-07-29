#include<iostream>
#include<string>
#include"RPN.hpp"

int main(){
    RPN Ryan;
    Ryan.One_Stack.Push(100);
    Ryan.One_Stack.Push(200);
    Ryan.One_Stack.Print();

    std::string str("3,4,+,2,*,1,+");
    int total_number = 0;
    RPN Amber;
    Amber.Calculation(str,total_number);
    std::cout <<"TOTAL NUMBER: " << total_number << std::endl;
    Amber.One_Stack.Print();
    return 0;
}
