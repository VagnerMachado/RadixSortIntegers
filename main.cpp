
/***********************************************************************
 * Vagner Machado QCID 23651127
 * Project 2
 * Professor Tsaiyun Phillips
 * Queens College - Spring 2019
 ***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  // to get length of int
#include <math.h>   // abs()
#include <climits>  //MIN_INT to validate sort
using namespace std;

/**
 * listNode class declaration
 */
class listNode
{
	friend class RadixSort;
	friend class LLQ;
	friend class LLStack;
private:
	int data;
	listNode* next;
public:
	int getData();
	listNode();
	listNode(int z);
};

/**
 * LLStack class declaration
 */
class LLStack
{
	friend class RadixSort;
private:
	listNode * top;
public:
	LLStack();
	void push(listNode newNode);
	listNode pop();
	bool isEmpty();
	void printStack();
	void printStack(ofstream &out);
};

/**
 * LLQ class declaration
 */
class LLQ
{
	friend class RadixSort;
private:
	listNode * head;
	listNode * tail;
public:
	LLQ();
	void addTail(listNode x);
	listNode deleteHead();
	bool isEmpty();
	void printQueue(int index);
	void printQueue(int index, ofstream &out);
};

class RadixSort
{
private:
	const int tableSize = 10;
	LLQ ** hashTable;
	int maxData;
	int currentTable;
	int previousTable;
	int maxDigits;
	int offSet;
	int currentDigit;
	int currentQueue;
public:
	void firstReading(ifstream &inFile, int &maxDigits, int &offset);
	void loadStack (ifstream &inFile, ofstream &out, LLStack * top);
	void dumpStack(LLStack * top, ofstream &out, int curDigit, int curTable);
	int tableIndex();
	int getMaxDigits(int digit);
	int getDigit(listNode node, int &curDigit);
	int hashIndex();
	RadixSort();
	void radixSort(LLStack * stack, ofstream &out);
	void printTable(int table);
	void printTable(int table, ofstream &out);
	void output(ofstream &outfile, ofstream &debug);
};


/**************************************************************
 * main method - Enables the user to use a stack or a queue
 * to insert and delete integers. Input is provided by the user
 * using the console keyboard
 *************************************************************/
int main(int argc, char *argv[])
{
	//HAD TO ADD OFSTREAM PARAMETER TO A FEW FUNTIONS TO PRINT DEBUGGUNG INFO
	cout << "\n\n*** Welcome to Vagner's Project 2 ***\n\n";
	ifstream infile;
	ofstream outfile1;
	ofstream outfile2;
	outfile1.open(argv[2]);
	outfile2.open(argv[3]);
	outfile2 << "\n\n*** Vagner's Project 2 Debugging***\n\n";
	infile.open(argv[1]);
	LLStack * stack = new LLStack();
	RadixSort radix;
	int a,b;
	radix.firstReading(infile,a,b);
	infile.close();
	infile.open(argv[1]);
	radix.loadStack(infile, outfile2, stack);
	radix.radixSort(stack, outfile2);
	radix.output(outfile1, outfile2);
	outfile1.close();
	outfile2.close();
	cout << "\n** Sorting finished and inserted to " << argv[2] << " ***\n";
	cout << "\n** Debugging information inserted to " << argv[3] << " ***\n";
	outfile1.close();
	outfile2.close();
}

/*****************************************************************
 * listNode Methods
 *****************************************************************/
listNode::listNode(int x)
{
	data = x;
	next = NULL;
}

/**
 * listNode default constructor
 */
listNode::listNode()
{
	data = 0;
	next = NULL;
}


/*****************************************************************
 * LLStack Methods
 *****************************************************************/

/**
 * stack constructor
 */
LLStack::LLStack()
{
	top = NULL;
}

/**
 * push - pushes a node onto the stack
 * creates dynamic node with the data in node passed as parameter
 * coded in this manner to comply with guidelines provided
 */
void LLStack::push(listNode newNode)
{
	listNode * temp = new listNode(newNode.data);
	if(top != NULL)
	{
		temp->next = top;
		top = temp;
	}
	else
		top = temp;
}

/**
 * pop - removes the top item fromthe stack, returns a listNode
 */
listNode LLStack::pop()
{
	listNode a(top->data);
	top = top->next;
	return a;
}

/**
 * isEmpty - verifies if the stack is empty
 * return true if empty, false otherwise
 */
bool LLStack::isEmpty()
{
	return top == NULL;
}

/**
 * printStack - prints the stack in the console
 */
void LLStack::printStack()
{
	listNode * x = top;
	cout  <<"Top -> ";
	while (x != NULL)
	{
		cout << "(" << x->data << ", ";
		x = x-> next;
		if (x==NULL)
			cout << "NULL) -> ";
		else
		{
			cout << x->data << ") -> ";
			x = x->next;
		}
	}
	cout << " NULL\n";
}


/**
 * printStack - pritns the stack to file stream passed as parameter
 */
void LLStack::printStack(ofstream &out)
{
	listNode * x = top;
	out  <<"Top -> ";
	while (x != NULL)
	{
		out << "(" << x->data << ", ";
		x = x-> next;
		if (x == NULL)
			out << "NULL) -> ";
		else
		{
			out << x->data << ") -> ";
			x = x->next;
		}
	}
	out << " NULL\n";
}

/*****************************************************************
 * LLQ Methods
 *****************************************************************/

/**
 * queue constructor - contains a dummy node
 */
LLQ::LLQ()
{
	listNode * dum = new listNode(9999);
	head = dum;
	tail = dum;
}

/**
 * add a list node to the tail.
 * tail node is created from data in node passed as parameter
 * coded in this manner to comply with requirements given.
 *
 */
void LLQ::addTail(listNode x)
{
	listNode * temp = new listNode(x.data);
	tail->next = temp;
	tail = temp;
}

/**
 * deleteHead - deletes the head of the queue
 * returns a listNode instantiated with data from deleted node
 * coded this way to comply with requirements
 */
listNode LLQ::deleteHead()
{
	if(head != tail)
	{
		listNode a (head->next->data);
		if(head->next->next != NULL)
			head->next = head->next->next;
		else
		{
			head->next = NULL;
			tail = head;
		}
		return a;
	}
	else
		return listNode(head->data);
}


bool LLQ::isEmpty()
{
	return head == tail;
}

void LLQ::printQueue(int index)
{

	listNode * x = head->next;
	if(x == NULL)
	{
		cout << "Front (" << index << ") -> (NULL) \n";
		cout  <<"Tail  (" << index << ") -> (NULL) \n";
	}
	else
	{
		cout  <<"Front (" << index << ") -> ";
		while (x != NULL)
		{
			cout << "(" << x->data << ", ";
			x = x-> next;
			if (x==NULL)
				cout << "NULL) -> ";
			else
			{
				cout << x->data << ") -> ";
				x = x->next;
			}
		}
		cout << " NULL\n";
		x = tail;
		cout  <<"Tail  (" << index << ") -> (" << x->data << ", NULL) ->\n";
	}
}

void LLQ::printQueue(int index, ofstream &out)
{

	listNode * x = head->next;
	if(x == NULL)
	{
		out << "Front (" << index << ") -> (NULL) \n";
		out  <<"Tail  (" << index << ") -> (NULL) \n";
	}
	else
	{
		out  <<"Front (" << index << ") -> ";
		while (x != NULL)
		{
			out << "(" << x->data << ", ";
			x = x-> next;
			if (x==NULL)
				out << "NULL) -> ";
			else
			{
				out << x->data << ") -> ";
				x = x->next;
			}
		}
		out << " NULL\n";
		x = tail;
		out  << "Tail  (" << index << ") -> (" << x->data << ", NULL) ->\n";
	}
}
/*****************************************************************
 * RadixSort Methods
 *****************************************************************/

void RadixSort::firstReading(ifstream &inFile, int &maxD, int &off)
{ //cannot figure out why we need the int parameters
	int negativeNum = 0;
	int positiveNum = 0;
	int data;
	while(inFile >> data)
	{
		if(data < negativeNum)
			negativeNum = data;
		if (data > positiveNum)
			positiveNum = data;
	}

	offSet = abs(negativeNum);
	maxData = positiveNum;
	off = offSet; //case wanna use on main?
	positiveNum = positiveNum + off;
	maxDigits = getMaxDigits(positiveNum);
	maxD = maxDigits; //case wanna use on main?
}

void RadixSort::loadStack (ifstream &inFile, ofstream &out, LLStack * top)
{
	int data;
	while(inFile >> data)
	{
		data += offSet;
		listNode node = listNode(data);
		top->push(node);
	}
	cout << "\n*** Below is the constructed Stack ***\n";
	out << "\n*** Below is the constructed Stack ***\n";
	top->printStack();
	top->printStack(out);
	cout << "\n";
}

void RadixSort::dumpStack(LLStack * top, ofstream &out, int curDigit, int curTable)
{
	while(!top->isEmpty())
	{
		listNode temp(top->pop().data);
		hashTable[curTable][getDigit(temp,curDigit)].addTail(temp);
	}

	cout << "\n*** Below are the non-empty Queues ***\n";
	this->printTable(curTable);
	this->printTable(curTable, out);
}

int RadixSort::tableIndex()
{
	return currentQueue;
}

int RadixSort::getMaxDigits(int digit)
{
	stringstream v;
	v << digit;
	return v.str().length();
}

int RadixSort::getDigit(listNode node, int &x)
{
	int y = 0;
	int data = node.data;
	while(y++ < x)
	{
		data = data/10;
	}
	return data % 10;
}

int RadixSort::hashIndex()
{
	return currentDigit;
}

RadixSort::RadixSort()
{
	hashTable = new LLQ * [2];
	currentDigit = 0;
	currentTable = 0;

	for(int i = 0; i < 2; i++)
	{
		hashTable[i] = new LLQ[10];
		for (int j = 0; j < 10; j++)
		{
			hashTable[i][j] = LLQ();
		}
	}
}

void RadixSort::radixSort(LLStack * stack, ofstream &out)
{
	dumpStack(stack, out, currentDigit, currentTable);
	currentDigit++;
	currentTable = 1;
	previousTable = 0;
	currentQueue = 0;

	while (currentDigit < maxDigits)
	{
		while (currentQueue <= tableSize - 1)
		{
			while (!hashTable[previousTable][currentQueue].isEmpty())
			{
				listNode temp = listNode(hashTable[previousTable][currentQueue].deleteHead().data);
				int digit = this->getDigit(temp, currentDigit);
				hashTable[currentTable][digit].addTail(temp);
			}
			currentQueue++;
		}
		this->printTable(currentTable);
		this->printTable(currentTable, out);
		int t = currentTable;
		currentTable = previousTable;
		previousTable = t;
		currentQueue = 0;
		currentDigit++;
	}
}
void RadixSort::printTable(int curTable)
{
	cout << "\n *** Table " << curTable << " ***\n";
	for (int j = 0; j < 10; j++)
		if(!hashTable[curTable][j].isEmpty())
			hashTable[curTable][j].printQueue(j);
}

void RadixSort::printTable(int curTable, ofstream &out)
{
	out << "\n *** Table " << curTable << " ***\n";
	for (int j = 0; j < 10; j++)
		if(!hashTable[curTable][j].isEmpty())
			hashTable[curTable][j].printQueue(j, out);
}

void RadixSort::output(ofstream &outfile, ofstream &debug)
{
	int min = INT_MIN;
	int total = 0;
	int column = 0;
	bool error = false;
	for (int j = 0; j < 10; j++)
	{
		if(!hashTable[previousTable][j].isEmpty())
		{
			while(!hashTable[previousTable][j].isEmpty())
			{
				int data = hashTable[previousTable][j].deleteHead().data;
				data = (offSet == 0) ? data : data - offSet;
				outfile << data << " ";
				total++;

				if (data < min) //validate sort for long files
				{
					cout << "\n\n*** Sorting Failed ***\n"
							<< "\n ** See information on debugging file created ** "  "\n\n";
					cout << "\n\n*** Sorting Failed  because " << data <<
							" was sorted as being less than " << min << "\n";
					debug << "\n\n*** Sorting Failed  because " << data <<
							" was sorted as being less than " << min << "\n";
					error = true;
				}
				min = data;
				if (++column % 20 == 0) // 20 NUMBERS PER COLUMN.
					outfile << "\n";
			}
		}
	}
	int big = maxData + offSet;
	debug << "\n** Processed " << total << " integers **\n"
			<<"\n** Offset:  " << offSet << " **\n"
			<<"\n** Largest Number:  " << maxData << " **\n"
			<<"\n** Largest number plus offSet:  " << (big) << " **\n"
			<<"\n** Largest number plus offSet have:  " << maxDigits << " digits **\n";

	cout << "\n** Processed " << total << " integers **\n"
			<<"\n** Offset:  " << offSet << " **\n"
			<<"\n** Largest Number:  " << maxData << " **\n"
			<<"\n** Largest number plus offSet:  " << (big) << " **\n"
			<<"\n** Largest number plus offSet have:  " << maxDigits << " digits **\n";

	if (error)
	{
		debug << "\n\n***    WARNING: THE SORTING FAILED   ***\n\n";
		cout  << "\n\n***    WARNING: THE SORTING FAILED   ***\n\n";
	}
	else
	{
		debug << "\n\n***    THE SORTING WAS SUCCESSFUL   ***\n\n";
		cout  << "\n\n***    THE SORTING WAS SUCCESSFUL   ***\n\n";
	}
}


