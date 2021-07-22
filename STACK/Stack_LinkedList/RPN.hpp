#ifndef RPN_HPP
#define RPN_HPP
#include<iostream>
#include<string>
#include<cmath>
#include"Stack_Linked_List.hpp"

/*RPN: Reverse Polish Notation:
    EX: "3,4,+,2,*,1,+" => ((3+4)*2) + 1 .Scan from left to right.

Algorithm:
    THEORY:
    * Convert std::string to number. Scanning whole string and distinguish in 3 catagories: Number, Comma and Arithmetic(+,-,*,/). 
        + Number: make sure it scanning a whole number before comma. Ex: 23, => number 23. Not number 2 and 3. 
            # fomular to scan a big number:
            whole_number = whole_number * 10^counter + number.
            where:  number is a convert str to number. Ex: 0 -> 9
                    whole_number is a real number. Ex: 0 -> +infinity.
            EX: number 192 = 1* 10^2 + 9*10^1 + 2*10^0.
                first scanning number 1. Apply the fomular, whole_number = 0. 
                step 1: whole_number    =   whole_number    * 10^counter    + number = 1;
                            1           =       0           *   10^0        +   1;
                step 2: whole_number    =   whole_number    * 10^counter    + number = 9;
                            19          =       1           *   10^1        +   9
                step 3: whole_number    =   whole_number    * 10^counter    + number = 2;
                            192         =       19          *   10^2        +   2
                => whole_number = 192.
        + Comma: to distinguish what number and arithmetic. Number can be push to the stack when current state is comma. 
        + Arithmetic: select a correct calculation:
            Ex: "3,4,+,2,x,1,+" => (3+4)
                                    (total * 2)
                                        (total + 1) 
    * Need 2 states: Current_state and Prev_state. Push to stack when Prev_state is number(0,1,2..) not the arithmetic(+,-*,/).
    * To push number to the stack need 2 factors:
        + Current_state is comma(,).
        + Prev_state is a number. 
    
    PRACTICE:
    *scan a whole string in while or for loop.
        + case 0: convert string to number (0 -> 9) => whole number after comma.
        + case 1: when scanning a string is comma(,). if prev_state is not athrimetic(+,-,*,/), Push whole number in th stack. Set whole_number = 0
                    number = 0 and power(or hat ^) = 0.
        + case 2: if scanning a string is end the string => return or break.
        + case 3: if scanning a string is a arithmetic(-,+,*,/):
                    + when it is a first arithmetic, Get out 2 elements from the stack and delete them in stack.
                    + when it is not a first arithmetic, get out only 1 element in the stack and delete it in stack
*/

class RPN{
    public:
        Stack_Linked_List One_Stack;

        void Arithmetic_Selection(char &str, int &Total, int &arithmetic){
            int number_in_stack = 0;
            if(str == '+'){
                arithmetic++;
                if(arithmetic == 1){
                    number_in_stack = One_Stack.Top();
                    One_Stack.Pop();
                    Total = number_in_stack + One_Stack.Top();
                    One_Stack.Pop();
                }
                else{                        
                    Total = Total + One_Stack.Top();
                    One_Stack.Pop();
                }
            }
            else if(str == '*'){
                arithmetic++;
                if(arithmetic == 1){
                    number_in_stack = One_Stack.Top();
                    One_Stack.Pop();
                    Total = One_Stack.Top() * number_in_stack;
                    One_Stack.Pop();
                }
                else{
                    Total = Total * One_Stack.Top();
                    One_Stack.Pop();
                }
            }
            else if(str == '-'){
                arithmetic++;
                if(arithmetic == 1){
                    number_in_stack = One_Stack.Top();
                    One_Stack.Pop();
                    Total = One_Stack.Top() - number_in_stack;
                    One_Stack.Pop();
                }
                else{
                    Total = Total - One_Stack.Top();
                    One_Stack.Pop();
                }
            }
            else if(str == '/'){
                arithmetic++;
                if(arithmetic == 1){
                    number_in_stack = One_Stack.Top();
                    One_Stack.Pop();
                    Total = One_Stack.Top() / number_in_stack;
                    One_Stack.Pop();
                }
                else{
                    Total = Total / One_Stack.Top();
                    One_Stack.Pop();
                }
            }
            

            return;
        }


        void Calculation(std::string &str, int &Total){
            int number = 0, counter = 0, whole_number = 0;
            char prev_state, current_state;
            int arithmetic = 0;
            int number_in_stack = 0;
            int count = 0;
            for(int i = 0; i <= str.size();i++){
                current_state = str[i];
                if(str[i] >= '0' && str[i] <= '9'){
                    number = str[i] - '0';
                    whole_number = whole_number * pow(10,counter) + number;
                    counter++;
                }

                else if(str[i] == ','){
                    if(prev_state != '+' && prev_state != '-' && prev_state != '*' && prev_state != '/'){
                        One_Stack.Push(whole_number);
                        counter = 0;
                        number = 0;
                        whole_number = 0;
                    }
                    else{
                        continue;
                    }
                }

                else if(str[i] == '\0'){
                    //std::cout <<"ENTER TO END OF THE STRING. " << std::endl;
                    return;
                }
                else if(str[i] == '+'){
                    Arithmetic_Selection(str[i],Total,arithmetic);
                }
                else if(str[i] == '*'){
                    Arithmetic_Selection(str[i],Total,arithmetic);
                }
                else if(str[i] == '-'){
                    Arithmetic_Selection(str[i],Total,arithmetic);
                }
                else if(str[i] == '/'){
                    Arithmetic_Selection(str[i],Total,arithmetic);
                }
                else{
                    std::cout << "This RPN only take 4 arithmetics: + - * / . Something is wrong. " << std::endl;
                    exit(1);
                }
                prev_state = current_state;

            }

            return;
        }

};

#endif