#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

template<class T> class MagicBag 
{
public:
	class Node 
	{
	public:
		Node *next;
		T payload;

		Node() 
		{ // Default node constructor 
			next = nullptr;
		}
	};

	/*Defualt constructor*/
	MagicBag() 
	{
		srand((unsigned int)time(NULL)); // Seed the rand() function 
		head = nullptr;
		listSize = 0; 
	}

	/* This will create a new MagicBag using another */
	MagicBag(const MagicBag& other) 
	{
		Node *current;
		// Copy the existing MagicBag
		if (other.head) 
		{
			current = other.head;
			while (current) 
			{
				addGrade(current->payload);
				current = current->next;
			}
		}
	}

	/*This is the copy constructor that makes sure that all of the nodes 
	in the list get copied over correctly*/
	MagicBag& operator=(const MagicBag& other) 
	{
		Node *current;

		// Copy the existing MagicBag
		if (other.head) 
		{
			current = other.head;
			while (current) 
			{
				insert(current->payload);
				current = current->next;
			}
		} 
		return *this; 
		this->~MagicBag(); // Calls the destructor on the node that is getting copied
	}

	/*Destructor*/
	// Needs to start that the head and delete each node in the list 
	~MagicBag() 
	{
		Node *deleteMe; // current
		Node *deleteNext; // next
		if (head) 
		{
			deleteMe = head;
			deleteNext = head->next; 

			delete (deleteMe);

			while (deleteNext)
			{
				deleteMe = deleteNext;
				deleteNext = deleteNext->next;
				delete (deleteMe);
			}
		}
		head = nullptr; // After all nodes have been deleted, nullify the head
	}

	/*Can hold an arbitrary amount of items within the bounds of RAM	*/
	/*Duplicates are allowed											*/
	void insert(T item)
	{
		Node *newItem;
		Node *current;
		newItem = new Node();
		newItem->payload = item;

		if (!head) // if list is empty 
		{
			head = newItem;
			listSize++;
		}
		else {
			current = head;
			while (current->next) 
			{ // Goes to the end of the list and inserts a node at the NULL value 
				current = current->next;
			}
			current->next = newItem;
			listSize++;
		}
	}

	/*Returns a random element from the bag and removes it	*/
	/*The returned item should be randomized				*/
	/*If the bag is empty, should throw an exception		*/
	T draw() 
	{ 
		int randIndex = rand() % listSize; // Makes sure the list is large enough to draw the random index from 
		if (!head) // if you try to draw from an empty bag
		{throw exception();}
				
		if(head)
		{
			Node *current, *previous; 
			current = head;
			previous = nullptr;

			for (int i = 0; i < randIndex; i++) // Will iterate to the random index
			{
				previous = current;
				current = current->next;
			}
			previous->next = current->next; // Keeps the list connected to ensure that the removal of the desired node does not break the list 
			return current->payload; // Returns the data in the node and then deletes it 
			delete (current);
		}
	}

	/*This function checks to see how many instances of a specified item are in the magic bag.		*/
	/*The function will keep count of how many times the specified item appears in the magic bag	*/
	int peek(T item) 
{
		Node *current; 
		current = head;
		int count = 0; 
		while (current) // Iterates until at the final node in the list 
		{
			if (current->payload == item) // Checks to see if the payload of the node is = to the item 
				count++; 
			current = current->next; // continues to iterate through the list 
		}
		return count;
	}
//=============================================================================
	/*Use this print method if MagicBag.cpp uses .print(), otherwise use the 
	overloaded << method.*/
	void print(ostream& os) 
	{
		Node *current;
		if (head == nullptr)
			cout << "Error: The specified MagicBag is empty." << endl;
		else {
			while (current) 
			{
				cout << current->payload << endl;
				current = current->next;
			}
		}
	}
//=============================================================================
private:

	/*This method should print to any ostream you pass to it*/	
	friend ostream& operator<<(ostream& os, const MagicBag& mb) 
	{
		Node *current;
		if (mb.head == nullptr)
			os << "Error: There is nothing in the bag to print." << endl;
		else 
		{
			current = mb.head;
			while (current) 
			{
				os << current->payload << endl;
				current = current->next;
			}
			return os;
		}
	}

	/*Member data for the nodes in the Magicbag*/
	Node *head;
	int listSize; 

};
