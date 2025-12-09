#pragma once
#include <string>
#include <iostream>
#include "PostingList.h"

struct HashNode {
    std::string word;
    PostingList* postings;
    HashNode* next; 

    HashNode(std::string w) : word(w), next(nullptr) {
        postings = new PostingList();
    }
    
    ~HashNode() { delete postings; }
};

class HashIndex {
private:
    static const int TABLE_SIZE = 100; 
    HashNode* table[TABLE_SIZE];

    // Unit 6: Hash Function
    int hashFunction(std::string word) {
        int hash = 0;
        for (char c : word) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return (hash < 0) ? -hash : hash;
    }

public:
    HashIndex() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }

    ~HashIndex() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* prev = current;
                current = current->next;
                delete prev;
            }
        }
    }

    void insert(std::string word, int docID) {
        int index = hashFunction(word);
        HashNode* current = table[index];

        while (current != nullptr) {
            if (current->word == word) {
                current->postings->add(docID);
                return;
            }
            current = current->next;
        }

        HashNode* newNode = new HashNode(word);
        newNode->postings->add(docID);
        newNode->next = table[index];
        table[index] = newNode;
    }

    void search(std::string word) {
        int index = hashFunction(word);
        HashNode* current = table[index];

        while (current != nullptr) {
            if (current->word == word) {
                std::cout << "[Hash Found] Word: '" << word << "' in ";
                current->postings->display();
                std::cout << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "[Hash] Word '" << word << "' not found." << std::endl;
    }

    PostingList* getPostingList(std::string word) {
        int index = hashFunction(word);
        HashNode* current = table[index];
        while (current != nullptr) {
            if (current->word == word) return current->postings;
            current = current->next;
        }
        return nullptr;
    }
};