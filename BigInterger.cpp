
/****	 A number will first be input as a string,	****/
/****		then stored in a List in reverse		****/
/**** i.e: 1234 will be stored as 4-3-2-1 in a List ****/
/****		-1234 will be stored as 4-3-2-(-1)		****/

#include <iostream>
#include <string>
using namespace std;

struct NODE
{
	int key;
	NODE* next;
}; typedef NODE* Node;
Node GetNode(int);
struct List
{
	Node head;
	Node tail;
	List()
	{
		head = NULL;
		tail = NULL;
	}
};
void AddHead(List&, Node);
void AddTail(List&, Node);
int isEmpty(List);

struct BIGINTERGER
{
	List num;
	BIGINTERGER() {}
	BIGINTERGER(string str)
	{
		if (str[0] == '-')
		{
			AddHead(number.num, GetNode(-((int)str[1] - '0')));
			for (int i = 2; i < str.length(); i++)
				AddHead(number.num, GetNode((int)str[i] - '0'));
		}
		else
			for (int i = 0; i < str.length(); i++)
				AddHead(number.num, GetNode((int)str[i] - '0'));
	}
	BIGINTERGER(char c)
	{
		AddHead(num, GetNode((int)c - '0'));
	}
};

istream& operator>>(istream&, BIGINTERGER&);
ostream& operator<<(ostream&, BIGINTERGER);
bool operator>(BIGINTERGER, BIGINTERGER);
bool operator<(BIGINTERGER, BIGINTERGER);
bool operator==(BIGINTERGER, BIGINTERGER);
BIGINTERGER operator+(BIGINTERGER, BIGINTERGER);
BIGINTERGER operator-(BIGINTERGER, BIGINTERGER);
BIGINTERGER operator-(BIGINTERGER);
BIGINTERGER operator*(BIGINTERGER, BIGINTERGER);
BIGINTERGER operator*(BIGINTERGER, int);
BIGINTERGER operator/(BIGINTERGER, BIGINTERGER);

int main()
{
	BIGINTERGER a, b;
	cin >> a >> b;
	cout << "Sum: " << a + b;
	cout << "\nMinus: " << a - b;
	cout << "\nMultiply: " << a * b;
	cout << "\nDivide: " << a / b;
	cout << endl;
	return 0;
}

int isEmpty(List list)
{
	return list.head == NULL;
}
void AddHead(List& list, Node p)
{
	if (isEmpty(list))
	{
		list.head = list.tail = p;
	}
	else
	{
		p->next = list.head;
		list.head = p;
	}
}
void AddTail(List& list, Node p)
{
	if (isEmpty(list))
	{
		list.head = list.tail = p;
	}
	else
	{
		list.tail->next = p;
		list.tail = p;
	}
}
Node GetNode(int key)
{
	Node p = new NODE;
	p->key = key;
	p->next = NULL;
	return p;
}
istream& operator>>(istream& is,BIGINTERGER& number)
{
	cout << "Input: ";
	string strTemp;
	is >> strTemp;
	if (strTemp[0] == '-')
	{
		AddHead(number.num, GetNode(-((int)strTemp[1] - '0')));
		for (int i = 2; i < strTemp.length(); i++)
			AddHead(number.num, GetNode((int)strTemp[i] - '0'));
	}
	else
	for (int i = 0; i < strTemp.length(); i++)
		AddHead(number.num, GetNode((int)strTemp[i] - '0'));
	return is;
}
ostream& operator<<(ostream& os, BIGINTERGER a)
{
	string temp = "";
	for (Node k = a.num.head; k != NULL; k = k->next)
	{
		temp = to_string(k->key) + temp;
	}
	os << temp;
	return os;
}
bool operator>(BIGINTERGER a, BIGINTERGER b)
{
	// convert BIGINTERGERs back into strings
	string tempA = "", tempB = "";
	for (Node k = a.num.head; k != NULL; k = k->next)
		tempA = to_string(k->key) + tempA;
	for (Node k = b.num.head; k != NULL; k = k->next)
		tempB = to_string(k->key) + tempB;

	// check if both numbers are negative or positive
	// if they are, compare them or their length
	if ((tempA[0] != '-' && tempB[0] != '-') || (tempA[0] == '-' && tempB[0] == '-'))
	{
		if (tempA.length() == tempB.length())
			return tempA.compare(tempB) > 0;
		return tempA.length() > tempB.length();
	}
	else // if they are not, then one of them must be negative
		return tempB[0] == '-';
}
bool operator<(BIGINTERGER a, BIGINTERGER b)
{
	string tempA = "", tempB = "";
	for (Node k = a.num.head; k != NULL; k = k->next)
		tempA = to_string(k->key) + tempA;
	for (Node k = b.num.head; k != NULL; k = k->next)
		tempB = to_string(k->key) + tempB;

	if ((tempA[0] != '-' && tempB[0] != '-') || (tempA[0] == '-' && tempB[0] == '-'))
	{
		if (tempA.length() == tempB.length())
			return tempA.compare(tempB) < 0;
		return tempA.length() < tempB.length();
	}
	else
		return tempA[0] == '-';
}
bool operator==(BIGINTERGER a, BIGINTERGER b)
{
	string tempA = "", tempB = "";
	for (Node k = a.num.head; k != NULL; k = k->next)
		tempA = to_string(k->key) + tempA;
	for (Node k = b.num.head; k != NULL; k = k->next)
		tempB = to_string(k->key) + tempB;

	return tempA.compare(tempB) == 0;
}

BIGINTERGER operator+(BIGINTERGER a, BIGINTERGER b)
{
	// For negative terms
	if (a.num.tail->key < 0 && b.num.tail->key>0)
		return b - (-a);
	else if (a.num.tail->key > 0 && b.num.tail->key < 0)
		return a - (-b);
	else if (a.num.tail->key < 0 && b.num.tail->key < 0)
		return (-a) + (-b);

	BIGINTERGER result;
	int remain = 0;
	Node k, h;
	if (a > b)
	{
		k = b.num.head;
		h = a.num.head;
	}
	else
	{
		k = a.num.head;
		h = b.num.head;
	} // make sure k is smaller or equal to h

	for (; k != NULL; k = k->next)
	{
		int temp = k->key + h->key + remain;
		remain = temp / 10;
		AddTail(result.num, GetNode(temp % 10));
		h = h->next;
	}
	if (h != NULL)
	{
		for (; h != NULL; h = h->next)
		{
			int temp = h->key + remain;
			remain = temp / 10;
			AddTail(result.num, GetNode(temp % 10));
		}
	}
	if (remain != 0)
		AddTail(result.num, GetNode(remain));
	return result;
}

BIGINTERGER operator-(BIGINTERGER a, BIGINTERGER b)
{
	if (a.num.tail->key < 0 && b.num.tail->key > 0)
		return -(-a + b);
	else if (a.num.tail->key > 0 && b.num.tail->key < 0)
		return a + (-b);
	else if (a.num.tail->key < 0 && b.num.tail->key < 0)
		return -((-a) + (-b));

	BIGINTERGER result;
	int thieu = 0;
	Node k, h;
	if (a < b)
	{
		k = b.num.head;
		h = a.num.head;
	}
	else
	{
		k = a.num.head;
		h = b.num.head;
	} // make sure k is smaller or equal to h

	for (; h != NULL; h = h->next)
	{
		int temp = k->key - h->key - thieu;
		if (temp < 0)
		{
			thieu = 1;
			AddTail(result.num, GetNode(10 + temp));
		}
		else if (temp > 0 || (temp == 0 && k->next != NULL))
		{
			thieu = 0;
			AddTail(result.num, GetNode(temp));
		}
		k = k->next;
	}
	if (k != NULL)
	{
		for (; k != NULL; k = k->next)
		{
			int temp = k->key - thieu;
			if (temp < 0)
			{
				thieu = 1;
				AddTail(result.num, GetNode(10 + temp));
			}
			else if (temp > 0)
			{
				thieu = 0;
				AddTail(result.num, GetNode(temp));
			}
		}
	}
	if (a < b)
		result.num.tail->key *= -1;
	return result;
}
BIGINTERGER operator-(BIGINTERGER a)
{
	BIGINTERGER result;
	for (Node k = a.num.head; k != NULL; k = k->next)
		AddTail(result.num, GetNode(k->key));
	result.num.tail->key = -result.num.tail->key;
	return result;
}

/*
* To multiply:
*	multiply each digit of one number with the other number
*	then add them up in their correct unit
*/
BIGINTERGER operator*(BIGINTERGER a, int so)
{
	int surplus = 0;
	BIGINTERGER result;
	for (Node k = a.num.head; k != NULL; k = k->next)
	{
		int temp = k->key * so + surplus;
		AddTail(result.num, GetNode(temp % 10));
		surplus = temp / 10;
	}
	if (surplus != 0)
		AddTail(result.num, GetNode(surplus));
	return result;
}
BIGINTERGER operator*(BIGINTERGER a, BIGINTERGER b)
{
	if (a.num.tail->key < 0 && b.num.tail->key > 0)
		return -(-a * b);
	else if (a.num.tail->key > 0 && b.num.tail->key < 0)
		return a * (-b);
	else if (a.num.tail->key < 0 && b.num.tail->key < 0)
		return -((-a) * (-b));

	BIGINTERGER result;
	BIGINTERGER k;
	Node h;
	int temp = 10;
	if (a < b)
	{
		k = b;
		h = a.num.head;
	}
	else
	{
		k = a;
		h = b.num.head;
	}
	result = k * h->key;
	for (h = h->next; h != NULL; h = h->next)
	{
		result = result + (k * h->key) * temp;
		temp = temp * 10;
	}
	return result;
}


BIGINTERGER operator/(BIGINTERGER a, BIGINTERGER b)
{
	// For negative numbers
	if (a.num.tail->key < 0 && b.num.tail->key > 0)
		return -(-a / b);
	else if (a.num.tail->key > 0 && b.num.tail->key < 0)
		return a / (-b);
	else if (a.num.tail->key < 0 && b.num.tail->key < 0)
		return -((-a) / (-b));

	if (a < b)
	{
		BIGINTERGER result("0");
		return result;
	}
	else if (a == b)
	{
		BIGINTERGER result("1");
		return result;
	}

	// A lot of Math and a bunch of heachdaches

	BIGINTERGER result;
	BIGINTERGER ogNum, divideBy;
	ogNum = a;
	divideBy = b;

	string numH = "";
	string ogDividedNum = "";
	string dividedNum = "";
	Node k = ogNum.num.head;
	for (Node h = divideBy.num.head; h != NULL; h = h->next)
	{
		numH = to_string(h->key) + numH;
	}
	for (Node h = ogNum.num.head; h != NULL; h = h->next)
		ogDividedNum = to_string(h->key) + ogDividedNum;
	int lengthK = ogDividedNum.length();
	int lengthH = numH.length();
	for (int i = 0; i < lengthH; i++)
		dividedNum = ogDividedNum[i] + dividedNum;
	BIGINTERGER divided(dividedNum);
	BIGINTERGER temp2(ogDividedNum[lengthH]);
	for (int i = 0; i < lengthK - lengthH + 1; i++)
	{
		int temp = 0;
		if (divided > divideBy || divided == divideBy)
		{
			for (int j = 0; j <= 10; j++)
				if (divideBy * j < divided || divideBy * j == divided)
					temp = j;
			AddHead(result.num, GetNode(temp));
		}
		divided = (divided - divideBy * temp) * 10 + temp2;
		if (i + 1 != lengthK - lengthH + 1)
		{
			BIGINTERGER temp3(dividedNum[lengthH + i]);
			temp2 = temp3;
		}
	}

	return result;
}