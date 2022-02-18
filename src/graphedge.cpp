#include "graphnode.h"
#include "graphedge.h"

GraphEdge::GraphEdge(int id) { _id = id; }

void GraphEdge::SetChildNode(GraphNode *childNode) { _childNode = childNode; }

void GraphEdge::SetParentNode(GraphNode *parentNode) {
  _parentNode = parentNode;
}

GraphEdge& GraphEdge::operator=( GraphEdge&& source)
{
	if (&source == this) return *this;
	_id = source._id;
	_childNode=source._childNode;
	_parentNode = source._parentNode;
	_keywords = std::move(source._keywords);
	source._id = 0;
	source._childNode = nullptr;
	source._parentNode = nullptr;
	return *this;
}
GraphEdge::GraphEdge(GraphEdge&& source)
{
	_id = source._id;
	_childNode = source._childNode;
	_parentNode = source._parentNode;
	_keywords = std::move(source._keywords);
	source._id = 0;
	source._childNode = nullptr;
	source._parentNode = nullptr;
}
GraphEdge& GraphEdge::operator=(const GraphEdge& source)
{
	if (&source == this) return *this;
	_id = source._id;
	_childNode = source._childNode;
	_parentNode = source._parentNode;
	_keywords = std::move(source._keywords);
	return *this;
}

GraphEdge::GraphEdge(const GraphEdge& source)
{
	_id = source._id;
	_childNode = source._childNode;
	_parentNode = source._parentNode;
	_keywords = std::move(source._keywords);
}
void GraphEdge::AddToken(std::string token) { _keywords.push_back(token); }