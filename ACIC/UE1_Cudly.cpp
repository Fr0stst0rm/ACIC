#include <iostream>
#include <string.h>
#include <stdio.h>

class String {
private:
	const char* m_c_str;

public:
	
	String(const char* str) {
		char * temp = new char[strlen(str) + 1];
		strcpy(temp, str);
		m_c_str = temp;
	}

	~String() {
		delete[] m_c_str;
	}

	void Concatenate(String&  str) {
		Concatenate(str.c_str());
	}


	void Concatenate(const char* str) {
		int size = GetLength() + strlen(str) + 1;
		char * temp = new char[size];
		strcpy(temp, m_c_str);
		strcat(temp, str);
		
		delete[] m_c_str;
		m_c_str = temp;
	}
		
	const char* c_str() {
		return m_c_str;
	}

	size_t GetLength() {
		return strlen(m_c_str);
	}

};

int main() {
	
	String myString("Hello");
	myString.Concatenate("World");
	myString.Concatenate(myString);
	const char* cStr = myString.c_str();
	std::cout << cStr;
	
	std::cout << "\n\n" << "Press any button to exit...";

	getchar();

	return 0;
}