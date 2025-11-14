// Advanced Algorithms Coursework
// Question 4

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bool areAnagrams(string x, string y) {
	if (x.length() != y.length()) {
		return false;
	}
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	return x == y;
}

int main() {
	string word1, word2;
	cout << "Enter two strings to check for anagrams: ";
	cin >> word1 >> word2;
	if (areAnagrams(word1, word2)) {
		cout << "The two words are anagrams." << endl;
	} 
	else {
		cout << "The two words are not anagrams." << endl;
	}
}