#pragma once

#include<iostream>
using namespace std;

class LinkNode
{
public:
	int course;
	LinkNode* next;
	LinkNode() { next = NULL; }
};

class Link
{
public:
	LinkNode* head;
	LinkNode* tail;
	Link();
	void Add(int s);
	void Delete(int s);
};
void Link::Add(int s)
{
	tail->next = new LinkNode;
	tail = tail->next;
	tail->course = s;
}
void Link::Delete(int s)
{
	LinkNode* cur = head->next;
	LinkNode* per = head;
	while(cur!=NULL)
	{
		if (cur->course == s)
		{
			per->next = cur->next;
			break;
		}
		per = cur;
		cur = cur->next;
	}
}

Link::Link()
{
	head = new LinkNode;
	tail = head;
}
