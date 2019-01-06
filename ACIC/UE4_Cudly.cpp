#include <iostream>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <Windows.h>

class Base {
public:
	virtual void Foo() const{
		std::cout << "Base Foo\n";
	}

	virtual void Bar() const{
		std::cout << "Base Bar\n";
	}
};

class Derived : public Base {
public:
	virtual void Foo() const{
		std::cout << "Derived Foo\n";
	}
	
	virtual void Bar() const{
		std::cout << "Derived Bar\n";
	}
};


int main() {

	std::cout << "Step1:\n";

	Base *b = new Base();
	Derived *d = new Derived();


	//Prints "Base Foo" and "Base Bar" to console
	b->Foo();
	b->Bar();

	//Prints "Derived Foo" and "Derived Bar" to console
	d->Foo();
	d->Bar();

	//the pointer of the base class v table is copied to the the derived class 
	uintptr_t ** temp_b = reinterpret_cast<uintptr_t**>(b);
	uintptr_t ** temp_d = reinterpret_cast<uintptr_t**>(d);

	*temp_d = *temp_b;

	//d calls Base functions and prints "Base Foo" and "Base Bar" to console,
	//because the v-table pointer points to the base functions 
	d->Foo();
	d->Bar();

	Derived *new_d = new Derived();
	//Prints "Derived Foo" and "Derived Bar" again, because a new v-table for the new Derived object is created
	new_d->Foo();
	new_d->Bar();

	std::cout << "Step2:\n";

	Base *b_s2 = new Base();
	Derived *d_s2 = new Derived();


	//Prints "Base Foo" and "Base Bar" to console
	b_s2->Foo();
	b_s2->Bar();

	//Prints "Derived Foo" and "Derived Bar" to console
	d_s2->Foo();
	d_s2->Bar();

	uintptr_t ** temp_b_s2 = reinterpret_cast<uintptr_t**>(b_s2);
	uintptr_t ** temp_d_s2 = reinterpret_cast<uintptr_t**>(d_s2);

	std::cout << "Changing v-table...\n";

	DWORD oldProtection;
	//Set protection to read write
	VirtualProtect(reinterpret_cast<LPVOID>(*temp_d_s2), 8, PAGE_READWRITE, &oldProtection);

	(*temp_d_s2)[0] = (*temp_b_s2)[0];
	
	//set protection back to read only
	VirtualProtect(reinterpret_cast<LPVOID> (*temp_d_s2), 8, PAGE_READONLY, &oldProtection);

	//Prints "Base Foo" and "Derived Bar" to console, because only the first element of the v-table was overwritten
	d_s2->Foo();
	d_s2->Bar();

	Derived *new_d_s2 = new Derived();
	//Prints "Base Foo" and "Derived Bar", because the v-table entry was not protected
	new_d_s2->Foo();
	new_d_s2->Bar();

	std::cout << "\n\n" << "Press any button to exit...";

	getchar();
	delete b;
	delete d;
	delete b_s2;
	delete d_s2;
	delete new_d;
	delete new_d_s2;
	
	return 0;
}