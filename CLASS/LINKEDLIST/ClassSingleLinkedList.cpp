#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<memory>

class Node{
    public:
        int value;
        Node* next;
};

class SingleLinkedList:public Node{
    public:
        virtual void PrintList(Node* head){
            int counter = 0;
            while(head != NULL){
                std::cout << "Value: " << head -> value << ". Position: " << counter  << std::endl;
                head = head -> next;
                counter++;
            }
            return;
        }

        virtual void Add2Back(Node* &head, int number){
            Node* new_node = new Node;
            new_node -> value = number;
            Node* travel = head;
            if(head == NULL){
                head = new_node;
            }
            else{
                while(travel -> next){
                    travel = travel -> next;
                }
                travel -> next = new_node;
            }
            return;
        }

        void Add2Front(Node* &head, int number){
            Node* new_node = new Node;
            new_node -> value = number;

            new_node -> next = head;// point next to head
            head = new_node;// define again head is new_node

        }

        virtual void DeleteByValue(Node* &head, int number){
            Node* prev_node = NULL;
            Node* current_node = head;
            int counter = 0;
            if(head -> value == number){
                head = head -> next;
            }
            else{
                while(current_node -> next){
                    prev_node = current_node;
                    current_node = current_node -> next;
                    if (current_node -> value == number){
                        std::cout<< "prev_node: " << prev_node -> value << std::endl;
                        prev_node -> next = current_node -> next;
                        delete current_node;
                        counter++;
                    }        
                }
                if(counter == 0){
                    std::cout << "No node with value " << number << " in list" << std::endl;
                }
            }
            
            return;
        }

        void DeleteByPosition(Node* &head, int position){
            int counter = 0;
            Node* prev_node = NULL;
            Node* current_node = head;
            if(position == 0){
                head = head -> next;
            }
            else{
                while(current_node -> next){
                    prev_node = current_node;
                    current_node = current_node -> next;
                    counter++;
                    if(counter == position){
                        prev_node -> next = current_node -> next;
                        delete current_node;
                    }
                }
            }
            if(position > counter){
                std::cout << "Please enter the position integer from range 0 to " << counter << std::endl;
            }
            return;
        }
        //algorithm
        //need 3 nodes. prev_node, current_node = head and next_node.
        //current_node is not NULL. 
        //step1: point current_node to next_node.
        //step2: point current_node to prev_node.
        //step3: move prev_node to current_node.
        //step4: move current_node to next_node.
        //end of node. prev_node is a last node. make sure copy prev_node to head. 
        void Reverse(Node* &head){
            Node* prev_node = NULL;
            Node* current_node = head;
            Node* next_node = NULL;

            while(current_node != NULL){
                next_node = current_node -> next;
                current_node -> next = prev_node;
                prev_node = current_node;
                current_node = next_node;
            }
            head = prev_node;
            return;
            
        }
        //algorithm
        //check both linked lists are not NULL in while loop.
        //compare the value at current node in both linkedlist. new_node will copy the smaller node. 
        //point new_node to a smaller current node in both lists. Move a smaller current node to the next node in list. travel the new_list to next node.
        //exit out the while loop in both case when list1 == NULL and List2 == NULL
        void Merge2SortLinkedList(Node* &head1, Node* &head2, Node* &new_node){
            new_node = new Node;
            Node* travel1 = head1;
            Node* travel2 = head2;
            Node* new_list = new_node;

            while(travel1 != NULL || travel2 != NULL){
                if(travel1 -> value > travel2 -> value){
                    new_list -> next = travel2;
                    travel2 = travel2 -> next;
                    new_list = new_list -> next;
                }
                else{
                    new_list -> next = travel1;
                    travel1 = travel1 -> next;
                    new_list = new_list -> next;
                }

                if(travel1 == NULL){
                    new_list -> next = travel2;
                    break;
                }
                if(travel2 == NULL){
                    new_list -> next = travel1;
                    break;
                }
            }
            new_node = new_node -> next;
            return;
        }

        void DeepCopy(Node* &head, Node* &new_list){
            std::cout << "enter the deep copy " << std::endl;
            Node* travel = head;
            while(travel != NULL){// or while(head) //true
                Add2Back(new_list,travel -> value);
                std::cout << "enter the while loop deep copy: " << head -> value << std::endl;
                travel = travel -> next;
            }
            return;
        }

};

class RecursionSingleLinkedList: public SingleLinkedList{
    public:
        int counter = 0;
        void PrintList(Node* head, int counter = 0){
            if(head == NULL){
                return;
            }
            std::cout << "Value: " << head -> value << ". Counter " << counter << std::endl;
            counter++;
            PrintList(head -> next,counter);
            return;
        }

        void Add2Back(Node* &head, int number){
            if(head == NULL){
                Node* new_node = new Node;
                new_node -> value = number;
                head = new_node;
                return;
            }
            Add2Back(head->next,number);
            return;
        }

        //algorithm
        //travel in head.
        //create a separate node by allocate new node in new list and copy the value from head.
        //when head move to NULL => exit or return to previous upper function.
        void CloneLinkedList(Node* &head, Node* &new_node){
            if(head == NULL){
                return;
            }
            new_node = new Node;// allocate
            new_node -> value = head -> value;
            CloneLinkedList(head -> next, new_node -> next);
            return;
        }

};

int main(){
    
    SingleLinkedList Ryan;
    RecursionSingleLinkedList Ryan_derived;
    SingleLinkedList* Ryan_ptr = &Ryan_derived;
    
    Node* head = NULL;
    Node* new_node = NULL;
    Node* new_head = NULL;

    Ryan_ptr -> Add2Back(head, 3);
    Ryan_ptr -> Add2Back(head, 4);
    Ryan_ptr -> Add2Back(head, 5);
    Ryan_ptr -> DeepCopy(head,new_head);
    //Ryan_ptr -> DeleteByPosition(new_head,2);
    Ryan_derived.PrintList(new_head);
    std::cout << "PRINT OUT HEAD" << std::endl;
    Ryan_ptr -> PrintList(head);
    Ryan_ptr -> Merge2SortLinkedList(head,new_head, new_node);
    std::cout << "PRINT OUT new node" << std::endl;

    Ryan_derived.PrintList(new_node);
    std::cout << "PRINT OUT add new node" << std::endl;

    Ryan_derived.Add2Back(new_node,7);
    Node* new_list = NULL;
    Ryan_derived.CloneLinkedList(new_node, new_list);
    Ryan_derived.DeleteByPosition(new_list,4);
    Ryan_derived.PrintList(new_list);


    return 0;
}

