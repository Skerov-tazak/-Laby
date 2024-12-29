#include "prev.h"
#include<climits>
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
	std::shared_ptr<treepathNode> right;
	std::shared_ptr<treepathNode> left;

	treepathNode(intrv _interval, int _best_index, std::shared_ptr<treepathNode> _right, std::shared_ptr<treepathNode> _left)
	{
		interval = _interval;
		best_index = _best_index;
		left = _left;
		right = _right;
	}

	void dump()
	{
		std::cout << "{" << " {" << interval.low << "," << interval.high << "}, " << best_index << ", " << left << ", " << right << " }" << std::endl;
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
			if(isEqual(mirror_node->right->interval, current->right->interval))
			{
				current->left = mirror_node->left;
				mirror_node = mirror_node->right;
			}
			else 
			{
				current->left = mirror_node->right;
				mirror_node = mirror_node->left;
			}
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
	begining->right = current;
	moveMirror(mirror_node, begining); // moves the mirror pointer at the begining
	
	while(current_intrv.high != current_intrv.low) // goes down the tree, finding the proper element
	{
		int mid = current_intrv.low - (current_intrv.low - current_intrv.high) / 2; // avoids overflows
		current_intrv = newInterval(mid, x, current_intrv);
		std::shared_ptr<treepathNode> next_node = std::make_shared<treepathNode>(current_intrv, i, nullptr, nullptr);
		current->right = next_node;
		moveMirror(mirror_node, current); // moves the mirror pointer after every iteration and connects the current tree to the forest
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

bool contains(intrv bigger, std::shared_ptr<treepathNode> contained)
{
	if(contained == nullptr)
		return false;

	if(contained->interval.low >= bigger.low && contained->interval.high >= bigger.high)
		return true;
	else 
		return false;
}

bool overlaps(intrv a, std::shared_ptr<treepathNode> current)
{
	if(current == nullptr)
		return false;

	int	interval_end = std::max(a.low, current->interval.low); 
	int interval_start = std::min(a.high, current->interval.high);

	if(interval_start <= interval_end)
		return true;
	else
		return false;
}

int prevInRange_helper(std::shared_ptr<treepathNode> current, intrv range)
{
	if(current == nullptr)
		return -1;

	int current_best = -1;
	std::shared_ptr<treepathNode> current2 = nullptr;

	while(current->interval.low != current->interval.high)
	{
		if(overlaps(range, current->right))
		{
			if(contains(range, current->left))
			{
				if(current_best <= current->left->best_index)
					current_best = current->left->best_index;
			}
			else if(overlaps(range, current->left))
			{
				current2 = current->left;
			}
			current = current->right;
		}
		else if(overlaps(range, current->left))
		{
			current = current->left;
		}
	}

	if(current->best_index > current_best)
		current_best = current->best_index;	
		
	return std::max(current_best,prevInRange_helper(current2, range));
}

int prevInRange(int i, int lo, int hi)
{
	std::shared_ptr<treepathNode> current = trees[i].path_start;	
	intrv range = {lo, hi};
	return prevInRange_helper(current, range);
}

void pushBack(int value)
{	
	trees.push_back({value, genPath(trees.size(), value)});
}

void done()
{

}


