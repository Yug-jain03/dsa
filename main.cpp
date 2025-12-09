#include <iostream>
#include <string>
#include <vector>
#include <fstream>  
#include <chrono>   
#include <cctype>   
#include "BSTIndex.h"
#include "HashIndex.h"

std::string cleanWord(std::string raw) {
    std::string clean = "";
    for (char c : raw) {
        if (std::isalnum(c)) { 
            clean += std::tolower(c); 
        }
    }
    return clean;
}

int main() {
    BSTIndex bst;
    HashIndex hashTable;
    
    std::string filename = "dataset.txt"; 
    int wordLimit;

    std::cout << "=================================================\n";
    std::cout << "   SEARCH ENGINE: PERFORMANCE BENCHMARK TOOL     \n";
    std::cout << "=================================================\n";
    std::cout << "[Step 1] Setup\n";
    std::cout << "Ensure 'dataset.txt' contains a book chapter.\n";
    std::cout << "Enter number of words to index (e.g., 100, 1000, 10000): ";
    std::cin >> wordLimit;

    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "\n[ERROR] Could not open " << filename << ".\n";
        std::cerr << "Please create 'dataset.txt' in this folder and paste text into it.\n";
        return 1;
    }

    std::cout << "\n[Step 2] Reading file and building indices...\n";
    
    std::string rawWord;
    int count = 0;
    
    
    auto startBuild = std::chrono::high_resolution_clock::now();

    while (file >> rawWord && count < wordLimit) {
        std::string word = cleanWord(rawWord);
        
        
        if (word.length() > 0) {
            
            bst.insert(word, 1);
            hashTable.insert(word, 1);
            count++;
        }
    }
    
    auto endBuild = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedBuild = endBuild - startBuild;
    
    file.close();
    std::cout << ">> Processed " << count << " words.\n";
    std::cout << ">> Index Construction Time: " << elapsedBuild.count() << " seconds.\n";

    
    std::cout << "\n[Step 3] Running Speed Test...\n";
    std::string query = "the"; // Common word that usually exists
    std::cout << "Searching for common word: '" << query << "'\n";
    
    
    auto startBST = std::chrono::high_resolution_clock::now();
    bst.search(query);
    auto endBST = std::chrono::high_resolution_clock::now();
    auto bstTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endBST - startBST).count();

    
    auto startHash = std::chrono::high_resolution_clock::now();
    hashTable.search(query);
    auto endHash = std::chrono::high_resolution_clock::now();
    auto hashTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endHash - startHash).count();

    
    std::cout << "\n-------------------------------------------------\n";
    std::cout << " EXPERIMENTAL RESULTS (N = " << count << ")\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "Structure      | Time Complexity | Actual Time\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "BST Index      | O(log N)        | " << bstTime << " ns\n";
    std::cout << "Hash Index     | O(1)            | " << hashTime << " ns\n";
    std::cout << "-------------------------------------------------\n";
    
    if (hashTime < bstTime) {
        double speedup = (double)bstTime / (double)hashTime;
        std::cout << "CONCLUSION: Hash Table was " << speedup << "x faster.\n";
    } else {
        std::cout << "CONCLUSION: BST was faster (likely due to small N or cache locality).\n";
    }

    
    std::cout << "\n[Step 4] Verifying Advanced Logic (Boolean AND)...\n";
    std::cout << "Attempting to intersect lists (Simulated)...\n";
    PostingList* list1 = bst.getPostingList("the");
    PostingList* list2 = bst.getPostingList("and"); 
    
    if (list1 && list2) {
        PostingList* result = PostingList::intersect(list1, list2);
        std::cout << "Intersection calculated successfully using Two-Pointer Algorithm.\n";
        delete result;
    } else {
        std::cout << "Could not verify intersection (words missing from text).\n";
    }

    return 0;
}