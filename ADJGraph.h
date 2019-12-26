#ifndef ADJGRAPH_H_INCLUDED
#define ADJGRAPH_H_INCLUDED

#include <iostream>
#include <iomanip>
using namespace std;

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
public:
	int tag;
	WeightType weight;
	int from_node, to_node;
	ADJArc<NodeType, WeightType> *from_next, *to_next;

public:
	ADJArc();
	ADJArc(const WeightType Weight, const int &FromNode, const int &ToNode, ADJArc<NodeType, WeightType> *FromNext, ADJArc<NodeType, WeightType> *ToNext);
	int get_Num(int u) const; //返回在边的哪个节点上
};

template <class NodeType, class WeightType>
ADJArc<NodeType, WeightType>::ADJArc()
	: tag(0), weight(0), from_node(0), to_node(0), from_next(NULL), to_next(NULL)
{
}

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
	ADJNode(const NodeType &Data, ADJArc<NodeType, WeightType> *FirstArc);
};

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType>::ADJNode()
	: tag(0), data(0), first_arc(NULL)
{
}

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType>::ADJNode(const NodeType &Data, ADJArc<NodeType, WeightType> *FirstArc)
{
	this->tag = 0;
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
	int simple_path(const int &st, const int &ed, int u, int len, int l);
	void DFS(int u);

public:
	ADJGraph(const int MaxSize);
	int get_NodeOrder(const NodeType &value) const;
	Stats add_Node(const NodeType &Data);
	Stats add_Arc(const int FromNode, const int ToNode, const WeightType &Weight);
	ADJNode<NodeType, WeightType> *get_Nodeptr(const int &node);
	int simple_path(const int &st, const int &ed, int len);
	void print_Node() const;
	void print_Graph() const;
	void print_NodeConnect(const int &nodeorder) const;
	void delete_Arc(int u, int v) const;
	void delete_Node(int u);
	int get_FirstNode(const int &nodeorder) const;
	int get_NextNode(const int &nodeorder, const int &last) const;
	WeightType get_Weight(const int &fromorder, const int &toorder) const;
	bool is_Empty() const;
	void clear();
	int get_NodeCount() const;
	void DFS_traverse();
	NodeType get_NodeData(const int &nodeorder) const;
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
int ADJGraph<NodeType, WeightType>::get_NodeOrder(const NodeType &value) const
{
	for (int i = 0; i < this->node_count; i++)
	{
		if (this->node_array[i].data == value)
			return i;
	}
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
	int from = min(FromNode, ToNode);
	int to = max(FromNode, ToNode);
	ADJArc<NodeType, WeightType> *new_arc = new ADJArc<NodeType, WeightType>(Weight, from, to, NULL, NULL);
	if (this->node_array[from].first_arc == NULL)
	{
		this->node_array[from].first_arc = new_arc;
	}
	else
	{
		ADJArc<NodeType, WeightType> *p = this->node_array[from].first_arc;
		while (1)
		{
			int num = p->get_Num(from);
			if (num == 1)
			{
				if (p->from_next)
					p = p->from_next;
				else
					break;
			}
			else
			{
				if (p->to_next)
					p = p->to_next;
				else
					break;
			}
		}
		int num = p->get_Num(from);
		if (num == 1)
			p->from_next = new_arc;
		else
			p->to_next = new_arc;
	}
	if (this->node_array[to].first_arc == NULL)
	{
		this->node_array[to].first_arc = new_arc;
	}
	else
	{
		ADJArc<NodeType, WeightType> *p = this->node_array[to].first_arc;
		while (1)
		{
			int num = p->get_Num(to);
			if (num == 1)
			{
				if (p->from_next)
					p = p->from_next;
				else
					break;
			}
			else
			{
				if (p->to_next)
					p = p->to_next;
				else
					break;
			}
		}
		int num = p->get_Num(to);
		if (num == 1)
			p->from_next = new_arc;
		else
			p->to_next = new_arc;
	}
}

template <class NodeType, class WeightType>
ADJNode<NodeType, WeightType> *ADJGraph<NodeType, WeightType>::get_Nodeptr(const int &node)
{
	if (node >= node_count)
		throw OVER_RANGE;
	return node_array + node;
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::print_Node() const
{
	for (int i = 0; i < this->node_count; i++)
	{
		std::cout << this->node_array[i].data << " ";
	}
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::print_Graph() const
{
	if (is_Empty())
	{
		cout << "Empty Graph";
		return;
	}
	for (int i = 0; i < node_count; i++)
	{
		cout << "(" << i << ")\t" << node_array[i].data;
		ADJArc<NodeType, WeightType> *tmp = node_array[i].first_arc;
		//ADJArc<NodeType, WeightType>* p;
		while (tmp)
		{
			int num = tmp->get_Num(i);
			int to;
			if (num == 1)
				to = tmp->to_node;
			else
				to = tmp->from_node;
			cout << " -[" << setw(3) << tmp->weight << "]->" << node_array[to].data;
			if (num == 1)
				tmp = tmp->from_next;
			else
				tmp = tmp->to_next;
		}
		cout << endl;
	}
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::print_NodeConnect(const int &nodeorder) const
{
	if (nodeorder < 0 || nodeorder >= node_count)
		return;
	cout << "(" << nodeorder << ")\t" << node_array[nodeorder].data;
	ADJArc<NodeType, WeightType> *tmp = node_array[nodeorder].first_arc;
	//ADJArc<NodeType, WeightType>* p;
	while (tmp)
	{
		int num = tmp->get_Num(nodeorder);
		int to;
		if (num == 1)
			to = tmp->to_node;
		else
			to = tmp->from_node;
		cout << " -[" << setw(3) << tmp->weight << "]->" << node_array[to].data;
		if (num == 1)
			tmp = tmp->from_next;
		else
			tmp = tmp->to_next;
	}
}

template <class NodeType, class WeightType>
int ADJGraph<NodeType, WeightType>::get_FirstNode(const int &nodeorder) const
{
	if (nodeorder < 0 || nodeorder >= node_count)
		return -1;
	// cout << node_array[nodeorder].data;
	ADJArc<NodeType, WeightType> *tmp = node_array[nodeorder].first_arc;
	//ADJArc<NodeType, WeightType>* p;
	if (tmp)
	{
		int num = tmp->get_Num(nodeorder);
		int to;
		if (num == 1)
			return tmp->to_node;
		else
			return tmp->from_node;
	}
	return -1;
}

template <class NodeType, class WeightType>
int ADJGraph<NodeType, WeightType>::get_NextNode(const int &nodeorder, const int &last) const
{
	if (nodeorder < 0 || nodeorder >= node_count)
		return -1;
	// cout << "(" << nodeorder << ")\t" << node_array[nodeorder].data;
	ADJArc<NodeType, WeightType> *tmp = node_array[nodeorder].first_arc;
	//ADJArc<NodeType, WeightType>* p;
	while (tmp)
	{
		int num = tmp->get_Num(nodeorder);
		int to;
		if (num == 1)
			to = tmp->to_node;
		else
			to = tmp->from_node;
		if (to == last)
		{
			if (num == 1)
				tmp = tmp->from_next;
			else
				tmp = tmp->to_next;
			if (!tmp)
				return -1;
			num = tmp->get_Num(nodeorder);
			if (num == 1)
				to = tmp->to_node;
			else
				to = tmp->from_node;
			return to;
		}
		if (num == 1)
			tmp = tmp->from_next;
		else
			tmp = tmp->to_next;
	}
	return -1;
	// cout << endl;
}

template <class NodeType, class WeightType>
WeightType ADJGraph<NodeType, WeightType>::get_Weight(const int &fromorder, const int &toorder) const
{
	if (fromorder < 0 || fromorder >= node_count || toorder < 0 || toorder >= node_count || fromorder == toorder)
		throw INVALID_RANGE;
	// cout << "(" << nodeorder << ")\t" << node_array[nodeorder].data;
	ADJArc<NodeType, WeightType> *tmp = node_array[fromorder].first_arc;
	//ADJArc<NodeType, WeightType>* p;
	while (tmp)
	{
		int num = tmp->get_Num(fromorder);
		int to;
		if (num == 1)
			to = tmp->to_node;
		else
			to = tmp->from_node;
		if (to == toorder)
		{
			return tmp->weight;
		}
		if (num == 1)
			tmp = tmp->from_next;
		else
			tmp = tmp->to_next;
	}
	throw INVALID_VAULE;
}

template <class NodeType, class WeightType>
bool ADJGraph<NodeType, WeightType>::is_Empty() const
{
	return node_count == 0;
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::clear()
{
	while (!is_Empty())
	{
		delete_Node(0);
	}
}

template <class NodeType, class WeightType>
int ADJGraph<NodeType, WeightType>::get_NodeCount() const
{
	return this->node_count;
}

template <class NodeType, class WeightType>
NodeType ADJGraph<NodeType, WeightType>::get_NodeData(const int &nodeorder) const
{
	if (nodeorder < 0 || nodeorder >= node_count)
		throw INVALID_RANGE;
	else
	{
		return this->node_array[nodeorder].data;
	}
}

template <class NodeType, class WeightType>
int ADJGraph<NodeType, WeightType>::simple_path(const int &st, const int &ed, int u, int len, int l)
{
	ADJNode<NodeType, WeightType> *node_u = get_Nodeptr(u);
	node_u->tag = 1;
	if (l == len)
	{
		node_u->tag = 0;
		return u == ed;
	}
	int _cnt = 0;

	ADJArc<NodeType, WeightType> *EDGE = node_u->first_arc;
	while (EDGE != NULL)
	{
		int v = 0;
		if (EDGE->get_Num(u) == 1)
			v = EDGE->to_node, EDGE = EDGE->from_next;
		else
			v = EDGE->from_node, EDGE = EDGE->to_next;
		ADJNode<NodeType, WeightType> *node_v = get_Nodeptr(v);
		if (node_v->tag == 0)
		{
			_cnt += simple_path(st, ed, v, len, l + 1);
		}
	}
	node_u->tag = 0;
	return _cnt;
}

template <class NodeType, class WeightType>
int ADJGraph<NodeType, WeightType>::simple_path(const int &st, const int &ed, int len)
{
	return simple_path(st, ed, st, len, 0);
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::delete_Arc(int u, int v) const
{
	ADJArc<NodeType, WeightType> *tmpu = node_array[u].first_arc;
	ADJArc<NodeType, WeightType> *tmpv = node_array[v].first_arc;
	ADJArc<NodeType, WeightType> *upre, *vpre, *unext, *vnext;
	if ((tmpu->from_node == u && tmpu->to_node == v && tmpv->from_node == u && tmpv->to_node == v) || (tmpu->from_node == v && tmpu->to_node == u && tmpv->from_node == v && tmpv->to_node == u))
	{
		//cout << "tmpuv" << endl;
		int numu = tmpu->get_Num(u);
		if (numu == 1)
		{
			node_array[u].first_arc = tmpu->from_next;
			node_array[v].first_arc = tmpv->to_next;
			delete tmpu;
			tmpu = tmpv = NULL;
		}
		else
		{
			node_array[u].first_arc = tmpu->to_next;
			node_array[v].first_arc = tmpv->from_next;
			delete tmpv;
			tmpu = tmpv = NULL;
		}
		return;
	}
	if ((tmpu->from_node == u && tmpu->to_node == v) || (tmpu->from_node == v && tmpu->to_node == u))
	{
		//cout << "tmpu" << endl;
		while (1)
		{
			int num = tmpv->get_Num(v);
			//cout << num << endl;
			if (num == 1)
			{
				if (tmpv->from_next != NULL)
				{
					//cout << 2 << endl;
					if (tmpv->from_next->from_node == u || tmpv->from_next->to_node == u)
					{
						//cout << 3 << endl;
						vpre = tmpv;
						tmpv = tmpv->from_next;
						vnext = tmpv->from_node == v ? tmpv->from_next : tmpv->to_next;
						break;
					}
					//cout << 4 << endl;
					tmpv = tmpv->from_next;
				}
				else
					break;
			}
			else
			{
				if (tmpv->to_next)
				{
					if (tmpv->to_next->from_node == u || tmpu->to_next->to_node == u)
					{
						vpre = tmpv;
						tmpv = tmpv->to_next;
						vnext = tmpv->from_node == v ? tmpv->from_next : tmpv->to_next;
						break;
					}
					tmpv = tmpv->to_next;
				}
				else
					break;
			}
		}
		int numu = tmpu->get_Num(u);
		int numv = tmpv->get_Num(v);
		if (numu == 1)
			node_array[u].first_arc = tmpu->from_next;
		else
			node_array[u].first_arc = tmpu->to_next;
		if (vnext)
		{
			if (numv == 1)
			{
				vpre->from_next = vnext;
			}
			else
				vpre->to_next = vnext;
		}
		else
		{
			if (numv == 1)
				vpre->from_next = NULL;
			else
				vpre->to_next = NULL;
		}
		return;
	}
	if ((tmpv->from_node == u && tmpv->to_node == v) || (tmpv->from_node == v && tmpv->to_node == u))
	{
		//cout << "tmpv" << endl;
		while (1)
		{
			int num = tmpu->get_Num(u);
			//cout << num << endl;
			if (num == 1)
			{
				if (tmpu->from_next != NULL)
				{
					//cout << 2 << endl;
					if (tmpu->from_next->from_node == v || tmpu->from_next->to_node == v)
					{
						//cout << 4 << endl;
						upre = tmpu;
						tmpu = tmpu->from_next;
						unext = tmpu->from_node == u ? tmpu->from_next : tmpu->to_next;
						break;
					}
					//cout << 3 << endl;
					//cout << 1 << endl;
					tmpu = tmpu->from_next;
				}
				else
				{
					//cout << tmpu->to_node << endl;
					break;
				}
			}
			else
			{
				if (tmpu->to_next)
				{
					if (tmpu->to_next->from_node == v || tmpu->to_next->to_node == v)
					{
						upre = tmpu;
						tmpu = tmpu->to_next;
						unext = tmpu->from_node == u ? tmpu->from_next : tmpu->to_next;
						break;
					}
					tmpu = tmpu->to_next;
				}
				else
				{
					//cout << tmpu->from_node << endl;
					break;
				}
			}
		}
		int numu = tmpu->get_Num(u);
		int numv = tmpv->get_Num(v);
		if (numv == 1)
			node_array[v].first_arc = tmpv->from_next;
		else
			node_array[v].first_arc = tmpv->to_next;
		if (unext)
		{
			if (numu == 1)
			{
				upre->from_next = unext;
			}
			else
				upre->to_next = unext;
		}
		else
		{
			if (numu == 1)
				upre->from_next = NULL;
			else
				upre->to_next = NULL;
		}
		return;
	}
	int flag = 0;
	while (1)
	{
		int num = tmpu->get_Num(u);
		//cout << num << endl;
		if (num == 1)
		{
			if (tmpu->from_next != NULL)
			{
				//cout << 2 << endl;
				if (tmpu->from_next->from_node == v || tmpu->from_next->to_node == v)
				{
					//cout << 4 << endl;
					upre = tmpu;
					tmpu = tmpu->from_next;
					unext = tmpu->from_node == u ? tmpu->from_next : tmpu->to_next;
					break;
				}
				//cout << 3 << endl;
				//cout << 1 << endl;
				tmpu = tmpu->from_next;
			}
			else
			{
				//cout << tmpu->to_node << endl;
				flag = 1;
				break;
			}
		}
		else
		{
			if (tmpu->to_next)
			{
				if (tmpu->to_next->from_node == v || tmpu->to_next->to_node == v)
				{
					upre = tmpu;
					tmpu = tmpu->to_next;
					unext = tmpu->from_node == u ? tmpu->from_next : tmpu->to_next;
					break;
				}
				tmpu = tmpu->to_next;
			}
			else
			{
				//cout << tmpu->from_node << endl;
				flag = 1;
				break;
			}
		}
	}
	//cout << 1 << endl;
	if (flag)
	{
		cout << "This edge is not exist" << endl;
		return;
	}
	while (1)
	{
		int num = tmpv->get_Num(v);
		//cout << num << endl;
		if (num == 1)
		{
			if (tmpv->from_next != NULL)
			{
				//cout << 2 << endl;
				if (tmpv->from_next->from_node == u || tmpv->from_next->to_node == u)
				{
					//cout << 3 << endl;
					vpre = tmpv;
					tmpv = tmpv->from_next;
					vnext = tmpv->from_node == v ? tmpv->from_next : tmpv->to_next;
					break;
				}
				//cout << 4 << endl;
				tmpv = tmpv->from_next;
			}
			else
				break;
		}
		else
		{
			if (tmpv->to_next)
			{
				if (tmpv->to_next->from_node == u || tmpu->to_next->to_node == u)
				{
					vpre = tmpv;
					tmpv = tmpv->to_next;
					vnext = tmpv->from_node == v ? tmpv->from_next : tmpv->to_next;
					break;
				}
				tmpv = tmpv->to_next;
			}
			else
				break;
		}
	}
	//cout << 10 << endl;
	delete tmpu;
	tmpu = tmpv = NULL;
	//cout << 1 << endl;
	//cout << upre << ' ' << vpre << endl;
	int numu = upre->get_Num(u);
	int numv = vpre->get_Num(v);
	//cout << numu << ' ' << numv << endl;
	if (unext)
	{
		if (numu == 1)
		{
			upre->from_next = unext;
		}
		else
			upre->to_next = unext;
	}
	else
	{
		if (numu == 1)
			upre->from_next = NULL;
		else
			upre->to_next = NULL;
	}
	if (vnext)
	{
		if (numv == 1)
		{
			vpre->from_next = vnext;
		}
		else
			vpre->to_next = vnext;
	}
	else
	{
		if (numv == 1)
			vpre->from_next = NULL;
		else
			vpre->to_next = NULL;
	}
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::delete_Node(int u)
{
	ADJNode<NodeType, WeightType> *nodeu = get_Nodeptr(u);
	ADJArc<NodeType, WeightType> *arcu = nodeu->first_arc, *lstarc;
	while (arcu != NULL)
	{
		lstarc = arcu;
		if (arcu->get_Num(u) == 1)
			arcu = arcu->from_next;
		else
			arcu = arcu->to_next;
		delete_Arc(lstarc->from_node, lstarc->to_node);
	}
	for (int i = u; i < node_count - 1; ++i)
	{
		node_array[i] = ADJNode<NodeType, WeightType>(node_array[i + 1].data, node_array[i + 1].first_arc);
	}
	node_count--;
	for (int i = u; i < node_count; ++i)
	{
		arcu = get_Nodeptr(i)->first_arc;
		while (arcu != NULL)
		{
			if (arcu->get_Num(i + 1) == 1)
				arcu->from_node--, arcu = arcu->from_next;
			else
				arcu->to_node--, arcu = arcu->to_next;
		}
	}
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::DFS(int u) {
	cout << " -> " << u;
	ADJNode<NodeType, WeightType> *nodeu = get_Nodeptr(u),*nodev = NULL;
	nodeu -> tag=1;
	ADJArc<NodeType, WeightType> *arcu = nodeu-> first_arc;
	while(arcu != NULL){
		if(arcu->get_Num(u)==1){
			nodev = get_Nodeptr(arcu->to_node);
			if(nodev->tag==0) DFS(arcu->to_node);
			arcu = arcu->from_next;
		}
		else{
			nodev = get_Nodeptr(arcu->from_node);
			if(nodev->tag==0) DFS(arcu->from_node);
			arcu = arcu->to_next;
		}
	}
}

template <class NodeType, class WeightType>
void ADJGraph<NodeType, WeightType>::DFS_traverse(){
	cout << "DFS_traverse:";
	for(int i = 0; i < node_count; ++i){
		if((node_array+i)->tag==0){
			cout << "\n *";
			DFS(i);
			cout << " -> *";
		}
	}
	for(int i = 0; i < node_count; ++i) (node_array+i)->tag=0;
}


#endif
