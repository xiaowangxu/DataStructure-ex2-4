/*
 * @Date         : 2019-12-23 13:16:53
 * @Author       : ssyze sun
 * @Description  :
 */
#include "ADJGraph.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{
	/*ADJGraph<char, double> TEST(100);
	TEST.add_Node('A');
	TEST.add_Node('B');
	TEST.add_Node('C');
	TEST.add_Node('D');
	TEST.print_Node();
	TEST.add_Arc(0, 1, 1.0);
	TEST.add_Arc(0, 2, 1.0);
	TEST.add_Arc(0, 3, 1.0);
	TEST.add_Arc(1, 2, 1.0);
	TEST.add_Arc(1, 3, 1.0);
	TEST.add_Arc(2, 3, 1.0);

	cout << '\n';
	cout << TEST.simple_path(0, 1, 2);
	cout << '\n';
	cout << '\n';
	TEST.print_Graph();
	cout << '\n';
	//TEST.add_Node('C');
	//TEST.print_Graph();
	TEST.delete_Arc(0, 1);
	TEST.print_Graph();
	cout << '\n';
	TEST.delete_Node(0);
	TEST.delete_Node(1);
	TEST.print_Graph();
	cout << "\nHello world!" << endl; */

	ADJGraph<char, double> Graph(100);

	fstream test;
	test.open("test.txt");

	int Count;

	// Add Node
	string title;
	while (test >> title)
	{
		cout << "--- TEST CASE : " << title << " ---" << endl
			 << endl;
		test >> Count;
		cout << "Add Node :";
		for (int i = 0; i < Count; i++)
		{
			char Node;
			test >> Node;
			cout << " " << Node;
			Graph.add_Node(Node);
		}
		cout << endl
			 << "\nResult: " << endl;
		Graph.print_Graph();
		cout << endl;
		system("PAUSE");
		system("CLS");

		// Add Arc
		cout << "--- TEST CASE : " << title << " ---" << endl
			 << endl;
		cout << "Add Arc" << endl
			 << endl;
		test >> Count;
		for (int i = 0; i < Count; i++)
		{
			char from, to;
			test >> from >> to;
			int fromorder = Graph.get_NodeOrder(from), toorder = Graph.get_NodeOrder(to), weight;
			test >> weight;
			cout << ">> connect " << from << " to " << to << " with weight of " << weight << endl
				 << endl;
			Graph.add_Arc(fromorder, toorder, weight);
			Graph.print_NodeConnect(fromorder);
			cout << endl;
			Graph.print_NodeConnect(toorder);
			cout << endl
				 << endl;
		}

		cout << "Result: " << endl;
		Graph.print_Graph();
		cout << endl;
		system("PAUSE");
		system("CLS");

		// Test Connection
		cout << "--- TEST CASE : " << title << " ---" << endl
			 << endl;
		cout << "Test Connection" << endl
			 << endl;
		for (int i = 0; i < Graph.get_NodeCount(); i++)
		{
			cout << "(" << i << ")\t" << Graph.get_NodeData(i) << " -> ";
			int last = Graph.get_FirstNode(i);
			int next;
			while (last != -1)
			{
				// cout << "{" << last << "}";
				cout << Graph.get_NodeData(last) << "[" << last << "]  "
					 << " ";
				last = Graph.get_NextNode(i, last);
				// cout << "{" << last << "}";
			}
			cout << endl
				 << endl;
		}

		cout << endl;
		system("PAUSE");
		system("CLS");

		// Delete Node
		test >> Count;
		cout << "--- TEST CASE : " << title << " ---" << endl
			 << endl;
		cout << "Delete Node :";
		for (int i = 0; i < Count; i++)
		{
			char Node;
			test >> Node;
			cout << " " << Node;
			Graph.delete_Node(Graph.get_NodeOrder(Node));
		}
		cout << endl
			 << "\nResult: " << endl;
		Graph.print_Graph();
		cout << endl;
		system("PAUSE");
		system("CLS");

		// Delete Arc
		cout << "--- TEST CASE : " << title << " ---" << endl
			 << endl;
		cout << "Delete Arc" << endl
			 << endl
			 << "Original Graph"
			 << endl;
		Graph.print_Graph();
		cout << endl;
		test >> Count;
		for (int i = 0; i < Count; i++)
		{
			int fromorder, toorder;
			test >> fromorder >> toorder;
			cout << ">> disconnect " << Graph.get_NodeData(fromorder) << " with " << Graph.get_NodeData(toorder) << endl
				 << endl;
			Graph.delete_Arc(fromorder, toorder);
			Graph.print_NodeConnect(fromorder);
			cout << endl;
			Graph.print_NodeConnect(toorder);
			cout << endl
				 << endl;
		}

		cout << "Result: " << endl;
		Graph.print_Graph();
		cout << endl;
		system("PAUSE");
		system("CLS");

		// Simple Path
		cout << "--- TEST CASE : " << title << " ---" << endl
			 << endl;
		cout << "Simple Path" << endl
			 << endl
			 << "Original Graph"
			 << endl;
		Graph.print_Graph();
		cout << endl;
		int *array = new int[Graph.get_NodeCount()];
		for (int i = 0; i < Graph.get_NodeCount(); i++)
		{
			for (int j = i + 1; j < Graph.get_NodeCount(); j++)
			{
				cout << "\t" << Graph.get_NodeData(i) << " to " << Graph.get_NodeData(j) << endl;
				for (int l = 1; l < Graph.get_NodeCount() - 1; l++)
				{
					array[l - 1] = Graph.simple_path(i, j, l);
				}
				cout << "Len\t";
				for (int l = 1; l < Graph.get_NodeCount() - 1; l++)
				{
					cout << l << "\t";
				}
				cout << "\nCount\t";
				for (int l = 1; l < Graph.get_NodeCount() - 1; l++)
				{
					cout << array[l - 1] << "\t";
				}
				cout << endl
					 << endl;
			}
		}
		delete[] array;
		cout << endl;
		system("PAUSE");
		system("CLS");

		cout << "--- TEST CASE : " << title << " ---" << endl
			 << endl;
		cout << "Clear Graph" << endl
			 << endl;
		Graph.clear();
		Graph.print_Graph();
		cout << endl;
		system("PAUSE");
		system("CLS");
	}

	return 0;
}
