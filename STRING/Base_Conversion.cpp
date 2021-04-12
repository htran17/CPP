#include<iostream>
#include<sstream>
#include<math.h>

void Base_Conversion(std::string &input_base, int &first_base, std::string &output_base, int &second_base){
    int base10 = 0;
    int counter = 0;
    std::string convert;
    for(int i = input_base.length() - 1; i >= 0; i--){
        if(input_base[i] >= '0' && input_base[i] <= '9'){
            if((input_base[i] - '0') >= first_base){
                std::cout << "check base and number in base. For example: base 10 is included 0 to 9" << std::endl;
                break;
            }
            base10 = base10 + ((input_base[i] -'0') * pow(first_base,counter));// 101 = 1*2^2 + 0*2^1 + 1*2^0
        }
        else if(input_base[i] >= 'A' && input_base[i] <= 'F'){
            if((input_base[i] - 'A' + 10 )>= first_base){
                std::cout << "check base and number in base. For example: base 16 is included 0 to F" << std::endl;
                break;
            }
            base10 = base10 + ((input_base[i] - 'A' + 10) * pow(first_base,counter));
        }
        else if(input_base[i] >= 'a' && input_base[i] <= 'f'){
            if((input_base[i] - 'a' + 10 )>= first_base){
                std::cout << "check base and number in base. For example: base 12 is included 0 to B" << std::endl;
                break;
            }
            base10 = base10 + ((input_base[i] - 'a' + 10) * pow(first_base,counter));
        }
        counter++;
    }
    std::cout << "base10: " <<base10 << std::endl;


    while(base10 != 0){
        if(base10 % second_base >= 10 && base10 % second_base <= 15){
            convert = (base10 % second_base) - 10 + 'A';
            
        }
        else if(base10 % second_base >= 0 && base10 % second_base <= 9){
            convert = (base10 % second_base) + '0';
        }
        output_base = convert + output_base;
        base10 = base10 / second_base;
    }
    return;
}

int main(){
    std::string string("abcd");
    std::string output;
    int input_base = 16, output_base = 3;
    Base_Conversion(string,input_base,output,output_base);
    std::cout << "base" << output_base <<" : " << output << std::endl;
    return 0;
}