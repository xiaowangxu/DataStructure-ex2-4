/*
 * @Date         : 2019-12-23 13:16:53
 * @Author       : ssyze
 * @Description  : 
 */
#include "ADJGraph.h"
#include <iostream>

using namespace std;

int main()
{
    ADJGraph<char, double> TEST(100);
    TEST.add_Node('A');
    TEST.add_Node('B');
    TEST.print_Node();
    TEST.add_Arc(0, 1, 1.0);
    cout << '\n';
    TEST.print_Graph();
    TEST.add_Node('C');
    TEST.print_Graph();
    cout << "\nHello world!" << endl;
    return 0;
}
