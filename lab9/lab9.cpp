/*
Lab 9 - Text File Word Counter
------------------------------
Create a program which will count and report on the number of occurrences of 
distinct, case insensitive words in a text file.

The program should have a loop that:

1. Prompts the user to enter a file name.  Terminate the loop and the program 
   if the user presses the Enter key only.
2. Verifies that a file with the name entered exists.  If the file does 
   not exist, display an appropriate message and return to step 1.
3. Reads and displays the contents of the file.
4. Displays a count of the distinct words in the file.
5. Displays a sorted list of each of the distinct words in the file and the 
   number of occurrences of each word. Sort the list in descending order by
   word count, ascending order by word.

A screen display and sample input files can be found in the Blackboard Review
folder.

Submit your�solution (main.cpp) as the file lab9_annnnnnn.cpp where annnnnnn 
is your ACC student identification number.
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Structure containing word and number of occurrences
struct WordCount {
	string word;	// the word
	int count;		// the number of occurances
	WordCount(string s) {word=s; count=1;}
};

// Function Prototypes
string InputText();							// Prompt user for file name and get text
string Normalize(string);					// Convert string to lowercase and remove punctuation
vector<WordCount> DistinctWords(string);	// Build sorted vector of word count structures
int FindWord(string,vector<WordCount>);		// Linear search for word in vector of structures
void DisplayResults(vector<WordCount>);		// Display results

// Main
int main(int argc, char** argv) {
	cout << "Lab 9 - Text File Word Counter" << endl;
	cout << "------------------------------" << endl;
	// Input text from file
	string buffer = InputText();
	while(buffer != "") {
		// Display origonal text from file
		cout << "\nThis is the text string read from the file" << endl;
		cout << "------------------------------------------" << endl;
		cout << buffer << endl << endl;
		// Build vector of words and counts
		vector<WordCount> words = DistinctWords(buffer);
		// Display results
		cout << "There are " << words.size() << " unique words in the above text." << endl;
		cout << "--------------------------------------------" << endl << endl;
		DisplayResults(words);
		buffer = InputText();
	}
	return 0;
}

// Read contents of text file
string ReadText(string filename) {
	fstream file(filename, ios::in);
	string buffer = "";
	if (file) {
		stringstream ss;
		ss << file.rdbuf();
		if(!file.fail())
			buffer = ss.str();
		file.close();
	}
	return buffer;
}

// Prompt user for file name and read text
string InputText() {
	string filename, buffer = "";
	do {
		cout << endl << "File name? ";
		getline(cin, filename);
		if(filename != "") {
			buffer = ReadText(filename);
			if(buffer == "")
				cout << "File '" << filename << "' not found or empty";
		}
	}
	while(filename != "" && buffer == "");
	return buffer;
}

// Compare function used for word count structure sort
struct SortFunc {
    bool operator ()(WordCount const& wc1, WordCount const& wc2) const {
    	bool swap = false;
    	// descending by count
    	if(wc1.count > wc2.count)
    		swap = true;
		// ascending by word
    	else if(wc1.count==wc2.count && wc1.word < wc2.word)
    		swap = true;
    	return swap;	
    }
};

// Create and sort vector of structures of distinct words and counts
vector<WordCount> DistinctWords(string s) {
	vector<WordCount> words;
	istringstream ss(Normalize(s));
	string word;
	while (ss >> word) {
		int index = FindWord(word, words);
		if(index == -1)  {
			WordCount wc(word);
			words.push_back(wc);
		}
		else
			words[index].count += 1;
	}
	// Sort the vector and return
	sort(words.begin(), words.end(), SortFunc());
	return words;
}

// Convert string to lowercase and remove punctuation
string Normalize(string s) {
	int max = s.length();
	for(int i=0; i<max; i++)
		s[i] = ispunct(s[i]) ? ' ' : tolower(s[i]);
    return s;
}

// Perform linear search for word
int FindWord(string w, vector<WordCount> v) {
	for(int i=0; i < v.size(); i ++)
		if(v[i].word == w) return i;
	return -1;
}

// Display column headings
void DisplayHeadings(int cols) {
	for(int i = 0; i < cols; i++)
		cout << setw(15) << left << "Word" << setw(5) << "Count" << "\t";	
	cout << endl;
	for(int i = 0; i < cols; i++)
		cout << "--------------------" << "\t";
	cout << endl;
}

// Display results in columnar form
void DisplayResults(vector<WordCount> words) {
	// Define number of columns
	const int cols = 4;
	// Display column headings
	DisplayHeadings(cols);
	// Calculate number of rows required for desired columns
	int rows = words.size() / cols;
	if(words.size() % cols) rows += 1;
	// Display words and counts in rows of col columns
	for(int row = 0; row < rows; row++) {
		for(int i = row; i < words.size(); i += rows)
			cout << setw(15) << left << words[i].word << setw(5) << right << words[i].count << "\t";
		cout << endl;
	}
}
