//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    // Create a MinHeap object
    MinHeap encodingTree;

    // Loop through all leaf nodes (recorded by next free)
    for (int i = 0; i < nextFree; i++) {
        // Push each leaf node into MinHeap
        encodingTree.push(i, weightArr);
    }

    // Loop through MinHeap while size is greater than 1
    while (encodingTree.size > 1) {
        // Pop and store left child first (first element will be less than second)
        int left = encodingTree.pop(weightArr);
        // Pop and store right child
        int right = encodingTree.pop(weightArr);
        // Create parent node with the combined weight
        weightArr[nextFree] = weightArr[left] + weightArr[right];
        // Set left and right pointers
        leftArr[nextFree] = left;
        rightArr[nextFree] = right;
        // Push new parent index back into heap
        encodingTree.push(nextFree, weightArr);

        // Increment number of nodes
        nextFree++;
    }

    // If the MinHeap is empty return invalid index
    if (encodingTree.size == 0) {
        return -1;
    }

    // Return the index of the root otherwise
    return encodingTree.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    // Declare stack<pair<int, string>>
    stack<pair<int, string>> s;

    // Create element to start traversal
    s.push({root, ""});

    // Loop while stack s has elements
    while (!s.empty()) {
        // Store top pair as p
        pair<int, string> p = s.top();
        // Remove first element
        s.pop();

        // Store the int and string stored in pair as individual variables
        int node = p.first;
        string code = p.second;

        // If node is stored in the left array
        if (leftArr[node] >= 0) {
            // Push node into stack with 0 added
            s.push({leftArr[node], code + "0"});
        }
        // If node is stored in the right array
        if (rightArr[node] >= 0) {
            // Push node into stack with 1 added
            s.push({rightArr[node], code + "1"});
        }
        // If node is in neither array (leaf node)
        if (leftArr[node] < 0 && rightArr[node] < 0) {
            // Record code
            char ch = charArr[node];
            codes[ch - 'a'] = code;
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}