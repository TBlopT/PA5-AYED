// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 5
// ESTILO: Google C++ Style Guide
// COMENTARIOS: Clase RPN (Reverse Polish Notation)

#ifndef RPNT_H_
#define RPNT_H_

#include <iostream>
#include <cctype>
#include <cmath>
//#include <cstdlib>

#include "queue_l_t.h"

// Clase RPN (Reverse Polish Notation)
template <class T> class rpn_t {
 public:
  // constructor
 rpn_t(void) : stack_() {}

  // destructor
  ~rpn_t() {}

  // operaciones
  const int evaluate(queue_l_t<char>&);

 private: 
  T stack_;
  void operate_(const char operador);
};


// operaciones
template<class T>
const int rpn_t<T>::evaluate(queue_l_t<char>& q) {
  while (!q.empty()) {
    char c = q.front();
    q.pop();
    std::cout << "Sacamos de la cola un carácter: " << c;

    if (std::isdigit(c)) {
      // -- Dígito: lo metemos directo --
      int valor = c - '0';
      stack_.push(valor);
      std::cout << " (es un dígito)" << std::endl
                << "   Lo metemos en la pila..." << std::endl;
    } else {
      // -- Operador: distinguimos unarios y binarios --
      std::cout << " (es un operador)" << std::endl;
      int resultado = 0;

      if (c == 'r' || c == 'l' || c == 'c') {
        // Operador unario
        if (stack_.empty()) {
          std::cerr << "   Error: pila vacía para operador unario" << std::endl;
          return -1;
        }
        int op = stack_.top();
        stack_.pop();

        switch (c) {
          case 'r':  // raíz cuadrada
            resultado = static_cast<int>(std::sqrt(op));
            break;
          case 'l':  // log base 2
            resultado = static_cast<int>(std::log2(op));
            break;
          case 'c':  // elevación al cuadrado
            resultado = op * op;
            break;
        }
      } else {
        // Operador binario
        if (stack_.empty()) {
          std::cerr << "   Error: faltan operandos en la pila" << std::endl;
          return -1;
        }
        int b = stack_.top();
        stack_.pop();

        if (stack_.empty()) {
          std::cerr << "   Error: faltan operandos en la pila" << std::endl;
          return -1;
        }
        int a = stack_.top();
        stack_.pop();

        switch (c) {
          case '+':
            resultado = a + b;
            break;
          case '-':
            resultado = a - b;
            break;
          case '*':
            resultado = a * b;
            break;
          case '/':
            resultado = a / b;
            break;
          case '^':
            resultado = static_cast<int>(std::pow(a, b));
            break;
          default:
            std::cerr << "   Operador no soportado: " << c << std::endl;
            return -1;
        }
      }

      std::cout << "   Metemos en la pila el resultado: " << resultado << std::endl;
      stack_.push(resultado);
    }
  }

  // Al final, sacamos el resultado de la pila
  if (!stack_.empty()) {
    int final_result = stack_.top();
    stack_.pop();
    std::cout << "Resultado: " << final_result << std::endl;
    return final_result;
  } else {
    std::cerr << "   Error: pila vacía al final" << std::endl;
    return -1;
  }
}

#endif 