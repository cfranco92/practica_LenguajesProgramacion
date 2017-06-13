/* CRISTIAN FRANCO BEDOYA */

#include <iostream>
#include <sstream>
#include <string>
#include "calcex.h"
#include "calculator.h"
#include <stdlib.h>
#include <fstream>
#include "parser.h"
using namespace std;

/* Intancia de calculator */
Calculator* calc;

/* Ejecución del programa */
int main(int argc, char* argv[])
{
  string line;
  bool isFile;
  
  try
    {
      calc = new Calculator();
      istream* in;
      Parser *parser;

      /* Recorrido de los argumentos */
      for(int i = 1; i < argc; i++)
	{
	  string argumento = argv[i];
	  if(argumento.compare("-v") == 0)
	    {
	      i++;
	      argumento = argv[i];
	      string letra = argumento;
	      
	      /* Recorrido del argumento de la variable */
	      for(int j = 0; j < argumento.length(); j++)
		{
		  if(argumento.at(j) == '=')
		    {
		      letra = argumento.substr(0,j);
		      j++;
		      int numero = atoi(argumento.substr(j).c_str());
		      calc->storeVar(letra,numero);
		    }
		}
	    }
	  else
	    {
	      /* Se lee el nombre del archivo */
	      in = new ifstream(argv[i]);
	      string fileName = argumento;
	      
	      /* Recorrido del argumento del nombre del archivo */
	      for(int j = 0; j < argumento.length();j++)
		{
		  if(argumento.at(j)=='.')
		    {
		      fileName = argumento.substr(0,j);
		      isFile = true;
		    }
		}
	      /* Es un archivo, la calculadora se comporta diferente */
	      if(isFile)
		{
		  parser = new Parser(in,isFile,fileName);
		  parser->parse();
		  
		  if(i == argc-1 && isFile)
		    {
		      return 0;
		    }
		}
	    }
	}
      /* Inicio normal de la calculadora llamando al parser */
      in = &cin;
      parser= new Parser(in);
      parser->parse();
    }
  catch(Exception ex)
    {
      cout << "Program Aborted due to exception!" << endl;
    }
}
