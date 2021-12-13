#ifndef LinkedListClass_hpp
#define LinkedListClass_hpp
#include<iostream>

class Node{
    public:
        int value;
        Node* next;
};

class Linked_List{
    private:
        Node* head;
    public:
        Linked_List(){
            head = NULL;
        }

        Linked_List(int number){
           Node* new_node = new Node;
           new_node -> value = number;
           new_node -> next = NULL;
           head = new_node;
        }

        ~Linked_List(){
            std::cout << "END of This class. " << std::endl;
        }

        int Get_Value_Head() const {
            return head -> value;
        }
        int Get_Value_Head(Node* new_head) const{
            return new_head -> value;
        }

        Node* Get_List() const { //return whole private linked list (with linked list class created)
            return head;
        }
        Node* Get_List(Node* new_head) const{ // return a whole linked list (with linked list class not created that list) to another linked list.
            return new_head;
        }

        void Copy_Linked_List(Node*& new_head){

            if(head == NULL){
                std::cout << "This Linked List is empty. Can't copy it" << std::endl;
                return;
            }
            Node* travel = head;
            while(travel != NULL){
                Add_Back(new_head,travel -> value);
                travel = travel -> next;
            }
            return;
        }

        void Add_Back(int number){ //add to the private head
            Node* new_node = new Node;
            new_node -> value = number;
            if(head == NULL){
                new_node -> next  = head;
                head = new_node;
                return;
            }
            Node* travel = head;
            while(travel -> next != NULL){
                travel = travel -> next;
            }
            travel -> next = new_node;
            return;
        }
        void Add_Back(Node*& new_head, int number){ //add to the new head
            Node* new_node = new Node;
            new_node -> value = number;
            Node* travel = new_head;

            if(new_head == NULL){
                new_node -> next  = new_head;
                new_head = new_node;
                return;
            }
            
            while(travel -> next != NULL){
                travel = travel -> next;
            }
            travel -> next = new_node;
            return;
        }

        

        void Add_Front(int number){
            Node* new_node = new Node;
            new_node -> value = number;
            new_node -> next = head;
            head = new_node;
        }
        void Add_Front(Node*& new_head,int number){
            Node* new_node = new Node;
            new_node -> value = number;
            new_node -> next = new_head;
            new_head = new_node;
        }
        

        void Print(){
            if(head == NULL){
                std::cout << "in Print statement: This linked list is empty. " << std::endl;
                return;
            }
            Node* travel = head;
            int counter = 0;
            while(travel  != NULL){
                std::cout << "counter: " << counter << " . Travel: " << travel -> value << std::endl;
                counter++;
                travel = travel -> next;
            }
            return;
        }
        void Print(Node*& new_head){
            if(new_head == NULL){
                std::cout << "This linked list is empty. " << std::endl;
                return;
            }
            Node* travel = new_head;
            int counter = 0;
            while(travel  != NULL){
                std::cout << "counter: " << counter << " . Travel: " << travel -> value << std::endl;
                counter++;
                travel = travel -> next;
            }
        }

        void DeleteByValue(int number){
            if(head == NULL){
                std::cout << "This Linked List has no element. " << std::endl;
                return;
            }

            Node* new_list = NULL;
            Node* travel = head;
            while(travel != NULL){
                if(travel -> value == number){
                    travel = travel -> next;
                }

                else if(travel == NULL){
                    break;
                }

                else{
                    Add_Back(new_list,travel -> value);
                    travel = travel -> next;
                }
            }

            head = new_list;
            return;
        }

        void DeleteByValue(Node*& new_head,int number){
            if(new_head == NULL){
                std::cout << "This Linked List has no element. " << std::endl;
                return;
            }

            Node* new_list = NULL;
            Node* travel = new_head;
            while(travel != NULL){
                if(travel -> value == number){
                    travel = travel -> next;
                }

                else if(travel == NULL){
                    break;
                }

                else{
                    Add_Back(new_list,travel -> value);
                    travel = travel -> next;
                }
            }

            new_head = new_list;
            return;
        }


        void DeleteByPosition(int position){
            if(head == NULL){
                std::cout << "Delete By Position: This Linked List has no Element. " << std::endl;
                return;
            }
            int counter = 0; 
            Node* new_list = NULL;
            Node* travel = head;

            while(travel != NULL){
                if(position == counter){
                    travel = travel -> next;
                    counter++;
                }
                else if(travel == NULL){
                    break;
                }
                else{
                    Add_Back(new_list,travel -> value);
                    travel = travel -> next;
                    counter++;
                }
            }
            head = new_list;
            return;
        }

        void DeleteByPosition(Node*& new_head, int position){
            if(new_head == NULL){
                std::cout << "Can't delete because this link list is empty. " << std::endl;
                return;
            }
            int counter = 0;
            Node* list = NULL;
            Node* travel = new_head;
            while(travel != NULL){
                if(position == counter){
                    travel = travel -> next;
                    counter++;
                }
                else if(travel == NULL){
                    break;
                }
                else{
                    Add_Back(list,travel -> value);
                    travel = travel -> next;
                    counter++;
                }
            }
            new_head = list;
            return;
            
        }

};

#endif
