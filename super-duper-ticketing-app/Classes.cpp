#include <iostream>
#include <string>
#include <string.h>
using namespace std;

enum LocationType { MOVIE_THEATER, THEATER, CONFERENCE_HALL, STAGE, STADIUM, ARENA };
enum EventType { CONCERT, STAND_UP, FOOTBALL, BASEBALL, MOVIE, THEATER_PLAY, CONFERENCE };
enum Zones { VIP, NORMAL, STAND1, STAND2, TRIBUNE, CATEGORY1, CATEGORY2, BOX, STANDING };

class WrongDateFormatException: public exception {
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
class WrongNumberException : public exception {
public:
	WrongNumberException(string msg) :exception(msg.c_str())
	{

	}
};

struct Date {
	int year;
	int month;
	int day;
	Date() :day(1), month(1), year(2023) {

	}
	Date(int d, int m, int y): day(d), month(m), year(y) {
		
	}
};

class EventLocation {
	char* venueName = nullptr;
	char venueManager[30] = "";
	int noRows = 0;
	int noSeatsPerRow = 0;
	float rentingPrice = 0;
	LocationType type = LocationType::THEATER;
	int* availableSeatsOnRow = nullptr;	//shows explicitly the free seats' number
	int noAvailableSeatsOnRow = 0;
	int** availableSeats = nullptr; //array of pointers to each int* availableSeatsOnRow; noElements = noRows

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

	//constructors
	EventLocation() {

	}
	EventLocation(const char* venueName, LocationType type) {
		this->setVenueName(venueName);
	}
	EventLocation(const char* venueName, const char* venueManager, int maxNoSeats, int noRows, int noSeatsPerRow, LocationType type, float rentingPrice)
		: noRows(noRows), noSeatsPerRow(noSeatsPerRow), type(type), rentingPrice(rentingPrice) {
		this->setVenueName(venueName);
		this->setVenueManager(venueManager);
	}

	//getters
	float getRentingPrice() {
		return this->rentingPrice;
	}
	int getNoRows() {
		return this->noRows;
	}
	int getNoSeatsPerRow() {
		return this->noSeatsPerRow;
	}
	char* getVenueManager() {
		char* copy = new char[strlen(this->venueManager) + 1];
		strcpy_s(copy, strlen(this->venueManager) + 1, this->venueManager);
		return copy;
	}
	char* getVenueName() {
		char* copy = new char[strlen(this->venueName) + 1];
		strcpy_s(copy, strlen(this->venueName) + 1, this->venueName);
		return copy;
	}
	LocationType getLocationType() {
		return this->type;
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
	int* getAvailableSeatsOnRow() {
		int* copy = new int[this->noAvailableSeatsOnRow];
		for (int i = 0; i < this->noAvailableSeatsOnRow; i++) {
			copy[i] = availableSeatsOnRow[i];
		}
		return copy;
	}

	//setters
	void setRentingPrice(float newPrice) {
		if (newPrice <= 0) {
			throw WrongNumberException("Price cannot be lower than 0!");
		}
		this->rentingPrice = newPrice;
	}
	void setLocationType(LocationType type) {
		if (type >= 0 && type <= 5) {
			this->type = type;
		}
		else {
			throw WrongNumberException("That location type is invalid!");
		}
	}
	void setNoSeatsPerRows(int noSeatsPerRow){
		if (noSeatsPerRow < 0) {
			throw WrongNumberException("Wrong number!");
		}
		this->noSeatsPerRow = noSeatsPerRow;
	}
	void setNoRows(int noRows) {
		if (noRows < 0) {
			throw WrongNumberException("Wrong number!");
		}
		this->noRows = noRows;
	}
	void setVenueName(const char* name) {
		if (strlen(name) < EventLocation::MIN_NAME_LENGTH || strlen(name) > EventLocation::MAX_NAME_LENGTH) {
			throw WrongNumberException("The location name must be between 5 and 30 characters!");
		}
		else {
			if (this->venueName != nullptr) {
				delete[]this->venueName;
			}
			this->venueName = new char[strlen(name) + 1];
			strcpy_s(this->venueName, strlen(name) + 1, name);
		}
	}
	void setVenueManager(const char* manager) {
		if (strlen(manager) < EventLocation::MIN_NAME_LENGTH || strlen(manager) > EventLocation::MAX_NAME_LENGTH) {
			throw WrongNumberException("The name must have between 5 and 30 characters!");
		}
		strcpy_s(this->venueManager, strlen(manager) + 1, manager);
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

	//copy constructor
	EventLocation(const EventLocation& object)
		: noRows(object.noRows), noSeatsPerRow(object.noSeatsPerRow), type(object.type), rentingPrice(object.rentingPrice) {
		this->venueName = new char[strlen(object.venueName) + 1];
		strcpy_s(this->venueName, strlen(object.venueName) + 1, object.venueName);
		strcpy_s(this->venueManager, strlen(object.venueManager) + 1, object.venueManager);
		this->availableSeatsOnRow = new int[object.noAvailableSeatsOnRow];
		for (int i = 0; i < object.noAvailableSeatsOnRow; i++) {
			this->availableSeatsOnRow[i] = object.availableSeatsOnRow[i];
		}
		this->noAvailableSeatsOnRow = object.noAvailableSeatsOnRow;
		this->availableSeats = new int* [object.noRows];
		for (int i = 0; i < this->noRows; i++) {
			this->availableSeats[i] = object.availableSeats[i];
		}
	}

	//destructor
	~EventLocation() {
		delete[]this->venueName;
		delete[]this->availableSeats;
		delete[]this->availableSeatsOnRow;
	}

	//operators
	void operator=(const EventLocation source) {
		if (&source == this) {
			return;
		}
		this->setVenueName(source.venueName);
		this->setNoRows(source.noRows);
		this->setNoSeatsPerRows(source.noSeatsPerRow);
	}
	bool operator==(EventLocation object) {
		if (object.calculateTotalNoSeats() == this->calculateTotalNoSeats()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator>=(EventLocation object) {
		if (object.calculateTotalNoSeats() >= this->calculateTotalNoSeats()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!() {
		if (this->noRows == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	EventLocation operator--() {
		this->rentingPrice -= 1;
		return *this;
	}
	EventLocation operator--(int) {
		EventLocation copy = *this;
		this->rentingPrice -= 1;
		return copy;
	}
	EventLocation operator*(int n) {
		EventLocation copy = *this;
		copy.rentingPrice *= n;
		return copy;
	}
	int& operator[](int index) {
		if (index<0 || index>this->noSeatsPerRow) {
			throw WrongNumberException("Wrong index number");
		}
		return this->availableSeatsOnRow[index];
	}
	explicit operator float() {
		int sum = 0;
		for (int i = 0; i < this->noAvailableSeatsOnRow; i++) {
			sum += this->availableSeatsOnRow[i];
		}
		if (this->noAvailableSeatsOnRow == 0) {
			return 0;
		}
		else {
			return (float)sum / this->noAvailableSeatsOnRow;
		}
	}

	friend void operator<<(ostream& console, EventLocation& eventLocation);
	friend void operator>>(istream& console, EventLocation& eventLocation);
};

void operator<<(ostream& console, EventLocation& eventLocation) {
	console << endl << "Location name: " << eventLocation.venueName;
	console << endl << "Manager name is: " << eventLocation.venueManager;
	console << endl << "renting price is: " << eventLocation.rentingPrice;
	console << endl << "Event type is: " << eventLocation.getLocationTypeName(eventLocation.type);
	console << endl << "Number of rows: " << eventLocation.noRows;
	console << endl << "Number of seatsPerRow: " << eventLocation.noSeatsPerRow;
}
void operator>>(istream& console, EventLocation& eventLocation) {
	cout << endl << "Venue Name: ";
	char* venueName;
	console >> venueName;
	eventLocation.venueName = venueName;
	cout << endl << "Venue manager: ";
	char venueManager[30];
	console >> venueManager;
	eventLocation.setVenueManager(venueManager);
	cout << endl << "Renting price is: ";
	float price;
	console >> price;
	eventLocation.rentingPrice = price;
	cout << endl << "Number of rows: ";
	int noRows;
	console >> noRows;
	eventLocation.noRows = noRows;
	cout << endl << "Number of seats per row: ";
	int noSeatsPerRow;
	console >> noSeatsPerRow;
	eventLocation.noSeatsPerRow = noSeatsPerRow;
	cout << endl << "Location type: ";
	int type;
	console >> type;
	if (type >= 0 && type <= 5) {
		LocationType type = static_cast<LocationType>(type);
		eventLocation.type = type;
	}
}

class Event {
	Date date;
	char eventName[30] = "";
	EventType type = EventType::CONCERT;
	EventLocation location;
	string* starsOfTheShow = nullptr;
	int noStarsOfTheShow = 0;
	float entryPrice = 0;
public:
	//statics
	static int MIN_NAME_LENGTH;
	static int MAX_NAME_LENGTH;

	//other methods
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
	void displayDate() {
		cout << endl << this->date.day << "/" << this->date.month << "/" << this->date.year;
	}
	void printInfo() {
		cout << endl << "Event name is: " << this->eventName;
		cout << endl << "Event entry price is: " << this->entryPrice;
		cout << endl << "Event date is: " << this->date.day << "/" << this->date.month << "/" << this->date.year;
		cout << endl << "Event type is: " << this->getEventTypeName(type);
		cout << endl << "Event location is: " << this->location.getVenueName();
		cout << endl << "The star(s) of the show is/are: ";
		for (int i = 0; i < this->noStarsOfTheShow;i++) {
			cout << " " << this->starsOfTheShow[i];
		}
	}

	//constructors
	Event() :date(), location() {

	}
	Event(const char* eventName, float enthryPrice) : entryPrice(entryPrice) {
		this->setEventName(eventName);
	}
	Event(int day, int month, int year, EventType type, const char* venueName, LocationType locationType, const char* eventName, float entryPrice)
		: date(day, month, year), location(venueName, locationType), type(type), entryPrice(entryPrice) {
		this->setEventName(eventName);
	}

	//getters
	float getEntryPrice() {
		return this->entryPrice;
	}
	Date getDate() {
		return this->date;
	}
	char* getEventName() {
		char* copy = new char[strlen(this->eventName) + 1];
		strcpy_s(copy, strlen(this->eventName) + 1, this->eventName);
		return copy;
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
	void setEntryPrice(float newEntryPrice) {
		if (newEntryPrice <= 0) {
			throw WrongNumberException("Price cannot be lower than 0!");
		}
		this->entryPrice = newEntryPrice;
	}
	void setDate(int d, int m, int y) {
		if (d < 0 || d > 31) {
			throw WrongDateFormatException("Invalid day!");
		}
		if (m < 1 || m > 12) {
			throw WrongDateFormatException("Invalid month!");
		}
		if (y < 2023) {
			throw WrongDateFormatException("Invalid year!");
		}
		this->date.day = d;
		this->date.month = m;
		this->date.year = y;
	}
	void setEventName(const char* name) {
		if (strlen(name) < Event::MIN_NAME_LENGTH || strlen(name) > Event::MAX_NAME_LENGTH) {
			throw WrongNumberException("The name must have between 5 and 30 characters!");
		}
		strcpy_s(this->eventName, strlen(name) + 1, name);
	}
	void setNoStarsOfTheShow(int number){
		if (number < 0) {
			throw WrongNumberException("Wrong number!");
		}
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
		if (type < 0 || type > 6) {
			throw WrongNumberException("Wrong number!");
		}
		this->type = type;
	}
	void setEventLocation(EventLocation location) {
		this->location = location;
	}

	//copy constructor
	Event(const Event& object) : date(object.date), type(object.type), location(object.location), entryPrice(object.entryPrice) {
		this->starsOfTheShow = new string[object.noStarsOfTheShow];
		for (int i = 0; i < object.noStarsOfTheShow; i++) {
			this->starsOfTheShow[i] = object.starsOfTheShow[i];
		}
		this->noStarsOfTheShow = object.noStarsOfTheShow;

		strcpy_s(this->eventName, strlen(object.eventName), object.eventName);
	}

	//destructor
	~Event() {
		delete[]this->starsOfTheShow;
	}

	//operators
	void operator=(const Event source) {
		if (&source == this) {
			return;
		}
		this->setDate(source.date.day, source.date.month, source.date.year);
		this->setEventLocation(source.location);
		this->setEventType(source.type);
		this->setNoStarsOfTheShow(source.noStarsOfTheShow);
		this->setStarsOfTheShow(source.starsOfTheShow->c_str());
	}
	bool operator>=(Event object) {
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
	bool operator==(Event object) {
		if (this->entryPrice == object.entryPrice) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!() {
		if (this->noStarsOfTheShow == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	Event operator++() {
		this->entryPrice += 1;
		return *this;
	}
	Event operator++(int) {
		Event copy = *this;
		this->entryPrice += 1;
		return copy;
	}
	Event operator-(int n) {
		Event copy = *this;
		this->entryPrice -= n;
		return copy;
	}
	string& operator[](int index) {
		if (index < 0 || index >= this->noStarsOfTheShow) {
			throw WrongNumberException("Wrong index number");
		}
		return this->starsOfTheShow[index];
	}
	explicit operator int() {
		return static_cast<int>(this->entryPrice);
	}

	friend void operator<<(ostream& console, Event& event);
	friend void operator>>(istream& console, Event& event);
};

void operator<<(ostream& console, Event& event) {
	console << endl << "Event date: " << event.date.day << "/" << event.date.month << "/" << event.date.year;
	console << endl << "Event name is: " << event.eventName;
	console << endl << "Entry price is: " << event.entryPrice;
	console << endl << "Event type is: " << event.getEventTypeName(event.type);
	console << endl << "The star(s) of the show is/are: ";
	for (int i = 0; i < event.noStarsOfTheShow;i++) {
		console << " " << event.starsOfTheShow[i];
	}
}
void operator>>(istream& console, Event& event) {
	cout << endl << "Set the date of the event: ";
	cout << endl << "Day: ";
	int day;
	console >> day;
	event.date.day = day;
	cout << endl << "Month: ";
	int month;
	console >> month;
	event.date.month = month;
	cout << endl << "Year: ";
	int year;
	console >> year;
	event.date.year = year;
	cout << endl << "Event name: ";
	char eventName[30];
	console >> eventName;
	cout << endl << "Entry price is: ";
	float price;
	console >> price;
	event.entryPrice = price;
	event.setEventName(eventName);
	cout << endl << "Event type: ";
	int type;
	console >> type;
	if (type >= 0 && type <= 6) {
		EventType type = static_cast<EventType>(type);
		event.type = type;
	}
	cout << endl << "Number of stars of the show (performers): ";
	int noStarsOfTheShow;
	console >> noStarsOfTheShow;
	event.noStarsOfTheShow = noStarsOfTheShow;
	cout << endl << "Names of the performers: ";
	string* starsOfTheShow;
	for (int i = 0; i < event.noStarsOfTheShow; i++) {
		cout << endl << i << ". Input a name: ";
		string name;
		console >> name;
		starsOfTheShow[i] = name;
		console >> starsOfTheShow[i];
	}
	event.starsOfTheShow = starsOfTheShow;
	cout << endl << "Location: ";
	cout << endl << "Input the location name: ";
	char* venueName;
	console >> venueName;
	event.location.setVenueName(venueName);
	cout << endl << "Input the type of the location: ";
	int locationType;
	console >> locationType;
	if (locationType >= 0 && locationType <= 5) {
		LocationType locationType = static_cast<LocationType>(locationType);
		event.location.setLocationType(locationType);
	}
}


class Ticket {
	int id = 0;
	char ownerName[30] = "";
	int seatNumber = 1;
	int rowNumber = 0;
	EventLocation location;
	Zones zone = Zones::NORMAL;
	int* usedIds = nullptr;		//to keep track of already used ID's & ensure uniqueness of new ID's
	int noUsedIds = 0;
public:
	//statics
	static int MIN_NAME_LENGTH;
	static int MAX_NAME_LENGTH;

	//other methods
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
	int checkIdUniqueness(int k) {
		int ok = 1;
		for (int i = 0; i < this->noUsedIds;i++) {
			if (k == usedIds[i]) {
				ok = -1;
			}
		}
		return ok;
	}

	//constructors
	Ticket() {
	}
	Ticket(int id, const char* ownerName, int seatNumber, int rowNumber) : id(id), seatNumber(seatNumber), rowNumber(rowNumber) {
		this->setOwnerName(ownerName);
	}
	Ticket(int id, int seatNumber, int rowNumber, const char* venueName, LocationType type, Zones zone, const char* ownerName)
		:id(id), seatNumber(seatNumber), rowNumber(rowNumber), location(venueName, type), zone(zone) {
		this->setOwnerName(ownerName);
	}

	//getters
	int getId() {
		return this->id;
	}
	char* getOwnerName() {
		char* copy = new char[strlen(this->ownerName) + 1];
		strcpy_s(copy, strlen(this->ownerName) + 1, this->ownerName);
		return copy;
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
	Zones getZone() {
		return this->zone;
	}

	//setters
	void setZone(Zones zone) {
		if (zone < 0 || zone >8) {
			throw WrongNumberException("Wrong number!");
		}
		this->zone = zone;
	}
	void setOwnerName(const char* name) {
		if (strlen(name) < Ticket::MIN_NAME_LENGTH || strlen(name) > Ticket::MAX_NAME_LENGTH) {
			throw WrongNumberException("The name must have between 5 and 30 characters!");
		}
		strcpy_s(this->ownerName, strlen(name) + 1, name);
	}
	void setSeatNumber(int seatNumber) {
		if (seatNumber <= 0 || seatNumber > 50) {
			throw WrongNumberException("The seat number is not valid!");
		}
		else {
			this->seatNumber = seatNumber;
		}
	}
	void setRowNumber(int rowNumber) {
		if (rowNumber < 0 || rowNumber > 100) {
			throw WrongNumberException("The row number is not valid!");
		}
		else {
			this->rowNumber = rowNumber;
		}
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
	Ticket(const Ticket& object)
		:id(object.id), seatNumber(object.seatNumber), rowNumber(object.rowNumber), location(object.location), zone(object.zone) {
		this->usedIds = new int[object.noUsedIds];
		for (int i = 0; i < object.noUsedIds; i++) {
			this->usedIds[i] = object.usedIds[i];
		}
		this->noUsedIds = object.noUsedIds;

		strcpy_s(this->ownerName, strlen(object.ownerName) + 1, object.ownerName);
	}

	//destructor
	~Ticket() {
		delete[]this->usedIds;
	}

	//operators
	void operator=(const Ticket source) {
		if (&source == this) {
			return;
		}
		this->setId();
		this->setRowNumber(source.rowNumber);
		this->setSeatNumber(source.seatNumber);
		this->setZone(source.zone);
	}
	bool operator==(Ticket object) {
		if (this->rowNumber == object.rowNumber) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator<=(Ticket object) {
		if (this->rowNumber <= object.rowNumber) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!() {
		if (this->noUsedIds == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	Ticket operator++(int) {
		Ticket copy = *this;
		this->seatNumber += 1;
		return copy;
	}
	Ticket operator++() {
		this->seatNumber += 1;
		return *this;
	}
	Ticket operator+(int n) {
		Ticket copy = *this;
		this->rowNumber += n;
		return copy;
	}
	int& operator[](int index) {
		if (index < 0 || index >= this->noUsedIds) {
			throw WrongNumberException("Wrong index number");
		}
		return this->usedIds[index];
	}
	explicit operator string() {
		return static_cast<string>(ownerName);
	}

	friend void operator<<(ostream& console, Ticket& ticket);
	friend void operator>>(istream& console, Ticket& ticket);
};

void operator<<(ostream& console, Ticket& ticket) {
	console << endl << "Ticket ID: " << ticket.id;
	console << endl << "Name is: " << ticket.ownerName;
	console << endl << "Row number is: " << ticket.rowNumber;
	console << endl << "Seat number is " << ticket.seatNumber;
	console << endl << "Zone is: " << ticket.getZoneName(ticket.zone);
	console << endl << "Location is: " << ticket.location;
}
void operator>>(istream& console, Ticket& ticket) {
	cout << endl << "Your unique ID is being generated: ";
	ticket.setId();
	cout << endl << "Enter your name: ";
	char ownerName[30];
	console >> ownerName;
	ticket.setOwnerName(ownerName);
	cout << endl << "Row number: ";
	int noRow;
	console >> noRow;
	ticket.rowNumber = noRow;
	cout << endl << "Seat number: ";
	int seatNumber;
	console >> seatNumber;
	ticket.seatNumber = seatNumber;
	cout << endl << "Select zone: ";
	int zone;
	console >> zone;
	if (zone >= 0 && zone <= 8) {
		Zones zone = static_cast<Zones>(zone);
		ticket.zone = zone;
	}
	cout << endl << "Location: ";
	cout << endl << "Input the location name: ";
	char* venueName;
	console >> venueName;
	ticket.location.setVenueName(venueName);
	cout << endl << "Input the type of the location: ";
	int locationType;
	console >> locationType;
	if (locationType >= 0 && locationType <= 5) {
		LocationType locationType = static_cast<LocationType>(locationType);
		ticket.location.setLocationType(locationType);
	}

}

int EventLocation::MIN_NAME_LENGTH = 5;
int EventLocation::MAX_NAME_LENGTH = 30;