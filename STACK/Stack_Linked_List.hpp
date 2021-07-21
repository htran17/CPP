#ifndef Stack_Linked_List_HPP
#define Stack_Linked_List_HPP
#include<iostream>

class Node{
    public:
        int value;
        Node* next;
};

class Stack_Linked_List{
    private:
        Node* head;
    public:
        Stack_Linked_List():head(NULL){};
        
        void Print(){
            if(head == NULL){
                std::cout << "No element in this stack. " << std::endl;
                return;
            }
            Node *travel = head;
            while(travel != NULL){
                int counter = 0;
                std::cout << "Position: " << counter << " . Value: " << travel -> value << std::endl;
                travel = travel -> next;
                counter++;
            }
            return;
        }

        void Push(int number){
            Node* new_node = new Node;
            new_node -> value = number;
            new_node -> next = head;
            head = new_node;
            return;
        }

        void Pop(){
            if(head == NULL){
                std::cout << "this stack is empty. Can't delete a top element. " << std::endl;
                return;
            }
            head = head -> next;
            return;
        }

        void Size(int &counter){
            if(head == NULL){
                std::cout << "No element in this stack. Size is 0 " << std::endl;
                return;
            }
            Node *travel = head;
            while(travel != NULL){
                counter = 0;
                //std::cout << "Position: " << counter << " . Value: " << travel -> value << std::endl;
                travel = travel -> next;
                counter++;
            }
            return;
        }

        void Top(int &number){
            if(head == NULL){
                std::cout << "Stack is empty. No value of the top element. " << std::endl;
                return;
            }
            number = head -> value;
            return;
        }

        bool Empty(){
            if(head == NULL){
                return true;
            }
            else{
                return false;
            }
        }
};

#endif