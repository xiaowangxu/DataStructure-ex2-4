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
    cout << "\nHello world!" << endl;
    return 0;
}
