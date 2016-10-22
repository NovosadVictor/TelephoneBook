#include <iostream>
#include <string>

struct Node {
	std::string _Name;
	long long _Number;
	Node() : _Name(""), _Number(-100) {}
	bool operator==(const Node &other) {
		return (_Name == other._Name && _Number == other._Number);
	}
	Node(const std::string &name, long long number) : _Name(name), _Number(number){}
};

class Map {

public:
	Map(int N) : _mass(new Node[N]), _size(0) {}
	int find(const std::string &name);
	void insert(const std::string &name,long long number);
	int size() { return _size;}
	Node &operator[](int i) { if (i < _size) return _mass[i]; }
	long long Number(const std::string &name);
	void Edit(const std::string &name,long long number);
	void Delete(const std::string &name);
	~Map() { delete[]_mass; _size = 0;}
private:
	Node *_mass;
	int _size;
};

int Map::find(const std::string &name) {
	for (int i = 0; i < _size; ++i)
		if (_mass[i]._Name == name)
			return i;
	return -1;
}
void Map::insert(const std::string &name,long long number) {
	if (_size > 0) {
		_mass[_size]._Name = name;
	//	_mass[_size]._Func = func;
		_mass[_size]._Number = number;
	}
	if (_size == 0) {
		_mass[0]._Name = name;
	//	_mass[0]._Func = func;
		_mass[0]._Number = number;
	}
	++_size;
}
void Map::Delete(const std::string &name) {
	_mass[(*this).find(name)]._Number = -100;
	_mass[(*this).find(name)]._Name = "";
	--_size;
}
void Map::Edit(const std::string &name, long long number) {
	_mass[(*this).find(name)]._Number = number;
}
long long Map::Number(const std::string &name) {
	return _mass[(*this).find(name)]._Number;
}                      
int main() {
	int N;
	std::cin >> N;
	Map M(N);
	Map M2(N);
	for (int i = 0; i < N; ++i) {
		std::string func;
		std::cin >> func;
		if (func == "ADD") {
			std::string name;
			std::cin >> name;
			long long numb;
			std::cin >> numb;
			if (M2.find(name) != -1)
				M.insert("ERROR", -1);
			else
				M2.insert(name, numb);
		}
		if (func == "PRINT") {
			std::string name;
			std::cin >> name;
			if (M2.find(name) != -1)
				M.insert(name, M2.Number(name));
			else
				M.insert("ERROR" , -1);
		}
		if (func == "EDITPHONE") {
			std::string name;
			long long numb;
			std::cin >> name;
			std::cin >> numb;
			if (M2.find(name) != -1) 
				M2.Edit(name, numb);
			else
				M.insert("ERROR", -1);
		}
		if (func == "DELETE") {
			std::string name;
			std::cin >> name;
			if (M2.find(name) != -1)
				M2.Delete(name);
			else
				M.insert("ERROR", -1);
		}
	}
	for (int i = 0; i < M.size(); ++i) {
		if (M[i]._Number == -1)
			std::cout << "ERROR" << std::endl;
		else
			std::cout << M[i]._Name << " " << M[i]._Number << std::endl;
	}
	return 0;
}
