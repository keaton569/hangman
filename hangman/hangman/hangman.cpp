#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <map>
#include <iomanip>  

using namespace std;

//TO DO///////////////////////////////////////////////////////////////////////////
//fix yes loop
//build the "no" side of the game
//game LOOOOOOOOP
//add in the graphics :)
//if word not on list, add to list
//clean up looks
///////////////////////////////////////////////////////////////////////////////////


int questionNumber = 1;
const int guessMax = 6;
int wrongGuess = 0;
vector<char> guessedLetters;
vector<int> letterPlacement;
char yesNO;
bool addedElement = false;
vector<string> updatedList;
vector<string> removalList;



vector<string> readDictionary(int wordLengthReturned) {
	ifstream file;
	file.open("words.txt");
	string word;
	vector<string> words;

	cout << "HMMM thinking...." << endl;

	if (!file.is_open()) {
		cout << "file didnt open" << endl;
		return words;
	}else{
		while (file >> word)
		{
			if (word.length() == wordLengthReturned)
			{
				words.push_back(word);
				//cout << "words size in readDictionary: " << words.size();
			}
		}
		
	}
	return words;
}

int WordLength() {
	int wordLength;
	cout << "How many letters is your word?" << "....";
	cin >> wordLength;
	return wordLength;
}

void clear_screen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

char calculateLetter(vector<string> words) {
	char mostUsedLetter;
	char countLetters;
	string word;
	map<char, int> letterCount;
	int initialLetterCount = 0;
	char arg_max;
	unsigned currentMax = 0;

	for (vector<string>::iterator it = words.begin(); it < words.end(); it++)
	{
		string currentWord = *it;


//##################   Count Chars ##################################################################
		for (const char &currentChar : currentWord)
			{
				map<char, int>::iterator mapIT = letterCount.find(currentChar);

				if (mapIT != letterCount.end()) {
					mapIT->second++;
				}
				else {
					letterCount.insert(make_pair(currentChar, 1));
				}
			}
		}
//###############  remove already guessed letters from list ########################################
	for (vector<char>::iterator i = guessedLetters.begin(); i < guessedLetters.end(); i++)
	{
		letterCount.erase(*i);
	}


//##################   find biggest Chars Count ####################################################

		for (auto mapValueIt = letterCount.cbegin(); mapValueIt != letterCount.end(); mapValueIt++)
		{
			if (mapValueIt->second > currentMax) {
				arg_max = mapValueIt->first;
				currentMax = mapValueIt->second;
			}
		}

		//cout << "Value " << arg_max << " occurs " << currentMax << " times " << endl;



		guessedLetters.push_back(arg_max);
	return arg_max;
}

void askQuestions(char mostUsedChar) {
	
	cout << "Question Number " << questionNumber << endl;
	cout << "Does your word have the letter: "<< mostUsedChar << endl;
	cin >> yesNO;
	questionNumber++;
	int letterInWord;
	letterPlacement.clear();

	while (yesNO == 'y' || yesNO == 'Y')
	{
		if (yesNO == 'y' || yesNO == 'Y')
		{
			clear_screen();
			cout << "Where is that letter in your word?" << endl;

			cin >> letterInWord;
			letterPlacement.push_back(letterInWord);
			addedElement = true;

			clear_screen();
			cout << "Is that letter in another spot in your word?" << endl;
			cin >> yesNO;
		}
		else {
			cout << "hmmm ok" << endl;
			wrongGuess++;
			cout << "wrong Guess count: " << wrongGuess;
		}
	}

	
	return;
}

int endGame() {
	int end;
	cout << "end game?" << endl;
	cin >> end;

	return end;
}

void printLines(int wordLengthReturned) {
	//clear_screen();
	cout << endl << endl << endl << endl;
	cout << " ";

	for (int i = 0; i < wordLengthReturned; i++)
	{
		cout << "_ ";
	}

	cout << endl;

}

vector<char> addLettersToUnknownWord(vector<int> letterPlacements, char mostUsedLetter, int wordLength) {
	
	vector<int>::iterator intIT = letterPlacements.begin();
	int position = 1;
	int size = letterPlacements.size();
	vector<char> vector;

	for (int i = 1; i <= wordLength; i++)
	{

		if (*intIT == i)
		{
			vector.push_back(mostUsedLetter);
			vector.push_back(' ');
			

			if (position < size)
			{
				intIT++;
				position++;
			}
		}
		else {
			vector.push_back('_');
			vector.push_back(' ');;
		}	
	}	
	return vector;
}

vector<char> addLettersToGuessHelper(vector<int> letterPlacements, char mostUsedLetter, int wordLength) {

	vector<int>::iterator intIT = letterPlacements.begin();
	int position = 1;
	int size = letterPlacements.size();
	vector<char> vector;

	for (int i = 1; i <= wordLength; i++)
	{

		if (*intIT == i)
		{
			vector.push_back(mostUsedLetter);
			vector.push_back(' ');


			if (position < size)
			{
				intIT++;
				position++;
			}
		}
		else {
			vector.push_back('_');
			vector.push_back(' ');;
		}
	}
	return vector;
}

void getLetterPositions() {


}

void printLettersAdded(vector<char> input) {

	for (vector<char>::iterator i = input.begin(); i < input.end(); i++)
	{
		cout << *i;
	}
	cout << endl;
}

vector<string> updateWordsList(char mostUsedLetter, vector<int> placement, vector<string> wordsList) {
	
	for (vector<string>::iterator it = wordsList.begin(); it < wordsList.end(); it++)
	{
		string currentWord = *it;
		bool good = true;
		int counter = 0;
		for (vector<int>::iterator IT = placement.begin(); IT < placement.end(); IT++)
		{
			int position = *IT;
			if (currentWord[position-1] == mostUsedLetter && good == true)
			{
				counter++;
				
				if (counter == placement.size())
				{
					cout << "updated list with word: " << currentWord << endl;
					updatedList.push_back(currentWord);
				}				
			}
			else {
				good = false;
			}
		}
	}
	return updatedList;
}


vector<string> updatedWordList(char mostUsedLetter, vector<int> placement) {
	string currentRemovalWord;
	removalList.clear();



	/*
	
	
	*/

	for (vector<string>::iterator it = updatedList.begin(); it < updatedList.end(); it++)
	{
		string currentWord = *it;
		bool good = true;
		int counter = 0;
		vector<int>::iterator IT = placement.begin();

		while (IT != placement.end())
		{
			int position = *IT;

			if (good == true)
			{

				if (currentWord[position - 1] == mostUsedLetter && counter < placement.size())
				{
					counter++;
				}
				else {
					cout << "erase" << endl;
					good = false;
					updatedList.erase(it);
					IT--;
				}
			}
		}
			
		
	}

	/*
	for (vector<string>::iterator it = removalList.begin(); it < removalList.end(); it++) {
		currentRemovalWord = *it;
		cout << "started" << endl;
		cout << currentRemovalWord << endl;
		updatedList.erase(it);
		cout << " ran" << endl;
	}

	*/
	cout << "ran" << endl;
	return updatedList;
}


void gameLoop(vector<string> updatedWordsList, int wordLengthReturned) {


	for (int i = wrongGuess; i <= guessMax; i++)
	{
		char mostUsedChar = calculateLetter(updatedList);

		askQuestions(mostUsedChar);

		if (addedElement == true)
		{
			vector<char> computerStringGuess = addLettersToUnknownWord(letterPlacement, mostUsedChar, wordLengthReturned);

			updatedWordList(mostUsedChar, letterPlacement);

			printLettersAdded(computerStringGuess);

			cout << "break here " << endl;

			for (vector<string>::iterator i = updatedList.begin(); i < updatedList.end(); i++)
			{
				cout << *i << endl;
			}

			addedElement = false;
		}

		
	}

	

}


int main() {
	int wordLengthReturned = WordLength();
	
	vector<string> wordsList = readDictionary(wordLengthReturned);

	printLines(wordLengthReturned);

	char mostUsedLetter = calculateLetter(wordsList);
	
	askQuestions(mostUsedLetter);

	vector<char> computerStringGuess = addLettersToUnknownWord(letterPlacement, mostUsedLetter, wordLengthReturned);

	vector<char> computerStringGuessHelper = addLettersToGuessHelper(letterPlacement, mostUsedLetter, wordLengthReturned);

	vector<string> updatedWrodList = updateWordsList(mostUsedLetter, letterPlacement, wordsList);

	printLettersAdded(computerStringGuess);



	cout << "game loop" << endl;
	gameLoop(updatedWrodList, wordLengthReturned);













	int end = endGame();
	return end;
}
