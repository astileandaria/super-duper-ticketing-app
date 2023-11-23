#include <iostream>
#include <string>
#include <string.h>
using namespace std;

enum LocationType { MOVIE_THEATER = 200, THEATER = 300, CONFERENCE_HALL = 450, STAGE = 800, STADIUM = 1000, ARENA = 3000 };
enum EventType { CONCERT, STAND_UP, FOOTBALL, BASEBALL, MOVIE, THEATER_PLAY, CONFERENCE };

class WrongDateFormatException {

};
class WrongNameException : public exception {
public:
	WrongNameException(string msg) :exception(msg.c_str()) 
	{

	}
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
	console << endl << "Number of rows: "<< eventLocation.noRows;
	console << endl << "Number of seatsPerRow: " << eventLocation.noSeatsPerRow;
}


class Event {
	string date = "";
	EventType type;
	EventLocation location;
	string* starsOfTheShow = nullptr;
	int noStarsOfTheShow = 0;
public:
	static int MIN_NAME_LENGTH;

	void setDate(string newDate) {
		if (newDate[2] != '/' || newDate[5] != '/' || newDate.size() != 10) {
			throw WrongDateFormatException();
		}
		if (newDate[0] < '0' || newDate[0]>'3') {
			throw WrongDateFormatException();
		}
		if (newDate[1] < '0' || newDate[1] > '9') {
			throw WrongDateFormatException();
		}
		if (newDate[3] < '0' || newDate[3]>'1') {
			throw WrongDateFormatException();
		}
		if (newDate[4] < '1' || newDate[4]>'9') {
			throw WrongDateFormatException();
		}
		this->date = newDate;
	}

	//getters
	string getDate() {
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
	EventType getEventType() {
		return this->type;
	}
	EventLocation getEventLocation() {
		return this->location;
	}
	
	//setters

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
	Event(const Event& object){
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
		if()
	}

	friend void operator<<(ostream& console, Event& event);
};

void operator<<(ostream& console, Event& event) {
	console << endl << "Event date: " << event.date;
	console << endl << "Event type is: " << event.getEventTypeName(event.type);
	console << endl << "The star(s) of the show is/are: ";
	for (int i = 0; i < event.noStarsOfTheShow;i++) {
		console << " " << event.starsOfTheShow[i];
	}
}



int EventLocation::MIN_NAME_LENGTH = 5;
int EventLocation::MAX_NAME_LENGTH = 30;