#include <iostream>
#include "ADJGraph.h"

using namespace std;

int main()
{
	ADJGraph<char, double> TEST(100);
	TEST.add_Node('A');
	TEST.add_Node('B');
	TEST.print_Node();
	TEST.add_Arc(0, 1, 1.0);
	cout << "\nHello world!" << endl;
	return 0;
}
