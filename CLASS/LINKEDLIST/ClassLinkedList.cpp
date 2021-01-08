#include<iostream>
#include<string>
#include<vector>
#include<queue>

class Node{
    public:
        int value;
        Node* next;
};

class LinkedList:public Node{
    public:


        virtual void PrintList(Node* head){
            int counter =0;
            if(IsCycle(head)){
                std::cout << "this is a cycle Linked List. " << std::endl;
                return;
            }
            else{
                std::cout << "this is a regular Linked List. " << std::endl;

            }
            while(head != NULL){
                std::cout <<"VALUE: " << head -> value << ". Position: " << counter << std::endl;
                head = head -> next; 
                counter++;

            }
            return;
        }

        virtual void Add2Back(Node* &head, int number){
            Node* new_node = new Node;
            Node* travel = NULL;
            new_node -> value = number;
            if(head == NULL){
                head = new_node;
            }
            else{
                travel = head;
                while(travel-> next){
                    travel = travel -> next;
                }
                travel -> next = new_node;
            }
            return;
        }

        void Add2Front(Node* *head, int number){
            Node* new_node = new Node;
            new_node -> value = number;
            //add new_node in front of head
            new_node -> next = *head;
            *head = new_node;//define head is new_node
            return;
        }
        //
        void DeleteByValue(Node* &head, int number){
            Node* current_node = NULL;
            current_node = head;
            Node* prev_node = NULL;
            if(head -> value == number){
                head = head -> next;
            }
            else{
                while(current_node -> next){
                    prev_node = current_node;
                    current_node = current_node -> next;
                    if(current_node -> value == number){
                        prev_node -> next = current_node -> next;
                        delete current_node;
                    }
                }
            }
            return;
        }
        //2 nodes. 1 previous, 1 current.
        //counter to count position.
        void DeleteByPosition(Node* &head, int position){
            Node* prev_node = NULL;
            Node* current_node = head;
            int counter = 0;
            if(position == 0){
                head = head -> next;
                return;
            }
            else{
                while(current_node -> next){
                    counter++;
                    prev_node = current_node;
                    current_node = current_node -> next;
                    if(counter == position){
                        prev_node -> next = current_node -> next;
                        delete current_node;
                    }
                   
                }
            }
            if(position > counter){
                std::cout << "No Node" << std::endl;
            }
            return;
        }
        //
        void Merge2SortLinkList(Node* *head1, Node* *head2, Node* &new_head){
            new_head = new Node;
            Node* copy_head1 = *head1;
            Node* copy_head2 = *head2;
            Node* copy_new_head = new_head;
            while(copy_head1 != NULL || copy_head2 != NULL){
                
                if(copy_head1 -> value <= copy_head2 -> value){
                    copy_new_head -> next = copy_head1;
                    copy_head1 = copy_head1 -> next;
                    copy_new_head = copy_new_head -> next;
                }
                else{
                    copy_new_head -> next = copy_head2;
                    copy_head2 = copy_head2 -> next;
                    copy_new_head = copy_new_head -> next;
                }

                if(copy_head1 == NULL){
                    copy_new_head -> next = copy_head2;
                    break;
                }
                if(copy_head2 == NULL){
                    copy_new_head -> next = copy_head1;
                    break;
                }

            }
            new_head = new_head -> next;
            return;
        }
        //using recursion
        //allocate new node
        //set new_node -> next to next node in head.
        //end of the list => return to previous recursive function
        Node* CloneLinkedList(Node* &head){
            Node* new_list = new Node; //allocate each node in new linked list
            if(head == NULL){//end of list
                std::cout << "move up" << std::endl;
                return head; // return to previous recursive function.
            }
            new_list -> value = head -> value;//copy each value of head to new_list
            new_list -> next = CloneLinkedList(head -> next);
            return new_list;
        }

        void CloneLinkedList1(Node* &head, Node* &new_list){
            if(head == NULL){//end of list
                std::cout << "move up" << std::endl;
                return; // return to previous recursive function.
            }
            new_list = new Node; //allocate each node in new linked list
            new_list -> value = head -> value;//copy each value of head to new_list
            CloneLinkedList1(head -> next,new_list -> next);
            return;
        }
        //Need 3 nodes. prev_node , current_node and next_node.
        //current_node = head. move next_node to a node ahead of current_node.
        //point current_node to prev_node.
        //move prev_node to current_node.
        //move current_node to next node.
        //now prev_node store all nodes but reverse. point head to prev_node.
        void Reverse(Node* &head){
            Node* next_node = NULL;
            Node* prev_node = NULL;
            Node* current_node = head;
            while(current_node!=NULL){
                next_node = current_node -> next;
                current_node -> next = prev_node;

                prev_node = current_node;
                current_node = next_node;
            }
            head = prev_node;//prev node
            return;
        }

        bool IsCycle(Node* &head){
            if(head == NULL){
                return true;
            }
            std::cout << head -> value << std::endl;
            Node* travel = head -> next;
            while(travel != NULL && travel != head){
                std::cout << travel -> value << std::endl;
                travel = travel -> next;
            }
            return (travel == head);
        }

        void CycleList(Node* &head){
            Node* travel = NULL;
            travel = head;
            while(travel -> next){
                travel = travel -> next;
                if(travel -> next == NULL){
                    travel -> next = head;
                    return;
                }
            }
            return;
        }

        

        //determine the same nodes ( same values) in 2 cycle list at the end of 2 cycle linked list
        //use 2 for loop. each for loop is iteration each cycle list.
        //find  a interval in both cycle linked list.

        void Overlapping(Node* &head1, Node* &head2){
            Node* travel1 = head1;
            Node* travel2 = head2;
            int length = 0;
             

        }
};

class SecondLinkedList:public LinkedList{
    public:
        void PrintNode(Node* head){
            if(head == NULL){
                return;
            }
            std::cout << head -> value << std::endl;
            PrintNode(head -> next);
            return;
        }
        
        void PrintList(Node* head){
            if(IsCycle(head)){
                std::cout << "this is a cycle Linked List. " << std::endl;
                return;
            }
            else{
                std::cout << "this is a regular Linked List. " << std::endl;      
                
            }
            PrintNode(head);
            return;
            

        }
        
        void Add2Back(Node* &head, int number){
            if(head == NULL){
                Node* new_node = new Node;
                new_node -> value = number;
                head = new_node;
                return;
            } 
            Add2Back(head -> next, number);
            return;
        }
};

int main(){
    LinkedList Ryan;
    SecondLinkedList Ryan_derived;
    LinkedList* Ryan_ptr = &Ryan_derived;
    Node* head = NULL;

    Ryan_ptr -> Add2Back(head,4);
    Ryan_ptr -> Add2Back(head,5);

    Ryan_ptr -> PrintList(head);

    Ryan_ptr -> CycleList(head);
    Ryan_ptr -> PrintList(head);
/*

    Ryan_ptr -> Add2Front(&head,3);
    Ryan_ptr -> Add2Back(head,6);
    Ryan_ptr -> Add2Back(head,7);

    //Ryan_ptr -> DeleteByPosition(head,0);
    Ryan_ptr -> PrintList(head);

    Node* head2 = NULL;
    Ryan_ptr -> Add2Front(&head2,8);
    Ryan_ptr -> Add2Back(head2,9);
    Ryan_ptr -> Add2Back(head2,10);

    Ryan_ptr -> PrintList(head2);

    Node* new_head = NULL;

    Ryan_ptr -> Merge2SortLinkList(&head,&head2,new_head);
    Ryan_ptr -> PrintList(new_head);
    std::cout << "-----" << std::endl;

    Node* new_list = NULL;
    //new_list =Ryan.CloneLinkedList(new_head);
    Ryan_ptr -> CloneLinkedList1(new_head, new_list);

    Ryan_ptr -> DeleteByValue(new_head,10);
    //Ryan_ptr -> PrintList(new_list);
        
    std::cout << "new_head -----" << std::endl;
    Ryan_ptr -> PrintList(new_head);
    std::cout << "new_list -----" << std::endl;

    Ryan_ptr -> PrintList(new_list);

    Ryan_ptr -> Reverse(new_list);
    std::cout << "Reverse new_list -----" << std::endl;
    //Ryan_ptr -> PrintList(new_list);

    Ryan_ptr -> CycleList(new_list);
    Ryan_ptr -> PrintList(new_list);

*/
    return 0;
}