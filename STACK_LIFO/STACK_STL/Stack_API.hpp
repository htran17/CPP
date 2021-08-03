#ifndef Stack_API_HPP
#define Stack_API_HPP
#include<iostream>
#include<stack>
#include<cmath>
#include<string>

//Stack is last in first our. when print out , the first element(the last push to stack) is on the top. 
//The last element(the first value push to stack) is on the bottom. 

void Print(std::stack<int> &my_stack){
    if(my_stack.empty() == true){
        std::cout << "No element in stack. " << std::endl;
        return;
    }
    std::stack<int> temp;
    int counter = 0;
    while(my_stack.empty() == false){
        std::cout << "Position: " << counter << " . Value: " << my_stack.top() << std::endl;
        temp.push(my_stack.top());
        my_stack.pop();
        counter++;
    }
    while(temp.empty() == false){
        my_stack.push(temp.top());
        temp.pop();
    }

    return;
}

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


void RPN_Calculation(std::string &str, int &result){
    std::stack<int> my_stack;
    int number = 0, digit = 0, counter_power = 0, counter_arithmetic = 0; 
    char prev_state, current_state;
    for(int i = 0; i < str[i]; i++){
        current_state = str[i];
        if(str[i] >= '0' && str[i] <= '9'){
            digit = str[i] - '0';
            number = number * pow(10,counter_power) + digit;
            counter_power++;
        }

        else if(str[i] == ','){
            if(prev_state != '+'){
                my_stack.push(number);
                number = 0, digit = 0,counter_power = 0;
            }
            
        }

        else if(str[i] == '+'){
            counter_arithmetic++;
            if(counter_arithmetic == 1){
                result = my_stack.top();
                my_stack.pop();
                result = result + my_stack.top();
                my_stack.pop();
            }
            else{
                result = result + my_stack.top();
                my_stack.pop();
            }
        }

        else if(str[i] == '*'){
            counter_arithmetic++;
            if(counter_arithmetic == 1){
                result = my_stack.top();
                my_stack.pop();
                result = my_stack.top() * result;
                my_stack.pop();
            }
            else{
                result = result * my_stack.top();
                my_stack.pop();
            }
        }

        else if(str[i] == '-'){
            counter_arithmetic++;
            if(counter_arithmetic == 1){
                result = my_stack.top();
                my_stack.pop();
                result = my_stack.top() - result;
                my_stack.pop();
            }
            else{
                result = result - my_stack.top();
                my_stack.pop();
            }
        }

        else if(str[i] == '/'){
            counter_arithmetic++;
            if(counter_arithmetic == 1){
                result = my_stack.top();
                my_stack.pop();
                result = my_stack.top() / result;
                my_stack.pop();
            }
            else{
                result = result / my_stack.top();
                my_stack.pop();
            }
        }
            

        else if(str[i] == '\0'){
            return;
        }

        else{
            std::cout << "some errors occur. Please check your code. " << std::endl;
            return;
        }

        prev_state = current_state;

    }
    return;
}



#endif

