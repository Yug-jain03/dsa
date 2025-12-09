#pragma once
#include <string>
#include <iostream>
#include "PostingList.h"

struct BSTNode {
    std::string word;
    PostingList* postings; 
    BSTNode* left;
    BSTNode* right;

    BSTNode(std::string w) : word(w), left(nullptr), right(nullptr) {
        postings = new PostingList();
    }
    
    ~BSTNode() {
        delete postings;
    }
};

class BSTIndex {
private:
    BSTNode* root;

    BSTNode* insertRecursive(BSTNode* node, std::string word, int docID) {
        if (node == nullptr) {
            BSTNode* newNode = new BSTNode(word);
            newNode->postings->add(docID);
            return newNode;
        }

        if (word == node->word) {
            node->postings->add(docID);
            return node;
        }

        if (word < node->word) {
            node->left = insertRecursive(node->left, word, docID);
        } else {
            node->right = insertRecursive(node->right, word, docID);
        }
        return node;
    }

    BSTNode* searchRecursive(BSTNode* node, std::string word) {
        if (node == nullptr || node->word == word) {
            return node;
        }
        if (word < node->word) {
            return searchRecursive(node->left, word);
        }
        return searchRecursive(node->right, word);
    }

    void destroyTree(BSTNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BSTIndex() : root(nullptr) {}
    ~BSTIndex() { destroyTree(root); }

    void insert(std::string word, int docID) {
        root = insertRecursive(root, word, docID);
    }

    void search(std::string word) {
        BSTNode* result = searchRecursive(root, word);
        if (result) {
            std::cout << "[BST Found] Word: '" << word << "' in ";
            result->postings->display();
            std::cout << std::endl;
        } else {
            std::cout << "[BST] Word '" << word << "' not found." << std::endl;
        }
    }

   
    PostingList* getPostingList(std::string word) {
        BSTNode* node = searchRecursive(root, word);
        return (node != nullptr) ? node->postings : nullptr;
    }
};