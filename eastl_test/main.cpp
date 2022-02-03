#include <iostream>
#include <string>
#include <vector>
#include <hash_map>
#include <unordered_map>
#include <map>
#include <array>
#include <algorithm>
#include <sort>
#include <chrono>
#include <memory>
#include <string>
#include <utility>
#include <tuple>
#include <heap>
#include <list>
#include <type_traits>
#include <iterator>
#include <winapi.h>

using namespace std;
using namespace std::chrono;


std::tuple<int, int, int, int> MakeSampleTuple(int a, int b)
{
	return std::make_tuple(a + b, a - b, a * b, a / b);
}

int Test_HashMap(void);
void Test_Unorder_Map();
void Test_Unorder_Map2();

int main(int argc, char** argv)
{
	int add, sub, div;
	std::tie(add, sub, std::ignore, div) = MakeSampleTuple(15, 18);

	printf("%d, %d, %d\n", add, sub, div);


	Test_HashMap();
	Test_Unorder_Map();
	Test_Unorder_Map2();

	return 0;
}

int Test_HashMap(void) {

	//��������!
	hash_map<int, float> hash1;	//hash_map ����
	hash_map<int, float>* hash2 = new hash_map<int, float>;	//hash_map �����Ҵ�

	//�ڷ��߰� = insert() �Լ�
	hash1.insert(hash_map<int, float>::value_type(10, 45.6f));	//�ܼ� �߰�
	hash1.insert(hash1.begin(), hash_map<int, float>::value_type(11, 50.2f));	//Ư����ġ�� �߰�
	hash2->insert(hash1.begin(), hash1.end());	//������ ������ �ִ°͵� �߰�

	//����
	hash1.erase(hash1.begin());		//ù��° ��ġ�� ��� ����
	hash1.erase(hash1.begin(), hash1.end());	//ó��~������ ����
	hash1.erase(11);		//key�� 11�� ��� ����

	//�˻� - key�� ����� ���� key�� ���� �ִ� ��Ҹ� ã��(ã���� iterator ��ȯ, �ƴϸ� end() ��ȯ)
	hash_map<int, float>::iterator Finditer = hash1.find(10);
	if (Finditer != hash1.end())
		Finditer->second = 290.44f;

	return 0;
}


void Test_Unorder_Map()
{
	unordered_map<string, int> umap;

	umap["GeeksforGeeks"] = 10;
	umap["Practice"] = 20;
	umap["Contribute"] = 30;

	for (auto x : umap)
		cout << x.first << " " << x.second << endl;
}

using namespace std;

void Test_Unorder_Map2()
{
	// Declaring umap to be of <string, double> type
	// key will be of string type and mapped value will
	// be of double type
	unordered_map<string, double> umap;

	// inserting values by using [] operator
	umap["PI"] = 3.14;
	umap["root2"] = 1.414;
	umap["root3"] = 1.732;
	umap["log10"] = 2.302;
	umap["loge"] = 1.0;

	// inserting value by insert function
	umap.insert(make_pair("e", 2.718));

	string key = "PI";

	// If key not found in map iterator to end is returned
	if (umap.find(key) == umap.end())
		cout << key << " not found\n\n";

	// If key found then iterator to that key is returned
	else
		cout << "Found " << key << "\n\n";

	key = "lambda";
	if (umap.find(key) == umap.end())
		cout << key << " not found\n";
	else
		cout << "Found " << key << endl;

	//    iterating over all value of umap
	unordered_map<string, double>::iterator itr;
	cout << "\nAll Elements : \n";
	for (itr = umap.begin(); itr != umap.end(); itr++)
	{
		// itr works as a pointer to pair<string, double>
		// type itr->first stores the key part  and
		// itr->second stores the value part
		cout << itr->first << "  " << itr->second << endl;
	}
}

void Test_Chrono()
{
	auto start = system_clock::now();
	Sleep(1000);
	auto end = system_clock::now();
	auto d = end - start;

	cout << (unsigned long)d.count() << endl;
}


int Random(int x)
{
	return rand() % x;
}

void Test_Random()
{
	std::vector<size_t> rngArray;

	for (size_t i = 0; i < 10; ++i)
		rngArray.push_back(i);

	random_shuffle(rngArray.begin(), rngArray.end(), Random);

	for (int i = 0; i < 10; i++)
		cout << rngArray[i] << " ";
}

void Test_Sort()
{
	array<int, 4> a = { 47, 23, 90, 1 };

	sort(a.begin(), a.end());

	for (auto i = a.begin(); i != a.end(); ++i)
	{
		cout << *i << endl;
	}
}

