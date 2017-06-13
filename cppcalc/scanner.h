/* CRISTIAN FRANCO BEDOYA */

#pragma once

#include <iostream>
#include "token.h"

/* Declaración de la clase Scanner, donde se encuentra: 
 * -> Obtener último token.
 * -> Devolver último token.
 *
 * ---> Atributos: inStream : istream*
 *                 lineCount : int
 *                 colCount : int
 *                 needToken : bool
 *                 lastToken : Token*
 */
class Scanner
{
 public:
  Scanner(istream* in);
  ~Scanner();
  
  Token* getToken();
  void putBackToken();
  
 private:
  Scanner();
  
  istream* inStream;
  int lineCount;
  int colCount;
  
  bool needToken;
  Token* lastToken;
};

  

