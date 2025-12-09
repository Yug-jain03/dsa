#pragma once
#include <iostream>


struct PostingNode {
    int docID;
    PostingNode* next;

    PostingNode(int id) : docID(id), next(nullptr) {}
};

class PostingList {
public:
    PostingNode* head;

    PostingList() : head(nullptr) {}

    
    ~PostingList() {
        PostingNode* current = head;
        while (current != nullptr) {
            PostingNode* next = current->next;
            delete current;
            current = next;
        }
    }

    
    void add(int docID) {
        if (!head) {
            head = new PostingNode(docID);
            return;
        }
        
        PostingNode* temp = head;
        while (temp->next != nullptr) {
            if (temp->docID == docID) return; 
            temp = temp->next;
        }
        
        if (temp->docID != docID) {
            temp->next = new PostingNode(docID);
        }
    }

    void display() {
        PostingNode* temp = head;
        while (temp != nullptr) {
            std::cout << "Doc" << temp->docID << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL";
    }

    static PostingList* intersect(PostingList* list1, PostingList* list2) {
        PostingList* result = new PostingList();
        
        if (!list1 || !list2) return result; 

        PostingNode* p1 = list1->head;
        PostingNode* p2 = list2->head;

    
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->docID == p2->docID) {
             
                result->add(p1->docID);
                p1 = p1->next;
                p2 = p2->next;
            } 
            else if (p1->docID < p2->docID) {
                p1 = p1->next; 
            } 
            else {
                p2 = p2->next; 
            }
        }
        return result;
    }
};