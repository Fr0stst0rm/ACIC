#include <iostream>
#include <string.h>
#include <stdio.h>
#include <assert.h>

class String {
private:
	size_t m_length;
	const char* m_c_str;

	void SetNewString(const String& str) {
		SetNewString(str.c_str());
	}

	void SetNewString(const char* str) {
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
		SetNewString(str);
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
			SetNewString(other);
		}

		return *this;
	}
};

int main() {

	String myString("Hello");
	myString.Concatenate("World");
	myString.Concatenate(myString);
	const char* cStr = myString.c_str();
	std::cout << cStr << std::endl;


	String otherString(myString);
	String yetAnotherString("AnotherWorld");
	std::cout << otherString.c_str() << std::endl;
	otherString = yetAnotherString;
	std::cout << otherString.c_str() << std::endl;


	std::cout << "\n\n" << "Press any button to exit...";

	getchar();

	return 0;
}