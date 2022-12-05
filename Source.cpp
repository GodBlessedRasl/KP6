#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <math.h>
#include <exception>
#include <string>

using namespace std; 

int binPow(int a, int b) {
	if (b == 0) {
		return 1;
	}
	int ans = binPow(a, b / 2);
	ans *= ans;
	if (b % 2 == 1) {
		ans *= b;
	}
	return ans;
}

template<typename TKey, typename TValue>
class HashTable {
private:
	int size_;
	int capacity_ = 13;
	std::vector<std::list<std::pair<TKey, TValue>>>table;
public:
	HashTable();
	HashTable(int settedCapacity);
	~HashTable();
	void Insert(const TKey& key_val, const TValue& el_value);
	const TValue Search(const TKey& key);
	void Output() const;
	void Delete(const TKey& key);
	size_t hash_function(const int& key) {
		return (int)key % capacity_;
	}
	size_t hash_function(const float& key) {
		return (int)key % capacity_;
	}
	size_t hash_function(const double& key) {
		return (int)key % capacity_;
	}
	size_t hash_function(const string& key) {
		size_t ind = 0;
		int prime = 7;
		for (size_t i = 0; i < key.size(); i++) {
			ind = (ind + static_cast<size_t>(key[i]) * binPow(prime, i)) % capacity_;
		}
		return ind;
	}
	const TValue operator[](const TKey& key);
};

template<typename TKey, typename TValue>
HashTable<TKey, TValue > ::HashTable() {
	size_ = 0;
	capacity_ = 13;
	table.assign(capacity_, std::list<std::pair<TKey, TValue>>());
}

template<typename TKey, typename TValue>
HashTable<TKey, TValue > ::HashTable(int settedCapacity) {
	size_ = 0;
	capacity_ = settedCapacity;
	table.assign(capacity_, std::list<std::pair<TKey, TValue>>());
}

template < typename TKey, typename TValue>
HashTable<TKey, TValue>::~HashTable() {
	size_ = 0;
	capacity_ = 0;
	table.clear();
}

template<typename TKey, typename TValue>
void HashTable<TKey, TValue > ::Insert(const TKey& key_val, const TValue& el_value) {
	size_t index = hash_function(key_val);
	std::pair<TKey, TValue> elem(key_val, el_value);
	std::list<std::pair<TKey, TValue>> &cell = table[index];
	if (!cell.empty()) {
		for (auto it = cell.begin(); it != cell.end();it++) {
			if (it->first == key_val) {
				it->second  = el_value;
				return;
			}
		}
	}
	cell.push_front(elem);
	++size_;
}

template < typename TKey, typename TValue>
const TValue HashTable<TKey, TValue > ::Search(const TKey& key){
	size_t index = hash_function(key);
	std::list<std::pair<TKey, TValue>>& cell = this->table[index];
	try {
		if (cell.size() == 0) {
			std::exception error("List is empty!");
			throw error;
		}
		for (auto it = cell.begin(); it != cell.end(); it++) {
			if (it->first == key) {
				return it->second;
			}
		}
	}
	catch (std::exception& err) {
		std::cout << err.what() << "\n";
	}
}

template < typename TKey, typename TValue>
void HashTable<TKey, TValue > ::Delete(const TKey& key) {
	size_t index = hash_function(key);
	std::list<std::pair<TKey, TValue>>& cell = this->table[index];
	try {
		if (cell.size() == 0) {
			std::exception error("List is empty!");
			throw error;
		}
		for (auto it = cell.begin(); it != cell.end(); it++) {
			if (it->first == key) {
				this->table[index].erase(it);
				return;
			}
		}
	}
	catch (std::exception& err) {
		std::cout << err.what() << "\n";
	}
}

template < typename TKey, typename TValue>
void HashTable< TKey, TValue>::Output() const {
	for (size_t i = 0; i < capacity_;i++) {
		if (table[i].size()) {
			std::cout << "Values of the Table[" << i << "] :";
			for (auto it = table[i].begin(); it != table[i].end(); it++) {
				std::cout << (it->second) << " ";
			}
			std::cout << "\n";
		}
	}
}

template < typename TKey, typename TValue>
const TValue HashTable< TKey, TValue>::operator[](const TKey& key) {
	size_t index = hash_function(key);
	std::list<std::pair<TKey, TValue>>& cell = table[index];
	try {
		if (cell.size() == 0) {
			std::exception error("List is empty!");
			throw error;
		}
		for (auto it = cell.begin(); it != cell.end(); it++) {
			if (it->first == key) {
				return it->second;
			}
		}
	}
	catch (std::exception& err) {
		std::cout << err.what() << "\n";
	}
	Insert(key, TValue());
	return operator[](key);
}


int main() {
	HashTable< int, string> table1;
	table1.Insert(2, "abab");
	table1.Output();

	
	HashTable< string, int> table2(7);
	table2.Insert("abab", 2);
	std::cout << table2["abab"] << "\n";
	table2.Insert("baba", 3);
	table2.Output();
	table2.Delete("abab");
	table2.Output();

	HashTable <string, string> names;
	names.Insert("Petrov", "Ivan");
	names.Output();
	std::cout << names.Search("Petrov") << "\n";
	names.Delete("Petrov");
	names.Output();

}