#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include "BST.h"
#include "WordPair.h"
#include "ElementAlreadyExistsInBSTException.h"
#include "ElementDoesNotExistInBSTException.h"

using namespace std;

void display(WordPair& anElement) {
    cout << anElement.getEnglish() << ":" << anElement.getTranslation() << endl;
} // end of display

int main() {
    BST<WordPair>* theTranslator = new BST<WordPair>();

    string aLine = "";
    string aWord = "";
    string englishW = "";
    string translationW = "";
    string filename = "dataFile.txt";
    string delimiter = ":";
    size_t pos = 0;
    WordPair translated;


    ifstream myfile (filename);
    if (myfile.is_open()) {
        // cout << "Reading from a file:" << endl;
        while (getline(myfile, aLine)) {
            // cout << aLine << '\n';   // For debugging purposes
            pos = aLine.find(delimiter);
            englishW = aLine.substr(0, pos);
            aLine.erase(0, pos + delimiter.length());
            translationW = aLine;
            //cout << "Read: " << englishW << ":" << translationW << endl;  // For debugging purposes
            WordPair aWordPair(englishW, translationW);
            //cout << "Read: " <<  aWordPair.getEnglish() << ":" << aWordPair.getTranslation() << endl;  // For debugging purposes
            try {
                theTranslator->insert(aWordPair);
            }
            catch (ElementAlreadyExistsInBSTException &anException) {
                cout << anException.what() << " => " << aWordPair.getEnglish() << ":" << aWordPair.getTranslation()
                     << endl;
            }
        }
        myfile.close();
        cout << endl;

        WordPair pair = WordPair("cloud");
        cout << "Test Retrieve for 'cloud': " << theTranslator->retrieve(pair).getTranslation() << endl;
        cout << endl;

        cout << "Element Count: " << theTranslator->getElementCount() << endl;
        cout << endl;

        cout << "Element Count: " << theTranslator->nodesCount() << endl;
        cout << endl;

        WordPair minElement;
        try {
            minElement = theTranslator->min();
            cout << "Min Element: " << minElement.getEnglish() << ":" << minElement.getTranslation() << endl;
        } catch(ElementDoesNotExistInBSTException& e) {
            cout << e.what() << endl;
        }
        cout << endl;

        WordPair maxElement;
        try {
            maxElement = theTranslator->max();
            cout << "Max Element: " << maxElement.getEnglish() << ":" << maxElement.getTranslation() << endl;
        } catch(ElementDoesNotExistInBSTException& e) {
            cout << e.what() << endl;
        }
        cout << endl;

        WordPair dupPair = WordPair("car");
        cout << "Number of copies of 'car': " << theTranslator->duplicate(dupPair) << endl;
        cout << endl;

        cout << "Removing car..." << endl;
        try {
            theTranslator->remove(dupPair);
        } catch(ElementDoesNotExistInBSTException& e) {
            cout << e.what() << endl;
        }

        cout << "Number of copies of 'car' now: " << theTranslator->duplicate(dupPair) << endl;
        cout << endl;

        cout << "Test inOrderTraverse: " << endl;
        cout << endl;

        theTranslator->traverseInOrder(display);

    } else {
        cout << "Unable to open file";
    }
    return 0;
}