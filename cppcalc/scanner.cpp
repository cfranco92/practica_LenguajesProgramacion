#include "scanner.h"
#include "calcex.h"
#include <iostream>
#include <string>
using namespace std;

/* Número de elemento en arreglo */
const int numberOfKeywords = 5;

/* Arreglo de palabras(letras) reservadas */
const string keywd[numberOfKeywords] =
  {
    string("S"), string("R"), string("C"), string("P"), string("M")
  };

/* Determina si es una letra */
int isLetter(char c)
{
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/* Determina si es un dígito */
int isDigit(char c)
{
  return (c >= '0' && c <= '9');
}

/* Determina si es un espacio en blanco */
int isWhiteSpace(char c)
{
  return (c == ' ' || c == '\t');
}

/* Constructor */
Scanner::Scanner(istream* in):
  inStream(in),
  lineCount(1),
  colCount(-1),
  needToken(true),
  lastToken(0)
{}

/* Destructor */
Scanner::~Scanner()
{
  try
    {
      delete inStream;
    }
  catch (...) {}
}

/* Definicion de devolver último token */
void Scanner::putBackToken()
{
  needToken = false;
}

/* Obtener último token (MÁQUINA DE ESTADO FINITO) */
Token* Scanner::getToken()
{
  if (!needToken)
    {
      needToken=true;
      return lastToken;
    }
  
  Token* t;
  int state=0;
  bool foundOne=false;
  char c;
  string lex;
  TokenType type;
  int k;
  int column, line;
  
  c = inStream->get();
  
  while (!foundOne)
    {
      colCount++;
      switch (state)
	{
	case 0 : 
	  lex = "";
	  column=colCount;
	  line = lineCount;
	  if (isLetter(c)) state=1;
	  else if (isDigit(c)) state=2;
	  else if (c=='+') state=3;
	  else if (c=='-') state=4;
	  else if (c=='*') state=5;
	  else if (c=='/') state=6;
	  else if (c=='(') state=7;
	  else if (c==')') state=8;
	  else if (c=='%') state=9;
	  else if (c=='\n' || c=='\0')
	    {
	      colCount=-1;
	      lineCount++;
	      foundOne = true;
	      type = eol;
	    }
	  else if (isWhiteSpace(c));
	  else if (inStream->eof())
	    {
	      foundOne=true;
	      type=eof;
	    }
	  else
	    {
	      throw UnrecognizedToken;
	    }
	  break;
	case 1 :
	  if (isLetter(c) || isDigit(c)) state=1;
	  else
	    {
	      for (k=0;k<numberOfKeywords;k++)
		if (lex == keywd[k])
		  {
		    foundOne = true;
		    type = keyword;
		  }
	      if (!foundOne)
		{
		  type = identifier;
		  foundOne = true;
		}
	    }
	  break;
	case 2 :
	  if (isDigit(c)) state=2;
	  else
	    {
	      type = number;
	      foundOne=true;
	    }
	  break;
	case 3 :
	  type = add;
	  foundOne = true;
	  break;
	case 4 :
	  type = sub;
	  foundOne = true;
	  break;
	case 5 :
	  type = times;
	  foundOne=true;
	  break;
	case 6 :
	  type = divide;
	  foundOne=true;
	  break;
	case 7 :
	  type = lparen;
	  foundOne=true;
	  break;
	case 8 :
	  type = rparen;
	  foundOne=true;
	  break;
	case 9 :
	  type = mod;
	  foundOne=true;
	  break;
	}
      
      if (!foundOne)
	{
	  lex = lex + c;
	  c = inStream->get();
	}
    }
  
  if(type != eol)
    {
      inStream->putback(c);
      colCount--;
    }
  
  if (type == number || type == identifier || type == keyword)
    {
      t = new LexicalToken(type,new string(lex), line, column);
    }
  else
    {
      t = new Token(type,line,column);
    }
  
#ifdef debug
  cout << "just found " << lex << " with type " << type << endl;
#endif
  
  lastToken = t;
  return t;  
}
