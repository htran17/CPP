#include<iostream>
#include"ClassSingleLinkedList.hpp"

int main(){
    SingleLinkedList test;
    RecursionSingleLinkedList test_derived;
    SingleLinkedList* test_ptr = &test_derived;

    Node* head = NULL;
    Node* new_head = NULL;

    test_ptr -> Add2Back(head,10);
    test_ptr -> Add2Back(head,20);
    test_ptr -> Add2Back(head,30);
    test_ptr -> Add2Back(head,20);
    test_ptr -> Add2Back(head,20);
    test_ptr -> Add2Back(head,20);

    test_ptr -> DeepCopy(head,new_head);
    test_ptr -> DeleteByValue(head,20);
    test_ptr -> PrintList(head);

    return 0;

}