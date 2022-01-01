#include<iostream>
#include<vector>

class QuickSort{
    public:
        //Pass by Reference
        void Swap(int &number1, int &number2){
            int temp =0;
            temp = number1;
            number1 = number2;
            number2 = temp;
            return;
        }
        //Pass by Pointer
        void Swap(int *number1, int *number2){
            int temp = 0;
            temp = *number1;
            *number1 = *number2;
            *number2 = temp;
            return;
        }
        
        //algorithm for partition: Use 2 iteration i and j to push all smaller than pivot to left and bigger number to right of pivot.
        //Every number on the right side of i means bigger and equal to pivot.
        //using iteration j to go to all elements in array to check it smaller than pivot. j run from index 0 to the last index - 1. We pick pivot number is the last index in array.
        // If the element smaller than pivot => i++ => at this time, i is locate at the element which is bigger than  pivot. j is location at the element smaller than pivot. 
        // Swap array[i] to array[j]. 
        
        //Pass by vector
        int Partition(std::vector<int> &array, int low, int high){
            int pivot = array[high];
            int i = low - 1;
            for(int j = low; j < high; j++){
                if(array[j] < pivot){
                    i++;
                    Swap(array[j], array[i]);
                }
            }
            Swap(array[i+1],array[high]);
            return i+1;
        }
        //pass by C array
        int Partition(int *array, int low, int high){
            int pivot = *(array + high);
            int i = low - 1;
            for(int j = low; j < high; j++){
                if(*(array + j) < pivot){
                    i++;
                    Swap(*(array + j), *(array + i));
                }
            }
            Swap(*(array + i + 1), *(array + high));
            return i+1;
        }        

        //pass by vector
        void Quick_Sort(std::vector<int> &array,int low, int high){
            if(low < high){
                int pivot = Partition(array,low,high);
                Quick_Sort(array,low,pivot-1);
                Quick_Sort(array,pivot +1,high);
                return;
            }
        }
        //Pass by C array
        void Quick_Sort(int *array, int low, int high){
            if(low < high){
                int pivot = Partition(array,low,high);
                Quick_Sort(array, low, pivot -1);
                Quick_Sort(array,pivot + 1, high);
                return;
            }
        }

};

int main(){
    QuickSort MySort;
    std::vector<int> my_array {10,9,8,7,5,4,3,2,6};
    int high = my_array.size() - 1;
    int low = 0;
    int pivot = MySort.Partition(my_array,low,high);
    MySort.Quick_Sort(my_array,low,high);
    std::cout <<"index pivot pass by vector: " << pivot << std::endl;
    for(int i = 0; i < my_array.size();i++){
        std::cout << my_array[i] << " "; 
    }
    std::cout << " " << std::endl;


    int array[] = {11,10,9,8,6,5,4,7};
    int array_high = sizeof(array)/sizeof(array[0]) - 1;
    int array_low = 0;
    int index_pivot = MySort.Partition(array, array_low,array_high);
    MySort.Quick_Sort(array,array_low,array_high);
    std::cout << "index pivot pass by c array: " << index_pivot << std::endl;
    for(int i = 0; i < (sizeof(array)/sizeof(array[0])); i++){
        std::cout << array[i] << " ";
    }
    std::cout << " " << std::endl;

    return 0;
}