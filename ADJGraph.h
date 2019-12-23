#ifndef ADJGRAPH_H_INCLUDED
#define ADJGRAPH_H_INCLUDED

#include <iostream>
using namespace std;

enum Stats {
    SUCCEEDED,
    FAILED,
    OVER_RANGE,
    INVALID_RANGE,
    INVALID_VAULE
};

// ////////////////////// Arc ////////////////////////////////

template <class NodeType, class WeightType>
class ADJArc
{
public:
	int tag;
	WeightType weight;
	int from_node, to_node;
	ADJArc<NodeType, WeightType> *from_next, *to_next;

public:
    ADJArc();
    ADJArc(const WeightType Weight, const int& FromNode, const int& ToNode, ADJArc<NodeType, WeightType>* FromNext, ADJArc<NodeType, WeightType>* ToNext);
    int get_Num(int u) const; //返回在边的哪个节点上
};

template <class NodeType, class WeightType>
ADJArc<NodeType, WeightType>::ADJArc()
    : tag(0)
    , weight(0)
    , from_node(0)
    , to_node(0)
    , from_next(NULL)
    , to_next(NULL)
{
}

template <class NodeType, class WeightType>
ADJArc<NodeType, WeightType>::ADJArc(WeightType Weight, const int& FromNode, const int& ToNode, ADJArc<NodeType, WeightType>* FromNext, ADJArc<NodeType, WeightType>* ToNext)
{
    this->tag = 0;
    this->weight = Weight;
    this->from_node = FromNode;
    this->to_node = ToNode;
    this->from_next = FromNext;
    this->to_next = ToNext;
}

template <class NodeType, class WeightType>
int ADJArc<NodeType, WeightType>::get_Num(int u) const
{
    if (from_node == u)
        return 1;
    else
        return 2;
}

// ////////////////////// Node ////////////////////////////////

template <class NodeType, class WeightType>
class ADJNode
{
public:
	bool tag;
	NodeType data;
	ADJArc<NodeType, WeightType> *first_arc;

public:
    ADJNode();
    ADJNode(const NodeType& Data, const ADJArc<NodeType, WeightType>* FirstArc);
};

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType>::ADJNode() : tag(0), data(0), first_arc(NULL) {}

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType>::ADJNode(const NodeType& Data, const ADJArc<NodeType, WeightType>* FirstArc)
{
	this->tag = 0;
	this->data = Data;
	this->first_arc = FirstArc;
}

// ////////////////////// Graph ////////////////////////////////

template <class NodeType, class WeightType>
class ADJGraph {
private:
	int node_count;
	int max_size;
	ADJNode<NodeType, WeightType> *node_array;
	int simple_path(const int &st, const int &ed, int u, int len, int l);

public:
	ADJGraph(const int MaxSize);
	Stats add_Node(const NodeType &Data);
	Stats add_Arc(const int FromNode, const int ToNode, const WeightType &Weight);
	ADJNode<NodeType, WeightType>* get_Nodeptr(const int &node);
	int simple_path(const int &st, const int &ed, int len);
	void print_Node() const;
    void print_Graph() const;
};

template <class NodeType, class WeightType>
ADJGraph<NodeType, WeightType>::ADJGraph(int MaxSize)
{
    if (MaxSize <= 0) {
        this->node_array = NULL;
        this->node_count = 0;
        this->max_size = 0;
        return;
    }
    this->max_size = MaxSize;
    this->node_array = new ADJNode<NodeType, WeightType>[this->max_size];
    this->node_count = 0;
}

template <class NodeType, class WeightType>
Stats ADJGraph<NodeType, WeightType>::add_Node(const NodeType& Data)
{
    if (this->node_count >= this->max_size) {
        return OVER_RANGE;
    }
    else {
        this->node_array[this->node_count].data = Data;
        this->node_count++;
        return SUCCEEDED;
    }
}

template <class NodeType, class WeightType>
Stats ADJGraph<NodeType, WeightType>::add_Arc(int FromNode, int ToNode, const WeightType& Weight)
{
    if (!(FromNode >= 0 && FromNode < this->node_count || FromNode >= 0 && FromNode < this->node_count)) {
        return INVALID_RANGE;
    }
    if (FromNode == ToNode) {
        return INVALID_VAULE;
    }
    int from = FromNode < ToNode ? FromNode : ToNode;
    int to = FromNode > ToNode ? FromNode : ToNode;
    ADJArc<NodeType, WeightType>* new_arc = new ADJArc<NodeType, WeightType>(Weight, from, to, NULL, NULL);
    if (this->node_array[from].first_arc == NULL) {
        this->node_array[from].first_arc = new_arc;
    }
    else {
        ADJArc<NodeType, WeightType>* p = this->node_array[from].first_arc;
        for (; p->from_next == NULL; p = p->from_next)
            ;
        p->from_next = new_arc;
    }
    if (this->node_array[to].first_arc == NULL) {
        this->node_array[to].first_arc = new_arc;
    }
    else {
        ADJArc<NodeType, WeightType>* p = this->node_array[to].first_arc;
        for (; p->to_next == NULL; p = p->to_next)
            ;
        p->to_next = new_arc;
    }
}

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType>* ADJGraph<NodeType,WeightType>::get_Nodeptr(const int &node){
	if(node >= node_count) throw OVER_RANGE;
	return node_array+node; 
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::print_Node() const
{
    for (int i = 0; i < this->node_count; i++) {
        std::cout << this->node_array[i].data << " ";
    }
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::print_Graph() const
{
    for (int i = 0; i < node_count; i++) {
        cout << node_array[i].data << " ->";
        ADJArc<NodeType, WeightType>* tmp = node_array[i].first_arc;
        //ADJArc<NodeType, WeightType>* p;
        while (tmp) {
            int num = tmp->get_Num(i);
            int to;
            if (num == 1)
                to = tmp->to_node;
            else
                to = tmp->from_node;
            cout << node_array[to].data << " ->";
            if (num == 1)
                tmp = tmp->from_next;
            else
                tmp = tmp->to_next;
        }
        cout << "*" << endl;
    }
}

template<class NodeType, class WeightType>
int ADJGraph<NodeType, WeightType>::simple_path(const int &st, const int &ed, int u, int len, int l)
{
	if(l==len){
		return u == ed;
	}
	int _cnt = 0;
	ADJNode<NodeType,WeightType> *node_u = get_Nodeptr(u);
	ADJArc<NodeType,WeightType> EDGE = node_u->first_arc;
	while (EDGE!=NULL)
	{
		int v = 0;
		if(EDGE->from_node==u) v = EDGE->to_node,EDGE = EDGE->from_next;
		else v = EDGE->from_node,EDGE = EDGE->to_next;
		ADJNode<NodeType,WeightType> *node_v = get_Nodeptr(v);
		if(node_v->tag==0){
			node_v->tag=1;
			_cnt += simple_path(st,ed,v,len,l+1);
			node_v->tag=0;
		}
	}
	return _cnt;
}

template<class NodeType, class WeightType>
int ADJGraph<NodeType, WeightType>::simple_path(const int &st, const int &ed, int len)
{
	return simple_path(st,ed,st,len,0);
}

#endif
