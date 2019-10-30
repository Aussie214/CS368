#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

//Grabs input from users
void task1(vector<int> &v) {
        int capacity;
        int size;
        cout << "enter a value for the vector ";
        int user;
        cin >> user; 
        while (user > -1) {
                capacity = v.capacity();
                size = v.size();
		//Stores element at the endof the vector
		v.push_back(user);
                cout << "enter a value for the vector ";
                cin >> user;
        }  	
}

//Inserts a specified element at a sepcified position
void task2(vector<int> &v, int index, int to_add) {
	if (index < 0) {
		index = 0;
	}
	if (index > v.size()) {
		index = v.size();
	}
	v.insert(v.cbegin() + index, to_add);
}

//Deletes the element at a given index
void task3(vector<int> &v, int del) {
	if (del < 0) {
		del = 0;
	}
	if (del > v.size()) {
		del = v.size() - 1;
	}
	v.erase(v.cbegin() + del);
}

//Sorts vector basedfrom lowest to highest value
vector<int> sort_vector(vector<int> v) {
	sort(v.begin(), v.end());
	return v;
}

//Removes duplicate elements from the vector
vector<int> remove_duplicates(vector<int> v) {
	vector<int>::iterator it;
	it = unique(v.begin(), v.end());
	v.resize(distance(v.begin(), it));
	return v;
}

//Sorts and then removes duplicate elements
void task4(vector<int> v) {
	cout << "sorted vector is" << endl;
        v = sort_vector(v);
        v.shrink_to_fit();
        int d = 0;
        for (auto it = v.cbegin(); it != v.cend(); ++it) {
                cout << "value at pos " << d << ": is " << *it << endl;
                d++;
        }
        cout << endl;
        cout << "Sorted vector after duplicate removal is" << endl;
        v = remove_duplicates(v);
        v.shrink_to_fit();
        int e = 0;
        for (auto it = v.cbegin(); it != v.cend(); ++it) {
                cout << "value at pos " << e << ": is " << *it << endl;
                e++;
        }
        cout << endl;
}

//Drives the program
int main() {
	//task1
	vector<int> v;
	task1(v);
	cout << " The elements of the container are" << endl;
	int t = 0;
	for (auto it = v.cbegin(); it != v.cend(); ++it) {
       		cout << "value at pos " << t << ": is " << *it << endl;
		t++;
	}
	cout << endl;
	//task2
	v.shrink_to_fit();
	cout << "Enter the value of the element you want to enter" << endl;
	int value;
	cin >> value;
	cout << "enter the position" << endl;
	int position;
	cin >> position;
	cout << value << position;
	task2(v, position, value);
	v.shrink_to_fit();
	int b = 0;
	cout << " the vector after insertion of a new value is" << endl;
	for (auto it = v.cbegin(); it != v.cend(); ++it) {
                cout << "value at pos " << b << ": is " << *it << endl;
       		b++;
       	}
	cout << endl;
	//task3
	cout << " Enter the position of the element you want to delelte" << endl;
	int del;
	cin >> del;
	task3(v, del);
	v.shrink_to_fit();
        int c = 0;
        for (auto it = v.cbegin(); it != v.cend(); ++it) {
                cout << "value at pos " << c << ": is " << *it << endl;
                c++;
        }
        cout << endl;
	//task4
	task4(v);
	return 0;
}
