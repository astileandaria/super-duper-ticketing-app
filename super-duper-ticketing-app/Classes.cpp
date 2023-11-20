#include <iostream>
#include <string>
#include <string.h>
using namespace std;

enum LocationType { MOVIE_THEATER = 200, THEATER = 300, CONFERENCE_HALL = 450, STAGE = 800, STADIUM = 1000, ARENA = 3000 };

class EventLocation {
	char* venueName = nullptr;
	int maxNoSeats = 0;
	int noRows = 0;
	int noSeatsPerRow = 0;
	LocationType type = LocationType::THEATER;

	int* availableSeatsOnRow = nullptr;
	int noAvailableSeatsOnRow = 0;
	int** availableSeats = nullptr; //array of pointers to each int* availableSeatsOnRow; noElements = noRows

public:
	//statics
	static int MIN_NAME_LENGTH;
	static int MAX_NAME_LENGTH;

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
	int getNoAvailableSeatsOnRow() {
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
	}
	string getLocationTypeName() {	//so we can see the actual names instead of the associated numbers
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
	void setInitialAvailableSeats(int* const availableSeatsOnRow, int** availableSeats) {
		//if (someAvailableSeats == nullptr) {
		//	throw exception("No more available seats!");
		//}
		if (this->availableSeatsOnRow != nullptr) {
			delete[]availableSeatsOnRow;
		}
		if (this->availableSeats != nullptr) {
			delete[]availableSeats;
		}
		this->availableSeatsOnRow = new int[this->noSeatsPerRow];
		this->availableSeats = new int* [this->noRows];

		for (int j = 0; j < this->noRows; j++) { //populating the array of pointers toeach row
			for (int i = 0; i < this->noSeatsPerRow; i++) {	//populating each row with its corresponding seat numbers
				this->availableSeatsOnRow[i] = i + 1; //the seat numbers start from 1 
			}
			this->availableSeats[j] = &this->availableSeatsOnRow[j];
		}
	}
};
int EventLocation::MIN_NAME_LENGTH = 5;
int EventLocation::MAX_NAME_LENGTH = 30;