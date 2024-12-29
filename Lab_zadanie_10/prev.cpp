#include "prev.h"
#include<climits>
#include <cstddef>
#include <iterator>
#include<memory>
#include<iostream>

typedef struct
{
	int low;
	int high;
}intrv;

typedef struct treepathNode treepathNode;
struct treepathNode
{
	intrv interval;
	int best_index;
	std::shared_ptr<treepathNode> next_node;
	std::shared_ptr<treepathNode> sibling;

	treepathNode(intrv _interval, int _best_index, std::shared_ptr<treepathNode> _next_node, std::shared_ptr<treepathNode> _sibling)
	{
		interval = _interval;
		best_index = _best_index;
		sibling = _sibling;
		next_node = _next_node;
	}

	void dump()
	{
		std::cout << "{" << " {" << interval.low << "," << interval.high << "}, " << best_index << ", " << sibling << ", " << next_node << " }" << std::endl;
	}
};

typedef struct
{
	int value;
	std::shared_ptr<treepathNode> path_start;
}elem;



std::vector<elem> trees;

bool isEqual(intrv a, intrv b)
{
	if(a.low == b.low && a.high == b.high)
		return true;
	else
		return false;
}

void moveMirror(std::shared_ptr<treepathNode> &mirror_node, std::shared_ptr<treepathNode> current)
{
		if(mirror_node != nullptr)
		{
			if(isEqual(mirror_node->interval, current->interval))
			{
				current->sibling = mirror_node->sibling;
			}
			else 
			{
				current->sibling = mirror_node;
				mirror_node = mirror_node->sibling;
			}
			if(mirror_node != nullptr)
				mirror_node = mirror_node->next_node;
		}
}

intrv newInterval(int mid, int x, intrv current_intrv)
{
		if(x > mid)
			return {mid + 1, current_intrv.high};
		else 
			return {current_intrv.low, mid};
}

std::shared_ptr<treepathNode> genPath(int i, int x)
{	
	intrv current_intrv = {INT_MIN, INT_MAX}; 
	std::shared_ptr<treepathNode> mirror_node, begining, current;

	mirror_node = (i == 0 ? nullptr : trees[i - 1].path_start); // sets the node on the previous tree, which will follow the current node;
															 
	begining = std::make_shared<treepathNode>(current_intrv, i, nullptr, nullptr); // Initalises the current tree
	begining->dump();

	current = begining;
	current_intrv = newInterval(-1, x, current_intrv); // the first intervals (-N, -1) and (0, N) need to be created seperately due to overflows
	current = std::make_shared<treepathNode>(current_intrv, i, nullptr, nullptr);
	begining->next_node = current;
	moveMirror(mirror_node, begining); // moves the mirror pointer at the begining
	
	while(current_intrv.high != current_intrv.low) // goes down the tree, finding the proper element
	{
		int mid = current_intrv.low - (current_intrv.low - current_intrv.high) / 2; // avoids overflows
		current_intrv = newInterval(mid, x, current_intrv);
		std::shared_ptr<treepathNode> next_node = std::make_shared<treepathNode>(current_intrv, i, nullptr, nullptr);
		current->next_node = next_node;

		moveMirror(mirror_node, current); // moves the mirror pointer after every iteration and connects the current tree to the forest
		current->dump();
		current = next_node;
	}

	current->dump();
	return begining;
}


void init(const std::vector<int> &seq)
{
	for(int i = 0; i < seq.size(); i++)
		pushBack(seq[i]);
}

bool contains(intrv interval, int x)
{
	if(x >= interval.low && x <= interval.high)
		return true;
	else 
		return false;
}

bool inRange(bool isLow, int value, intrv interval)
{
	if(isLow)
	{
		if(interval.high >= value)
			return true;
	}
	else 
	{
		if(interval.low <= value)
			return true;
	}
	return false;
}

std::shared_ptr<treepathNode> iterate(bool isLow, int value, std::shared_ptr<treepathNode> current)
{
	std::cout<<"#############################" << std::endl;
	if(isLow)
	{
		std::cout<< "finding for low at: " << value << std::endl;
	}
	else 
	{
		std::cout<< "finding for high at: " << value << std::endl;

	}
	while(current->sibling != nullptr || current->next_node != nullptr)
	{
		current->dump();
		if(contains(current->next_node->interval, value))
			current = current->next_node;
		else if(current->sibling != nullptr && contains(current->sibling->interval, value))
			current = current->sibling;
		else if(inRange(isLow, value, current->next_node->interval))
			current = current->next_node;
		else if(current->sibling != nullptr && inRange(isLow, value, current->sibling->interval))
			current = current->sibling;
		else 
			return current;
	}
	current->dump();
	return current;
}


int prevInRange(int i, int lo, int hi)
{
	std::shared_ptr<treepathNode> current = trees[i].path_start;
	std::shared_ptr<treepathNode> low = iterate(true, lo, current);
	std::shared_ptr<treepathNode> high = iterate(false, hi, current);
	


}

void pushBack(int value)
{	
	trees.push_back({value, genPath(trees.size(), value)});
}

void done()
{

}


