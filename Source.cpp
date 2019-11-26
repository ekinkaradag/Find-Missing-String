#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono> // to measure the elapsed time
using namespace std;

int findString(string main, string sub)
{
	int M = main.size();
	int N = sub.size();

	for (int i = 0; i <= M - N; i++) {
		int j;

		for (j = 0; j < N; j++)
		{
			if (main[i + j] != sub[j])
				break;
		}
		if (j == N)
			return i;
	}

	return -1;
}

int findString(string main, string sub, int index)
{
	int M = main.size();
	int N = sub.size();

	for (int i = index; i <= M - N; i++) {
		int j;

		for (j = 0; j < N; j++)
		{
			if (main[i + j] != sub[j])
				break;
		}
		if (j == N)
			return i;
	}

	return -1;
}

int main()
{
	auto start = chrono::high_resolution_clock::now();

	ifstream statementsFile("statements.txt"); //Read from the statements.txt

	string line, word;
	vector<string> statements;
	if (!statementsFile.good())
	{
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
		statementsUnderScoreIndex.push_back(statements[i].find("___"));

	}

	//Read script file
	ifstream scriptFile("the_truman_show_script.txt"); // to read from the file
	if (!scriptFile.good())
	{
		cout << "Unable to read the script file! The file name has to be \"the_truman_show_script.txt\" (without quatition marks)\n";
		return 0;
	}
	while (scriptFile.good())
	{
		getline(scriptFile, line, '\n');
	}

	for (int i = 0; i < statements.size(); i++) {
		string word;
		bool firstPassed = false;
		string firstString = statements[i].substr(0, statementsUnderScoreIndex[i]); // before ___ including " "
		string nextString = statements[i].substr(statementsUnderScoreIndex[i] + 3); // after ___ including " "
		int iterations = line.size();


		int first, last;
		first = findString(line, firstString) + firstString.size(); // first = line.find(firststring) + firststring.size();
		last = findString(line, nextString, first); // last = line.find(nextstring, first);
		word = line.substr(first, last - first);
		cout << i + 1 << ") " << statements[i] << '\n' << word << "\n";
	}

	auto finish = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = finish - start;

	cout << "\nElapsed time: " << elapsed.count() << " seconds\n";

	cout << "Press Enter to finish the program";
	cin.get();

}