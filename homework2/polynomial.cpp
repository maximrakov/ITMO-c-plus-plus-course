#include <cmath>
#include <iostream>
#include "polynomial.h"
//fixed cpp file
//fixed S P A C E S
//fixed make copy-constructor
Polynomial::Polynomial() {
  start_power = 0;
  end_power = 0;
  members = new int[end_power - start_power + 1];

  for(int i = 0; i <= end_power - start_power + 1; i++){
    members[i] = 0;	
  }
}
Polynomial::Polynomial(const Polynomial& other) {
  start_power = other.start_power;
  end_power = other.end_power;
  members = new int[end_power - start_power + 1];

  for(int i = 0; i < end_power - start_power + 1; i++) {
  	members[i] = other.members[i];
  }
}
Polynomial::Polynomial(int mn, int mx, int *polynom) {
  start_power = mn;
  end_power = mx;
  members = new int[end_power - start_power + 1];

  for(int i = 0; i < end_power - start_power + 1; i++) {
  	members[i] = polynom[i];
  }
}
//fixed remove const
//fixed make int -> const
const int& Polynomial::operator[](int ind) const {
  if(start_power > ind || end_power < ind) {
    return add;
  }else {
    return members[ind - start_power];
  }
}

int& Polynomial::operator[](int ind) {
  if(start_power > ind || end_power < ind){
  	int new_start_power = start_power, new_end_power = end_power;
  	if(start_power > ind) {
  	  new_start_power = ind;
  	}
  	if(end_power < ind) {
  	  new_end_power = ind;
  	}
  	
  	int* new_members = new int[new_end_power - new_start_power + 1];
  	for(int i = 0; i < new_end_power - new_start_power + 1; i++) {
  	  new_members[i] = 0;
  	}
  	for(int i = 0; i < end_power - start_power + 1; i++) {
  	  new_members[i + (start_power - new_start_power)] = members[i]; 
  	}
  	
  	delete[] members;
  	members = new int[new_end_power - new_start_power + 1];
  	for(int i = 0; i < new_end_power - new_start_power + 1; i++) {
  	  members[i] = new_members[i];
  	}
  	start_power = new_start_power;
  	end_power = new_end_power; 
  }
  return members[ind - start_power];
}
//fixed it already exists

//fixed const Polyminal&

Polynomial Polynomial::operator-()const {
  Polynomial negative = (*this);
  for(int i = negative.start_power; i <= negative.end_power; i++) {
    negative[i] *= -1;
  }
  return negative;
}

//fixed you need += and then + from +=
Polynomial Polynomial::operator+(const Polynomial& sum2)const {
  Polynomial sm = *this;
  sm += sum2;
  return sm;
}

//fixed without creating new object
Polynomial Polynomial::operator-(const Polynomial& sum2)const {
  Polynomial diff = *this;
  diff -= sum2;
  return diff;
}

Polynomial Polynomial::operator*(const Polynomial& sum2)const {
  Polynomial rs = *this;
  rs *= sum2;
  return rs;
}

Polynomial Polynomial::operator/(const int& del)const {
  Polynomial div = *this;
  div /= del;
  return div;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
  if(this == &other) {
    return *this;
  }
  start_power = other.start_power;
  end_power = other.end_power;
  delete[] members;
  members = new int[end_power - start_power + 1];
  for(int i = 0;i < end_power - start_power + 1;i++) {
  	members[i] = other.members[i];
  }
  return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
  for(int i = other.start_power; i <= other.end_power;i++){
  	(*this)[i] += other[i];
  }
  return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
  for(int i = other.start_power; i <= other.end_power;i++) {
  	(*this)[i] -= other[i];
  }
  return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
  Polynomial cur = (*this);
  for(int i = start_power;i <= end_power;i++) {
  	cur[i] = 0;
  }
  for(int i = start_power;i <= end_power;i++) {
  	for(int j = other.start_power;j <= other.end_power;j++) {
  	  cur[i + j] += (*this)[i] * other[j];
  	}
  }
  *this = cur;
  return *this;
}

Polynomial Polynomial::operator*(int mn)const {
  Polynomial prod = *this;
  for(int i = start_power;i <= end_power;i++) {
    prod[i] *= mn;
  }
  return prod;
}

Polynomial& Polynomial::operator/=(const int& d) {
  for(int i = start_power;i <= end_power;i++) {
  	(*this)[i] /= d;
  }
  return *this;
}

bool Polynomial::operator==(const Polynomial& other)const {
  int it_st = start_power;
  if(it_st > other.start_power){
    it_st = other.start_power;
  }
  int it_end = end_power;
  if(other.end_power > it_end){
    it_end = other.end_power;
  }
  for(int i = it_st; i <= it_end; i++) {
    if((*this)[i] != other[i]){
      return false;
	}
  }
  return true;
}

bool Polynomial::operator!=(const Polynomial& other)const {
  return !((*this) == other);
}

double Polynomial::get(const int& x)const {
  double res = 0;
  double cur_pw = pow(x, start_power);
  for(int i = start_power;i <= end_power;i++){
    res += (*this)[i] * cur_pw;
    cur_pw *= x;
  }
  return res;
}

Polynomial operator*(int mn, const Polynomial& p) {
 	Polynomial prod;
  	prod = p;
  	for(int i = prod.start_power; i <= prod.end_power; i++) {
      prod[i] *= mn;
  	}
  	return prod;
}
std :: ostream& operator<<(std::ostream& stream, const Polynomial& polynom) {
	bool has_elements = 0;

	for(int i = polynom.end_power; i >= polynom.start_power; i--) {
	  if(i == 0) {
		if(polynom[i] != 0) {
		  	has_elements = 1;
		  	stream << polynom[i];
		}
		if(i - 1 >= polynom.start_power) {
		  	if(polynom[i - 1] > 0 && has_elements) {
		      stream << "+";
		 	}
		}
		continue;
	  }
	  if(polynom[i] != 0) {
	  	if(i == 1) {
	  		if(polynom[i] == -1){
	  		  	stream << "-x";
			  	has_elements = 1;
			}else {
	  		  	stream << polynom[i] << "x";
				has_elements = 1;
	  		}
		}else {
	  		if(polynom[i] == -1) {
	  		  	stream << "-x^" << i;
				has_elements = 1;
			}else {
				if(polynom[i] == 1) {
					stream << "x^" << i;
					has_elements = 1;
				}else {
	  				stream << polynom[i] << "x^" << i;
					has_elements = 1;
	  			}
	  		}
	  	}
	  }
	  if(i - 1 >= polynom.start_power && polynom[i - 1] > 0 && has_elements) {
	      stream << "+";
	  }
	}
	if(!has_elements) {
		stream << "0";
	}
	return stream;
}
