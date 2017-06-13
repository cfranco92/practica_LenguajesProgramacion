#include "ast.h"
#include <iostream>
#include "calculator.h"
#include "calcex.h"

AST::AST()
{}

AST::~AST()
{}

BinaryNode::BinaryNode(AST* left, AST* right):
  AST(),
  leftTree(left),
  rightTree(right)
{}

BinaryNode::~BinaryNode()
{
#ifdef debug
  cout << "In BinaryNode destructor" << endl;
#endif
  
  try
    {
      delete leftTree;
    }
  catch (...)
    {}
  
  try
    {
      delete rightTree;
    }
  catch(...)
    {}
}

AST* BinaryNode::getLeftSubTree() const
{
  return leftTree;
}

AST* BinaryNode::getRightSubTree() const
{
  return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
  AST(),
  subTree(sub)
{}

UnaryNode::~UnaryNode()
{
#ifdef debug
  cout << "In UnaryNode destructor" << endl;
#endif
  
  try
    {
    delete subTree;
    }
  catch (...)
    {}
}

AST* UnaryNode::getSubTree() const
{
  return subTree;
}

AddNode::AddNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int AddNode::evaluate()
{
  return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

SubNode::SubNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int SubNode::evaluate()
{
  return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

TimesNode::TimesNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int TimesNode::evaluate()
{
  return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

DivideNode::DivideNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int DivideNode::evaluate()
{ 
  return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

ModNode::ModNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

int ModNode::evaluate()
{
  return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

SNode::SNode(AST *subTree):
  UnaryNode(subTree)
{}

int SNode::evaluate()
{
  int val = getSubTree()->evaluate();
  calc->store(val);
  return val;
}

PNode::PNode(AST *subTree):
  UnaryNode(subTree)
{}

int PNode::evaluate()
{
  int plus = getSubTree()->evaluate();
  int memory = calc->recall();
  memory += plus;
  calc->store(memory);
  return memory;
}

MNode::MNode(AST *subTree):
  UnaryNode(subTree)
{}

int MNode::evaluate()
{
  int minus = getSubTree()->evaluate();
  int memory = calc->recall();
  memory -= minus;
  calc->store(memory);
  return memory;
}

NumNode::NumNode(int n):
  AST(),
  val(n)
{}

int NumNode::evaluate()
{
  return val;
}

IdentifierNode::IdentifierNode(int n, string v):
  AST(),
  val(n),
  var(v)
{}

int IdentifierNode::evaluate()
{
  return val;
}

RNode::RNode():
  AST()
{}

int RNode::evaluate()
{
  return calc->recall();
}

CNode::CNode() :
  AST()
{}

int CNode::evaluate()
{
  calc->store(0);
  
  return 0;
}
