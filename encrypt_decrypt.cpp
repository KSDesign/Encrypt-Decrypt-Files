//encrypt_decrypt.cpp
//Sakhrani:Kabir:A00376745:CSC34141
//Submission 01: Encrypting and Decrypting Textfiles

/*
The whole program works to my knowledge.
*/

#include <iostream> //this is where cout, endl and cin.ignore() live
#include <fstream> //this is where ifstream and ofstream live
#include <string> //this is where getline() and to_string() live
#include <cstdlib> //this is where atoi() lives
#include <vector> //this is to use vector
#include <algorithm>
using namespace std; //<- This is a "using directive"


#include "utilities.h"
using Scobey::DisplayOpeningScreen;
using Scobey::Pause;
using Scobey::TextItems;
using Scobey::DisplayTextfile;


int main(int argc, char* argv[])
{
    // Displayed if there are no command-line parameters besides program name.
    if (argc == 1)
    {
        DisplayOpeningScreen("Sakhrani:Kabir:A00376745:csc34226",
            "Submission 01: Encrypting and Decrypting Textfiles");
        const TextItems TEXT("encrypt_decrypt.txt");
        TEXT.displayItem("Program Description");
        return 0;
    }
    // Displayed if there is an incorrect number of parameters required
    else if (argc != 5)
    {
        cout << "\nError: Incorrect number of parameters." << endl;
        cout << "Program now terminating." << endl;
        Pause();
    }
    else
    {
        string encodeOrDecode(argv[1]);
        if (encodeOrDecode != "e" && encodeOrDecode != "d")
        {
            cout << "\nError: Bad first parameter." << endl;
            cout << "Program now terminating." << endl;
            Pause();
            exit(EXIT_SUCCESS);
        }
        ifstream inFile(argv[2]);
        if (!inFile.is_open())
        {
            cout << "\nError: Cannot open file.ext for input." << endl;
            cout << "Program now terminating." << endl;
            Pause();
            exit(EXIT_SUCCESS);
        }
        ofstream outFile;
        outFile.open(argv[3]);
        if (!outFile.is_open())
        {
            cout << "\nError: Cannot open file.ext for output." << endl;
            cout << "Program now terminating." << endl;
            Pause();
            exit(EXIT_SUCCESS);
        }
        string userPhrase(argv[4]);
        if (userPhrase.size() < 10)
        {
            cout << "\nError: Key phrase must not be shorter than 10"
                    "characters." << endl;
            cout << "Program now terminating." << endl;
            Pause();
            exit(EXIT_SUCCESS);
        }

        //Creating the key
        //Removes all duplicate characters
        sort(userPhrase.begin(), userPhrase.end());
        userPhrase.erase(unique(userPhrase.begin(), userPhrase.end()),
        userPhrase.end());


        //Placed in the reverse order of the natural ASCII order
        sort(userPhrase.begin(), userPhrase.end());
        reverse(userPhrase.begin(), userPhrase.end());

        //The remaining, missing ascii characters are added to the end
        vector<int> asciiVals;
        for (char userPhraseChar : userPhrase)
        {
            int asciiNum = int(userPhraseChar);
            asciiVals.push_back(asciiNum);
        }
        vector<int>::iterator p;
        for (int x = 32; x <= 126; x++)
        {
            p = find(asciiVals.begin(), asciiVals.end(), x);
            if (p == asciiVals.end())
            {
                asciiVals.push_back(x);
            }
        }
        vector<char> keyPhrase;
        for (int asciiValue : asciiVals)
        {
            char asciiChar = char(asciiValue);
            keyPhrase.push_back(asciiChar);
        }

        //The key is reversed one last time
        reverse(keyPhrase.begin(), keyPhrase.end());

        //Created a vector with all the ascii values
        vector<char> asciiValsInOrder;
        for (int x = 32; x <= 126; x++)
        {
            asciiValsInOrder.push_back(char(x));
        }

        string inputText;
        //Code for the encryption
        if (encodeOrDecode == "e")
        {
            vector<char> encoder;
            while (getline(inFile, inputText))
            {
                for (char ascii : inputText)
                {
                    int keyIndex = (int(ascii)) - 32;
                    ascii = keyPhrase.at(keyIndex);
                    encoder.push_back(ascii);
                }
                for (vector<int>::size_type i = 0; i<encoder.size(); i++)
                    outFile << encoder.at(i);
                encoder.resize(0);
                outFile << "\n";
            }
        }
        //Code for the decryption
        else if (encodeOrDecode == "d")
        {
            vector<char>::iterator a;
            vector<char> decoder;
            while (getline(inFile, inputText))
            {
                for (char ascii : inputText)
                {
                    a = find(keyPhrase.begin(), keyPhrase.end(), ascii); 
                    int keyIndex = a - keyPhrase.begin();                   
                    ascii = asciiValsInOrder.at(keyIndex);
                    decoder.push_back(ascii);
                }
                for (vector<int>::size_type i = 0; i < decoder.size(); i++)
                {
                    outFile << decoder.at(i);
                }
                decoder.resize(0);
                outFile << "\n";
            }
        }
    }
}