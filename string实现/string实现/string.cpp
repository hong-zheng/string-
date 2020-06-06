#define _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <iostream>
using namespace std;
class String{
public:
	// ���ֹ��캯�����ڽ����ÿ�ָ���쳣
	//String()
	//:_str(nullptr)
	//,_size(0)
	//, _capacity(0)
	//{
	//}
	String()
	:_str(new char[16])
	,_size(0)
	,_capacity(0)
	{
		_str[_size] = '\0';//_size��ʾ��Ч�ַ��ĸ��������λ���зŵ���'\0'
		_capacity = 15;
	}
	// ȫȱʡ����2
	//String(char* str)
	//	:_str(str)
	//	, _size(strlen(str))
	//	, _capacity(strlen(str))
	//{
	//}
	// �Ķ�2
	String(const char* str){
		_size = strlen(str);
		_str = new char[_size + 1]; //���ݴ�С����ռ䣬�Լ����Ƶ���һ�ݣ���������
		strcpy(_str, str);
		_capacity = _size;
	}
	// ����汾1
	// ��������֮�����Դ����ͬ���ͷŲ���������⣬�����ж�������Դ
	//String(const String& str)
	//	:_str(new char[str._capacity+1])
	//	, _size(str._size)
	//	, _capacity(str._capacity)
	//{
	//	// ��Դ����,�˴���������
	//	strcpy(_str, str._str);
	//	cout << "String(const String& str)" << endl;
	//}
	// ����汾2
	// �������죺�ִ�д����Ҳ����������븴��
	String(const String& str)
		// ����ʼֵ��������ʱ�������������ʱ��������
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(str._str);
		Swap(tmp);
	}
	// ���������������ִ�д��,���븴��
	// �������죬��ֵ��ʱ����п������죬������ǰ��һ���ֲ�����
	// �����ֲ����󣬵��þֲ�����������������ͷ���Դ
	//String& operator=(String str){
	//	Swap(str);
	//	return *this;
	//}
	// ���õ�ʱ��ע��ֻ�����ɸ�
	String& operator=(const String& str){
		String tmp(str);
		Swap(tmp);
		return *this;
	}
	//// ����Ľ�����Ч�ʵͣ���������Ҳд
	//void SWAP(String& str){
	//	//��������
	//	String tmp = str;
	//	// ��ֵ�����
	//	str = *this;
	//	// ��ֵ�����
	//	*this = tmp;
	//}

	// �����ֶ�����������������������ݣ�ʵ�������
	void Swap(String& str){
		// �����������ḳֵ
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}
	//String& operator=(const String& str){
	//	if (this != &str) // �������ҽ��и�ֵ
	//	{
	//		// ���ռ�
	//		char* tmp = new char[str._capacity + 1];
	//		// ���ݿ���
	//		strcpy(tmp, str._str);
	//		// �ͷ�ԭ�пռ�
	//		delete[] _str;

	//		// ǳ������ͨ��������Դ�Ŀ�����Ϊ�������ֵ�����
	//		_str = tmp;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}
	// �˴��������ڹ���2���ͷŴ����������ݣ�deleteֻ���ͷŶ��е�����
	~String()
	{
		if (_str){
			delete[] _str;
			_size = _capacity = 0;
			_str = nullptr;
		}
		cout << "~String()" << endl;
	}
	const char* c_str(){
		return _str;
	}
	// ����һ���ַ�
	void pushBack(const char& ch){
		// �������
		if (_size == _capacity){
			size_t newC = _capacity == 0 ? 15 : 2*_capacity;
			reserve(newC);
		}
		// β��
		_str[_size] = ch;
		// ����size
		++_size;
		// ��һ��'\0'
		_str[_size] = '\0';
	}
	void reserve(size_t n){
		if (n > _capacity){
			// ���ռ�+1-->���'\0'
			char* tmp = new char[n + 1];
			// ����
			strcpy(tmp, _str);
			// �ͷ�ԭ�пռ�
			delete[] _str;
			_str = tmp;
			// ��������
			_capacity = n;
		}
	}
	// ����,ʵ�ֵ�����
	// ʹ�÷�ʽ������ָ��
	// ��������һ�ַ�������Ԫ�صĻ��ƣ����ַ�װ�����ԣ�����Ҫ��ע������ʵ��ϸ�ڣ��Ϳ���ֱ�ӷ��ʣ��ɶ���д��Ԫ��
	// ʹ�÷�ʽ��������ָ��Ĳ���
	// 1�������� --> ��ȡָ��λ�õ�����
	// 2��λ���ƶ� --> ָ������λ��

	// string : ��������ͨ��ָ��ʵ��
	typedef char* iterator;
	typedef const char* const_iterator;
	iterator begin(){
		// ��һ��Ԫ�ص�λ��
		return _str;
	}
	iterator end(){
		// ���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}
	// ֻ��������
	const_iterator begin() const{
		//��һ��Ԫ�ص�λ��
		return _str;
	}
	const_iterator end() const{
		//���һ��Ԫ�صĺ�һ��λ��
		return _str + _size;
	}
	char& operator[](size_t pos){
		if (pos < _size){
			return _str[pos];
		}
	}
	const char& operator[](size_t pos) const{
		if (pos < _size){
			return _str[pos];
		}
	}
	size_t size() const{
		return _size;
	}
	// β��һ���ַ���
	void Append(const char* str){
		int len = strlen(str);
		// �������
		if (_size+len > _capacity){
			// ����Ҫ��֤�����ַ�������
			reserve(_size + len);
		}
		// β��
		strcpy(_str + _size, str);
		// �޸�size
		_size += len;
	}
	String& operator+=(const char& ch){
		pushBack(ch);
		return *this;
	}
	String& operator+=(const char* str){
		Append(str);
		return *this;
	}
	void insert(size_t pos, const char& ch){
		if (pos > _size) return; // ��ʱ������
		// �������
		if (_size == _capacity){
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		// �ƶ�Ԫ���Ӻ���ǰ�ƶ�[pos,_size]�������ƶ����Ҷ��ַ�����ֹ����
		size_t end = _size;
		//while (end >= pos){ // �˴���BUG��size_t����>=0,��posΪ0ʱ�Ͳ�����ѭ��
		//	_str[end + 1] = _str[end];
		//	--end;
		//}
		while (end > pos){
			_str[end] = _str[end - 1];
			--end;
		}
		//����
		_str[pos] = ch;

		++_size;
	}
	void insert(size_t pos, const char* str){
		if (pos > _size) return;
		int len = strlen(str);
		if (_size + len > _capacity){
			reserve(_size + len);
		}
		// �ƶ�Ԫ�� (pos,_size)
		// size --> size+len , pos -->pos+len
		size_t end = _size + len;
		while (end > pos+len-1){
			_str[end] = _str[end - len];
			--end;
		}
		// ����
		// strcpy �´��'\0'����˲�����
		for (int i = 0; i < len; i++){
			_str[i + pos] = str[i];
		}
		_size += len;
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};
void printString(const String& s){ // cosnt����ֻ�ܵ���const�ӿ�
	// ����������
	String::const_iterator it = s.begin();
	cout << "iterator:>";
	while (it != s.end()){
		cout << *it << " ";
		//*it = '0'; // const�ӿھͲ�֧��д����
		++it;
	}
	cout << endl;
}
void test5(){
	String s;
	s += "1234";
	s.insert(1, 'a');
	printString(s);
	s.insert(4, "#######");
	printString(s);
}
void test4(){
	String s;
	s.Append("12345");
	printString(s);
	s.Append("abcdefghij");
	printString(s);
}
void test3(){
	String s = "";
	s.pushBack('1');
	s.pushBack('2');
	s.pushBack('a');
	s.pushBack('s');
	s.pushBack('D');
	s.pushBack('d');
	s.pushBack('f');
	cout << s.c_str() << endl;
	cout << "[]";
	for (int i = 0; i < s.size(); i++){
		cout << s[i] << " ";
		s[i] = '2';
	}
	cout << endl;
	printString(s);
// ֻҪʵ���˵������Ϳ���ʹ�÷�Χfor
	// Ҫ�޸ı���ʹ�����ò����޸ģ������Ǿֲ������޷��޸�
	// ֵ���գ�ֻ���޸���ʱ�ֲ�����
	cout << "��Χfor:>";
	for (const char& ch : s){
		cout << ch << " ";
	}
	cout << endl;
	for (char ch : s){
		ch = 'a';// s �����ݲ����޸ģ���ʱ��������Ҫ���òſ��Ըı�
	}
	//// ����������
	//String::iterator it = s.begin();
	//while (it != s.end()){
	//	cout << *it << " ";
	//	*it = '0';
	//	++it;
	//}
}
void test2(){
	String s("123");
	String str("12");
	s = str;
	// �������д������������ͷŵ�����
	//String s("123");
	//// ���ÿ�������,�˴�Ϊǳ��������Դ����������������ָ��ͬһ��λ�ã��ͷŵ�ʱ��
	// ��copy2->copy->s �� ����ͷ�ͬһ���ռ䣬��ɴ���
	// �˴��Ŀ�����Ҫ�������д������Դ���п���
	//String copy = s;
	//String copy2(s);
}
void test(){
	string s;
	const char* ptr = s.c_str(); // ����ȡ���ַ����ĵ�ַ
	if ( ptr ) cout << "ptr is't nullptr" << endl;
	printf("%p\n", ptr);
	cout << ptr << endl;
	cout << s.c_str() << endl;
	//String str; // ���ܻ���ڽ������쳣��Ϊ��
	//cout << str.c_str() << endl;
}
void main(){
	test5();
	//test4();
	//test3();
	//printf("%p\n", nullptr);
	//test2();
	//test();
	cout <<"end of process" <<endl;
	while (1);
}
/*
class String{
public:

	// ��������һ�ַ�������Ԫ�صĻ��ƣ����ַ�װ�����ԣ�����Ҫ��ע������ʵ��ϸ�ڣ��Ϳ���ֱ�ӷ��ʣ��ɶ���д��Ԫ��
	// ���ͷ���Ԫ�صĳɱ�
	// ʹ�÷�ʽ��������ָ��
	// 1��֧�ֽ����� --> ��ȡָ��λ�õ�����
	// 2��λ���ƶ� --> ָ������λ��
	//string ��������ͨ��ָ��ʵ��
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin(){
		// ��һ��Ԫ�ص�λ��
		return _str;
	}
	iterator end(){
		// ���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	const_iterator cbegin() const{
		// ��һ��Ԫ�ص�λ��
		return _str;
	}
	const_iterator cend() const{
		// ���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(0)
	{
		_str[_size] = '\0';
		_capacity = 15;
	}

	String(char* str){

	}
	const char* c_str(){
		return _str;
	}

	void pushBack(const char& ch){
		// �������
		if (_size == _capacity){
			size_t newC = _capacity == 0 ? 15:2*_capacity;
			reserve(newC);
		}
		//β��
		_str[_size] = ch;
		// ����size
		++_size;
		_str[_size] = '\0';
	}
	void reserve(size_t n){
		if (n > _capacity){
			//���ռ�:+1
			char* tmp = new char[n + 1];
			//����
			strcpy(tmp,_str);
			//�ͷ�ԭ�пռ�
			delete[] _str;

			_str = tmp;
			//��������
			_capacity = n; 
		}
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

void test(){
	String s("abcdefghijklmn");

	String::iterator it = s.begin();
	while (it != s.end()){
		cout << *it << endl;
		*it = '0';
		++it;
	}
}
int main(){
	test();


	while (1);
	return 0;
}
*/