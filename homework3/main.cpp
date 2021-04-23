#include <iostream>
#include "pugixml.hpp"
#include <typeinfo>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std; 
// #include "pugixml.hpp"
struct stop{
  int number;
  float cord_x,cord_y;
  string veh, obj, name_stp, of_nm, loc, rout;
};
class stops{
	public:
	  float a_to_f(string qq){
	  	int cnt = 0;
	  	bool after = 0;
	  	for(int i = 0;i < qq.size();i++){
          if(qq[i] == '.'){
            after = 1;
            continue;
          }
          if(after){
            cnt++;
          }
	  	}
	  	double mn = pow(10,-cnt);
	  	double res;
	  	for(int i = qq.size() - 1;i >= 0;i--){
	  		if(qq[i] >= '0' && qq[i] <= '9'){
	  			res += mn * (qq[i] - '0');
	  			mn *= 10;
	  		}
	  	}
	  	return res;
	  }
	  pair<float, float> sep_float(string floats){
	  	string fs_double, sc_double;
	  	bool fs = 1;
	  	for(int i = 0;i < floats.size();i++){
	  	  if(floats[i] == ','){
	  	    fs = 0;
	  	    continue;
	  	  }
	  	  if(floats[i] >= '0' && floats[i] <= '9'){
		  	  if(fs){
		  	  	fs_double += floats[i];
		  	  }else{
		  	  	sc_double += floats[i];
		  	  }
	  	  }else{
	  	  	if(fs){
		  	  	fs_double += char(46);
		  	  }else{
		  	  	sc_double += char(46);
		  	  }
	  	  }
	  	}
	  	return make_pair(a_to_f(fs_double.c_str()),  a_to_f(sc_double.c_str()));
	  }

	  stops(string file_name){
	    pugi::xml_parse_result result = doc.load_file("data.xml");
	  	pugi::xml_node tools = doc.child("dataset");
	    for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling()) {
	      stop current;

	      string str_number = tool.child_value("number");
	      current.number = atoi(str_number.c_str());

	      string str_veh = tool.child_value("type_of_vehicle");
	      current.veh = str_veh;

	      string str_obj = tool.child_value("object_type");
	      current.obj = str_obj;

	      string cur_name_stp = tool.child_value("name_stopping");
	      current.name_stp = cur_name_stp;

	      string str_of_nm = tool.child_value("the_official_name");
	      current.of_nm = str_of_nm;

	      string str_loc = tool.child_value("location");
	      current.loc = str_loc;

	      string cur_rout = tool.child_value("routes");
	      current.rout = cur_rout;

	      string str_coords = tool.child_value("coordinates");
	      pair<float, float> flts = sep_float(str_coords);

	      current.cord_x = flts.first;
	      current.cord_y = flts.second;

	      a.push_back(current);
	    }
	  }
	  vector<stop> get_sort(vector<stop>st){
	  	sort(st.begin(), st.end(), [](stop a, stop b) {
        	return (a.cord_x * a.cord_x + a.cord_y * a.cord_y) < (b.cord_x * b.cord_x + b.cord_y * b.cord_y);
    	});
    	return st;
	  }
	  vector<stop> get_transport(string name, vector<stop>z){
	  	vector<stop>rs;
	  	for(int i = 0;i < z.size();i++){
	  	  if(z[i].veh == name){
	  	    rs.push_back(z[i]);
	  	  }
	  	}
	  	return rs;
	  }
	   vector<string> parse_root(string root){
	  	vector<string>result;
	  	string current = "";
	  	for(int i = 0;i < root.size();i++){
	  		if(root[i] == ',' || root[i] == '.' || root[i] == ' '){
	  		  result.push_back(current);
	  		  current = "";
	  		}else{
	  		  current += root[i];
	  		}
	  	}

	  	result.push_back(current);

	  	return result;
	  }
	  vector<stop> parse_roots(){
	  	vector<stop>rss;
	  	for(int i = 0;i < a.size();i++){
	  	  stop curr = a[i];
	  	  vector<string> cur_roots = parse_root(string(curr.rout));
	  	  for(int j = 0;j < cur_roots.size();j++){
	  	    curr.rout = cur_roots[j];
	  	    rss.push_back(curr);
	  	  }
	  	}
	  	return rss;
	  }
	  vector<stop> get(){
	  	return a;
	  }
      void print(vector<stop>qq){
        for(int i = 0;i < qq.size();i++){	
      	  cout << qq[i].number << ' ' << qq[i].cord_x << ' ' << qq[i].cord_y << ' ' << qq[i].veh << ' ' << qq[i].obj << ' ' << qq[i].name_stp << ' ' << qq[i].of_nm << ' ' << qq[i].loc << ' ' << qq[i].rout << endl;
        }
      }
	private:
  	    pugi::xml_document doc;
		vector<stop>a;
};
void max_stops(string name,stops& pp){
  map<string,int>cnt_stops;
  vector<stop>cur_stop = pp.get_transport(name, pp.parse_roots());
  for(int i = 0;i < cur_stop.size();i++){
    cnt_stops[cur_stop[i].rout]++;
  }
  int cnt_max = 0;
  string name_of_max_stop;
  for(map<string,int>::iterator it = cnt_stops.begin();it != cnt_stops.end();it++){
  	if(it->second > cnt_max){
  	  cnt_max = it->second;
  	  name_of_max_stop = it->first;
  	}
  }
  cout << name_of_max_stop << endl;
}
void max_root(string name, stops& pp){
  map<string, vector<pair<float, float> > >cnt_roots;
  vector<stop>cur_stop = pp.get_transport(name, pp.parse_roots());
  map<string,int>length_of_root;
  for(int i = 0;i < cur_stop.size();i++){
    cnt_roots[cur_stop[i].rout].push_back(make_pair(cur_stop[i].cord_x,cur_stop[i].cord_y ));
  }
  for(map<string, vector<pair<float, float> > >::iterator it = cnt_roots.begin();it != cnt_roots.end();it++){
  	string name = it->first;
  	vector<pair<float, float> >cord = it->second;
  	double len = 0;
  	for(int j = 1;j < cord.size();j++){
  		len += sqrt((cord[j].first - cord[j - 1].first) * (cord[j].first - cord[j - 1].first) + (cord[j].second - cord[j - 1].second) * (cord[j].second - cord[j - 1].second));
  	}
  	length_of_root[name] = len;
  }
  double max_lnght = 0;
  string name_of_most;
  for(map<string, int>::iterator it = length_of_root.begin();it !=  length_of_root.end();it++){
  	if(max_lnght < it->second){
  	  max_lnght = it->second;
  	  name_of_most = it->first;
  	}
  }
  cout << name_of_most << endl;
}
void max_street(stops& pp){
  vector<stop>cur_stop = pp.get();
  map<string, int>cnt_street;
  for(int i = 0;i < cur_stop.size();i++){
    if(cur_stop[i].loc != ""){
    	cnt_street[cur_stop[i].loc]++;
    }
  }
  string name_of_street;
  int cnt_stops = 0;
  for(map<string, int>::iterator it = cnt_street.begin();it != cnt_street.end();it++){
    if(cnt_stops < it->second){
      cnt_stops = it->second;
      name_of_street = it->first;
    }
  }
  cout << name_of_street  << endl;
}
int main()
{ 
	setlocale(LC_ALL, "Russian");
    stops p("data.xml");
    max_root("Автобус",p);
    max_stops("Троллейбус", p);
    max_street(p);
}