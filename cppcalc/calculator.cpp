/* CRISTIAN FRANCO BEDOYA */

#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

/* Constructor */
Calculator::Calculator():
  memory(0),
  vars()
{}

/* Definición de la evaluación*/
void Calculator::eval(string expr)
{
  Parser* parser = new Parser(new istringstream(expr));
  
  parser->parse();
  
  delete parser;
}

/* Definición de guardar en memoria */
void Calculator::store(int val)
{
  memory = val;
}

/* Definición de llamar valor en memoria */
int Calculator::recall()
{
  return memory;
}

/* Definición de guardar variables en mapa */
void Calculator::storeVar(const string key, int val)
{
  if(vars.count(key)==0)
    {
      vars.insert(pair<string,int>(key,val));
    }
  else
    {
      vars[key] = val;
    }
}

/* Definición de llamar variables en mapa */
int Calculator::recallVar(string key)
{
  if(vars.count(key) == 1)
    {
      return vars.at(key);
    }
  
  return 0;
}
