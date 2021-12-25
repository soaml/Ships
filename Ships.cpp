#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
using namespace std;
int main() {
	ifstream fin("SHIPS.IN");
	ofstream fout("SHIPS.OUT");
	if (!fin) {
		fout << "File isn't found";
		return 1;
	}
	if (fin.peek() == EOF) {
		fout << "File is empty";
		return 1;
	}
	if (!fout.is_open()) {
		cout << "Can't open file";
		return 1;
	}

	int N;
	fin >> N;
	vector <string> docks(N);
	string s, ship_name;
	deque <string> ship_queue;
	stringstream text;
	int option, dock_number;

	while (getline(fin, s)) {
		fin >> option;
		text.clear();
		text << s;
		auto  empty_dock = find(docks.begin(), docks.end(), "");
		switch (option) {
		case '1':
			text >> ship_name;
			fout << "The ship " << ship_name << " arrived at the port." << endl;
			if (empty_dock == docks.end()) {
				ship_queue.push_back(ship_name);
				fout << "The ship queues up at the raid." << endl;
			}
			else {
				fout << "The ship goes to the dock." << endl;
				*empty_dock = ship_name;
			}
			break;

		case '2':
			text >> dock_number;
			fout << "The dock № " << dock_number << " is free." << endl;
			docks[dock_number - 1] = "";
			if (!ship_queue.empty()) {
				fout << "To the dock № " << dock_number << " goes the ship " << ship_queue.front() << endl;
				docks[dock_number - 1] = ship_queue.front();
				auto first = ship_queue.cbegin();
				ship_queue.erase(first);
			}
			break;

		case '3':
			fout << "Current state of the queue at the raid:" << endl;
			if (!ship_queue.empty()) {
				for (int i = 0; i < ship_queue.size(); i++) {
					fout << i + 1 << " " << ship_queue[i] << endl;
				}
			}
			else {
				fout << "There are no ships at the raid." << endl;
			}
			break;

		case '4':
			fout << "Current state of the docks:" << endl;
			for (int i = 0; i < N; i++) {
				fout << "The dock № " << i + 1;
				if (!docks[i].empty()) {
					fout << ": " << docks[i] << endl;
				}
				else {
					fout << " is empty." << endl;
				}
			}
			break;

		default:
			fout << "Unknown choice." << endl;
			break;
		}
	}
	fin.close();
	fout.close();
	return 0;
}