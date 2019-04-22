//
///***********************************************************************
// * Vagner Machado QCID 23651127
// * Project 2
// * Professor Tsaiyun Phillips
// * Queens College - Spring 2019
// ***********************************************************************/
//
//using namespace std;
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//
///**
// * listNode class declaration
// */
//class listNode
//{
//	friend class RadixSort;
//	friend class LLQ;
//	friend class LLStack;
//private:
//	listNode* next;
//public:
//	int data;
//	listNode();
//	listNode(int z);
//
//};
//
///**
// * LLStack class declaration
// */
//class LLStack
//{
//private:
//	listNode * top;
//public:
//	LLStack();
//	void push(listNode newNode);
//	listNode pop();
//	bool isEmpty();
//	void printS();
//};
//
///**
// * LLQ class declaration
// */
//class LLQ
//{
//private:
//	listNode * head;
//	listNode * tail;
//public:
//	LLQ();
//	void addQ(listNode x);
//	listNode deleteQ();
//	bool isEmpty();
//	void printQ();
//};
//
///************* AUXILIARY METHODS FOR MAIN *********************/
//
//void printTable(LLQ ** x)
//{
//	for(int i = 0; i < 10; i++)
//	{
//		cout << "\n";
//		cout << "|" << i << "|";
//		x[i]->printQ();
//	}
//}
//
//void getInput(LLStack &theStack, ifstream &infile, bool &hasNegative,
//		int &longestPositive, int &longestNegative)
//{
//	while(!infile.eof())
//	{
//		int x;
//		infile >> x;
//		if (x < 0 && hasNegative == false)
//		{
//			hasNegative = true;
//		}
//		if(hasNegative == true)
//		{
//			if( x < longestNegative)
//				longestNegative = x;
//		}
//
//		if(x > longestPositive)
//			longestPositive = x;
//
//		theStack.push(listNode(x));
//	}
//}
//
//string itos(int x)
//{
//	stringstream v;
//	v << x;
//	return v.str();
//}
//
///**
// * main method - Enables the user to use a stack or a queue
// * to insert and delete integers. Input is provided by the user
// * using the console keyboard
// */
//int main(int argc, char *argv[])
//{
//	cout << "\n\n*** Welcome to Vagner's Project 2 ***\n\n";
//
//	LLStack theStack;
//	bool hasNegative = false;
//	int longestNegative = 0;
//	int longestPositive = 0;
//	ifstream infile;
//	infile.open("input");
//
//	getInput(theStack, infile, hasNegative, longestPositive, longestNegative);
//	theStack.printS();
//
//	cout << "pos" << longestPositive
//			<< "\nneg" << longestNegative;
//
//	LLQ ** theTableA = new LLQ * [10];
//	for(int i = 0; i < 10; i++)
//		theTableA[i] = new LLQ();
//
//	LLQ ** theTableB = new LLQ * [10];
//	for(int i = 0; i < 10; i++)
//		theTableB[i] = new LLQ();
//
//	bool tableA = true;
//
//
//	switch (hasNegative)
//	{
//	case true:
//	{
//		cout << " has negative";
//		break;
//	}
//	case false:
//	{
//		int len = itos(longestPositive).length();
//		cout << "has positive";
//		for(int i = 0; i < len; i++)
//		{
//			if (tableA == true)
//			{
//				for(int j = 0; j < 10; j++)
//				{
//					if(theTableA[j] != NULL && !theTableA[j]->isEmpty())
//					{
//						int full = theTableA[j]->deleteQ().data;
//						int fullCopy = full;
//						int loop = i;
//						int count = 0;
//						while(count < loop)
//						{
//							full = full/10;
//							count++;
//						}
//						int place = full % 10;
//						theTableB[place]->addQ(fullCopy);
//					}
//				}
//				tableA =false;
//			}
//			else
//			{
//				for(int j = 0; j < 10; j++)
//				{
//					if(theTableB[j] != NULL && !theTableB[j]->isEmpty())
//					{
//						int full = theTableB[j]->deleteQ().data;
//						int fullCopy = full;
//						int loop = i;
//						int count = 0;
//						while(count < loop)
//						{
//							full = full/10;
//							count++;
//						}
//						int place = full % 10;
//						theTableA[place]->addQ(fullCopy);
//					}
//				}
//				tableA = true;
//			}
//		}
//		break;
//	}
//
//	}
//	/*
//		//choose stack or queue
//		cout<< "Please enter one of the following characters:\n" <<
//				"S to use a Stack\n"
//				"Q to use a Queue\n";
//		char structure= '$';
//		cin >> structure;
//		while(structure != 'S' && structure != 'Q')
//		{
//			cout << "\n*** Invalid choice ***\n" <<
//					"Please enter one of the following characters:\n" <<
//					"S to use a Stack\n" <<
//					"Q to use a Queue\n";
//			cin >> structure;
//		}
//		char choice = '$';
//		int value;
//		char loopInStruct = '$';
//		switch (structure)
//		{
//		//stack choice
//		case 'S':
//		{
//			cout << "\n** You chose to use a Stack **\n";
//			LLStack theStack;
//			//choose to insert or delete
//			while(loopInStruct != 'N')
//			{
//				cout << "\nPlease enter one of the following characters:\n" <<
//						"I to insert value to Stack\n" <<
//						"D to delete value from the Stack\n";
//				cin >> choice;
//				while(choice != 'I' && choice != 'D')
//				{
//					cout << "\n*** Invalid choice ***\n" <<
//							"\nPlease enter one of the following characters:\n" <<
//							"I to insert value to the Stack\n" <<
//							"D to delete value from the Stack\n";
//					cin >> choice;
//				}
//				if (choice == 'D')
//				{
//					//chose to delete
//					cout << "\n** Popping from Stack **\n";
//					if(theStack.isEmpty())
//						cout << "\nCannot delete: the Stack is Empty!\n";
//					else
//					{
//						listNode temp = theStack.pop();
//						cout << "\nValue deleted: " << temp.data << "\n";
//					}
//				}
//				//choose to insert
//				else
//				{
//					//integer input
//					cout << "\n** Pushing to Stack **\n";
//					cout  << "\nEnter integer to push to Stack:\n";
//					cin >> value;
//					cout << "\n** Pushing " << value << " to Stack **\n";
//					listNode temp = listNode(value);
//					theStack.push(temp);
//				}
//				//print stack after action
//				cout << "\n** Stack after performing the operation **\n";
//				theStack.printS();
//				//loop
//				cout << "\nWould you like to continue using the Stack? Enter:\n" <<
//						"Y to continue using the Stack\n" <<
//						"N to stop using the Stack\n";
//				cin >> loopInStruct;
//				while(loopInStruct != 'Y' && loopInStruct != 'N')
//				{
//					cout << "\n*** Invalid choice ***\n" <<
//							"\nWould you like to continue using the Stack? Enter:\n" <<
//							"Y to continue using the Stack\n" <<
//							"N to stop using the Stack\n";
//					cin >> loopInStruct;
//				}
//
//				if(loopInStruct == 'Y')
//					cout << "\n** You chose YES, let's continue **\n";
//				else
//					cout << "\n** You chose NO, application closing **\n";
//			}
//		}
//		break;
//		//queue choice
//		case 'Q':
//		{
//			cout << "\n** You chose to use a Queue **\n";
//			LLQ theQueue;
//			//insert or delete
//			while(loopInStruct != 'N')
//			{
//				cout << "\nPlease enter one of the following characters:\n" <<
//						"I to insert value to the Queue\n" <<
//						"D to delete value from the Queue\n";
//				cin >> choice;
//				while(choice != 'I' && choice != 'D')
//				{
//					cout << "\n*** Invalid choice ***\n" <<
//							"\nPlease enter one of the following characters:\n" <<
//							"I to insert value onto the Queue\n" <<
//							"D to delete value from the Queue\n";
//					cin >> choice;
//				}
//				//chose delete
//				if (choice == 'D')
//				{
//					cout << "\n** Dequeuing from Queue **\n";
//					if(theQueue.isEmpty())
//						cout << "\nCannot delete: the Queue is Empty!\n";
//					else
//					{
//						listNode temp = theQueue.deleteQ();
//						cout << "\nValue deleted: " << temp.data << "\n";
//					}
//				}
//				//chose insert
//				else
//				{
//					//input
//					cout << "\n** Enqueuing to Queue **\n";
//					cout  << "\nEnter integer to enqueue to Queue:\n";
//					cin >> value;
//					cout << "\n** Enqueuing " << value << " to Queue **\n";
//					listNode temp = listNode(value);
//					theQueue.addQ(temp);
//				}
//				cout << "\n** Queue after performing the operation **\n";
//				theQueue.printQ();
//				//loop in queue
//				cout << "\nWould you like to continue using the Queue? Enter:\n" <<
//						"Y to continue using the Queue\n" <<
//						"N to stop using the Queue\n";
//				cin >> loopInStruct;
//				while(loopInStruct != 'Y' && loopInStruct != 'N')
//				{
//					cout << "\n*** Invalid choice ***\n" <<
//							"\nWould you like to continue using the Queue? Enter:\n" <<
//							"Y to continue using the Queue\n" <<
//							"N to stop using the Queue\n";
//					cin >> loopInStruct;
//				}
//				if(loopInStruct == 'Y')
//					cout << "\n** You chose YES, let's continue **\n";
//				else
//					cout << "\n** You chose NO, application closing **\n";
//			}
//		}
//		break;
//		}
//		cout << "\n** Good Bye **\n";*/
//
//}
//
//listNode::listNode(int x)
//{
//	data = x;
//	next = NULL;
//}
//
//listNode::listNode()
//{
//	data = 0;
//	next = NULL;
//}
//
//LLStack::LLStack()
//{
//	top = NULL;
//}
//
//void LLStack::push(listNode newNode)
//{
//	listNode * temp = new listNode(newNode.data);
//	if(top != NULL)
//	{
//		temp->next = top;
//		top = temp;
//	}
//	else
//		top = temp;
//}
//
//listNode LLStack::pop()
//{
//	listNode a(top->data);
//	top = top->next;
//	return a;
//}
//
//bool LLStack::isEmpty()
//{
//	return top == NULL;
//}
//
//void LLStack::printS()
//{
//	listNode * x = top;
//	cout << "\n**Printing Stack**\n" <<
//			"(top) ";
//	while (x != NULL)
//	{
//		cout << x->data << " -> ";
//		x = x-> next;
//	}
//	cout << " (bottom)\n";
//}
//
//LLQ::LLQ()
//{
//	listNode * dum = new listNode(9999);
//	head = dum;
//	tail = dum;
//}
//
//void LLQ::addQ(listNode x)
//{
//	listNode * temp = new listNode(x.data);
//	tail->next = temp;
//	tail = temp;
//}
//
//listNode LLQ::deleteQ()
//{
//	if(head != tail)
//	{
//		listNode a (head->next->data);
//		if(head->next->next != NULL)
//			head->next = head->next->next;
//		else
//		{
//			head->next = NULL;
//			tail = head;
//		}
//		return a;
//	}
//	else
//		return listNode(head->data);
//}
//
//bool LLQ::isEmpty()
//{
//	return head == tail;
//}
//
//void LLQ::printQ()
//{
//	listNode * f  = head;
//	//cout << "\n**Printing Queue**\n(front) ";
//	while (f != NULL)
//	{
//		cout << f->data << " -> ";
//		f = f->next;
//	}
//	//cout << " (back)\n";
//}
