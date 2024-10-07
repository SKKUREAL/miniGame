#include<iostream>
#include<string.h>

class MyString {
	char* string_content;
	int string_length;
	int memory_capacity;
// 사용자 정의 클래스
// 멤버는 문자열을 저장하는 동적 메모리 string_content
// 문자열의 길이를 나타내는 정수 자료형 string_length
// 할당된 메모리 용량을 나타내는 정수 자료형 memory_capacity

public:
	MyString(char c);

	MyString(const char* str);

	MyString(const MyString& str);

	~MyString();

	int length() const;
	int capacity() const;
	void reserve(int size);

	void print() const;
	void println() const;

	MyString& assign(const MyString& str);
	MyString& assign(const char* str);

	char at(int i)	const;

	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);

	MyString& erase(int loc, int num);

	int find(int find_from, const MyString& str) const;
	int find(int find_from, const char* str) const;
	int find(int find_from, char c) const;

	int rfind(int find_from, const MyString& str) const;

	int compare(const MyString& str) const;
};
// 이 클래스 선언부에서는 생성자, 메서드 들을 정의하고 있다.
// public으로 선언해서 접근 가능하며 문자열 관리에 필요한 다양한 메서드들을 정의했다.

MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	memory_capacity = 1;
	string_length = 1;
}
MyString::MyString(const char* str) {
	string_length = strlen(str);
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++) {
		string_content[i] = str[i];
	}
}
//문자열 메모리를 할당 해제하는 방법
// 문자열 객체 = new char[문자열의 크기]
// delete[] 문자열 객체

// 생성자는 오버로딩 하여 하나의 문자를 입력받았을 때, 문자열 전체를 입력받았을 때로 구분
// 사용자 정의 생성자를 만들었기 때문에 aggregate 타입이 된다.
// 원리는 두 생성자 모두 동일한데
// 문자(열)을 저장할 동적 메모리 할당, 메모리의 크기는 string_length이다
// 문자를 저장할 때는 그대로 넣고, 문자열을 저장할 때는 for문을 통해 문자열을 넣는다.

MyString::~MyString() { delete[] string_content; }
// **중요!! 생성자에서 new로 메모리를 동적으로 할당했기 때문에 소멸자에서는 delete로
// 메모리를 해제해줘야 한다. 그렇게 하지 않으면 ***메모리 누수***가 발생한다.

int MyString::length() const { return string_length; }
// 문자열의 길이 반환 함수

void MyString::print() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
}
void MyString::println() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}

	std::cout << std::endl;
}
// 문자열 출력 함수 이다. 두 함수의 차이점은 문자열을 출력한 후 줄 바꿈을 수행하냐
// 하지 않냐이다.

MyString& MyString::assign(const MyString& str) {
	if (str.string_length > memory_capacity) {
		delete[] string_content;

		string_content = new char[str.string_length];
		memory_capacity = str.string_length;
	}
	for (int i = 0; i != str.string_length; i++) {
		string_content[i] = str.string_content[i];
	}

	string_length = str.string_length;

	return *this;
}
// assign 함수는 Mystring 객체를 입력받아 문자열을 할당하는 함수이다.
// str이라는 MyString 자료형의 레퍼런스를 인자로 받는다. 이는 복사 비용을 줄이기 위함
// 기존 문자열과 입력 받은 문자열의 길이를 비교, 후자의 길이가 더 클 경우
// 문자열을 할당할 메모리를 확보하기 위해 동적 메모리 재할당이 필요하다
// 입력 받은 문자열의 길이만큼 메모리를 재할당하고, for문으로 content를 갱신한다.
// 그 후 legnth와 capacity도 갱신

MyString& MyString::assign(const char* str) {
	int str_length = strlen(str);
	if (str_length > memory_capacity) {
		delete[] string_content;

		string_content = new char[str_length];
		memory_capacity = str_length;
	}
	for (int i = 0; i != str_length; i++) {
		string_content[i] = str[i];
	}

	string_length = str_length;

	return *this;
}
// 위 함수와의 차이점: MyString 클래스의 객체를 입력받는 것이 아님.
// 그래서 string_length 대신 strlen을 사용했다.

int MyString::capacity() const { return memory_capacity; }
// 이 함수는 메모리 용량을 리턴한다.

void MyString::reserve(int size) {
	if (size > memory_capacity) {
		char* prev_string_content = string_content;

		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i != string_length; i++)
			string_content[i] = prev_string_content[i];

		delete[] prev_string_content;
	}
}
// 이 함수는 메모리를 미리 할당하는 함수이다. 정수 자료형인 size를 인자로 받아
// 그 만큼 메모리를 할당할 수 있다. 이 때 기존의 메모리 용량보다 클 때만 할당한다.
// prev 개념이 나오는데 이것은 string_content의 content를 그대로 보존하고 싶은데
// 메모리를 해제하면 그 content가 없어지기 때문에 잠시 저장하는 용도로 쓰인다.

char MyString::at(int i) const	{
	if (i >= string_length || i < 0) {
		return 0;
	}
	else {
		return string_content[i];
	}
}
// 이 함수는 인덱스를 입력하면 그 인덱스에 해당하는 문자를 리턴하는 함수이다.

MyString& MyString::insert(int loc, const MyString& str) {
	if (loc < 0 || loc > string_length)
		return *this;
	// 이 함수는 문자열의 특정 구간에 문자를 삽입하는 함수이다.
	// 인자는 문자열의 특정 구간을 인덱스로 나타내는 정수형 loc,
	// 삽입할 문자열 객체를 나타내는 MyString 레퍼런스 str이다.
	// ***MyString&***를 반환하는 함수의 장점
	// 체이닝을 통해 여러 메서드를 연결하여 호출할 수 있다.
	// 체이닝이 없는 경우
	// MyString str("Hello");
	// str.assign("Hello, World");
	// str.insert(5, "beautiful");
	// str.print()

	// 체이닝이 있는 경우
	// MyString str("Hello");
	// str.assign("Hello, World").insert(5, "beautiful").print();
	// 이와 같이 메서드를 연속적으로 호출할 수 있다.
	// 이것이 가능한 이유: 반환값으로 MyString& 타입의 객체인 *this를 반환하기 때문에
	// 여기서 this는 호출된 객체 자신을 의미하는 것으로 *this은 이 객체의 레퍼런스로 반환하는 것
	// 예를 들어 str.assign() 메서드를 호출하면 위와 같은 경우 다시 str의 레퍼런스를 반환한다.
	// 이렇게 되면 str.assign().insert() 같이 연속적인 메서드 호출이 가능한 것이다.
	// 이 방법으로 간결한 코드를 작성할 수 있고, 객체를 다시 지정할 필요가 없다.
	if (string_length + str.string_length > memory_capacity) {

		if (memory_capacity * 2 > string_length + str.string_length)
			memory_capacity *= 2;
		else
			memory_capacity = string_length + str.string_length;
	// 먼저 예외 처리를 위해 loc의 범위가 string_length의 인덱스를 벗어날 시 현재 객체 반환
	// 현재 문자열 + 삽입할 문자열의 메모리와 메모리 용량을 비교, 메모리 용량이 부족한지 확인
	// ** 이 때 다음 삽입 시 메모리 용량이 또 부족할 것을 고려해
	// (현재 문자열 + 삽입할 문자열) * 2 만큼의 메모리 용량을 계속 늘린다
	// Q 이렇게 메모리 용량을 계속 늘리면 메모리 크기가 기하 급수적으로 늘어날텐데 괜찮나?
	// 메모리 용량이 기하급수적으로 늘어날 수 있다.
	//  예를 들어, 삽입이 반복될수록 메모리 용량은 
	// 30 -> 60 -> 120 -> 240 -> 480 -> 960 ... 등으로 커진다.
	// 하지만 이러한 메모리의 소모보다, 할당 해제를 여러 번 하는 것이 더 비효율적이다.
	// 삽입 성능을 최적화 하기 위한 전략임
	// 메모리 사용이 중요하다면 어떻게 개선할 수 있을까??
	// 1. 두 배로 늘리는 대신, 일정한 양만큼 증가시키기
	// 2. 최대 메모리 용량 제한
	// else의 경우 두 배보다 클 경우에는 딱 두 길이를 합한 만큼만 늘려준다.

		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];
	// string_content를 보존하기 위해 임시 객체 prev_string_content를 만들고 넣어 놓는다.
	// string_content에 memory_capacity만큼 메모리를 할당한다.

		int i;
		for (i = 0; i < loc; i++)
			string_content[i] = prev_string_content[i];
	// prev_string_content에 보존한 문자열을 이용해 loc 이전까지 문자열을 넣는다

		for (int j = 0; j != str.string_length; j++)
			string_content[i + j] = str.string_content[j];
	// loc 이후에는 새로 삽입한 문자열을 넣는다.

		for (; i < string_length; i++)
			string_content[str.string_length + i] = prev_string_content[i];
	// 마지막으로 삽입한 문자열 이후에는 나머지 뒤에 문자열을 넣는다
	// ***버퍼 오버런 경고 메시지가 떴다.
	// Visual Studio에서 경고 메시지가 뜨는 이유
	// 컴파일러가 코드의 특정 패턴에서 잠재적 위험을 감지했기 때문
	// 경고가 틀릴 수도 있으니 확인하자

		delete[] prev_string_content;
	// prev_string_content는 이제 필요 없으므로 메모리 해제해 누수를 막는다.

		string_length = string_length + str.string_length;
		return *this;
	// 맴버 변수를 갱신한다(잊지 말고 하자!)
	}


	// if (string_length + str.string_length =< memory_capacity)
	// 메모리 용량이 충분할 경우임
	for (int i = string_length - 1; i >= loc; i--)
		string_content[i + str.string_length] = string_content[i];
	// 삽입할 위치 이후의 문자를 뒤어 밀어내서 공간을 만든다.

	for (int i = 0; i < str.string_length; i++)
		string_content[i + loc] = str.string_content[i];
	// 그 공간에 삽입할 문자열을 넣는다

	string_length = string_length + str.string_length;
	// 멤버 변수 갱신
	return *this;
	// 체이닝을 위해 반환 타입 &MyString
}
MyString& MyString::insert(int loc, const char* str) {
	MyString temp(str);
	return insert(loc, temp);
// 위에 MyString에 대한 함수를 만들어 놨기 때문에 그 함수를 이용한다.
// 인자가 const MyString& 이기 때문에 MyString 객체로 바꿔준 후 함수를 호출하는 방식
// *추가 지식: 상수 객체는 앞에 const 가 붙은 것, 나머지는 비상수 객체
}
MyString& MyString::insert(int loc, char c) {
	MyString temp(c);
	return insert(loc, temp);
}
// 위와 동일

MyString& MyString::erase(int loc, int num) {
	if (num < 0 || loc < 0 || loc > string_length)
		return *this;

	for (int i = loc + num; i < string_length; i++) {
		string_content[i - num] = string_content[i];
	}

	string_length -= num;
	return *this;
}
// erase 함수는 문자열에서 특정 문자들을 지워주는 함수이다.
// 인자는 인덱스를 받는 loc, 지울 문자의 개수를 받는 num

int MyString::find(int find_from, const MyString& str) const {
	int i, j;
	if (str.string_length == 0)
		return -1;
	for (i = find_from; i <= string_length - str.string_length; i++) {
		for (j = 0; j < str.string_length; j++) {
			if (string_content[i + j] != str.string_content[j])
				break;
		}

		if (j == str.string_length)
			return i;
	}

	return -1; // -1은 찾지 못했다는 의미
}
// find 함수는 문자열의 특정 문자를 찾는 함수이다.
// 인자는 어떤 인덱스에서 찾을 지 선택하는 find_from, 찾을 문자열 const MyString& str
// find_from의 우측만 찾을 수 있어서 아래에 좌측 인덱스를 찾는 rfind 함수를 만듦

int MyString::rfind(int find_from, const MyString& str) const {
	int i, j;
	if (str.string_length == 0)
		return -1;

	// 인덱스를 find_from부터 0까지 감소시키며 탐색
	for (i = find_from; i >= 0; i--) {
		for (j = 0; j < str.string_length; j++) {
			if (i + j >= string_length || string_content[i + j] != str.string_content[j])
				break;
		}

		if (j == str.string_length)
			return i;  // 문자열을 찾은 경우 인덱스 반환
	}

	return -1;
}

int MyString::find(int find_from, const char* str) const {
	MyString temp(str);
	return find(find_from, temp);
}
int MyString::find(int find_from, char c) const {
	MyString temp(c);
	return find(find_from, temp);
}
int MyString::compare(const MyString& str) const {
	// *this - str 수행
	// 각각의 결과를 1, 0 ,-1로 리턴
	// 1=> this가 더 크다(뒤에 온다.), 0 => 같다, -1 => str가 더 크다.
	for (int i = 0; i < std::min(string_length, str.string_length); i++) {
		if (string_content[i] > str.string_content[i])
			return 1;

		else if (string_content[i] < str.string_content[i])
			return -1;
	}
	// 위의 절차를 진행한 후 같다면 두 문자열의 앞부분이 모두 같은 것

	if (string_length == str.string_length)
		return 0;
	//문자열의 길이가 같다면 두 문자열은 똑같은 것

	else if (string_length > str.string_length)
		return 1;
	// 문자열이 긴 것이 더 뒤에 온다.

	return -1;
}

int main() {
	MyString str1("this is a very very long string");
	std::cout << "Location of first <very> in the string : " << str1.find(0, "very") << std::endl;
	std::cout << "Location of second <very> in the string : " << str1.find(str1.find(0, "very") + 1, "very") << std::endl;


	MyString str2("abcdef");
	MyString str3("abcde");

	std::cout << "str2 and str3 compare : " << str2.compare(str3) << std::endl;
}