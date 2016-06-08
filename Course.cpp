#include "stdafx.h"
#include "iostream"
#include "string"
#include "windows.h"
#include "assert.h" 
#include "process.h"
#include "Mmsystem.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

template <class anim>
class ChoiseAnimal {
public:
	ChoiseAnimal(anim & vindent_anim, ChoiseAnimal<anim> * Push_anim, ChoiseAnimal<anim> * left_CH, ChoiseAnimal<anim> * right_CH)
		: value_EST(vindent_anim), par_anim(Push_anim), leftYES(left_CH), rightNO(right_CH) { }
	
	void release();
	int count(anim & testElement);
	void ChoiseINSERT(ChoiseAnimal<anim> *);
	int size_tree_anim();
	ChoiseAnimal<anim> * merge(ChoiseAnimal<anim> *, ChoiseAnimal<anim> *);
	anim value_EST;
	ChoiseAnimal<anim> * par_anim;
	ChoiseAnimal<anim> * leftYES;
	ChoiseAnimal<anim> * rightNO;
};


template <class anim> int ChoiseAnimal<anim>::size_tree_anim()
{
	int count = 1;
	if (leftYES != 0)
		count += leftYES.size_tree_anim();
	if (rightNO != 0)
		count += rightNO.size_tree_anim();
	return count;
}


template <class anim> void ChoiseAnimal<anim>::ChoiseINSERT(ChoiseAnimal<anim> * newNode)
{
	if (newElement < value_EST)
		if (leftYES != 0)
			leftYES->ChoiseINSERT(newNode);
		else {
			newNode->par_anim = this;
			leftYES = newNode;
		}
	else
		if (rightNO != 0)
			rightNO->ChoiseINSERT(newNode);
		else {
			newNode->par_anim = this;
			rightNO = newNode;
		}
}

template <class anim>
ChoiseAnimal<anim> * ChoiseAnimal<anim>::merge(ChoiseAnimal<anim> * left, ChoiseAnimal<anim> * right)
{
	if (left == 0)
		return right;
	if (right == 0)
		return left;
	ChoiseAnimal<T> * child = merge(left, right->leftYES);
	child->par_anim = right;
	right->leftYES = child;
	return right;
}
void Play(void*)
{
	mciSendString(L"play  d:\\1.mid wait", 0, 0, 0);
}

bool YOUR_answer() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (1) {
		string ans;
		getline(cin, ans);
		if ((ans[0] == '�') || (ans[0] == '�') || (ans[0] == '+'))
			return true;
		else if ((ans[0] == '�') || (ans[0] == '�') || (ans[0] == '-'))
			return false;
		cout << "�������� �������, '��' ��� '���' \n ";
	}
}

void New_Animal(ChoiseAnimal<string> * cour_team)
{
	string currentAnimal = cour_team->value_EST;
	cout << "����. ��� ����� �������� �� �������?\n";
	string newAnimal;
	getline(cin, newAnimal);
	cout << "��� ������  "
		<< cour_team->value_EST << " ���� �� �����  " << newAnimal << " ?\n";
	string newQuestion;
	ChoiseAnimal<string> * node1 = new ChoiseAnimal<string>(newAnimal, cour_team, 0, 0);
	ChoiseAnimal<string> * node2 = new ChoiseAnimal<string>(currentAnimal, cour_team, 0, 0);
	assert((node1 != 0) && (node2 != 0));
	getline(cin, newQuestion);
	cout << "��� ������ " << newAnimal << " ?\n";
	if (YOUR_answer() != 0) {
		_beginthread(Play, 100, NULL);
		cour_team->leftYES = node1;
		cour_team->rightNO = node2;
	}
	else {
		cour_team->leftYES = node2;
		cour_team->rightNO = node1;
	}
	cour_team->value_EST = newQuestion;
}

void MainRealt() {	
	_beginthread(Play, 100, NULL);	
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cd;
	cd.X = 10;
	cd.Y = 15;
	SetConsoleCursorPosition(hd, cd);
	system("color 76");
	cout << " ������! \n";
	Sleep(900);
	system("cls");
	cd.X = 30;
	cd.Y = 15;
	SetConsoleCursorPosition(hd, cd);
	system("color 71");
	cout << " ����� \n";
	Sleep(900);
	system("cls");
	cd.X = 50;
	cd.Y = 15;
	SetConsoleCursorPosition(hd, cd);
	system("color 7D");
	cout << " �������!!! \n";
	Sleep(900);
	system("color 70");
	system("cls");
	string first_z = "���";
	ChoiseAnimal<string> * root = new ChoiseAnimal<string>(first_z, 0, 0, 0);
	ChoiseAnimal<string> * cour_team = root;
	cout << "   ���� ���...                                                ���� ���-���  \n";
	cout << "� ���� �� ������� ���-��.... \n";
	while (cour_team != 0) {
		if (cour_team->leftYES != 0) {
					_beginthread(Play, 100, NULL);		
			cout << cour_team->value_EST << '\n';
			if (YOUR_answer())
				cour_team = cour_team->leftYES;
			else
				cour_team = cour_team->rightNO;
		}
		else {
			_beginthread(Play, 100, NULL);		
			cout << "��������... ��� " << cour_team->value_EST << " ?\n";
			if (YOUR_answer()){	
				cout << "��! � �������\n";
			}
			else {
				New_Animal(cour_team);
			}
			cout << "�����.... ��������?\n";
			if (YOUR_answer())
				cour_team = root;
			else
				return;
		}
	}
}

void main() {
	setlocale(LC_ALL, "Russian");
	MainRealt();
}