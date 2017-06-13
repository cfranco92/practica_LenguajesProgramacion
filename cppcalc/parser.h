/* CRISTIAN FRANCO BEDOYA */

#pragma once

#include "ast.h"
#include "scanner.h"
#include <string>

/* Declaración de la clase Parser, donde se encuentra:
 * La gramática independiente de contexto LL(1):
 *       -> Prog()
 *       -> ListExpr()
 *       -> Expr()
 *       -> RestExpr()
 *       -> RestTerm()
 *       -> Storable()
 *       -> MemOperation()
 *       -> Factor()
 *
 * ---> Atributos: scan : Scanner*
 *                 fileName : string
 *                 isFile : bool
 */
class Parser
{
 public:
  Parser(istream* in);
  Parser(istream*, bool isFile, string fileName);
  ~Parser();
  
  void parse();
  
 private:
  void Prog();
  void ListExpr();
  AST* Expr();
  AST* RestExpr(AST* e);
  AST* Term();
  AST* RestTerm(AST* t);
  AST* Storable();
  AST* MemOperation(AST* factor);
  AST* Factor();
  
  Scanner* scan;
  string fileName;
  bool isFile;
};
