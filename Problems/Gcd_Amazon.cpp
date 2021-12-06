#include<iostream>
#include<vector>
#include<array>
//The greatest common divisor(GCD), also called highest common factor (HCF) of N number 
//is the largest positive integer the divedes all numbers without giving a remainder.

//write an algorithm to determine the GCD of N positive integres. 
//Input
//The input to the finction/method consists of two arguments-
//num, an integer representing the number of positive integers.
//arr, a list of positive integers.
//Output
//Return an integer representing the GCD of the given positive integers.

//Example
//Input:
//num = 5
//arr = [2,4.6.8,10]
//Output:
//2
//Explaination:
//THe largest positive integer that divides all the positive integers 2,4,6,8,10 without a remainder is 2.  So the output is 2.

//Algorithm
//GCD in 2 numbers is the largest number that divides them both. For Example: GCD(6,9) is 3 because 9/3 and 6/3. 
//Factor:
//9: 1,3,9
//6: 1,3,6
// => 3 is the greatest common divisor(GCD) between 6 and 9.

//Factor:
// 2: 1,2
// 4: 1,2,4
// 6: 1,2,3,6
// 8: 1,2,4,8
// 10: 1,2,5,10
// The greatest common divisor(GCD) is 2. 

//2 number a and b. Case number when a > b, a < b, a = b, a = 0, b = 0;
//a= 0 => GCD = b; b = 0 => GCD = a. why? because 0*5 = 0 => 0/5 = 0 => 5 is divisor of 0.
//a = b => GCD = a = b;
//a > b => GCD(a-b,b) => recussion until a = b => GCD = a = b;
//a < b => GCD(a,b-a) => recussion until a = b => GCD = a = b;

//vector numbers with GCD;
//Pick first element is gcd then use GCD for 2 numbers to find the GCD between 2 number. 
//Like: gcd = vector[0] => 
//for (int i = 1; i < vector.size(); i++){
//      gcd = (gcd,vector[i])
//      if(gcd = 1) special case.
//          return 1;
//}

//C array. pass pointer array, array size.
// pick a first point array element.
// use for loop to  iterate gcd 2 numbers

//std array



int GCD2number(int &a, int &b){
    int gcd = -1;
    int c = -1;
    if(a == 0){
        return gcd = b;
    }

    if(b==0){
        return gcd = a;
    }

    if(a == b){
        return gcd = a;
    }

    if(a > b){
        c = a - b;
        return GCD2number(c,b);
    }

    if(a < b){
        c = b - a;
        return GCD2number(a,c);
    }
}
//GCD of an vector.
void GCD_Function(std::vector<int> &my_vector, int &gcd){
    gcd = my_vector[0];
    for(int i = 1; i < my_vector.size(); i++){
        gcd = GCD2number(gcd,my_vector[i]);
        if(gcd == 1){
            return;
        }
    }
    return;
}

//GCD of an C array
void GCD_Function_C_Array(int *array, int &size_array, int &gcd){
    gcd = *(array + 0);
    for(int i = 1; i < size_array; i++){
        gcd = GCD2number(gcd,*(array + i));
        if(gcd == 1){
            return;
        }
    }
    return;
}

template<size_t SIZE>

void GCD_Function_STD_Array(std::array<int,SIZE> &array, int &gcd){
    gcd = array[0];
    for(int i = 1; i < array.size(); i++){
        gcd = GCD2number(gcd,array[i]);
        if(gcd == 1){
            return;
        }
    } 
}


int main(){
    std::vector<int> my_vector = {99,9,6,15,0};
    int gcd = -1;
    GCD_Function(my_vector,gcd);
    std::cout << "GCD of vector is: " << gcd << std::endl;
    int array[] = {2,8,4,10};
    int size_array = sizeof(array)/sizeof(array[0]);
    GCD_Function_C_Array(array,size_array,gcd);
    std::cout << "GCD of C array: " << gcd << std::endl;
    std::array<int,5> std_array = {4,8,20,40,60};
    GCD_Function_STD_Array(std_array,gcd);
    std::cout << "GCD of std array: " << gcd << std::endl;

    return 0;

}