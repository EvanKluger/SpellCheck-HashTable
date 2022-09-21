#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cwchar>
#include <cwctype>
#include "hash.h"

using namespace std;

//Variables and Function declarations used later in Program
void input_dictionary();
void file_to_be_spellchecked(); 
void output_file(); 
ofstream *outFile;
string line;
string new_word;
/*
Functon that creates a dictionary by passing valid words from dictionary text file into hashtable
All values passed into dictionary are passed as lower case 
creating_dictionary() uses the getline() function to parse each line of text file that contains one word to be added to dictionary
*/
void creating_dictionary(string &input_file, hashTable &dictionary){
    ifstream ifs(input_file);
    if(ifs.is_open()){
        while(getline(ifs, line)){
        
        for (int i = 0; i < line.length(); i++) //for every letter in line if it is an uppercase turn it to a lowercase
            {
                line[i] = towlower(line[i]);
            }
            dictionary.insert(line); //for every word in each line add to the hashtable dictionary 
        }
    }
    //closes files 
    ifs.close();
}
/*
Function that spell checks an inputted text file and returns a file with declarations for non-valid words
parcing_spellchgeck() uses the getline() function to read each line of the inputted text file
A valid word is any word that is 20 char or less and is contained in the dictionary 
If these conditions are not meant output will return a sentence declaring where the non-valid word is in the input file
*/
void parcing_spellcheck(string &input_file, string &output_file, hashTable &dictionary){
    ifstream ifs(input_file); 
    ofstream ofs(output_file);
    outFile = &ofs;
    string current_word; //string declaration to hold the current word 
    int count = 1; //count varaible to keep track of line number in input file
    string line2;
    if(ifs.is_open()){
    while (getline(ifs, line2)) {
        line2 = line2 + ' ';
        //for every letter in the line check if it is a valid letter
        for (int i = 0; i < line2.length(); i++){
            //if the letter is a char, digit, -, or ' it is valid and add to current_word
            if(isalpha(line2[i]) || isdigit(line2[i]) || line2[i] == '-' || line2[i] == '\''){
                if(isupper(line2[i])){
                    line2[i] = tolower(line2[i]); //if the ltter is upper case convert to lower case
                }
                current_word += line2[i];        
            }
            //else: if the letter is nonvalid
            else{
                    //if any letter of current_word is a digit ignore the word
                    for(int j = 0; j<current_word.length();j++){
                        if(isdigit(current_word[j])){
                            current_word.clear();
                        }
                    }
                    //if current_word is a long word 
                    if(current_word.length() > 20){
                        *outFile << "Long word at line " << count <<", starts: " << current_word.substr(0,20) <<endl;
                        current_word.clear();
                    }
                    //if current_word is an unknown word
                    if(current_word.empty() == false  && dictionary.contains(current_word) == false){
                        *outFile << "Unknown word at line " << count <<": " << current_word <<endl;
                        current_word.clear();
                    }
                current_word.clear();
            } 
        }
        count = count + 1; //line is over so increment the count variable
    }
    }
    //closes files 
    ifs.close();
    ofs.close();
}
/*
Main function of the program that creates a dictionary and spellchecks a file.
create_dictionary() and parcing_spellcheck() are run and the time that each took is printed to the user along with an output file
containing the non-valid words in the inout file.
*/
int main(){
    hashTable dictionary(50000); //declaration of the object dictionary of class hashTable
    string filename;
    string filename_i;
    string filename_o;
    cout << "Enter name of Dictionary: ";
    cin >> filename;
    clock_t t1_Dict = clock(); //clock of start time of creating dictionary
    creating_dictionary(filename, dictionary);
    clock_t t2_Dict = clock(); //clock of end time of creating dictionary
    double timeDiff_Dict = ((double) (t2_Dict - t1_Dict)) / CLOCKS_PER_SEC; //total time to create dictionary
    cout << "Total time (in seconds) to load dictionary: " << timeDiff_Dict << "\n";
    cout << "Enter name of input file: ";
    cin >> filename_i;
    cout << "Enter name of output file: ";
    cin >> filename_o;
    clock_t t1_CD = clock(); //clock of start time of checking document
    parcing_spellcheck(filename_i,filename_o, dictionary);
    clock_t t2_CD = clock(); //clock of end time of checking document
    double timeDiff_CD = ((double) (t2_CD - t1_CD)) / CLOCKS_PER_SEC; //total time to check document
    cout << "Total time (in seconds) to check document: " << timeDiff_CD << "\n";;
    return 0;
}