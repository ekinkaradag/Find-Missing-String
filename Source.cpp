#include <iostream>	// simple input output library
#include <fstream> // to be able to open files.
#include <vector> // If we don't know the size of an array beforehand, it is better to use vectors. Because their size is dynamic
#include <string> // to be able to use strings
#include <chrono> // to measure the elapsed time
using namespace std;

int findString(string main, string sub)
{ //main is the script string, sub is the string that is to be searched
	int M = main.size();
	int N = sub.size();

	for (int i = 0; i <= M - N; i++) {
		int j;

		for (j = 0; j < N; j++)
		{
			if (main[i + j] != sub[j])
				break;
		}
		//If the inner loop if condition is never reached, algorithm can reach here
		if (j == N)
			return i;
	}
	// If no value is returned so far, that means nothing is found. Return an error value.
	return -1;
}

int findString(string main, string sub, int index)
{ //main is the script string, sub is the string that is to be searched
	int M = main.size();
	int N = sub.size();

	for (int i = index; i <= M - N; i++) {
		int j;

		for (j = 0; j < N; j++)
		{
			if (main[i + j] != sub[j])
				break;
		}
		//If the inner loop if condition is never reached, algorithm can reach here
		if (j == N)
			return i;
	}
	// If no value is returned so far, that means nothing is found. Return an error value.
	return -1;
}

int main()
{
	//Start measuring the time
	auto start = chrono::high_resolution_clock::now();

	//Read from the statements.txt
	ifstream statementsFile("statements.txt");

	string line;
	vector<string> statements;
	if (!statementsFile.good())
	{
		//Display error and exit the program
		cout << "Unable to read the statements file! The file name has to be \"statements.txt\" (without quatition marks)\n";
		return 0;
	}


	//Read statements one by one
	while (statementsFile.good())
	{
		getline(statementsFile, line, '\n');
		statements.push_back(line);
	}
	statementsFile.close();

	vector<size_t> statementsUnderScoreIndex; //This Index will store the location of the first underscore in statements.
	for (int i = 0; i < statements.size(); i++)
	{
		statementsUnderScoreIndex.push_back(findString(statements[i],"___")); //Find the starting indexes of "___"s
	}

	//Read script file
	ifstream scriptFile("the_truman_show_script.txt");
	if (!scriptFile.good())
	{
		//Display error and exit the program
		cout << "Unable to read the script file! The file name has to be \"the_truman_show_script.txt\" (without quatition marks)\n";
		return 0;
	}

	//Since the script file contains only one line, we read it only once.
	if (scriptFile.good())
	{
		getline(scriptFile, line);
	}
	scriptFile.close();
	
	//Search for each and every statement through the script file
	for (int i = 0; i < statements.size(); i++) {
		string firstString, nextString, word;
		firstString = statements[i].substr(0, statementsUnderScoreIndex[i]); // before ___ including " "
		nextString = statements[i].substr(statementsUnderScoreIndex[i] + 3); // after ___ including " "

		int first, last;
		first = findString(line, firstString) + firstString.size(); // find the first character index of the missing word

		if (first == (firstString.size() - 1)) { //Check if the statement exists
			cout << i + 1 << ") " << statements[i] << '\n' << "Statement NOT found\n";
			continue;
		}

		last = findString(line, nextString, first); // find the last character index of the missing word

		if (last == -1) { //Check if the statement exists
			cout << i + 1 << ") " << statements[i] << '\n' << "Statement NOT found\n";
			continue;
		}

		word = line.substr(first, last - first); // Take a substring of the word from script file
		cout << i + 1 << ") " << statements[i] << '\n' << word << "\n"; //Display the statement and it's missing word
	}

	//Display the elapsed time
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "\nElapsed time: " << elapsed.count() << " seconds\n";
	cout << "Press Enter to finish the program";
	cin.get();

}