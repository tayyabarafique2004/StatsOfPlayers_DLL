#include<iostream>
#include<string>
#include<fstream>
#include <iostream>
#include <cstdio>  
using namespace std;
struct Node
{
	string Name;
	int Test_macthes;
	int ODI;
	int T20;
	Node* next;
	Node* previous;
	Node(string Name, int Test_macthes, int ODI, int T20)
	{
		this->Name = Name;
		this->T20 = T20;
		this->Test_macthes = Test_macthes;
		this->ODI = ODI;
		this-> next = nullptr;
		this-> previous = nullptr;
	}
};
class DoublyLinkedList
{
private:
	Node* head;
	Node* tail;

public:
	DoublyLinkedList()
	{
		head = nullptr;
	    tail = nullptr;
	}
	~DoublyLinkedList()
	{
		Node* current = head;
		while (current != nullptr) {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
	}
	void displayStats()
	{
		if (isEmpty())
		{
			cout << "No Records found to be displayed!";
		}
		Node* current = head;
		while (current != nullptr)
		{
			cout<<"Name: "<<current->Name<<endl;
			cout << "Test Matches: " << current->Test_macthes<<endl;
			cout << "ODI matches: " << current->ODI<<endl;
			cout << "T20: " << current->T20 << endl;
			current = current->next;
			cout << "\n-------------------------------------------------------------------------------------------------------\n";

		}
	}
	bool insertStats(string name, int ODI, int test, int t20)
	{
		Node* newNode = new Node(name, test, ODI, t20);
		if (isEmpty())
		{
			head = newNode;
			tail = newNode;
			// Write player name to the main file
			ofstream mainFile("players.txt", ios::app);
			mainFile << name << endl;
			mainFile.close();
			writeToPlayerFile(name);
			return true;
		}
		else if (ifPlayerRecordExists(name))
		{
			cout << "Player Already Exists! Cant enter with this name Again! ";
			return false;
		}
		else
		{
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
			//no need to update tail pointer here
			head->previous = nullptr;
			// Write player name to the main file
			ofstream masterFile("players.txt", ios::app);
			masterFile << name << endl;
			masterFile.close();
			writeToPlayerFile(name);
			return true;
		}
	}
	bool deleteStatsOfPlayer(string name) {
		if (isEmpty()) {
			cout << "Deletion Unsuccessful! List Empty!" << endl;
			return false;
		}

		Node* current = head;
		while (current != nullptr) {
			if (current->Name == name) {
				// Handle node deletion
				if (current == head) { // If head
					head = current->next;
					if (head) {
						head->previous = nullptr;
					}
				}
				else if (current == tail) { // If tail
					tail = current->previous;
					if (tail) {
						tail->next = nullptr;
					}
				}
				else { // If in the middle
					current->previous->next = current->next;
					current->next->previous = current->previous;
				}

				delete current;
				cout << "Player stats deleted from the list!" << endl;

				if (deletePlayerFile(name)) {
					cout << "File deleted successfully for player: " << name << endl;
					updateMainFile(name);
				}
				else {
					cout << "Error deleting file for player: " << name << endl;
				}

				return true;
			}
			current = current->next;
		}

		cout << "Player not found!" << endl;
		return false;
	}
	void updateMainFile(const string& playerName) {
		ifstream masterFile("players.txt");
		ofstream tempFile("temp.txt");

		string line;
		while (getline(masterFile, line)) {
			if (line != playerName) {
				tempFile << line << endl;
			}
		}

		masterFile.close();
		tempFile.close();

		// replace the old main file
		remove("players.txt");

		// Check the result of rename
		if (rename("temp.txt", "players.txt") != 0) {
			cerr << "Error renaming temp file to master file!" << endl;
			return;  // Handle the failure case
		}
	}

	bool ifPlayerRecordExists(string name)
	{
		Node* current = head;
		while (current != nullptr)
		{
			if (current->Name == name)
			{
				return true;
			}
				current = current->next;
		}
		return false;
	}
	bool updateStats(string name)
	{
		int test_matches;
		int ODI;
		int T20;

		// Check if the player record exists in the list
		if (ifPlayerRecordExists(name))
		{
			while (true)
			{
				cout << "Enter number of Test Matches: ";
				if (cin >> test_matches)
				{
					if (test_matches >= 0) { break; }
					else
					{
						cout << "Enter a Positive Number:\n";
					}
				}
				else
				{
					cout << "Invalid input! Retry\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}

			while (true)
			{
				cout << "Enter number of ODI matches: ";
				if (cin >> ODI)
				{
					if (ODI >= 0) { break; }
					else
					{
						cout << "Enter a Positive Number:\n";
					}
				}
				else
				{
					cout << "Invalid input! Retry\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}

			while (true)
			{
				cout << "Enter number of T20 matches: ";
				if (cin >> T20)
				{
					if (T20 >= 0) { break; }
					else
					{
						cout << "Enter a Positive Number:\n";
					}
				}
				else
				{
					cout << "Invalid input! Retry\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}

			Node* current = head;
			while (current != nullptr)
			{
				if (current->Name == name)
				{
					current->Test_macthes = test_matches;
					current->ODI = ODI;
					current->T20 = T20;
					cout << "Player stats updated successfully.\n";
					writeToPlayerFile(name);  
					return true;  
				}
				current = current->next;
			}
		}
		else
		{
			cout << "Player doesn't exist! \n";
			return false;
		}
		return false;
	}

	bool isEmpty()
	{
		if (head == nullptr)
		{
			return true;
		}
		return false;
	}
	void writeToPlayerFile(string playerName)
	{
		ofstream outFile(playerName + ".txt");  // Creating a file with the player's name as filename
		if (outFile.is_open())
		{
			Node* current = head;
			while (current != nullptr)
			{
				if (current->Name == playerName)  // Check if this is the right player
				{
					outFile << "Name: " << current->Name << endl;
					outFile << "Test Matches: " << current->Test_macthes << endl;
					outFile << "ODI Matches: " << current->ODI << endl;
					outFile << "T20 Matches: " << current->T20 << endl;
					outFile.close();
					cout << playerName << "'s stats saved to file successfully." << endl;
					return;
				}
				current = current->next;
			}
		}
		else
		{
			cout << "Unable to open file for writing!\n";
		}
	}
	bool deletePlayerFile(const std::string& playerName)
	{
		std::string fileName = playerName + ".txt";  // Assuming file name is player name + .txt
		if (remove(fileName.c_str()) != 0)  // remove() returns 0 on success
		{
			std::cerr << "Error deleting file: " << fileName << std::endl;
			return false;
		}
		else
		{
			std::cout << "File deleted successfully: " << fileName << std::endl;
			return true;
		}
	}
	void loadPlayersFromMasterFile() {
		ifstream masterFile("players.txt");
		if (!masterFile.is_open()) {
			cout << "No master file found. Starting with an empty list." << endl;
			return;
		}

		string playerName;
		while (getline(masterFile, playerName)) {
			if (!ifPlayerRecordExists(playerName)) { // Check if player already exists
				ifstream playerFile(playerName + ".txt");
				if (playerFile.is_open()) {
					string name;
					int testMatches, odiMatches, t20Matches;

					// Read player data from the file
					playerFile.ignore(256, ':'); playerFile >> ws; getline(playerFile, name);
					playerFile.ignore(256, ':'); playerFile >> testMatches;
					playerFile.ignore(256, ':'); playerFile >> odiMatches;
					playerFile.ignore(256, ':'); playerFile >> t20Matches;

					// Insert into the doubly linked list
					insertStats(name, odiMatches, testMatches, t20Matches);

					playerFile.close();
				}
			}
		}

		masterFile.close();
		cout << "Players loaded from master file successfully!" << endl;
	}

};
void clearScreen() {
#ifdef _WIN32
	system("cls");
#endif
}

int main()
{
	DoublyLinkedList dll;
	dll.loadPlayersFromMasterFile();
	string player_Name;
	int test_matches;
	int ODI;
	int T20;
	string choice;
	bool flag = false;
	cout << "******** Choose Options from the following: *********" << endl;
	do
	{
		cout << "\n-------------------------------------------------------------------------------------------------------\n";
		cout << "1. Insert Stats of a Player.\n2. Update Stats of a Player.\n3. Delete a Player's Stats\n4. Display Stats of All Players.\n5. Exit\n";
		getline(cin, choice);
		if (choice == "1")
		{
			cout << "Enter Name of Player: ";
			getline(cin, player_Name);
			while (true)
			{
				cout << "Enter number of Test Matches: ";
				if (cin >> test_matches)
				{
					if (test_matches >= 0) { break; }

					else
					{
						cout << "Enter a Positive Number:\n";
					}
				}
				else
				{
					cout << "invalid input!\t Retry\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}
			cin.ignore(123, '\n');
			while (true)
			{
				cout << "Enter number of ODI matches: ";
				if (cin >> ODI)
				{
					if (ODI >= 0) { break; }

					else
					{
						cout << "Enter a Positive Number:\n";
					}
				}
				else
				{
					cout << "invalid input!\t Retry\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}
			cin.ignore(123, '\n');
			while (true)
			{
				cout << "Enter number of T20 matches: ";
				if (cin >> T20)
				{
					if (T20 >= 0) { break; }

					else
					{
						cout << "Enter a Positive Number:\n";
					}
				}
				else
				{
					cout << "invalid input!\t Retry\n";
					cin.clear();
					cin.ignore(123, '\n');
				}
			}
			cin.ignore(123, '\n');
			flag=dll.insertStats(player_Name, ODI, test_matches, T20);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			if (flag)
			{
				cout << "Insertion was successful!"<<endl;
			}
			else
			{
				cout << "Insertion was unsuccesful! Player Record already exists!" << endl;
			}
			dll.displayStats();
		}
		else if (choice == "2")
		{
			cout << "Enter name of player whose record you want to update: ";
			getline(cin, player_Name);
			flag=dll.updateStats(player_Name);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			if (flag)
			{
				cout << "Updation was successful!" << endl;
			}
			else
			{
				cout << "Updation was unsuccesful!" << endl;
			}
			dll.displayStats();
		}
		else if (choice == "3")
		{
			cout << "Enter name of player whose record you want to delete: ";
			getline(cin, player_Name);
			flag=dll.deleteStatsOfPlayer(player_Name);
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			if (flag)
			{
				cout << "Deletion was successful!" << endl;
			}
			else
			{
				cout << "Deletetion was unsuccesful! Player Record doesnt exist!" << endl;
			}
			dll.displayStats();
		}
		else if (choice == "4")
		{
			dll.displayStats();
		}
		else if (choice == "5")
		{
			clearScreen();
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			cout << "Exiting Application! " << endl;
			cout << "\n-------------------------------------------------------------------------------------------------------\n";
			break;
		}
		else
		{
			cout << "Invalid Input! "<<endl;
		}
	} while (true);



}