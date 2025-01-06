#pragma once
#include <windows.h>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
struct TIndex
{
	int x, y;
	bool operator == (const TIndex& pos)
	{
		return (x == pos.x && y == pos.y);
	}
	TIndex operator + (const TIndex& right_)
	{
		return{ x + right_.x, y + right_.y };
	}
	TIndex(int fX, int fY)
	{
		x = fX;
		y = fY;
	}
	TIndex()
	{
		x = y = 0;
	}
};
namespace AStar
{
	using CoordinateList = std::vector<TIndex>;
	using HeuristicFunction = std::function<UINT(TIndex, TIndex)>;
	struct Node
	{
		UINT G, H;
		TIndex coordinates;
		Node* parent;

		Node(TIndex coord_, Node* parent_ = nullptr);
		UINT getScore();
	};

	using NodeSet = std::set<Node*>;
	class Generator
	{
		TIndex worldSize;
		UINT   directions= 8;
		CoordinateList direction, walls;
		HeuristicFunction heuristic;
	public:
		void addCollision(TIndex coordinates_);
		void setWorldSize(TIndex worldSize_);
		CoordinateList findPath(TIndex source, TIndex target);
		bool detectCollision(TIndex coordinates_);
		Node* findNodeOnList(NodeSet& nodes_, TIndex coordinates_);
		void setHeuristic(HeuristicFunction heuristic_);
		void releaseNodes(NodeSet& nodes_);
		Generator();
	};

	class Heuristic
	{
		static TIndex getDelta(TIndex source_, TIndex target_);

	public:
		static UINT manhattan(TIndex source_, TIndex target_);//맨헤튼
		static UINT euclidean(TIndex source_, TIndex target_);//유클리드
		static UINT octagonal(TIndex source_, TIndex target_);//8변
	};
}

