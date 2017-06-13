/* CRISTIAN FRANCO BEDOYA */

#pragma once
#include <string>
using namespace std;

/* Declaracion de la interfaz AST, donde se encuentra: 
 * -> evaluate() : int
 */
class AST
{
 public:
  AST();
  virtual ~AST() = 0;
  virtual int evaluate() = 0;
};


/* Declaración de la clase abstracta BinaryNode, donde se encuentra:
 * -> getLeftSubTree() : AST*
 * -> getRightSubTree() : AST*
 *
 * ---> Atributos: leftTree : AST*
 *                 rigthTree : AST*
 */
class BinaryNode : public AST
{
 public:
  BinaryNode(AST* left, AST* right);
  ~BinaryNode();
  
  AST* getLeftSubTree() const;
  AST* getRightSubTree() const;
  
 private:
  AST* leftTree;
  AST* rightTree;
};


/* Declaración de la clase abstracta UnaryNode, donde se encuentra:
 * -> getSubTree() : AST*
 *
 * ---> Atributos: subTree : AST*
 */
class UnaryNode : public AST
{
 public:
  UnaryNode(AST* sub);
  ~UnaryNode();
  
  AST* getSubTree() const;
  
 private:
  AST* subTree;
};


/* Declaración de las clases AddNode, SubNode, 
 * TimesNode, DivideNode, ModNode 
 * donde se encuentra:
 * -> evaluate() : int
 *
 * ---> Atributos: Heredados de BinaryNode
 */

class AddNode : public BinaryNode
{
 public:
  AddNode(AST* left, AST* right);
  
  int evaluate();
};

class SubNode : public BinaryNode
{
 public:
  SubNode(AST* left, AST* right);
  
  int evaluate();
};

class TimesNode : public BinaryNode
{
 public:
  TimesNode(AST* left, AST* right);
  
  int evaluate();
};

class DivideNode : public BinaryNode
{
 public:
  DivideNode(AST* left, AST* right);
  
  int evaluate();
};

class ModNode : public BinaryNode
{
 public:
  ModNode(AST* left, AST* right);
  
  int evaluate();
};


/* Declaración de las clases SNode, PNode, MNode
 * donde se encuentra:
 * -> evaluate() : int
 *
 * ---> Atributos: Heredados de UnaryNode
 */
class SNode : public UnaryNode
{
 public:
  SNode(AST* subTree);
  
  int evaluate();
};

class PNode : public UnaryNode
{
 public:
  PNode(AST* subTree);
  
  int evaluate();
};

class MNode : public UnaryNode
{
 public:
  MNode(AST* subTree);
  
  int evaluate();
};


/* Declaración de la clase NumNode, donde se encuentra:
 * -> evaluate() : int
 *
 * ---> Atributos: val : int
 */
class NumNode : public AST
{
 public:
  NumNode(int n);
  
  int evaluate();
  
 private:
  int val;
};


/* Declaración de la clase IdentifierNode, donde se encuentra:
 * -> evaluate() : int
 *
 * ---> Atributos: val : int
 *                 var : string
 */
class IdentifierNode : public AST
{
 public:
  IdentifierNode(int val, string var);
  
  int evaluate();
  
 private:
  int val;
  string var;  
};

/* Declaración de las clases RNode, CNode
 * donde se encuentra:
 * -> evaluate() : int
 */
class RNode : public AST
{
 public:
  RNode();
  
  int evaluate();
};

class CNode: public AST
{
 public:
  CNode();
  
  int evaluate();
};
