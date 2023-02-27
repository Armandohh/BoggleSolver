#include "Dictionary.h"

// Your code here

Dictionary::Dictionary() {

    //establish a root node
    root = new Node;

    //set the total number of words to 0
    numWords = 0;
}

Dictionary::~Dictionary() {
    //call the destroy helper to destroy the tree starting from the root
    destroyHelper(root);
}

Dictionary::Dictionary(const Dictionary &otherDict) {

    //establish a root node
    root = new Node;

    //set the total number of words to 0
    numWords = 0;

    //call copy other and sending otherDict as a parameter to be copied
    copyOther(otherDict);
}

Dictionary::Dictionary(string filename) {

    //establish a root node
    root = new Node;

    //call load dictionary file and sending the filename as a parameter to copy words from file onto the tree
    LoadDictionaryFile(filename);
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {

    //while this dictionary is not at the same address as the other dictionary
    if (this != &otherDict)
        copyOther(otherDict);   //copy the contents of other into this

    //return self
    return *this;
}

void Dictionary::LoadDictionaryFile(string filename) {

    //open file
    ifstream dictionary;
    dictionary.open (filename);

    //check that file opens
    if (dictionary.fail())
        throw DictionaryError (filename + " failed to open");

    //declare a string variable
    string word;

    //add dictionary words to the tree by calling add word function
    while (dictionary >> word)
        AddWord(word);


    //close the file
    dictionary.close();


}

void Dictionary::SaveDictionaryFile(string filename) {

    //open file
    ofstream dictionary;
    dictionary.open (filename);

    //check that the file opens
    if (dictionary.fail())
        throw DictionaryError (filename + " failed to open");

    //call the save dictionary helper and send the root and dictionary to find every word in the tree and save it to the file
    SaveDictionaryHelper(root, "", dictionary);
}

void Dictionary::AddWord(string word) {

    //set a current node to the root of the tree
    Node* currNode = root;

    //iterate through each letter of the word
    for (char i : word) {

        //check that the letter is between 'a' and 'z' or throw error if not
        if (int(i) < 97 or int(i) > 122)
            throw DictionaryError("Invalid character");

        //check if the branch for the letter is null
        if (currNode->alphabet[int(i) - int('a')] == nullptr) {

            //if not null create new node at that branch
            currNode->alphabet[int(i) - int('a')] = new Node;

            //set the isWord to false
            currNode->alphabet[int(i) - int('a')]->isWord = false;
        }

        //point to the next branch
        currNode = currNode->alphabet[int(i) - int('a')];
    }

    //set the currNode's isWord flag to true
    currNode->isWord = true;

    //increment number of words
    numWords++;
}

void Dictionary::MakeEmpty() {

    //remove original tree
    destroyHelper(root);

    //rebuild root and reset number of words
    root = new Node;
    numWords = 0;
}

bool Dictionary::IsWord(string word) {

    //set a node at the root
    Node* currNode = root;

    //iterate through the word
    for (char i : word) {

        //check that the letter is between 'a' and 'z' or throw error if not
        if (int(i) < 97 or int(i) > 122)
            throw DictionaryError("Invalid character");

        //check if the branch for the letter is null, if it return false
        if (currNode->alphabet[int(i) - int('a')] == nullptr)
            return false;

        //point to the next branch
        currNode = currNode->alphabet[int(i) - int('a')];
    }

    //return the curreNode's isWord flag
    return currNode->isWord;
}

bool Dictionary::IsPrefix(string word) {

    //set a node at the root
    Node* currNode = root;

    //iterate through the word
    for (char i : word) {

        //check that the letter is between 'a' and 'z' or throw error if not
        if (int(i) < 97 or int(i) > 122)
            throw DictionaryError("Invalid character");

        //check if the branch for the letter is null
        if (currNode->alphabet[int(i) - int('a')] == nullptr)
            return false;

        //point to the next branch
        currNode = currNode->alphabet[int(i) - int('a')];
    }

    //return true
    return true;
}

int Dictionary::WordCount() {
    //return the number of words in the dictionary
    return numWords;
}

void Dictionary::copyOther(const Dictionary &otherDict) {

    //call make empty to delete our current dictionary
    MakeEmpty();

    //use the copy helper to send our root and the other dictionary's root to copy from it
    copyHelper(root, otherDict.root);

    //set the numWords to the otherDict numWords
    numWords = otherDict.numWords;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {

    //check if the node is null and return if it is
    if (thisTree == nullptr)
        return;

    //iterate through each branch of the currentNode and then recursively call destroyHelper sending each branch as a parameter
    for (auto & i : thisTree->alphabet)
        destroyHelper(i);

    //delete the node
    delete thisTree;
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {

    //if the other trees node is null
    if (otherTree == nullptr) {

        //set this node to null and return
        thisTree = nullptr;
        return;
    }

    //create a new Node
    thisTree = new Node;

    //copy the flag value from other to this
    thisTree->isWord = otherTree->isWord;

    //iterate through all the alphabet branches and recursively call copyHelper
    for (int i = 0; i < NUM_CHARS; i++)
        copyHelper(thisTree->alphabet[i], otherTree->alphabet[i]);
}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {

    //if the root is null return
    if (curr == nullptr)
        return;

    //if the path to the node is a word then write it to the file
    if (curr->isWord)
        outFile << currPrefix << endl;

    //for each letter we call the Save Dictionary Helper recursively
    for (int i = 0; i < NUM_CHARS; i++)
        SaveDictionaryHelper(curr->alphabet[i], currPrefix + char(i + int('a')), outFile);

}
