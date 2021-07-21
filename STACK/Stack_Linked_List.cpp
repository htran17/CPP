#include<iostream>
#include<vector>

class Node{
    public:
        int value;
        Node* next;
};

class Stack:public Node{
    private:
        Node* head;
    public:
        void Push(int number){
            Node* new_node = new Node;
            new_node -> value = number;

            new_node -> next = head;
            head = new_node;
            return;
        }

        void Display(){
            Node *move = head;
            if(move == NULL){
                std::cout << "No Node in stack. " << std::endl;
            }
            while(move != NULL){
                std::cout << move -> value << std::endl;
                move = move -> next;
            }
            return;
        }

        void Pop(){
            if(head == NULL){
                std::cout << "No element in stack. " << std::endl;
                exit(1);
            }
            else{
                head = head -> next;
            }
            return;
        }

        void Size(int &size_number){
            Node *move = head;
            int counter = 0;
            if(move == NULL){
                size_number = 0;
                std::cout << "size of stack: " << size_number << std::endl;
                return;
            }
            while(move != NULL){
                counter++;
                move = move -> next;
            }
            size_number = counter;
            std::cout << "size of stack: " << size_number << std::endl;

            return;
        }

};

int main(){
    Stack Ryan;
    int counter = 0;
    Ryan.Push(5);
    Ryan.Display();
    std::cout << "-----" << std::endl;
    Ryan.Push(51);

    Ryan.Display();

    Ryan.Pop();
    Ryan.Push(13);
    Ryan.Display();
    Ryan.Pop();
    Ryan.Pop();


    Ryan.Size(counter);
    return 0;
}