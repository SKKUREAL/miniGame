#include<iostream>
#include<string.h>

class MyString {
	char* string_content;
	int string_length;
	int memory_capacity;
// ����� ���� Ŭ����
// ����� ���ڿ��� �����ϴ� ���� �޸� string_content
// ���ڿ��� ���̸� ��Ÿ���� ���� �ڷ��� string_length
// �Ҵ�� �޸� �뷮�� ��Ÿ���� ���� �ڷ��� memory_capacity

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
// �� Ŭ���� ����ο����� ������, �޼��� ���� �����ϰ� �ִ�.
// public���� �����ؼ� ���� �����ϸ� ���ڿ� ������ �ʿ��� �پ��� �޼������ �����ߴ�.

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
//���ڿ� �޸𸮸� �Ҵ� �����ϴ� ���
// ���ڿ� ��ü = new char[���ڿ��� ũ��]
// delete[] ���ڿ� ��ü

// �����ڴ� �����ε� �Ͽ� �ϳ��� ���ڸ� �Է¹޾��� ��, ���ڿ� ��ü�� �Է¹޾��� ���� ����
// ����� ���� �����ڸ� ������� ������ aggregate Ÿ���� �ȴ�.
// ������ �� ������ ��� �����ѵ�
// ����(��)�� ������ ���� �޸� �Ҵ�, �޸��� ũ��� string_length�̴�
// ���ڸ� ������ ���� �״�� �ְ�, ���ڿ��� ������ ���� for���� ���� ���ڿ��� �ִ´�.

MyString::~MyString() { delete[] string_content; }
// **�߿�!! �����ڿ��� new�� �޸𸮸� �������� �Ҵ��߱� ������ �Ҹ��ڿ����� delete��
// �޸𸮸� ��������� �Ѵ�. �׷��� ���� ������ ***�޸� ����***�� �߻��Ѵ�.

int MyString::length() const { return string_length; }
// ���ڿ��� ���� ��ȯ �Լ�

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
// ���ڿ� ��� �Լ� �̴�. �� �Լ��� �������� ���ڿ��� ����� �� �� �ٲ��� �����ϳ�
// ���� �ʳ��̴�.

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
// assign �Լ��� Mystring ��ü�� �Է¹޾� ���ڿ��� �Ҵ��ϴ� �Լ��̴�.
// str�̶�� MyString �ڷ����� ���۷����� ���ڷ� �޴´�. �̴� ���� ����� ���̱� ����
// ���� ���ڿ��� �Է� ���� ���ڿ��� ���̸� ��, ������ ���̰� �� Ŭ ���
// ���ڿ��� �Ҵ��� �޸𸮸� Ȯ���ϱ� ���� ���� �޸� ���Ҵ��� �ʿ��ϴ�
// �Է� ���� ���ڿ��� ���̸�ŭ �޸𸮸� ���Ҵ��ϰ�, for������ content�� �����Ѵ�.
// �� �� legnth�� capacity�� ����

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
// �� �Լ����� ������: MyString Ŭ������ ��ü�� �Է¹޴� ���� �ƴ�.
// �׷��� string_length ��� strlen�� ����ߴ�.

int MyString::capacity() const { return memory_capacity; }
// �� �Լ��� �޸� �뷮�� �����Ѵ�.

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
// �� �Լ��� �޸𸮸� �̸� �Ҵ��ϴ� �Լ��̴�. ���� �ڷ����� size�� ���ڷ� �޾�
// �� ��ŭ �޸𸮸� �Ҵ��� �� �ִ�. �� �� ������ �޸� �뷮���� Ŭ ���� �Ҵ��Ѵ�.
// prev ������ �����µ� �̰��� string_content�� content�� �״�� �����ϰ� ������
// �޸𸮸� �����ϸ� �� content�� �������� ������ ��� �����ϴ� �뵵�� ���δ�.

char MyString::at(int i) const	{
	if (i >= string_length || i < 0) {
		return 0;
	}
	else {
		return string_content[i];
	}
}
// �� �Լ��� �ε����� �Է��ϸ� �� �ε����� �ش��ϴ� ���ڸ� �����ϴ� �Լ��̴�.

MyString& MyString::insert(int loc, const MyString& str) {
	if (loc < 0 || loc > string_length)
		return *this;
	// �� �Լ��� ���ڿ��� Ư�� ������ ���ڸ� �����ϴ� �Լ��̴�.
	// ���ڴ� ���ڿ��� Ư�� ������ �ε����� ��Ÿ���� ������ loc,
	// ������ ���ڿ� ��ü�� ��Ÿ���� MyString ���۷��� str�̴�.
	// ***MyString&***�� ��ȯ�ϴ� �Լ��� ����
	// ü�̴��� ���� ���� �޼��带 �����Ͽ� ȣ���� �� �ִ�.
	// ü�̴��� ���� ���
	// MyString str("Hello");
	// str.assign("Hello, World");
	// str.insert(5, "beautiful");
	// str.print()

	// ü�̴��� �ִ� ���
	// MyString str("Hello");
	// str.assign("Hello, World").insert(5, "beautiful").print();
	// �̿� ���� �޼��带 ���������� ȣ���� �� �ִ�.
	// �̰��� ������ ����: ��ȯ������ MyString& Ÿ���� ��ü�� *this�� ��ȯ�ϱ� ������
	// ���⼭ this�� ȣ��� ��ü �ڽ��� �ǹ��ϴ� ������ *this�� �� ��ü�� ���۷����� ��ȯ�ϴ� ��
	// ���� ��� str.assign() �޼��带 ȣ���ϸ� ���� ���� ��� �ٽ� str�� ���۷����� ��ȯ�Ѵ�.
	// �̷��� �Ǹ� str.assign().insert() ���� �������� �޼��� ȣ���� ������ ���̴�.
	// �� ������� ������ �ڵ带 �ۼ��� �� �ְ�, ��ü�� �ٽ� ������ �ʿ䰡 ����.
	if (string_length + str.string_length > memory_capacity) {

		if (memory_capacity * 2 > string_length + str.string_length)
			memory_capacity *= 2;
		else
			memory_capacity = string_length + str.string_length;
	// ���� ���� ó���� ���� loc�� ������ string_length�� �ε����� ��� �� ���� ��ü ��ȯ
	// ���� ���ڿ� + ������ ���ڿ��� �޸𸮿� �޸� �뷮�� ��, �޸� �뷮�� �������� Ȯ��
	// ** �� �� ���� ���� �� �޸� �뷮�� �� ������ ���� �����
	// (���� ���ڿ� + ������ ���ڿ�) * 2 ��ŭ�� �޸� �뷮�� ��� �ø���
	// Q �̷��� �޸� �뷮�� ��� �ø��� �޸� ũ�Ⱑ ���� �޼������� �þ�ٵ� ������?
	// �޸� �뷮�� ���ϱ޼������� �þ �� �ִ�.
	//  ���� ���, ������ �ݺ��ɼ��� �޸� �뷮�� 
	// 30 -> 60 -> 120 -> 240 -> 480 -> 960 ... ������ Ŀ����.
	// ������ �̷��� �޸��� �Ҹ𺸴�, �Ҵ� ������ ���� �� �ϴ� ���� �� ��ȿ�����̴�.
	// ���� ������ ����ȭ �ϱ� ���� ������
	// �޸� ����� �߿��ϴٸ� ��� ������ �� ������??
	// 1. �� ��� �ø��� ���, ������ �縸ŭ ������Ű��
	// 2. �ִ� �޸� �뷮 ����
	// else�� ��� �� �躸�� Ŭ ��쿡�� �� �� ���̸� ���� ��ŭ�� �÷��ش�.

		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];
	// string_content�� �����ϱ� ���� �ӽ� ��ü prev_string_content�� ����� �־� ���´�.
	// string_content�� memory_capacity��ŭ �޸𸮸� �Ҵ��Ѵ�.

		int i;
		for (i = 0; i < loc; i++)
			string_content[i] = prev_string_content[i];
	// prev_string_content�� ������ ���ڿ��� �̿��� loc �������� ���ڿ��� �ִ´�

		for (int j = 0; j != str.string_length; j++)
			string_content[i + j] = str.string_content[j];
	// loc ���Ŀ��� ���� ������ ���ڿ��� �ִ´�.

		for (; i < string_length; i++)
			string_content[str.string_length + i] = prev_string_content[i];
	// ���������� ������ ���ڿ� ���Ŀ��� ������ �ڿ� ���ڿ��� �ִ´�
	// ***���� ������ ��� �޽����� ����.
	// Visual Studio���� ��� �޽����� �ߴ� ����
	// �����Ϸ��� �ڵ��� Ư�� ���Ͽ��� ������ ������ �����߱� ����
	// ��� Ʋ�� ���� ������ Ȯ������

		delete[] prev_string_content;
	// prev_string_content�� ���� �ʿ� �����Ƿ� �޸� ������ ������ ���´�.

		string_length = string_length + str.string_length;
		return *this;
	// �ɹ� ������ �����Ѵ�(���� ���� ����!)
	}


	// if (string_length + str.string_length =< memory_capacity)
	// �޸� �뷮�� ����� �����
	for (int i = string_length - 1; i >= loc; i--)
		string_content[i + str.string_length] = string_content[i];
	// ������ ��ġ ������ ���ڸ� �ھ� �о�� ������ �����.

	for (int i = 0; i < str.string_length; i++)
		string_content[i + loc] = str.string_content[i];
	// �� ������ ������ ���ڿ��� �ִ´�

	string_length = string_length + str.string_length;
	// ��� ���� ����
	return *this;
	// ü�̴��� ���� ��ȯ Ÿ�� &MyString
}
MyString& MyString::insert(int loc, const char* str) {
	MyString temp(str);
	return insert(loc, temp);
// ���� MyString�� ���� �Լ��� ����� ���� ������ �� �Լ��� �̿��Ѵ�.
// ���ڰ� const MyString& �̱� ������ MyString ��ü�� �ٲ��� �� �Լ��� ȣ���ϴ� ���
// *�߰� ����: ��� ��ü�� �տ� const �� ���� ��, �������� ���� ��ü
}
MyString& MyString::insert(int loc, char c) {
	MyString temp(c);
	return insert(loc, temp);
}
// ���� ����

MyString& MyString::erase(int loc, int num) {
	if (num < 0 || loc < 0 || loc > string_length)
		return *this;

	for (int i = loc + num; i < string_length; i++) {
		string_content[i - num] = string_content[i];
	}

	string_length -= num;
	return *this;
}
// erase �Լ��� ���ڿ����� Ư�� ���ڵ��� �����ִ� �Լ��̴�.
// ���ڴ� �ε����� �޴� loc, ���� ������ ������ �޴� num

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

	return -1; // -1�� ã�� ���ߴٴ� �ǹ�
}
// find �Լ��� ���ڿ��� Ư�� ���ڸ� ã�� �Լ��̴�.
// ���ڴ� � �ε������� ã�� �� �����ϴ� find_from, ã�� ���ڿ� const MyString& str
// find_from�� ������ ã�� �� �־ �Ʒ��� ���� �ε����� ã�� rfind �Լ��� ����

int MyString::rfind(int find_from, const MyString& str) const {
	int i, j;
	if (str.string_length == 0)
		return -1;

	// �ε����� find_from���� 0���� ���ҽ�Ű�� Ž��
	for (i = find_from; i >= 0; i--) {
		for (j = 0; j < str.string_length; j++) {
			if (i + j >= string_length || string_content[i + j] != str.string_content[j])
				break;
		}

		if (j == str.string_length)
			return i;  // ���ڿ��� ã�� ��� �ε��� ��ȯ
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
	// *this - str ����
	// ������ ����� 1, 0 ,-1�� ����
	// 1=> this�� �� ũ��(�ڿ� �´�.), 0 => ����, -1 => str�� �� ũ��.
	for (int i = 0; i < std::min(string_length, str.string_length); i++) {
		if (string_content[i] > str.string_content[i])
			return 1;

		else if (string_content[i] < str.string_content[i])
			return -1;
	}
	// ���� ������ ������ �� ���ٸ� �� ���ڿ��� �պκ��� ��� ���� ��

	if (string_length == str.string_length)
		return 0;
	//���ڿ��� ���̰� ���ٸ� �� ���ڿ��� �Ȱ��� ��

	else if (string_length > str.string_length)
		return 1;
	// ���ڿ��� �� ���� �� �ڿ� �´�.

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