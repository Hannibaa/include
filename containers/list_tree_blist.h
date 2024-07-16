/* 
       BASIC LIST 
	        Node { T data, Node* next}
			BNode{ T data, Node* prev, Node* next}
			TNode{ T data, Node* left, Node* right}
			
	   FUNCTIONS 
*/


#pragma once
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

// Node ELEMENT AS DATA TYPE INTEGER

struct Node
{
	int data;
	Node* next;
};

// --------------------------- FUNCTION 1 ---------------------------
// -------------------INSERT FUNCTION AT HEAD LIST ------------------

void Insert_Node(Node** head, int n)//tested
{
	Node* tmp = new Node();                                      // Creating new space for node
	tmp->data = n;                                               // affectation to node
	tmp->next = *head;                                           // Time complexity O(1)
	*head = tmp;
}

// --------------------------- FUNCTION 2 ---------------------------
// ----------------------- INSERT AT END OF LIST --------------------

void Insert_Node_End(Node** head, int n)//tested                     // Time complexity O(1)   
{
	Node* tmp = new Node();
	tmp->data = n;
	tmp->next = nullptr;
	if (*head == nullptr) { *head = tmp; return; }
	Node* tm = *head;
	while (tm->next != nullptr) tm = tm->next;
	tm->next = tmp;                                                            
}

 // --------------------------- FUNCTION 3 --------------------------
 // ---------------------- INSERT AT POSITION N ---------------------

void Insert_Node_At(Node** head, int n, int pos)//tested
{
    if (pos <= 1) {
		Insert_Node(head, n);
		return;
	}

	Node* tmp = new Node();
	tmp->data = n;
	if (*head == nullptr) { tmp->next = nullptr; *head = tmp; return; }
	
	Node* tm = *head;
	for (int j = 1; j < pos - 1; ++j, tm = tm->next) 
		if (tm == nullptr)
	       {
			cout << "Error Out Of Range\n"; delete tmp; return;
	       };
	if (tm == nullptr) {
		cout << "Error Out Of Range\n";  return;
	}
	tmp->next = tm->next;
	tm->next = tmp;                                                  // Time complexity O(n)
}

// --------------------------- FUNCTION 4 ---------------------------
// -------------------------- SIZE OF LIST --------------------------

int Size_List(Node* l)//tested
{
	int j = 0;
	for (Node* tm = l; tm != nullptr; ++j, tm = tm->next);            // Time complexity O(n)

	return j;
}

// --------------------------- FUNCTION 5 ---------------------------
// -------------- PRINT  ALL ELEMENT OF LIST DATA PRINT -------------

void Print_List(const char* NameList, Node* head)//tested
{
	if (head == nullptr) { cout << "List is Empty\n"; return; }
	Node* tmp = head;
	cout << NameList;
	while (tmp != nullptr) { cout << tmp->data << "  "; tmp = tmp->next; };
	cout << endl;
}
// --------------------------- FUNCTION 5.1 ---------------------------
// ------------- Recurssive of Print reverse function -----------------
void rPrint_List_Reverse(Node* head)// tested
{
	if (head == nullptr) return;
	 
	rPrint_List_Reverse(head->next);cout << head->data << " ";
}
// --------------------------- FUNCTION 5.2 ---------------------------
// ------------------- Recurssive of Print function -------------------
void rPrint_List(Node* head)//tested
{
	if (head == nullptr) return;
    cout << head->data << " ";
	rPrint_List(head->next); 
}


// --------------------------- FUNCTION 6 ---------------------------
// -------- REMOVE FUNCTION FROM END ; FRONT ; POSITION -------------

void Delete_Node_At(Node** head, int pos)//tested                     // Complexity O(n)
{
	if (*head == nullptr) { cout << "Empty List \n"; return; }

	Node* tmp = *head;
	if (pos <= 1) {
		*head = tmp->next;
		delete tmp;
		return;
	};
	for (int i = 1; i < pos - 1; i++) {
		tmp = tmp->next;
		if (tmp->next == nullptr) { cout << "Error Position Is Out Of Range \n"; return; };
	}

	Node* tmp1 = tmp->next;
	tmp->next = tmp1->next;
	delete tmp1;
}

// --------------------------- FUNCTION 7 ---------------------------
// ------------------------- Delete a list --------------------------

void Delete_List(Node** head)//tested
{
	if (*head == nullptr) { cout << "Empty List \n"; return; }

	
	while (*head != nullptr) {
        Node* tmp = *head;
		*head = tmp->next;
		delete tmp;
	}
}

// --------------------------- FUNCTION 8 ---------------------------
// -------------------- Get data at position n ----------------------

int Get_Data_At(Node** head, int pos)//tested
{  
	if(pos < 1) { cout << "Out of Rang of List \n"; return -1; }
	if (*head == nullptr) {
		cout << "List is empty \n"; return -1;
	}
	Node* tmp = *head;
	for (int i = 1; (i < pos) && tmp != nullptr; i++) tmp = tmp->next;
	
	if (tmp == nullptr) {cout << "Out of Rang of List \n"; return -1;}

	return tmp->data;
}

// --------------------------- FUNCTION 9 ---------------------------
// -------------------- Get data at position n ----------------------

int Get_Data_Pos(Node** head, int data)//tested
{
	if (*head == nullptr) { cout << "Error : Empty List \n"; return -1; }

	Node* tmp = *head;

	for (int i = 1; tmp != nullptr; i++)
	{
		// check the data
		if (tmp->data == data) { return i; }
		tmp = tmp->next;
	}

	cout << " No Data Found \n";
	// not found return 0
	return 0;
}

// --------------------------- FUNCTION 10 ---------------------------
// -------------- Set data at Existing position n -------------------

int Set_Data_At(Node** head, int data, int pos)//tested
{
	if (pos < 1) { cout << "Error Out of range \n"; return -1; }
	if (*head == nullptr) {
		cout << "List is empty \n"; return -1;
	}
	Node* tmp = *head;
	for (int i = 1; (i < pos) && tmp != nullptr; i++) tmp = tmp->next;

	if (tmp == nullptr) { cout << "Out of Rang of List \n"; return -1; }

	tmp->data = data;
	return tmp->data;
}

// --------------------------- FUNCTION 11 ---------------------------
// --------------------- CONVERT LIST TO ARRAY -----------------------

void List_To_Array(Node* L, int*& a)//tested
{
	if (L == nullptr) { cout << " Error Empty List "; a = nullptr; return; }
	Node* tmp = L;
	int i = 0;
	a = new int[Size_List(L)];
	while (tmp != nullptr) {
		a[i] = tmp->data;
		tmp = tmp->next;
		i++;
	}
}

// --------------------------- FUNCTION 12 ---------------------------
// -------------------- CONVERT LIST TO VECTOR -----------------------

void List_To_Vector(Node* L, vector<int>& v)// tested
{
	if (L == NULL) { cout << " Error Empty List "; return; }
	Node* tmp = L;
	while (tmp != nullptr) {
		v.push_back(tmp->data);
		tmp = tmp->next;
	}
}

// --------------------------- FUNCTION 13 ---------------------------
// ---------------------- CONVERT ARRAY TO LIST ----------------------
enum Option{Add,New};

void Array_To_List(int a[], Node** L, Option option = Option::New)// Not Pass Test!!!!
{
	if (option == New && *L != nullptr) { 
		cout << "Error; List is not empty, Chose new empty list \n";
		return; 
	}
	
	int sz = sizeof(a) / sizeof(a[0]);
	for (int i = 1; i <= 5; ++i) Insert_Node(L, a[5-i]);
}

// --------------------------- FUNCTION 14 ---------------------------
// ---------------------- CONVERT VECTOR TO LIST ---------------------

void Vector_To_List(vector<int>& v, Node** L, Option option = Option::New)//tested
{
	if (option == New && *L != nullptr) {
		cout << "Error; List is not empty, Chose new empty list \n";
		return;
	}

	for (int i = 0; i < v.size(); ++i) Insert_Node(L, v[v.size() - i-1]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------- OPERATION ON THE LISTS -----------------------

// --------------------------- FUNCTION 15 ----------------------------
// -------------------------- REVERSE LIST ----------------------------

void Reverse_List(Node** L)
{
	if (*L == nullptr) { cout << "Error Empty list \n"; return; }

	Node* ptmp, *tmp, *ntmp;
	ptmp = nullptr;
	tmp = *L;
	while (tmp != nullptr) {
		ntmp = tmp->next;
		tmp->next = ptmp;
		ptmp = tmp;
		tmp = ntmp;
	}
	*L = ptmp;
	
}
 
// --------------------------- FUNCTION 15.1 --------------------------
// --------------------- Recursive REVERSE LIST -----------------------

void rReverse_List(Node* p, Node** L)
{

	if (p->next == nullptr)
	{
		*L = p;
		return;
	}

	rReverse_List(p->next, L);
	Node* q = p->next;
	q->next = p;
	p->next = nullptr;	
}

// --------------------------- FUNCTION 16 ----------------------------
// ------------------- CONNECT TWO LIST L1 AND L2 ---------------------

void Connect2List(Node** l1, Node** l2)
{
	// mathematical is l1= l1 union l2;
	Node* tmp = *l1;
	while (tmp->next != NULL) tmp = tmp->next;
	tmp->next = *l2;

	return;
}

// --------------------------- FUNCTION 17 ---------------------------
// --------------COPY A LIST L2 TO LIST L1; MATH L1=L1+L2 ------------
// ---------- TWO OPTION AT 'end' OR AT 'front', at Position ---------

enum Pos { front = -1, end };
void Copy_2List(Node** l1, Node* l2,int pos = Pos::end)
{
	if (l2 == nullptr) { cout << "List is empty\n"; return; }
	
	Node* tmp = l2;
	int i = 1;
	switch (pos)
	{
	case Pos::end:
          while (tmp != nullptr) {
			Insert_Node_End(l1, tmp->data);
			tmp = tmp->next;
		  }
		  return;

	case Pos::front:
	
          while (tmp != nullptr) {
		     Insert_Node_At(l1, tmp->data,i); 
		     tmp = tmp->next;
			 ++i;
	      }
		return;

	default:
		int j = 0;
		while (tmp != nullptr) {
			Insert_Node_At(l1, tmp->data, pos + j);
			tmp = tmp->next;
			j++;
		}
		break;
	}
	
	
}

// --------------------------- FUNCTION 17 ---------------------------
// --- CUT LIST IN TWO PIECE OF LIST OF SIZE N + M = SIZE OF LIST L --

Node* Splite_List(Node* L,int (*q)(int,int), int option = 0)
{
	if (L == nullptr) { cout << "Error"; return nullptr; }
	Node* newL = new Node;
	newL = nullptr;

	Node* tmp = L;
	while (tmp)
	{
		if ( q(tmp->data, option) ) Insert_Node(&newL, tmp->data);
		tmp = tmp->next;
	}

	return newL;
}


// COMPARE TWO LIST

// LIST DENSITY DISTRIBUTION

 