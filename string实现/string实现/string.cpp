#define _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <iostream>
using namespace std;
class String{
public:
	// 这种构造函数存在解引用空指针异常
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
		_str[_size] = '\0';//_size表示有效字符的个数，这个位置中放的是'\0'
		_capacity = 15;
	}
	// 全缺省构造2
	//String(char* str)
	//	:_str(str)
	//	, _size(strlen(str))
	//	, _capacity(strlen(str))
	//{
	//}
	// 改动2
	String(const char* str){
		_size = strlen(str);
		_str = new char[_size + 1]; //根据大小申请空间，自己复制得有一份，拷贝所得
		strcpy(_str, str);
		_capacity = _size;
	}
	// 深拷贝版本1
	// 拷贝构造之后的资源都不同，释放不会出现问题，都会有独立的资源
	//String(const String& str)
	//	:_str(new char[str._capacity+1])
	//	, _size(str._size)
	//	, _capacity(str._capacity)
	//{
	//	// 资源拷贝,此处完成了深拷贝
	//	strcpy(_str, str._str);
	//	cout << "String(const String& str)" << endl;
	//}
	// 深拷贝版本2
	// 拷贝构造：现代写法，也是深拷贝，代码复用
	String(const String& str)
		// 给初始值，否则临时对象调用析构的时候会出问题
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(str._str);
		Swap(tmp);
	}
	// 复制运算符深拷贝的现代写法,代码复用
	// 拷贝构造，传值的时候进行拷贝构造，创建当前的一个局部对象，
	// 交换局部对象，调用局部对象的析构函数，释放资源
	//String& operator=(String str){
	//	Swap(str);
	//	return *this;
	//}
	// 引用的时候注意只读不可改
	String& operator=(const String& str){
		String tmp(str);
		Swap(tmp);
		return *this;
	}
	//// 深拷贝的交换：效率低，不建议这也写
	//void SWAP(String& str){
	//	//拷贝构造
	//	String tmp = str;
	//	// 赋值运算符
	//	str = *this;
	//	// 赋值运算符
	//	*this = tmp;
	//}

	// 并非手动深拷贝，但是完成了深拷贝的内容，实现了深拷贝
	void Swap(String& str){
		// 交换，并不会赋值
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}
	//String& operator=(const String& str){
	//	if (this != &str) // 不是自我进行赋值
	//	{
	//		// 开空间
	//		char* tmp = new char[str._capacity + 1];
	//		// 内容拷贝
	//		strcpy(tmp, str._str);
	//		// 释放原有空间
	//		delete[] _str;

	//		// 浅拷贝，通过以上资源的拷贝称为深拷贝，赋值运算符
	//		_str = tmp;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}
	// 此处不能用于构造2，释放代码区的内容，delete只能释放堆中的内容
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
	// 插入一个字符
	void pushBack(const char& ch){
		// 检查容量
		if (_size == _capacity){
			size_t newC = _capacity == 0 ? 15 : 2*_capacity;
			reserve(newC);
		}
		// 尾插
		_str[_size] = ch;
		// 更新size
		++_size;
		// 补一个'\0'
		_str[_size] = '\0';
	}
	void reserve(size_t n){
		if (n > _capacity){
			// 开空间+1-->存放'\0'
			char* tmp = new char[n + 1];
			// 拷贝
			strcpy(tmp, _str);
			// 释放原有空间
			delete[] _str;
			_str = tmp;
			// 更新容量
			_capacity = n;
		}
	}
	// 遍历,实现迭代器
	// 使用方式类似于指针
	// 迭代器：一种访问容器元素的机制，体现封装的特性，不需要关注容器的实现细节，就可以直接访问（可读可写）元素
	// 使用方式：类似于指针的操作
	// 1、解引用 --> 获取指向位置的内容
	// 2、位置移动 --> 指向其他位置

	// string : 迭代器，通过指针实现
	typedef char* iterator;
	typedef const char* const_iterator;
	iterator begin(){
		// 第一个元素的位置
		return _str;
	}
	iterator end(){
		// 最后一个元素的下一个位置
		return _str + _size;
	}
	// 只读迭代器
	const_iterator begin() const{
		//第一个元素的位置
		return _str;
	}
	const_iterator end() const{
		//最后一个元素的后一个位置
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
	// 尾插一个字符串
	void Append(const char* str){
		int len = strlen(str);
		// 检查容量
		if (_size+len > _capacity){
			// 必须要保证所开字符串长度
			reserve(_size + len);
		}
		// 尾插
		strcpy(_str + _size, str);
		// 修改size
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
		if (pos > _size) return; // 此时非连续
		// 检查容量
		if (_size == _capacity){
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		// 移动元，从后向前移动[pos,_size]，首先移动最右端字符，防止覆盖
		size_t end = _size;
		//while (end >= pos){ // 此处有BUG，size_t本就>=0,当pos为0时就产生死循环
		//	_str[end + 1] = _str[end];
		//	--end;
		//}
		while (end > pos){
			_str[end] = _str[end - 1];
			--end;
		}
		//插入
		_str[pos] = ch;

		++_size;
	}
	void insert(size_t pos, const char* str){
		if (pos > _size) return;
		int len = strlen(str);
		if (_size + len > _capacity){
			reserve(_size + len);
		}
		// 移动元素 (pos,_size)
		// size --> size+len , pos -->pos+len
		size_t end = _size + len;
		while (end > pos+len-1){
			_str[end] = _str[end - len];
			--end;
		}
		// 插入
		// strcpy 会拷贝'\0'，因此不可用
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
void printString(const String& s){ // cosnt对象只能调用const接口
	// 迭代器遍历
	String::const_iterator it = s.begin();
	cout << "iterator:>";
	while (it != s.end()){
		cout << *it << " ";
		//*it = '0'; // const接口就不支持写操作
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
// 只要实现了迭代器就可以使用范围for
	// 要修改必须使用引用才能修改，否则是局部变量无法修改
	// 值接收，只是修改临时局部变量
	cout << "范围for:>";
	for (const char& ch : s){
		cout << ch << " ";
	}
	cout << endl;
	for (char ch : s){
		ch = 'a';// s 的内容不能修改，临时变量，需要引用才可以改变
	}
	//// 迭代器遍历
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
	// 如果不重写，会引起二次释放的问题
	//String s("123");
	//// 调用拷贝构造,此处为浅拷贝，资源共享，导致三个对象指向同一个位置，释放的时候
	// 从copy2->copy->s ： 多次释放同一个空间，造成错误
	// 此处的拷贝需要深拷贝，重写，对资源进行拷贝
	//String copy = s;
	//String copy2(s);
}
void test(){
	string s;
	const char* ptr = s.c_str(); // 可以取出字符串的地址
	if ( ptr ) cout << "ptr is't nullptr" << endl;
	printf("%p\n", ptr);
	cout << ptr << endl;
	cout << s.c_str() << endl;
	//String str; // 可能会存在解引用异常，为空
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

	// 迭代器：一种访问容器元素的机制，体现封装的特性，不需要关注容器的实现细节，就可以直接访问（可读可写）元素
	// 降低访问元素的成本
	// 使用方式：类似于指针
	// 1、支持解引用 --> 获取指向位置的内容
	// 2、位置移动 --> 指向其他位置
	//string 迭代器：通过指针实现
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin(){
		// 第一个元素的位置
		return _str;
	}
	iterator end(){
		// 最后一个元素的下一个位置
		return _str + _size;
	}

	const_iterator cbegin() const{
		// 第一个元素的位置
		return _str;
	}
	const_iterator cend() const{
		// 最后一个元素的下一个位置
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
		// 检查容量
		if (_size == _capacity){
			size_t newC = _capacity == 0 ? 15:2*_capacity;
			reserve(newC);
		}
		//尾插
		_str[_size] = ch;
		// 更新size
		++_size;
		_str[_size] = '\0';
	}
	void reserve(size_t n){
		if (n > _capacity){
			//开空间:+1
			char* tmp = new char[n + 1];
			//拷贝
			strcpy(tmp,_str);
			//释放原有空间
			delete[] _str;

			_str = tmp;
			//更新容量
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