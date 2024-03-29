// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_VALUES   4
#define NUM_OF_OPERATIONS   4
#define MAX_NUM_OF_OPERATIONS 16

typedef unsigned char uint8;


struct InstanceData {
	int u8Num1;
	int u8Num2;
	int u8Operation;
	struct InstanceData* next;
};

typedef struct InstanceData stInstanceData;

struct nodedata {
	int u8Number; //Number 
	int u8InstanceCount; // Instances of number through other combinations
	stInstanceData* pstInstanceData; // 
	struct nodedata* next; //next node
};

typedef struct nodedata node;
static node* head = NULL;
static node* tail = NULL;

// Static function to create node with a number
static node* pstCreateNode(uint8 u8Number)
{
	node* pstNode = (node *)malloc(sizeof(node));
	pstNode->u8Number = u8Number;
	pstNode->u8InstanceCount = 0;
	pstNode->pstInstanceData = NULL;
	pstNode->next = NULL;

	return pstNode;
}

// Check if the number is part of the list 
// return 0 if No, 1 if True
static int iCheckIfPresentInList(int num)
{
	int count = 0;
	int ret = 0xFFFFFFFF;
	node* it;
	if (head != NULL)
	{
		it = head;
		while (it != NULL)
		{
			if (it->u8Number == num)
			{
				ret = count;
				break;
			}
			it = it->next;
			count++;
		}
	}
	return ret;
}
// function to print the list of nodes
static void printNodeList(void)
{
	printf("Printing Node list \n");
	// iterate through the nodes and print the number and instance count
	node* it = head;
	while (it != NULL)
	{
		printf("\nNumber is %d\n", it->u8Number);
		printf("Instances = %d\n", it->u8InstanceCount);
		it = it->next;
	}
}

// Function to add instance of a number
void addInstance(int ioffset, int inum1, int inum2, int iOperation)
{
	node* it = head;
	stInstanceData* itInst;
	stInstanceData* pstInstance;
	int instCount;
	// use offset to to get to the node
	while (ioffset)
	{
		it = it->next;
		ioffset--;
	} 

	//create instance
	pstInstance = (stInstanceData *) malloc(sizeof(stInstanceData));

	// enter data in the instance
	pstInstance->u8Num1 = inum1;
	pstInstance->u8Num2 = inum2;
	pstInstance->u8Operation = iOperation;
	pstInstance->next = NULL;

	// link the new instance to the instance list
	instCount = it->u8InstanceCount;
	
	// if there is no instance present then add instance to the number node

	// iterate to the last instance and add the new one to the list
	itInst = it->pstInstanceData;
	while (--instCount)
	{
		itInst = itInst->next;
		//instCount--;
	}
	itInst->next = pstInstance;

	// Increment the instance count at the end
	it->u8InstanceCount++;
	
}
static void addFirstInstance(node* tail, int inum1, int inum2, int iOperation)
{
	stInstanceData* pstInstance;

	pstInstance = (stInstanceData *)malloc(sizeof(stInstanceData));

	// enter data in the instance
	pstInstance->u8Num1 = inum1;
	pstInstance->u8Num2 = inum2;
	pstInstance->u8Operation = iOperation;
	pstInstance->next = NULL;

	tail->u8InstanceCount++;
	tail->pstInstanceData = pstInstance;
}
static void printNodeDetails(void)
{

}
static void PrintOutput(void)
{
	int iReqNumber = 10;
	node *it;
	stInstanceData *itInst;
	char op[4] = { '+','-','*','/' };

	it = head;

	while ((it != NULL) && (it->u8Number != iReqNumber))
	{
		it = it->next;
	}

	if (it != NULL)
	{
		printf("Number = %d \n", it->u8Number);
		itInst = it->pstInstanceData;

		while (itInst != NULL)
		{
			printf("Num1 = %d  %c  Num2 = %d \n", itInst->u8Num1, op[itInst->u8Operation-1], itInst->u8Num2);
			itInst = itInst->next;
		}

	}
}
int main()
{
	uint8 idx;
	int i, j, temp, num1, num2, result; // temporary variables and counters
	int aiArrayOfInput[NUM_OF_VALUES]; // store the input values
	int iMaxNumber, iReqNumber = 10;
	node *pstNode, *it, *it2;
	// Enter the four numbers that are required
	printf("Enter the four numbers \n ");
	for (i = 0; i < NUM_OF_VALUES; i++)
	{
		scanf("%d", &aiArrayOfInput[i]);
	}

	printf("test \n");
	for (i = 0; i < NUM_OF_VALUES; i++)
		printf("%d \t", aiArrayOfInput[i]);

	printf("\n");
	// sort the array
	for (i = 0; i < NUM_OF_VALUES; i++)
	{
		for (j = 0; j < NUM_OF_VALUES; j++)
		{
			if ((i != j) && (aiArrayOfInput[i] == aiArrayOfInput[j])) {
				printf("Values are repeated, should be unique. Quitting!!");
				return 0;
			}

			if ((aiArrayOfInput[i]) < aiArrayOfInput[j])
			{
				int temp;
				temp = aiArrayOfInput[i];
				aiArrayOfInput[i] = aiArrayOfInput[j];
				aiArrayOfInput[j] = temp;
			}
		}
	}

	printf("sorted values \n");
	for (i = 0; i < NUM_OF_VALUES; i++)
		printf("%d \t", aiArrayOfInput[i]);

	printf("\n");
	// create a node 
	head = pstCreateNode(aiArrayOfInput[0]);
	addFirstInstance(head, 0, 0, -1);
	tail = head;
	
	// create a node for the main set of numbers
	for(i = 1; i < NUM_OF_VALUES; i++)
	{
		// create a node
		pstNode = pstCreateNode(aiArrayOfInput[i]);
		tail->next = pstNode;
		// updating tail to new Node
		tail = pstNode;
		addFirstInstance(tail, 0, 0, -1);
	}
	
	// print the Node details
	printNodeList();
	
	// create the combination of the products
	// the 
	for (i = 0; i < NUM_OF_VALUES; i++)
	{
		for (j = i + 1; j < NUM_OF_VALUES; j++)
		{
			int num = aiArrayOfInput[i] * aiArrayOfInput[j];
			//check if the new number if part of the list
			int inList = iCheckIfPresentInList(num);
			// if already part of the list then add an entry for the Instance
			if (inList != 0xFFFFFFFF)
			{
				// addInstance
				// addInstance(inList, aiArrayOfInput[i], aiArrayOfInput[j], 3);
				addInstance(inList, aiArrayOfInput[i], aiArrayOfInput[j], 3);
			}
			// else create a new node
			else
			{
				pstNode = pstCreateNode(num);
				tail->next = pstNode;
				tail = pstNode;
				addFirstInstance(tail, aiArrayOfInput[i], aiArrayOfInput[j], 3);
			}
		}
	}

	// printing node list after multiplication
	printNodeList();

	// need to one more loop of division before
	// now the more difficult part is to create the instances of division
	// will need to iterate through the list in a double for loop
	// to get multiple combinations
	
	// iterate through the input array as only that can possibly divide
	// the product part achieved earlier will be bigger so cannot divide 
	it = head;
	for (i = 0; i < NUM_OF_VALUES; i++)
	{
		int num = aiArrayOfInput[i];

		// iterating through the nodes
		while (it != NULL)
		{
			// retrieve the number
			temp = it->u8Number;
			// divide only if divisible
			if ((temp % num == 0) && (temp != num))
			{
				result = temp / num;
				//check if the new number if part of the list
				int inList = iCheckIfPresentInList(result);
				// if already part of the list then add an entry for the Instance
				if (inList != 0xFFFFFFFF)
				{
					// addInstance
					// addInstance(inList, aiArrayOfInput[i], aiArrayOfInput[j], 3);
					addInstance(inList, temp, num, 4);
				}
				// else create a new node
				else
				{
					pstNode = pstCreateNode(result);
					tail->next = pstNode;
					tail = pstNode;
					addFirstInstance(tail, temp, num, 4);
				}
			}
			it = it->next;
		}
	}
	// printing node list after division
	printNodeList();

	// performing addition and subtraction
	// iterate through the list and perform the addition or subtraction
	iMaxNumber = aiArrayOfInput[NUM_OF_VALUES - 1] + iReqNumber;
	it = head;
	while (it != NULL)
	{
		it2 = head;
		num1 = it->u8Number;
		while (it2 != NULL)
		{
			num2 = it2->u8Number;
			if (num1 != num2)
			{
				result = num1 + num2;
				if (result < iMaxNumber)
				{
					//check if the new number if part of the list
					int inList = iCheckIfPresentInList(result);
					// if already part of the list then add an entry for the Instance
					if (inList != 0xFFFFFFFF)
					{
						// addInstance
						// addInstance(inList, aiArrayOfInput[i], aiArrayOfInput[j], 3);
						addInstance(inList, num1, num2, 1);
					}
					// else create a new node
					else
					{
						pstNode = pstCreateNode(result);
						tail->next = pstNode;
						tail = pstNode;
						addFirstInstance(tail, num1, num2, 1);
					}
				}
			}
			it2 = it2->next;
		}
		it = it->next;
	}
	// printing node list after division
	printNodeList();

	it = head;
	while (it != NULL)
	{
		it2 = head;
		num1 = it->u8Number;
		while (it2 != NULL)
		{
			num2 = it2->u8Number;
			if (num1 != num2)
			{
				result = num1 - num2;
				if (result == iReqNumber) // only checking if ten occurs
				{ 
					//check if the new number if part of the list
					int inList = iCheckIfPresentInList(result);
					// if already part of the list then add an entry for the Instance
					if (inList != 0xFFFFFFFF)
					{
						// addInstance
						// addInstance(inList, aiArrayOfInput[i], aiArrayOfInput[j], 3);
						addInstance(inList, num1, num2, 2);
					}
					// else create a new node
					else
					{
						pstNode = pstCreateNode(result);
						tail->next = pstNode;
						tail = pstNode;
						addFirstInstance(tail, num1, num2, 2);
					}
				}
			}
			it2 = it2->next;
		}
		it = it->next;
	}

	// printing node list after division
	printNodeList();

	PrintOutput();

	return 0;
}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
