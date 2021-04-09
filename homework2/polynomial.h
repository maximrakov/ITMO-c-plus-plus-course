#include <cmath>
#include <iostream>
//fixed cpp file
//fixed S P A C E S
class Polynomial {
  public:
  	//fixed make copy-constructor
  	Polynomial();
	Polynomial(const Polynomial& other);
	Polynomial(int mn, int mx, int *polynom);
	//fixed remove const
	//fixed make int -> const
	int operator[](int ind) const;
	int& operator[](int ind);
	//fixed it already exists
	
	friend std::ostream& operator<<(std::ostream& stream, const Polynomial& polynom);
	//fixed const Polyminal&
	friend Polynomial operator*(int mn, const Polynomial& p);

	Polynomial operator-()const;
	
	//fixed you need += and then + from +=
	Polynomial operator+(const Polynomial& sum2)const;
	
	//fixed without creating new object
	Polynomial operator-(const Polynomial& sum2)const;
	
	Polynomial operator*(const Polynomial& sum2)const;
	
	Polynomial operator/(const int& del)const;
	
	Polynomial& operator=(const Polynomial& other);
	
	Polynomial& operator+=(const Polynomial& other);
	
	Polynomial& operator-=(const Polynomial& other);
	
	Polynomial& operator*=(const Polynomial& other);

	Polynomial operator*(int mn)const;
	
	Polynomial& operator/=(const int& d);
	
	bool operator==(const Polynomial& other)const;

	bool operator!=(const Polynomial& other)const;

	double get(const int& x)const;

	
	friend Polynomial operator*(int mn, const Polynomial& p);

	friend std::ostream& operator<<(std::ostream& stream, const Polynomial& polynom);

  private:
  	int* members, dop;
  	int start_power, end_power, add = 0;
};
Polynomial operator*(int mn, const Polynomial& p);

std :: ostream& operator<<(std::ostream& stream, const Polynomial& polynom);
