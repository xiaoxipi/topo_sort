#pragma once


#include<iostream>
#include<fstream>
#include"link.h"
#include<string>
using namespace std;

void Run()
{
	fstream infile("course_inf.txt");
	if (!infile)
	{
		cout << "error!" << endl;
		system("pause");
		exit(0);
	}
	char line[100];
	infile.getline(line, 100, '\n');
	while ((line[0] == '/'&&line[1] == '/')||line[0]=='\0'||line[1]=='\0')
	{
		infile.getline(line, 100, '\n');
	}
	int cur = 0;
	int courses[8];
	int all = 0;
	for (int i = 0; i < 8; i++)
	{
		int a = 0;
		a = line[cur] - 48;
		cur++;
		//if (line[cur] == '\t')cur++;
		if (line[cur] >= '0'&&line[cur] <= '9')
		{
			a = a * 10 + line[cur] - 48;
			cur++;
		}
		else
			cur++;
		courses[i] = a;
		all += a;
	}
	char **cour;
	cour = new char*[all];
	for (int i = 0; i < all; i++)
	{
		cour[i] = new char[100];
	}
	infile.getline(line, 100, '\n');
	while ((line[0] == '/'&&line[1] == '/')||line[0]=='\0'||line[1]=='\0')
	{
		infile.getline(line, 100, '\n');
	}
	for (int i = 0; i < 100; i++)
	{
		cour[0][i] = line[i];
	}



	for (int i = 1; i < all; i++)
	{
		infile.getline(cour[i], 100, '\n');
	}
	string* numbercour = new string[all];
	string* namecour = new string[all];
	int* timecour = new int[all];
	int* startcour = new int[all];
	string* pre = new string[all];
	Link* adjcour = new Link[all];
	bool* used = new bool[all];
	int** arrange=new int*[8];
	int *arrangecur = new int[8];
	for (int i = 0; i < 8; i++)arrangecur[i] = 0;
	for (int i = 0; i < 8; i++)
	{
		arrange[i] = new int[courses[i]];
	}
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < courses[i]; j++)
			arrange[i][j] = 0;
	}*/
	for (int i = 0; i < all; i++)used[i] = false;
	for (int i = 0; i < all; i++)
	{
		cur = 0;
		//cour[i][cur]
		while (cour[i][cur] != '\t')
		{
			numbercour[i] += cour[i][cur++];
		}
		adjcour[i].head->course = i;
		while (cour[i][cur] == '\t')cur++;
		while (cour[i][cur] != '\t')
			namecour += cour[i][cur++];
		while (cour[i][cur] == '\t')
			cur++;
		int time = 0;
		time = cour[i][cur] - 48;
		while (cour[i][cur] != '\t')time = time * 10 + cour[i][cur++] - 48;
		timecour[i] = time;
		while (cour[i][cur] == '\t')cur++;
		int start = cour[i][cur] - 48;
		if (start != 0)
		{
			used[i] = true;
			arrange[start-1][arrangecur[start-1]++] = i;
		}
		cur++;
		while (cour[i][cur] == '\t')cur++;
		while (cour[i][cur]!='\0')
		{
			string s;
			int a = 0;
			s += cour[i][cur++];
			while (cour[i][cur] != ' '&& cour[i][cur]!='\0')
			{
				a = a * 10 + cour[i][cur] - 48;
				s += cour[i][cur++];
			}
			if(a!=0)
				adjcour[a-1].Add(i);
			if (cour[i][cur] != '\0')
				cur++;
		} 
	}

	int *getNumber = new int[all];
	for (int i = 0; i < all; i++)
	{
		getNumber[i] = 0;
	}
	for (int i = 0; i < all; i++)
	{
		LinkNode* cur = adjcour[i].head;
		while (cur->next!=NULL)
		{
			getNumber[cur->next->course]++;
			cur = cur->next;
		}
	}
	int term = 0;
	int next = 0;
	int g = 0;
	for (int i = 0; i < 8; i++)next += arrangecur[i];
	bool*now = new bool[all];
	for (int i = 0; i < all; i++)now[i] = true;
	while (next < all)
	{
		if (arrangecur[term] == courses[term])
		{
			term++;
			for (int i = 0; i < all; i++)now[i] = true;
		}
		if (getNumber[g] == 0 && used[g] == false&&now[g]==true)
		{
			arrange[term][arrangecur[term]++] = g;
			next++;
			//adjcour[g]
			LinkNode* cur = adjcour[g].head;
			while (cur->next != NULL)
			{

				getNumber[cur->next->course]--;
				now[cur->next->course] = false;
				cur = cur->next;
			}
		}
		g=(g+1)%all;
	}
	
	for (int i = 0; i < 8; i++)
	{
		cout << i + 1 << ":" << endl;
		for (int j = 0; j < courses[i]; j++)
		{
			cout << 'c'<<arrange[i][j]+1 << " ";
		}
		cout << endl;
	}
}