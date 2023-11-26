#include <iostream>
#include <string>
#include "Classess.h"
using namespace std;

int main() {
	EventLocation eventLocation;
	while (true) {
		try {
			cin >> eventLocation;
		}
		catch (WrongDateFormatException e) {
			cout << endl << "Wrong date";
		}
		catch (WrongNameException e) {
			cout << endl << "Wrong name";
		}
		catch (WrongNumberException e) {
			cout << endl << "Wrong number";
		}
		catch (...) {
			cout << endl << "There's an issue";
		}
	}


	Event event;
	while (true) {
		try {
			cin >> event;
		}
		catch (WrongDateFormatException e) {
			cout << endl << "Wrong date";
		}
		catch (WrongNameException e) {
			cout << endl << "Wrong name";
		}
		catch (WrongNumberException e) {
			cout << endl << "Wrong number";
		}
		catch (...) {
			cout << endl << "There's an issue";
		}
	}

	Ticket ticket;
	while (true) {
		try {
			cin >> ticket;
		}
		catch (WrongDateFormatException e) {
			cout << endl << "Wrong date";
		}
		catch (WrongNameException e) {
			cout << endl << "Wrong name";
		}
		catch (WrongNumberException e) {
			cout << endl << "Wrong number";
		}
		catch (...) {
			cout << endl << "There's an issue";
		}
	}
	
}


