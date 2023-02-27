#include "Dictionary.h"
#include "Boggle.h"
#include <QApplication>


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");

    //initialize each entry of board to empty string and each entry of visited to false
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = "";
            visited[i][j] = false;
        }
    }

}

Boggle::Boggle(string filename) {

    //load file into dict
    dict.LoadDictionaryFile(filename);

    //initialize each entry of board to empty string and each entry of visited to false
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = "";
            visited[i][j] = false;
        }
    }
}

void Boggle::SetBoard(string (*board)[4]) {

    //copy each entry of board to this->board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    //reset the wordsFound dictionary
    wordsFound.MakeEmpty();

    //for each position in the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {

            //call Solve Board Helper for each letter in the board
            SolveBoardHelper(i, j, 1, printBoard, "", output);
        }
    }

}

void Boggle::SaveSolve(string filename) {

    //save the words found
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output) {

    //for each row
    for (int i = 0; i < BOARD_SIZE; i++) {

        //print the board
        for (int j = 0; j < BOARD_SIZE; j++) {

            if (visited[i][j])
                output << " '" << board[i][j] << "' ";
            else
                output << "  " << board[i][j] << "  ";
        }

        //tab
        output << "\t";

        //print the visited
        for (int k = 0; k < BOARD_SIZE; k++) {
            if (visited[i][k] != 0)
                output << "  " << visited[i][k] << "  ";
            else
                output << "  0  ";
        }

        output <<endl;
    }
    output <<endl;
}

void Boggle::SolveBoardHelper (int row, int column, int step, bool printBoard, string word, ostream &output) {

    //return if we go out of bounds
    if (row < 0 or column < 0 or row >= BOARD_SIZE or column >= BOARD_SIZE)
        return;

    //if we already visited this then return
    if (visited[row][column] != 0)
        return;

    //concatenate our word
    word+= board[row][column];

    //if its not a prefix lets return because we know it wont lead to a word
    if (!dict.IsPrefix(word)) {
        return;
    }

    //set the step were at on the visited matrix
    visited[row][column] = step;

    //if this a word in the dictionary and this a word we have never found
    if (dict.IsWord(word) and !wordsFound.IsWord(word)) {

        //add the word to our words found
        wordsFound.AddWord(word);

        //check if user wants board printed
        if (printBoard) {
            output << "Word: " << word <<endl;
            output << "Number of Words: " << wordsFound.WordCount() <<endl;
            PrintBoard (output);
        }
        else
            output << wordsFound.WordCount() << "\t" << word <<endl;
    }

    //in which way will we move around the board:

    //north
    SolveBoardHelper(row-1, column, step + 1, printBoard, word, output);
    //northeast
    SolveBoardHelper(row-1, column+1, step + 1, printBoard, word, output);
    //east
    SolveBoardHelper(row, column+1, step + 1, printBoard, word, output);
    //southeast
    SolveBoardHelper(row+1, column+1, step + 1, printBoard, word, output);
    //south
    SolveBoardHelper(row+1, column, step + 1, printBoard, word, output);
    //southwest
    SolveBoardHelper(row+1, column-1, step + 1, printBoard, word, output);
    //west
    SolveBoardHelper(row, column-1, step + 1, printBoard, word, output);
    //northwest
    SolveBoardHelper(row-1, column-1, step + 1, printBoard, word, output);

    //set the visited to 0 because we checked all possible directions and it doesnt lead to anywhere
    visited[row][column] = 0;
}



