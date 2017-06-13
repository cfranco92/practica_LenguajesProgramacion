/* CRISTIAN FRANCO BEDOYA */

#include "parser.h"
#include "calcex.h"
#include "calculator.h"
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/* Constructor */
Parser::Parser(istream* in)
{
  scan = new Scanner(in);
}

/* Constructor sobrecargado para archivos */
Parser::Parser(istream* in,bool isFile, string fileName)
{
  scan = new Scanner(in);
  this->fileName = fileName;
  this->isFile = isFile;
}

/* Destructor */
Parser::~Parser()
{
  try
    {
      delete scan;
    } catch (...) {}
}

/* parse -> Inicia la gramática (Prog) */
void Parser::parse()
{
  Prog();
}

/* Prog -> ListExpr */
void Parser::Prog()
{
  ListExpr();
}

/* ListExpr -> Expr EOL ListExpr | EOF */
void Parser::ListExpr()
{
  if(!isFile)
    {
      cout << "> ";
    }
  
  cout.flush();
  
  Token* t = scan->getToken();

  if (t->getType() != eof)
    {
      scan->putBackToken();
      
      try
	{
	  AST* ast = Expr();
	  int result = ast->evaluate();
	  calc->store(0);
	  t = scan->getToken();
	  
	  if(t->getType() == eol)
	    {
	      cout << "= " << result << endl;
	    }
	}
      catch (...)
	{
	  //cout << "* parse error" << endl;
  	  //throw ParseError;
  	}
    }
  else
    {
      if(isFile)
	{
	  ofstream file(fileName.c_str());
	  file.close();
	}
      return;
    }
   ListExpr();
}

/* Expr -> Term RestExpr */
AST* Parser::Expr()
{
  return RestExpr(Term());
}

/* RestExpr -> +Term RestExpr | -Term RestExpr | E(epsilon) */
AST* Parser::RestExpr(AST* e)
{
  Token* t = scan->getToken();
  
  if (t->getType() == add)
    {
      return RestExpr(new AddNode(e,Term()));
    }
  
  if (t->getType() == sub)
    {
      return RestExpr(new SubNode(e,Term()));
    }
  
  scan->putBackToken();
  
  return e;
}

/* Term -> Storable RestTerm */
AST* Parser::Term()
{
  return RestTerm(Storable());
}

/* *Term RestTerm || /Term RestTerm || %Term RestTerm || E(epsilon) */
AST* Parser::RestTerm(AST* e)
{
  Token* t = scan->getToken();

  if(t->getType() == times)
    {
      return RestTerm(new TimesNode(e, Storable()));
    }
  
  if(t->getType() == divide)
    {
      return RestTerm(new DivideNode(e, Storable()));
    }
  
  if(t->getType() == mod)
    {
      return RestTerm(new ModNode(e, Storable()));
    }
  
  scan->putBackToken();
  
  return e;
}

/* Storable -> Factor MemOperation */
AST* Parser::Storable()
{
  return MemOperation(Factor());
}

/* MemOperation -> S | P | M | E(epsilon) */
AST* Parser::MemOperation(AST* e)
{
  Token *t = scan->getToken();
  
  if(t->getType() == keyword)
    {
      if(t->getLex().compare("S") == 0)
	{
	  return new SNode(e);
	}
      else if(t->getLex().compare("P") == 0)
	{
	  return new PNode(e);
	}
      else if(t->getLex().compare("M") == 0)
	{
	  return new MNode(e);
	}
      else
	{
	  cout << "* parser error" << endl;
	}
    }
  
  scan->putBackToken();
  
  return e;
}

/* Factor -> number | identifier | R | C | (Expr) */
AST* Parser::Factor()
{
  Token *t = scan->getToken();
  
  if (t->getType() == number)
    {
      istringstream in(t->getLex());
      int val;
      in >> val;
      return new NumNode(val);
    }
  
  if(t->getType() == identifier)
    {
      string key = t->getLex();
      int value = calc->recallVar(key);
      return new IdentifierNode(value, key);
    }
  
  if (t->getType() == keyword)
    {
      if (t->getLex().compare("R") == 0)
	{
	  return new RNode();
	}
      else if(t->getLex().compare("C") == 0)
	{
	  return new CNode();
	}
      else{
	cout << "* parser error" << endl;
      }
    }
  
  if(t->getType() == lparen)
    {
      AST* result = Expr();
      t = scan->getToken();
      if (t->getType() == rparen)
	{
	  return result;
	}
      else
	{
	  cout << "* parser error" << endl;
	}
    }
  
  throw ParseError;
}
