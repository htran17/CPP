#include<iostream>
#include<array>
#include<vector>

//Eight houses, represented as cells, are arranged in a straight line. Each day every cell competes with its adjacent cells(neighbors). 
//An integer value of 1 represents an active cell and a value of 0 represents an inactive cell. 
//If the neighbors on both sides of a cell are either active or inactive, the cell becomes inactive on the next day, otherwise the cell becomes active. 
//The two cell on each end have a single a single adjacent cell, so assume that the unoccupied space on the opposite side is an inactive cell. 
//Even after updating the cell state, consider its previous state when updating the state of other cells. 
//The state information of all cells should be updated simultaneously.
//Create an algorithm to output the state of the cells after the given number of days.

//case study:
// 8 houses either 0 or 1: EX: 1 1 1 1 0 0 0 0 with both adjacent cell are 0 => (0) 1 1 1 1 0 0 0 0 (0)
// inactivate cell: neighbors both side inactive or active  (0) 0 (0)  => 0
//                                                          (1) 0 (1)  => 0
//                                                          (0) 1 (0)  => 0
//                                                          (1) 1 (1)  => 0 
// active cell: neighbors   (0) 0 (1) => 1
//                          (1) 0 (0) => 1
//                          (0) 1 (1) => 1
//                          (1) 1 (0) => 1

//Algorithm:
// use Xor gate ^ to apply to active and inactive cell. 
//  A   b   c
//  0   0   0
//  0   1   1
//  1   0   1
//  1   1   0

// pass std::array in C++
void cell_change(std::array<bool,8> &array_in, std::array<bool,8> &array_out, int &day){
    std::array<bool,8> temp_in, temp_out;
    temp_in = array_in;
    while(day > 0){
        temp_out[0] = 0 ^ temp_in[1];
        temp_out[7] = temp_in[6] ^ 0;
        for(int i = 1; i < (temp_in.size()-1); i++){
            temp_out[i] = temp_in[i-1] ^ temp_in[i+1];
        }
        day--;
        if(day > 0){
            temp_in = temp_out;
        }
    }
    array_out = temp_out;
    return;
}

//pass c array and return in c++ vector.
std::vector<int> cellCompete(int* states, int days){
    std::vector<int> vector_in(8);
    std::vector<int> vector_out(8);
    for(int i = 0; i < vector_in.size(); i++){
        vector_in[i] = *(states + i);
    }
    for(int j = 0; j < vector_in.size();j++){
        std::cout << " " << vector_in[j];
    }
    std::cout << " " << std::endl;

    while(days > 0){
        vector_out[0] = 0 ^ vector_in[1];
        vector_out[7] = vector_in[6] ^ 0;
        for(int i = 1; i < 7; i++){
            vector_out[i] = vector_in[i-1] ^ vector_in[i+1];
        }
        for(int j = 0; j < vector_out.size();j++){
            std::cout << " " << vector_out[j];
        }
        std::cout << " " << std::endl;
        days--;
        if(days > 0){
            vector_in = vector_out;
        }
    }
    return vector_out;

}



int main(){
    std::array<bool,8> array = {1,1,1,0,1,1,1,1}; //0 0 0 0 0 1 1 0
    std::array<bool,8> array_out;
    int day = 1;
    
    
    cell_change(array,array_out,day);
    for(int i = 0; i < array_out.size(); i++){
        std::cout << "array_out: " << array_out[i] << std::endl;
    }
    
    int my_array[] = {1,1,1,0,1,1,1,1};//0 0 0 0 0 1 1 0
    std::vector<int> your_array(8);
    your_array = cellCompete(my_array,2);
    return 0;
}