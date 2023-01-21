#include<random>
#include <iostream>
#include<functional>
using namespace std;

class MyString {
	char* string = nullptr;
	char* generate(int len) {
		char* str = new char[len + 1];

		for (int i = 0; i < len; ++i)
			str[i] = 'a' + rand() % ('z' - 'a');
		str[len] = '\0';

		return str;
	}
public:

	MyString(int length) {
		string = generate(length);
	}
	MyString(){
		string = generate(rand()%20 + 1);
	}
	MyString(char* str) {
		int n = strlen(str);
		this->string = new char[n+1];
		for (int i = 0;i < n+1;i++)
			this->string[i] = str[i];
	}
	MyString(MyString& obj) {
		int n = strlen(obj.string);

		string = new char[n+1];
		for (int i = 0;i < n+1;i++)
			this->string[i] = obj.string[i];
	}
	~MyString() {
		delete[] string;
	}

	MyString& operator=(const char* str) {
		if (this->string != nullptr) delete[] this->string;

		int n = strlen(str);
		this->string = new char[n + 1];
		for (int i = 0;i < n + 1;i++)
			this->string[i] = str[i];
		return *this;
	}
	MyString(const char* str) {
		int n = strlen(str);
		if (n > 20) throw exception("передаваемая строка не должна содержать больше 20 символов");
		this->string = new char[n + 1];
		for (int i = 0;i < n + 1;i++)
			this->string[i] = str[i];
	}


	MyString& operator=(MyString& obj) {
		if (this->string != nullptr) delete[] this->string;

		int n = obj.get_length();
		this->string = new char[n+1];
		for (int i = 0;i < n+1;i++)
			this->string[i] = obj.string[i];

		return *this;
	}
	MyString& operator=(char* str) {
		if(this->string!=nullptr) delete[] this->string;

		int n = strlen(str);
		if(n>20) throw exception("передаваемая строка не должна содержать больше 20 символов");

		this->string = new char[n+1];
		for (int i = 0;i < n+1;i++)
			this->string[i] = str[i];
		return *this;
	}
	
	bool operator>(MyString& obj) {
		return strcmp(string, obj.string) > 0;
	}

	bool operator<(MyString& obj) {
		return strcmp(string, obj.string) < 0;
	}

	bool operator>(const char * str) {
		return strcmp(string, str)  > 0;
	}

	bool operator==(MyString& obj){
		return strcmp(this->string, obj.string)==0;
	}
	bool operator==(const char * str) {
		return strcmp(this->string, str) == 0;
	}

	friend ostream& operator<<(ostream& stream, MyString& obj);

	int get_length() {
		int i = 0;
		char* p = string;
		while (*p++ != '\0') i++;
		return i;

		//strlen 
	}
};

ostream& operator<<(ostream& stream, MyString& obj) {
	stream << '[';
	stream << obj.string;
	stream << ']';
	return stream;
}

class MyStringArray {
	MyString* array = nullptr;
	int length;
	
	void sort(function<bool(MyString&, MyString&)> compare) {
		for (int i = length - 1;i >= 0;i--)
			for (int j = 0; j < i; j++)
				if (compare(array[j],array[j + 1])) {
					MyString t = array[j];
					array[j] = array[j + 1];
					array[j + 1] = t;
				}
	}
public:
	MyStringArray(int len) {
		length = len;
		array = new MyString[len];
	}
	~MyStringArray() {
		delete[] array;
	}

	MyString& operator[](int index) {
		return array[index];
	}

	void sort_by_content() {
		sort([](MyString& obj1, MyString& obj2) {
			return obj1 > obj2;
			});
	}
	void sort_by_length() {
		sort([](MyString& obj1, MyString& obj2) {
			return obj1.get_length() > obj2.get_length();
			});
	}

	bool contains(const char * str) {
		int b = length, a = 0;
		int m;
		while (a < b) {
			m = (a + b) / 2;
			if (array[m] == str) return true;
			if (array[m] > str)
				b = m - 1;
			else
				a = m + 1;

		}
		return false;
	}

	bool check_sort() {
		for (int i = 0;i < length - 1;i++)
			if (array[i] > array[i + 1])return false;
		return true;
	}

	friend ostream& operator<<(ostream& stream, MyStringArray& obj);
};

ostream& operator<<(ostream& stream, MyStringArray& obj) {
	int n = obj.length;
	stream << '{' << '\n';
	for (int i = 0;i < n;i++) stream << obj.array[i] << '\n';
	stream << '}';
	return stream;
}

int main()
{
	MyStringArray a(10);
	
	a.sort_by_content();
	cout << "sort_by_content():" << a << endl << endl;
	cout << "check_sort():" << a.check_sort() << endl << endl;
	
	a.sort_by_length();
	cout << "sort_by_length():" << a << endl << endl;

	cout << "contains('aaaa'):" << a.contains("aaaa") << endl << endl;
	cout << "a[0] = 'aaaa'" << endl << endl;
	a[0] = "aaaa";

	a[2] = a[0] = a[1];

	/*MyString& operator=(MyString & obj) {
		if (this->string != nullptr) delete[] this->string;

		int n = obj.get_length();
		this->string = new char[n + 1];
		for (int i = 0;i < n + 1;i++)
			this->string[i] = obj.string[i];

		return *this;
	}*/

	cout << "contains('aaaa'):" << a.contains("aaaa") << endl << endl;
}


