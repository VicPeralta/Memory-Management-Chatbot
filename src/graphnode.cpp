#include "graphedge.h"
#include "graphnode.h"
#include "debug.h"
GraphNode::GraphNode(int id) { 
  _id = id; }

GraphNode::~GraphNode() {
  //// STUDENT CODE
  ////
  // This is the cause of the crash when the application is closed
  // Graphnode never create a new instance of chatbot, so never has to delete it

  // delete _chatBot;

  ////
  //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token) { _answers.push_back(token); }

void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
  _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(GraphEdge edge) {
  _childEdges.push_back(std::make_unique<GraphEdge>(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot chatbot) {
	if (_chatBot.get() == nullptr)
		_chatBot = std::make_unique<ChatBot>(chatbot);
	else
		*_chatBot=std::move(chatbot);
	_chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {
	/// When the program is executed, messages are printed to the console indicating 
	/// which Rule of Five component of ChatBot is being called.
	/*
	ChatBot Constructor // allocates space in the new node
	ChatBot Move Constructor // move in calling MoveChatbotHere
	ChatBot Move Assignment Operator // assigne to new node
	ChatBot Destructor // destroy parameter instance created 
	ChatBot Destructor // destroy previous node's chatbot instance
	*/
  newNode->_chatBot = std::make_unique<ChatBot>();
  //TRACE(L"Moving: %x\n", _chatBot.get());
  newNode->MoveChatbotHere(std::move(*_chatBot));
  _chatBot = nullptr;
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {
  //// STUDENT CODE
  ////

  return _childEdges[index].get();

  ////
  //// EOF STUDENT CODE
}