#ifndef BOGGLE_H
#define BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:

    /*
     * Function:
     * Initializes the Boggle object by initializing its dictionary object variable with the dictionary.txt file and
     * initialized its board and visited matrix values to empty and/or false.
     *
     * Precondition:
     * None
     *
     * Postcondition:
     * Boggle object is initialized
     */
    Boggle();  // load "dictionary.txt" into dict

    /*
     * Function:
     * Initializes the Boggle object by initializing its dictionary object variable with a provided text file and
     * initialized its board and visited matrix values to empty and/or false.
     *
     * Precondition:
     * File must be valid and must open.
     *
     * Postcondition:
     * Boggle object is initialized
     */
    explicit Boggle(string filename);  // load filename into dict

    /*
    * Function:
    * Takes a board and copies all its values to this->board.
    *
    * Precondition:
    * None.
    *
    * Postcondition:
    * Boggle's board has values from other board
    */
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    /*
    * Function:
    * Finds all the words on the current board stored by board and saves the words to the words found dictionary
     * Also outputs the values to the output stream object.
    *
    * Precondition:
    * wordsFound dictionary is emptied.
    *
    * Postcondition:
    * wordsFound dictionary is filled with all the words that could be made up from the board.
    */
    void SolveBoard(bool printBoard, ostream& output);

    /*
    * Function:
    * Calls the words found SaveDictionaryFile function to save all the words found to a file.
    *
    * Precondition:
    * File must be valid and must open.
    *
    * Postcondition:
    * File has all the words found from the current board.
    */
    void SaveSolve(string filename);   // Saves all the words from the last solve.

    Dictionary GetDictionary();
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    /*
    * Function:
    * Prints out board in a specific format, and is used by Solve Board Helper to print each word found and how it was
     * found.
    *
    * Precondition:
    * None.
    *
    * Postcondition:
    * Boggle is printed.
    */
    void PrintBoard(ostream& output);

    /*
    * Function:
    * Takes a row, column, starts with step at 1, whether the board should be printed, an empty string, and the ofstream
     * object to find words in the board and print them each time they are found.
    *
    * Precondition:
    * Cannot go out of bounds, cannot use the same letter that we have visited, it must be a prefix and it must be a word
     * that we have not found to be added to our words found and to be printed.
    *
    * Postcondition:
    * All the words in our current board are found and printed in a specific way depending on the printBoard flag.
    */
    void SolveBoardHelper(int row, int column, int currStep, bool printBoard,  string word, ostream& output);
};

#endif // BOGGLE_H
