/**
 * Nassim Marhari
 * string.cpp
 * CS 23001 string project
 */

#include "string.hpp"

String::String() {
	stringSize = 1; // make char array of 1 and hold only null terminator
	str = new char[stringSize]; // allocate memory needed...
	str[0] = 0;
}

String::String(char ch) {
	if (ch == 0) stringSize = 1; // if ch is \0 it will be an empty String
	else stringSize = 2; // otherwise, itll be ch and null terminator
	str = new char[stringSize];
	str[0] = ch; // index 0 is ch
	if (ch != 0) str[1] = 0; // if it isnt \0 then index 1 is null termin.
}

String::String(const char input[]) {
	int len = 0;
	while (input[len] != 0) ++len; // get length of input[]

	stringSize = 1 + len; // +1 for null terminator
	str = new char[stringSize];

	int i = 0;
	while (i != len) { // while it is not the end of the char array...
		if (i > capacity()) break;
		str[i] = input[i]; // str[i] = input[i]
		++i;
	}
	str[i] = 0; // null terminator
}

String::String(const String& rhs) {
	stringSize = rhs.stringSize; // copy rhs stringSize to *this
	str = new char[stringSize];
	for (int i = 0; i < stringSize; ++i) {	// copy elements
		str[i] = rhs.str[i];		// (including null terminator)
	}
}

String::~String() { delete[] str; } //deallocates memory

void String::swap(String& rhs) {
	char* temp = str;
	str = rhs.str;
	rhs.str = temp; // trade what each str pointer is pointing to^^

	int sizeTemp = stringSize;
	stringSize = rhs.stringSize;
	rhs.stringSize = sizeTemp; // trade stringSize ^^
}

String& String::operator=(String rhs) {
	swap(rhs); // from class
	return *this;
}

int String::capacity() const { return stringSize - 1; }
// can not be just stringSize or else no room for null terminator

int String::length() const {
	int len = 0;
	while (str[len] != 0) ++len; // while it isnt the end of the char array
	// increment the length
	return len;
}

char& String::operator[](int i) { return str[i]; }

char String::operator[](int i) const { return str[i]; }

String& String::operator+=(const String& rhs) {
	stringSize += rhs.length(); //make room for rhs' elements
	int len = length(); // keep track of length for later use

	char* temp = new char[stringSize]; // temp array to do manipulation
	for (int j = 0; j < len; ++j) { temp[j] = str[j]; } // w/o memory leak
	// make temp a copy of lhs up to lhs' length()
	int i = 0;
	while (rhs.str[i] != 0) { // while rhs hasnt ended...
		temp[len + i] = rhs.str[i]; //add rhs' elements to end of temp
		++i;
	}
	temp[len + i] = 0; // put null terminator on temp

	delete[] str; // delete str since capacity() needs to change
	str = temp; // update str to be the same as temp

	return *this; // return lhs with rhs added on to the end
}

String operator+(String lhs, const String& rhs) { // function
	return lhs += rhs;
}

bool String::operator==(const String& rhs) const {
	int i = 0;
	while (i < length() && i < rhs.length()) { // while neither has ended
		if (str[i] != rhs[i]) return false; // see if they dont match
		++i; // if they do match keep going
	}
	return str[i] == rhs[i]; // see if final element matches
}

bool String::operator<(const String& rhs) const {
	int i = 0;
	while (str[i] != 0) { // while it is not the end of the string
		if (str[i] == rhs[i]) { ++i; continue; }
		if (str[i] != rhs[i]) break; // break if there is a diff char
	}
	return str[i] < rhs[i]; //return the 'bigger' or 'smaller' char
}

String String::substr(int start, int end) const {
	String result;

	if (start < 0) start = 0;
	if (end < start) return result;
	if (start > end) return result;
	if (end >= length()) end = length() - 1;

	int j = 0;
	for (int i = start; i <= end; ++i) { // from "start" to "end"...
		result += String(str[i]); // add str[i] onto the end of result
		++j;
	}
	result.str[j] = 0; // null terminator on result

	return result;
}

int String::findch(int start, char ch) const {
	if (start < 0 || start >= length()) return -1;
	int i = start;
	while (str[i] != 0) { // while we have not reached the end of str
		if (str[i] == ch) return i; // if it is found at i, return i
		++i;
	}

	return -1; // if it is not found return -1
}

int String::findstr(int start, const String& rhsStr) const {
	int position = -1;
	for (int i = start; i <= length(); ++i) { // from "start" to end of str
		if (str[i] == rhsStr[0]) { //if str[i] matches start of rhsStr
			String temp(str); // make new temp string
			temp = temp.substr(i, (i + rhsStr.length() - 1));
			// temp = from str[i] to where rhsStr should end
			if (temp == rhsStr) { position = i; break; }
			// if temp matches rhsStr, it is found
		}
	}

	return position; // return where it is found, -1 if not found
}

std::vector<String> String::split(char ch) const {
	int len = this->length();
	int start = 0;			//starting point of substring
	int end = 0;			//ending point of substring

	std::vector<String> result;		//what will be returned
	while (this->findch(start, ch) != -1) { //ch ch still in str?
		end = this->findch(start, ch);  //end = wherever ch is
		result.push_back(this->substr(start, end - 1));
		//add substr of this, from start to right before ch
		start = end + 1; // start of next substr is where ch is + 1
	}
	result.push_back(this->substr(start, len)); // add last substr

	return result;		// return vector of substrings
}

int String::convertInt() const {

	int result = 0;
	int tens = 1; // instead of 10^n
	for (int i = length() - 1; i >= 0; --i) { // while isnt end of str
		result += (str[i] - '0') * tens; //+= rightmost digit * 10^n
		tens *= 10; // 10^n... 
	}

	return result;
}

std::istream& operator>>(std::istream& in, String& rhs) { // String friend
	char temp[256]; // temporary array to take input
	in >> temp;     // utilize already available syntax
	String result(temp);
	rhs = result; // is now what the input was

	return in;
}

std::ostream& operator<<(std::ostream& out, const String& rhs) { // String fr.
	out << rhs.str;	// utilize already availably syntax for output

	return out;
}

// -------- };

// String operator+ ^^

bool operator==(const char lhs[], const String& rhs) {
	return String(lhs) == rhs;
}

bool operator==(const String& lhs, const char rhs[]) { // variation
	return lhs == String(rhs);
}

bool operator==(char lhs, const String& rhs) {
	return lhs == rhs[0];
}

bool operator==(const String& lhs, char rhs) { // variation
	return lhs[0] == rhs;
}

bool operator<(const char lhs[], const String& rhs) {
	return String(lhs) < rhs;
}

bool operator<(const String& lhs, const char rhs[]) { // variation
	return lhs < String(rhs);
}

bool operator<(char lhs, const String& rhs) {
	return String(lhs) < rhs;
}

bool operator<(const String& lhs, char rhs) { // variation
	return lhs < String(rhs);
}

bool operator<=(const String& lhs, const String& rhs) {
	return (lhs == rhs || lhs < rhs);
}

bool operator!=(const String& lhs, const String& rhs) {
	return !(lhs == rhs);
}

bool operator>=(const String& lhs, const String& rhs) {
	return (lhs == rhs || lhs > rhs);
}

bool operator>(const String& lhs, const String& rhs) {
	return !(lhs < rhs);
}
