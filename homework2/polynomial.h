#include <cmath>
class Polynomial {
  public:
  	Polynomial() {
  	  start_power = 0;
  	  end_power = 0;
  	  members = new int[maxn * 2 + 1];
  	  for(int i = 0;i <= maxn;i++){
	    members[i] = 0;	
	  }
  	  members[0] = 0;
	}
	
	Polynomial(int mn, int mx, int *polynom) {
	  start_power = mn;
	  end_power = maxn;
	  members = new int[maxn * 2 + 1];
	  for(int i = 0;i <= 2 * maxn;i++){
	    members[i] = 0;	
	  }
	  for(int i = 0;i < mx - mn + 1;i++) {
	  	members[i] = polynom[i];
	  }
	}
	int& operator[](int ind) const{
	  if(start_power > ind){
  		int *p = new int[1];
		p[0] = 0;	
		return p[0];
	  }
 	  return members[ind - start_power];
	}
	
	int min(int a,int b)const{
	  if(a < b){
	    return a;
	  }else{
	    return b;
	  }
	}
	
	int max(int a,int b)const{
	  if(a > b){
	    return a;
	  }else{
	    return b;
	  }
	}
	
	friend std::ostream& operator<<(std::ostream& stream, const Polynomial& polynom);
	friend Polynomial operator*(int mn, const Polynomial p);
	Polynomial operator-()const{
	  int* res_members = new int[end_power - start_power + 1];
	  Polynomial w = Polynomial(start_power, end_power, res_members);
	  for(int i = start_power;i <= end_power;i++){
		w[i] = (-1) * ((*this)[i]);
	  }
	  return w;
	}
	
	Polynomial operator+(const Polynomial& sum2)const{
	  int res_start_power = min(start_power, sum2.start_power);
	  int res_end_power = max(end_power, sum2.end_power);
	  int* res_members = new int[res_end_power - res_start_power + 1];
	  Polynomial rs(res_start_power, res_end_power, res_members);
	  for(int i = res_start_power;i <= res_end_power;i++){
	  	rs[i] = (*this)[i] + sum2[i];
	  }
	  return rs;
	}
	
	Polynomial operator-(const Polynomial& sum2)const{
	  return *this + (-sum2);
	}
	
	Polynomial operator*(const Polynomial& sum2)const{
		int res_start_power = start_power + sum2.start_power;
		int res_end_power = end_power + sum2.end_power;
		int *res_members = new int[res_end_power - res_start_power + 1];
		for(int i = 0;i < res_end_power - res_start_power + 1;i++){
		  res_members[i] = 0;
		}
	  	Polynomial rs(res_start_power, res_end_power, res_members);
		for(int i = start_power;i <= end_power;i++){
		  for(int j = sum2.start_power;j <= sum2.end_power;j++){
		  	rs[i + j] += members[i - start_power] * sum2[j];
		  }
		}
		return rs;
	}
	
	Polynomial operator/(const int& del)const {
	  Polynomial div;
	  div = *this;
	  for(int i = start_power;i <= end_power;i++) {
	    div[i] /= del;
	  }
	  return div;
	}
	
	Polynomial operator=(const Polynomial& other){
	  if(this == &other){
	    return *this;
	  }
	  start_power = other.start_power;
	  end_power = other.end_power;
	  delete[] members;
	  members = new int[end_power - start_power + 1];
	  for(int i = 0;i < end_power - start_power + 1;i++){
	  	members[i] = other.members[i];
	  }
	  return *this;
	}
	
	Polynomial operator+=(const Polynomial& other){
	  *this = *this + other;
	  return *this;
	}
	
	Polynomial operator-=(const Polynomial& other){
	  *this = *this - other;
	  return *this;
	}
	
	Polynomial operator*=(const Polynomial& other){
	  *this = *this * other;
	  return *this;
	}
	Polynomial operator*(int mn)const{
	  Polynomial prod;
	  prod = *this;
	  for(int i = start_power;i <= end_power;i++) {
	    prod[i] *= mn;
	  }
	  return prod;
	}
	
	Polynomial operator/=(const int& d){
	  *this = ((*this) / d);
	  return *this;
	}
	
	bool operator==(const Polynomial& other)const{
	  for(int i = min(start_power, other.start_power);i <= max(end_power, other.end_power);i++){
	    if((*this)[i] != other[i]){
	      return false;
		}
	  }
	  return true;
	}
	bool operator!=(const Polynomial& other)const{
	  return !((*this) == other);
	}
	double get(int x)const{
	  double res = 0;
	  for(int i = start_power;i <= end_power;i++){
	    res += (*this)[i] * (pow(x,i));
	  }
	  return res;
	}
  private:
  	const int maxn = 100;
  	int* members,dop;
  	int start_power, end_power;
};
Polynomial operator*(int mn, const Polynomial p){
  Polynomial prod;
  prod = p;
  for(int i = prod.start_power;i <= prod.end_power;i++) {
    prod[i] *= mn;
  }
  return prod;
}
std :: ostream& operator<<(std::ostream& stream, const Polynomial& polynom) {
	bool has_elements = 0;
	for(int i = polynom.end_power;i >= polynom.start_power;i--){
	  if(i == 0){
		if(polynom[i] != 0){
		  has_elements = 1;
		  stream << polynom[i];
		}
		if(i - 1 >= polynom.start_power){
			  if(polynom[i - 1] > 0 && has_elements){
			    stream << "+";
			  }
		}
		continue;
	  }
	  if(polynom[i] != 0){
	  	if(i == 1){
	  		if(polynom[i] == -1){
	  		  stream << "-x";
				has_elements = 1;
			}else{
	  			stream << polynom[i] << "x";
				has_elements = 1;
	  		}
		}else{
	  		if(polynom[i] == -1){
	  		  stream << "-x^" << i;
				has_elements = 1;
			}else{
				if(polynom[i] == 1){
					stream << "x^" << i;
					has_elements = 1;
				}else{
	  				stream << polynom[i] << "x^" << i;
					has_elements = 1;
	  			}
	  		}
	  	}
	  }
	  if(i - 1 >= polynom.start_power && polynom[i - 1] > 0 && has_elements){
		stream << "+";
	  }
	}
	if(!has_elements){
	  stream << "0";
	}
	return stream;
}
