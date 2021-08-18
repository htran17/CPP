#include<iostream>

//count set bit mean count how many set bit 1 in binary number.
// EX: 6 in binary is 0110. => count set bit means 6 has 2 set bits. 

void Count_Set_Bit(int number, int &count){
    while(number != 0){
        count = count + (number & 1);
        number = number >> 1;
    }
}

int main(){
    int count = 0;
    Count_Set_Bit(10,count);
    std::cout << "count: " << count << std::endl;
    return 0;
}