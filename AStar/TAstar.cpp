#include "TAstar.h"
namespace AStar
{
	Node::Node(TIndex coordinates_, Node* parent_)
	{
		parent = parent_;
		coordinates = coordinates_;
		G = H = 0;
	}

	UINT AStar::Node::getScore()
	{
		return G + H;
	}
	Generator::Generator()
	{
		direction = {
			{ 0, 1 }, 
			{ 1, 0 },
			{ 0, -1 },
			{ -1, 0 },
			{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
		};
	}
	void Generator::setWorldSize(TIndex worldSize_)
	{
		worldSize = worldSize_;
	}
	CoordinateList Generator::findPath(TIndex source, TIndex target)
	{
		std::vector<TIndex> currentList;
		NodeSet openSet, closedSet;
		openSet.insert(new Node(source));
		Node* current = nullptr;
		while (!openSet.empty())
		{
			current = *openSet.begin();
			for (auto node : openSet)
			{
				int iNodeValue = node->getScore();
				int iCurrentValue = current->getScore();
				if (iNodeValue <= iCurrentValue)
				{
					current = node;
				}
			}
			if (current->coordinates == target)
			{
				break;
			}
			closedSet.insert(current);
			openSet.erase(std::find(openSet.begin(), 
				openSet.end(),
				current));
			currentList.push_back(current->coordinates);

			for (UINT i = 0; i < directions; ++i)
			{
				TIndex newCoordinates(current->coordinates + direction[i]);
				if (detectCollision(newCoordinates))
				{
					continue;
				}
				if (findNodeOnList(closedSet, newCoordinates))
				{
					continue;
				}
				UINT totalCost = current->G + ((i < 4) ? 10 : 14);
				Node* successor = findNodeOnList(openSet, newCoordinates);
				if (successor == nullptr)
				{
					successor = new Node(newCoordinates, current);
					successor->G = totalCost;
					successor->H = heuristic(successor->coordinates, target);
					openSet.insert(successor);
				}
				else if (totalCost < successor->G)
				{
					successor->parent = current;
					successor->G = totalCost;
				}
			}
		}
		CoordinateList path;
		while (current != nullptr)
		{
			path.push_back(current->coordinates);
			current = current->parent;
		}
		std::reverse(path.begin(), path.end());
		releaseNodes(openSet);
		releaseNodes(closedSet);

		return path;
	}
	void Generator::releaseNodes(NodeSet& nodes_)
	{
		for (auto it = nodes_.begin(); it != nodes_.end();)
		{
			delete* it;
			it = nodes_.erase(it);
		}
	}
	void Generator::setHeuristic(HeuristicFunction heuristic_)
	{
		heuristic = std::bind(heuristic_, 
			std::placeholders::_1, 
			std::placeholders::_2);
	}
	bool Generator::detectCollision(TIndex coordinates_)
	{
		if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
			coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
			std::find(walls.begin(), walls.end(), coordinates_) != walls.end())
		{
			return true;
		}
		return false;
	}
	Node* Generator::findNodeOnList(NodeSet& nodes_, TIndex coordinates_)
	{
		for (auto node : nodes_)
		{
			if (node->coordinates == coordinates_)
			{
				return node;
			}
		}
		return nullptr;
	}

	void Generator::addCollision(TIndex coordinates_)
	{
		walls.push_back(coordinates_);
	}

	TIndex Heuristic::getDelta(TIndex source_, TIndex target_)
	{
		return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
	}

	UINT Heuristic::manhattan(TIndex source_, TIndex target_)
	{
		auto delta = std::move(getDelta(source_, target_));
		return static_cast<UINT>(10 * (delta.x + delta.y));
	}

	UINT Heuristic::euclidean(TIndex source_, TIndex target_)
	{
		TIndex a = getDelta(source_, target_);
		//TIndex&& delta = std::move(getDelta(source_, target_));
		return static_cast<UINT>(10 * sqrt(pow(a.x, 2) + pow(a.y, 2)));
	}

	UINT Heuristic::octagonal(TIndex source_, TIndex target_)
	{
		auto delta = std::move(getDelta(source_, target_));
		return 10 * (delta.x + delta.y) + (-6) * min(delta.x, delta.y);
	}
}