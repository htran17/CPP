#include<iostream>
#include<stack>


//input 1234567
//output 1,234,567

//sudoku: take out each number. every 3 number from right side print one comma.

//pass by reference number. Put each digit to a stack(LIFO). 
//EX: 980650 => Stack(LIFO)( 9, 8, 0, 6, 5, 0). Digit will go from left to right in my stack.
void Number2Digits(int& number, std::stack<int> &my_stack){
    int each_digit = 0;
    while(number != 0){
        each_digit = number % 10;
        my_stack.push(each_digit);
        number = number /10;
    }
}
//from stack(LIFO) using counter = stack.size() to know how many element in stack. 
//EX: Stack (9,8,0,6,5,0) => counter = stack.size() = 6. Element 9 should be in location 6, 8 should be in location 5. 0 should be in location 4.
// after 0 should be a comma => (counter % 3 = 1) should put a comma. 
// the resuld should be like 980,650
void Print_Out(std::stack<int> &my_stack){
    int counter = my_stack.size();
    while(!my_stack.empty()){
        std::cout << my_stack.top() ;
        if(counter % 3 == 1 && counter != 1){
            std::cout << ",";
        }
        counter--;
        my_stack.pop();
    }
    std::cout << " " << std::endl;
}

int main(){
    int number = 9701231;
    std::stack<int> my_stack;
    Number2Digits(number,my_stack);
    Print_Out(my_stack);
    return 0;
}