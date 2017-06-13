/* CRISTIAN FRANCO BEDOYA */

#pragma once
#include <string>
#include <map>

using namespace std;

/*
 * Declaración de la clase calculator, donde se encuentra: 
 * -> Evaluación de una expresion llamando al parser.
 * -> Guardar un valor en la memoria.
 * -> Llamar el valor actual en la memoria.
 * -> Guardar variables en el mapa con una key y un entero.
 * -> Llamar variables en el mapa con una key.
 *
 * ---> Atributos: memoria : int 
 *                 vars : map<string,int>
 */
class Calculator
{
 public:
  Calculator();
  
  void eval(string expr);
  void store(int val);
  int recall();
  void storeVar(string key, int val);
  int recallVar(string key);
  
 private:
  int memory;
  map<string,int> vars;
};

extern Calculator* calc;
