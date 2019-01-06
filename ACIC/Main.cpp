#include <iostream>
#include <string.h>
#include <stdio.h>
#include <assert.h>

class GenericDelegate {
public:

	template<typename O, typename T > void Bind(T(*func) (int, float), const O * obj) {
		m_funtionP = reinterpret_cast<void(*) (int, float)>(func);
	}

	template<typename T> void Bind(T(*func) (int, float)) {
		m_funtionP = reinterpret_cast<void(*) (int, float)>(func);
	}

	template<typename T = void> T Invoke(int i, float f) const {
		return reinterpret_cast<T(*) (int, float)>(m_funtionP)(i, f);
	}

private:
	void(*m_funtionP) (int, float);
};


void print(int i, float f) {
	std::cout << "Int: " << i << " Float: " << f << "\n";
}

class Test {
public:
	void Do(int i, float f) {
		print(i, f);
	}
	void ConstDo(int i, float f) const {
		print(i, f);
	}
};


void Callback(const GenericDelegate& delegate) {
	delegate.Invoke(0, 0.0f);
}

float add(int i, float f) {
	return static_cast<float>(i) + f;
}

int main() {

	GenericDelegate d;
	d.Bind(&print);
	d.Invoke(10, 1.0f);
	Callback(d);

	{
		Test t;
		d.Bind<Test,void>(&print, &t);
		//d.Bind<Test>(&Test::Do, &t);
		d.Invoke(20, 2.0f);
		d.Bind<Test,void>(&Test::ConstDo, &t);
		d.Invoke(30, 3.0f);
	}
	{
		//const OtherClass t;
		//d.Bind(&OtherClass::ConstDo, &t);
		//d.Invoke(50, 5.0f);
	}


	std::cout << "\n\n" << "Press any button to exit...";

	getchar();

	return 0;
}