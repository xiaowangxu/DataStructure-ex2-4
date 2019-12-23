#ifndef ADJGRAPH_H_INCLUDED
#define ADJGRAPH_H_INCLUDED

#include <iostream>

enum Stats
{
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
private:
	int tag;
	WeightType weight;
	int from_node, to_node;
	ADJArc<NodeType, WeightType> *from_next, *to_next;

public:
	ADJArc();
	ADJArc(const WeightType Weight, const int &FromNode, const int &ToNode, ADJArc<NodeType, WeightType> *FromNext, ADJArc<NodeType, WeightType> *ToNext);
};

template <class NodeType, class WeightType>
ADJArc<NodeType, WeightType>::ADJArc() : tag(0), weight(0), from_node(0), to_node(0), from_next(NULL), to_next(NULL) {}

template <class NodeType, class WeightType>
ADJArc<NodeType, WeightType>::ADJArc(WeightType Weight, const int &FromNode, const int &ToNode, ADJArc<NodeType, WeightType> *FromNext, ADJArc<NodeType, WeightType> *ToNext)
{
	this->tag = 0;
	this->weight = Weight;
	this->from_node = FromNode;
	this->to_node = ToNode;
	this->from_next = FromNext;
	this->to_next = ToNext;
}

// ////////////////////// Node ////////////////////////////////

template <class NodeType, class WeightType>
class ADJNode
{
private:
	NodeType data;
	ADJArc<NodeType, WeightType> *first_arc;

public:
	ADJNode();
	ADJNode(const NodeType &Data, const ADJArc<NodeType, WeightType> *FirstArc);
};

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType>::ADJNode() : data(0), first_arc(NULL) {}

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType>::ADJNode(const NodeType &Data, const ADJArc<NodeType, WeightType> *FirstArc)
{
	this->data = Data;
	this->first_arc = FirstArc;
}

// ////////////////////// Graph ////////////////////////////////

template <class NodeType, class WeightType>
class ADJGraph
{
private:
	int node_count;
	int max_size;
	ADJNode<NodeType, WeightType> *node_array;

public:
	ADJGraph(const int MaxSize);
	Stats add_Node(const NodeType &Data);
	Stats add_Arc(const int FromNode, const int ToNode, const WeightType &Weight);
	void print_Node() const;
};

template <class NodeType, class WeightType>
ADJGraph<NodeType, WeightType>::ADJGraph(int MaxSize)
{
	if (MaxSize <= 0)
	{
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
Stats ADJGraph<NodeType, WeightType>::add_Node(const NodeType &Data)
{
	if (this->node_count >= this->max_size)
	{
		return OVER_RANGE;
	}
	else
	{
		this->node_array[this->node_count].data = Data;
		this->node_count++;
		return SUCCEEDED;
	}
}

template <class NodeType, class WeightType>
Stats ADJGraph<NodeType, WeightType>::add_Arc(int FromNode, int ToNode, const WeightType &Weight)
{
	if (!(FromNode >= 0 && FromNode < this->node_count || FromNode >= 0 && FromNode < this->node_count))
	{
		return INVALID_RANGE;
	}
	if (FromNode == ToNode)
	{
		return INVALID_VAULE;
	}
	int from = FromNode < ToNode ? FromNode : ToNode;
	int to = FromNode > ToNode ? FromNode : ToNode;
	ADJArc<NodeType, WeightType> *new_arc = new ADJArc<NodeType, WeightType>(Weight, from, to, NULL, NULL);
	if (this->node_array[from].first_arc == NULL)
	{
		this->node_array[from].first_arc == new_arc;
	}
	else
	{
		ADJArc<NodeType, WeightType> *p = this->node_array[from].first_arc;
		for (; p->from_next == NULL; p = p->from_next)
			;
		p->from_next = new_arc;
	}
	if (this->node_array[to].first_arc == NULL)
	{
		this->node_array[to].first_arc == new_arc;
	}
	else
	{
		ADJArc<NodeType, WeightType> *p = this->node_array[to].first_arc;
		for (; p->to_next == NULL; p = p->to_next)
			;
		p->to_next = new_arc;
	}
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::print_Node() const
{
	for (int i = 0; i < this->node_count; i++)
	{
		std::cout << this->node_array[i].data << " ";
	}
}

#endif
