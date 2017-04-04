
#include "GlobalIOUtilities.h"

string GetBaseDirectory()
{
	return "../";
}

string LoadFileToString(string filename)
{
	ifstream file(filename.c_str());

	stringstream fileContent;

	if (file.is_open())
	{
		while (!file.eof())
		{
			string line;
			getline(file, line);
			fileContent << line;
			fileContent << endl;
		}
	}
	else
	{
		cout << "Failed to open file: " << filename << endl;
	}

	return fileContent.str();
}