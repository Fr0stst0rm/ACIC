#include <iostream>
#include <string.h>
#include <stdio.h>
#include <assert.h>

class String {
private:
	size_t m_length;
	const char* m_c_str;
	
	void SetNewString(const char* str) {

		assert("Given string may not be null" && (str != nullptr));

		m_length = strlen(str);
		char * temp = new char[m_length + 1u];
		std::memcpy(temp, str, (m_length + 1u));
		m_c_str = temp;
	}

public:

	explicit String(const char* str) {
		SetNewString(str);
	}

	String(const String& str) {
		SetNewString(str.c_str());
	}

	~String() {
		delete[] m_c_str;
	}

	void Concatenate(const String&  str) {
		Concatenate(str.c_str());
	}


	void Concatenate(const char* str) {
		size_t lengthNewStr = strlen(str);
		char * temp = new char[(GetLength() + lengthNewStr) + 1u];

		std::memcpy(temp, m_c_str, m_length);
		std::memcpy(temp + m_length, str, lengthNewStr + 1u);

		delete[] m_c_str;
		m_c_str = temp;
		m_length = lengthNewStr;
	}

	const char* c_str() const {
		return m_c_str;
	}

	size_t GetLength() const {
		return m_length;
	}

	String& operator=(const String& other) {

		if (this != &other) {
			delete[] m_c_str;
			SetNewString(other.c_str());
		}

		return *this;
	}

	String& operator+=(const String& rhs) {
		Concatenate(rhs);
		return *this;
	}

	String operator+(const String& rhs) const
	{
		String temp = String(*this);
		temp.operator+=(rhs);
		return temp;
	}

	String& operator+=(const char* rhs){
		Concatenate(rhs);
		return *this;
	}
	
	String operator+(const char* rhs) const
	{
		String temp = String(*this);
		temp.operator+=(rhs);
		return temp;
	}

	friend String operator+(const char* lhs, const String& rhs){
		String temp = String(lhs);
		temp.operator+=(rhs);
		return temp;
	}

};

int main() {
	
	String myString("Hello");
	
	/*
	myString.Concatenate("World");
	myString.Concatenate(myString);
	const char* cStr = myString.c_str();
	std::cout << cStr << std::endl;
*/

	String otherString(myString);
	String yetAnotherString("AnotherWorld");

	myString = yetAnotherString + otherString;

	std::cout << myString.c_str() << std::endl;

	myString = yetAnotherString + "Test 1";

	std::cout << myString.c_str() << std::endl;

	myString = "Test 2" + yetAnotherString;

	std::cout << myString.c_str() << std::endl;

	/*
	std::cout << otherString.c_str() << std::endl;
	otherString = yetAnotherString;
	std::cout << otherString.c_str() << std::endl;
	*/

	std::cout << "\n\n" << "Press any button to exit...";

	getchar();

	return 0;
}