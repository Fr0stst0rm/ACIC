#include <iostream>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define SET_FIRST_BIT_OF_BYTE(A,B) (A) |= (B) << 7;
#define GET_FIRST_BIT_OF_BYTE(A) (A) & 0x80u

#define GET_LENGTH_OUT_OF_BYTE(A) (A) & 0x75u

class String {
private:

	static const size_t MAX_LEN_OPTIMIZED = sizeof(size_t) + sizeof(char*) - sizeof(uint8_t);

	union {
		struct {
			size_t m_length;
			char* m_c_str;
		} LongString;
		struct {
			uint8_t m_length;
			char m_c_str[MAX_LEN_OPTIMIZED];
		} ShortString;
	} Optimizer;



	void SetNewString(const char* str) {
		
		//std::cout << MAX_LEN_OPTIMIZED << "\n";

		assert("Given string may not be null" && (str != nullptr));

		size_t length = strlen(str);

		if (length < MAX_LEN_OPTIMIZED)
		{
			std::memcpy(Optimizer.ShortString.m_c_str, str, (length + 1u));
			Optimizer.ShortString.m_length = length;
			SET_FIRST_BIT_OF_BYTE(Optimizer.ShortString.m_length, 1u);
		}
		else {
			char * temp = new char[length + 1u];
			std::memcpy(temp, str, (length + 1u));
			Optimizer.LongString.m_c_str = temp;
			Optimizer.LongString.m_length = length;
		}
	}

public:

	explicit String(const char* str) {
		SetNewString(str);
	}

	String(const String& str) {
		SetNewString(str.c_str());
	}

	~String() {
		if (!IsOptimised()) {
			delete[] Optimizer.LongString.m_c_str;
		}
	}

	void Concatenate(const String&  str) {
		Concatenate(str.c_str());
	}


	void Concatenate(const char* str) {
		size_t lengthNewStr = strlen(str);
		size_t lengthCombined = (GetLength() + lengthNewStr);

		if (lengthCombined < MAX_LEN_OPTIMIZED) {
			memcpy(Optimizer.ShortString.m_c_str + GetLength(), str, lengthNewStr + 1u);
			Optimizer.ShortString.m_length = lengthCombined;
			SET_FIRST_BIT_OF_BYTE(Optimizer.ShortString.m_length, 1u);
		}
		else {
			char * temp = new char[lengthCombined + 1u];


			std::memcpy(temp, c_str(), GetLength());

			if (!IsOptimised()) {
				delete[] Optimizer.LongString.m_c_str;
			}

			
			std::memcpy(temp + GetLength(), str, lengthNewStr + 1u);
						
			Optimizer.LongString.m_c_str = temp;
			Optimizer.LongString.m_length = lengthCombined;
		}
	}

	const char* c_str() const {
		if (IsOptimised()) {
			return Optimizer.ShortString.m_c_str;
		}
		else {
			return Optimizer.LongString.m_c_str;
		}
	}

	size_t GetLength() const {
		if (IsOptimised()) {
			return GET_LENGTH_OUT_OF_BYTE(Optimizer.ShortString.m_length);
		}
		else {
			return Optimizer.LongString.m_length;
		}
	}

	String& operator=(const String& other) {

		if (this != &other) {
			if (!IsOptimised()) {
				delete[] Optimizer.LongString.m_c_str;
			}
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

	String& operator+=(const char* rhs) {
		Concatenate(rhs);
		return *this;
	}

	String operator+(const char* rhs) const
	{
		String temp = String(*this);
		temp.operator+=(rhs);
		return temp;
	}

	friend String operator+(const char* lhs, const String& rhs) {
		String temp = String(lhs);
		temp.operator+=(rhs);
		return temp;
	}

	bool IsOptimised() const {
		return GET_FIRST_BIT_OF_BYTE(Optimizer.ShortString.m_length);
	}

};

int main() {

	String myString("Hello");

	/*
	myString.Concatenate("World");
	myString.Concatenate(myString);
	const char* cStr = myString.c_str();
	std::cout << cStr << std::endl;
	7*/

	
	String otherString(myString);

	String yetAnotherString("AnotherLongWorld");
	
	myString = otherString + "Test 1";

	std::cout << myString.c_str() << std::endl;

	myString = yetAnotherString + otherString;

	std::cout << myString.c_str() << std::endl;

	myString = "A very long Test 2" + yetAnotherString;

	std::cout << myString.c_str() << std::endl;

	std::cout << otherString.c_str() << std::endl;
	otherString = yetAnotherString;
	std::cout << otherString.c_str() << std::endl;
	
	std::cout << "\n\n" << "Press any button to exit...";

	getchar();

	return 0;
}