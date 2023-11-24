#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

enum LocationType { MOVIE_THEATER = 200, THEATER = 300, CONFERENCE_HALL = 450, STAGE = 800, STADIUM = 1000, ARENA = 3000 };
enum EventType { CONCERT, STAND_UP, FOOTBALL, BASEBALL, MOVIE, THEATER_PLAY, CONFERENCE };
enum Zones { VIP, NORMAL, STAND1, STAND2, TRIBUNE, CATEGORY1, CATEGORY2, BOX, STANDING };

class WrongDateFormatException : public exception {
public:
	WrongDateFormatException(string msg) :exception(msg.c_str()) {

	}
};
class WrongNameException : public exception {
public:
	WrongNameException(string msg) :exception(msg.c_str())
	{

	}
};

struct Date {
	int year;
	int month;
	int day;
};

class EventLocation {
	char* venueName = nullptr;
	int maxNoSeats = 0;
	int noRows = 0;
	int noSeatsPerRow = 0;
	LocationType type = LocationType::THEATER;

	//int* availableSeatsOnRow = nullptr;
	//int noAvailableSeatsOnRow = 0;
	//int** availableSeats = nullptr; //array of pointers to each int* availableSeatsOnRow; noElements = noRows

public:
	//statics
	static int MIN_NAME_LENGTH;
	static int MAX_NAME_LENGTH;

	//other methods
	int calculateTotalNoSeats() {
		int total = 0;
		total = this->noRows * this->noSeatsPerRow;
		return total;
	}

	//constructors
	EventLocation() {

	}
	EventLocation(const char* venueName, LocationType type) : type(type) {
		setVenueName(venueName);
	}
	EventLocation(const char* venueName, int maxNoSeats, int noRows, int noSeatsPerRow, LocationType type)
		: maxNoSeats(maxNoSeats), noRows(noRows), noSeatsPerRow(noSeatsPerRow), type(type) {
		setVenueName(venueName);
	}
	EventLocation(const EventLocation& location)
		:venueName(location.venueName), maxNoSeats(location.maxNoSeats), noRows(location.noRows), noSeatsPerRow(location.noSeatsPerRow), type(location.type) {

	}

	//getters
	int getMaxNoSeats() {
		return this->maxNoSeats;
	}
	int getNoRows() {
		return this->noRows;
	}
	int getNoSeatsPerRow() {
		return this->noSeatsPerRow;
	}
	/*int getNoAvailableSeatsOnRow() {
		return this->noAvailableSeatsOnRow;
	}
	int** getAvailableSeats() {
		int** copy = new int* [this->noRows];
		for (int i = 0; i < this->noRows; i++) {
			copy[i] = availableSeats[i];
		}
		return copy;
	}
	char* getVenueName() {
		return this->venueName;
	}
	int* getAvailableSeatsOnRow() {
		int* copy = new int[this->noAvailableSeatsOnRow];
		for (int i = 0; i < this->noAvailableSeatsOnRow; i++) {
			copy[i] = availableSeatsOnRow[i];
		}
		return copy;
	}*/
	string getLocationTypeName(LocationType type) {	//so we can see the actual names instead of the associated numbers
		switch (this->type)
		{
		case MOVIE_THEATER:
			return "Undergraduate";
		case THEATER:
			return "MOVIE_THEATER";
		case CONFERENCE_HALL:
			return "Phd";
		case STAGE:
			return "Stage";
		case STADIUM:
			return "Stadium";
		case ARENA:
			return "Arena";
		}
	}
	LocationType getLocationType() {
		return this->type;
	}

	//setters

	void setMaxNoSeats(LocationType type) {
		this->maxNoSeats = (int)type;
	}
	void setNoSeatsPerRows(int noSeatsPerRow) {
		this->noSeatsPerRow = noSeatsPerRow;
	}
	void setNoRows(int noRows) {
		this->noRows = noRows;
	}
	void setVenueName(const char* name) {
		if (strlen(name) < EventLocation::MIN_NAME_LENGTH || strlen(name) > EventLocation::MAX_NAME_LENGTH) {
			throw exception("The location name must be between 5 and 30 characters!");
		}
		else {
			if (this->venueName != nullptr) {
				delete[]this->venueName;
			}
			this->venueName = new char[strlen(name) + 1];
			strcpy_s(this->venueName, strlen(name) + 1, name);
		}
	}
	//void setInitialAvailableSeats(int* const availableSeatsOnRow, int** availableSeats) {
	//	//if (someAvailableSeats == nullptr) {
	//	//	throw exception("No more available seats!");
	//	//}
	//	if (this->availableSeatsOnRow != nullptr) {
	//		delete[]availableSeatsOnRow;
	//	}
	//	if (this->availableSeats != nullptr) {
	//		delete[]availableSeats;
	//	}
	//	this->availableSeatsOnRow = new int[this->noSeatsPerRow];
	//	this->availableSeats = new int* [this->noRows];

	//	for (int j = 0; j < this->noRows; j++) { //populating the array of pointers toeach row
	//		for (int i = 0; i < this->noSeatsPerRow; i++) {	//populating each row with its corresponding seat numbers
	//			this->availableSeatsOnRow[i] = i + 1; //the seat numbers start from 1 
	//		}
	//		this->availableSeats[j] = &this->availableSeatsOnRow[j];
	//	}
	//}

	//copy constructor
	EventLocation(const EventLocation& object) {
		this->venueName = new char[strlen(object.venueName) + 1];
		for (int i = 0; i < strlen(object.venueName) + 1; i++) {
			this->venueName[i] = object.venueName[i];
		}
	}

	//destructor
	~EventLocation() {
		delete[]this->venueName;
	}

	//operators

	bool operator==(EventLocation object) {
		if (object.calculateTotalNoSeats() == this->calculateTotalNoSeats()) {
			return true;
		}
		else {
			return false;
		}
	}

	friend void operator<<(ostream& console, EventLocation& eventLocation);
};

void operator<<(ostream& console, EventLocation& eventLocation) {
	console << endl << "Location name: " << eventLocation.venueName;
	console << endl << "Event type is: " << eventLocation.getLocationTypeName(eventLocation.type);
	console << endl << "Number of rows: " << eventLocation.noRows;
	console << endl << "Number of seatsPerRow: " << eventLocation.noSeatsPerRow;
}


class Event {
	Date date;
	EventType type;
	EventLocation location;
	string* starsOfTheShow = nullptr;
	int noStarsOfTheShow = 0;
public:
	static int MIN_NAME_LENGTH;

	void setDate(Date newDate) {
		if (newDate.day < 0 || newDate.day>31) {
			throw WrongDateFormatException("Invalid day!");
		}
		if (newDate.month < 1 || newDate.month>12) {
			throw WrongDateFormatException("Invalid month!");
		}
		if (newDate.year < 2023) {
			throw WrongDateFormatException("Invalid year!");
		}
	}

	//getters
	Date getDate() {
		return this->date;
	}
	int getNoStarsOfTheShow() {
		return this->noStarsOfTheShow;
	}
	string* getStarsOfTheShow() {
		string* copy = new string[this->noStarsOfTheShow];
		for (int i = 0; i < this->noStarsOfTheShow; i++) {
			copy[i] = starsOfTheShow[i];
		}
		return copy;
	}

	string getEventTypeName(EventType type) {	//so we can see the actual names instead of the associated numbers
		switch (this->type)
		{
		case CONCERT:
			return "Concert";
		case STAND_UP:
			return "Stand up";
		case FOOTBALL:
			return "Football";
		case BASEBALL:
			return "Baseball";
		case MOVIE:
			return "Movie";
		case THEATER_PLAY:
			return "Theater play";
		case CONFERENCE:
			return "Conference";
		}
	}
	EventType getEventType() {
		return this->type;
	}
	EventLocation getEventLocation() {
		return this->location;
	}

	//setters



	void setNoStarsOfTheShow(int number) {
		this->noStarsOfTheShow = number;
	}
	void setStarsOfTheShow(string name) {
		if (name.size() < MIN_NAME_LENGTH) {
			throw WrongNameException("Name is too short!");
		}
		string* newList = new string[this->noStarsOfTheShow = 1];
		for (int i = 0; i < this->noStarsOfTheShow;i++) {
			newList[i] = this->starsOfTheShow[i];
		}
		delete[] this->starsOfTheShow;
		this->starsOfTheShow = newList;
		this->starsOfTheShow[this->noStarsOfTheShow] = name;
		this->noStarsOfTheShow += 1;
	}
	void setEventType(EventType type) {
		this->type = type;
	}
	void setEventLocation(EventLocation location) {
		this->location = location;
	}

	//copy constructor
	Event(const Event& object) {
		this->starsOfTheShow = new string[object.noStarsOfTheShow];
		for (int i = 0; i < object.noStarsOfTheShow; i++) {
			this->starsOfTheShow[i] = object.starsOfTheShow[i];
		}
		this->noStarsOfTheShow = object.noStarsOfTheShow;
	}

	//destructor
	~Event() {
		delete[]this->starsOfTheShow;
	}

	//operators

	bool operator >=(Event object) {
		int ok = 0; //while ok = 0, the object's date is not >= than the "this" date
		if (object.date.year > this->date.year) {
			ok = 1;
		}
		if (object.date.year == this->date.year) {
			if (object.date.month > this->date.month) {
				ok = 1;
			}
			if (object.date.month == this->date.month) {
				if (object.date.day > this->date.day) {
					ok = 1;
				}
			}
		}
		if (ok == 1) {
			return true;
		}
		else return false;
	}

	friend void operator<<(ostream& console, Event& event);
};

void operator<<(ostream& console, Event& event) {
	console << endl << "Event date: " << event.date.day << "/" << event.date.month << "/" << event.date.year;
	console << endl << "Event type is: " << event.getEventTypeName(event.type);
	console << endl << "The star(s) of the show is/are: ";
	for (int i = 0; i < event.noStarsOfTheShow;i++) {
		console << " " << event.starsOfTheShow[i];
	}
}



class Ticket {
	int id = 0;
	int seatNumber = 1;
	int rowNumber = 0;
	EventLocation location;
	Zones zone = Zones::NORMAL;

	int* usedIds = nullptr;		//to keep track of already used ID's & ensure uniqueness of new ID's
	int noUsedIds = 0;

public:
	//constructors
	Ticket() {
	}
	Ticket(int id, int seatNumber, int rowNumber, const char* venueName, LocationType type, Zones zone)
		:id(id), seatNumber(seatNumber), rowNumber(rowNumber), location(venueName, type), zone(zone) {

	}
	Ticket(const Ticket& ticket) : id(ticket.id), seatNumber(ticket.seatNumber), rowNumber(ticket.rowNumber), location(ticket.location), zone(ticket.zone) {

	}

	//getters
	int getId() {
		return this->id;
	}
	int getSeatNumber() {
		return this->seatNumber;
	}
	int getRowNumber() {
		return this->rowNumber;
	}
	EventLocation getEventLocation() {
		return this->location;
	}

	string getZoneName(Zones zone) {	//so we can see the actual names instead of the associated numbers
		switch (this->zone)
		{
		case VIP:
			return "VIP";
		case NORMAL:
			return "Normal";
		case STAND1:
			return "Stand 1";
		case STAND2:
			return "Stand 2";
		case TRIBUNE:
			return "Tribune";
		case CATEGORY1:
			return "Category 1";
		case CATEGORY2:
			return "Category 2";
		case BOX:
			return "Box";
		case STANDING:
			return "Standing";
		}
	}
	Zones getZone() {
		return this->zone;
	}

	//setters
	void setZone(Zones zone) {
		this->zone = zone;
	}
	void setSeatNumber(int seatNumber) {
		if (seatNumber <= 0 || seatNumber > 50) {
			throw exception("The seat number is not valid!");
		}
		else {
			this->seatNumber = seatNumber;
		}
	}
	void setRowNumber(int rowNumber) {
		if (rowNumber < 0 || rowNumber > 100) {
			throw exception("The row number is not valid!");
		}
		else {
			this->rowNumber = rowNumber;
		}
	}

	int checkIdUniqueness(int k) {
		int ok = 1;
		for (int i = 0; i < this->noUsedIds;i++) {
			if (k == usedIds[i]) {
				ok = -1;
			}
		}
		return ok;
	}

	void setId() {
		int k = rand() % 1000000;
		while (checkIdUniqueness(k) == -1) {
			k = rand() % 1000000;
		}
		usedIds[noUsedIds++] = k;
		this->id = k;
	}

	//copy constructor
	Ticket(const Ticket& object) {
		this->usedIds = new int[object.noUsedIds];
		for (int i = 0; i < object.noUsedIds; i++) {
			this->usedIds[i] = object.usedIds[i];
		}
		this->noUsedIds = object.noUsedIds;
	}

	//destructor
	~Ticket() {
		delete[]this->usedIds;
	}

	//operators

	friend void operator<<(ostream& console, Ticket& ticket);
};

void operator<<(ostream& console, Ticket& ticket) {
	console << endl << "Ticket ID: " << ticket.id;
	console << endl << "Row number is: " << ticket.rowNumber;
	console << endl << "Seat number is " << ticket.seatNumber;
	console << endl << "Zone is: " << ticket.getZoneName(ticket.zone);
	console << endl << "Location is: " << ticket.location;
}

/*
bool isValid = true;
	do { //the user will be in this loop until they insert correct values
		isValid = true;
		cout << endl << "Product price: ";
		cin >> price;
		if (price < Product::MIN_PRICE) {
			cout << endl << "Wrong price";
			isValid = false;
		}
		cout << endl << "Product name: ";
		cin >> name;
		if (strlen(name) < Product::MIN_NAME_LENGTH) {
			cout << endl << "Wrong name";
			isValid = false;
		}
		cout << endl << "Product manufacturer: ";
		cin >> manufacturer;
	} while (!isValid);
*/



int EventLocation::MIN_NAME_LENGTH = 5;
int EventLocation::MAX_NAME_LENGTH = 30;