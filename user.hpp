#pragma once

// Gestión de la clase user (user.hpp)

#include <iostream>
#include <string>

class User {
 public:
  // Constructor por defecto
  User() = default;
  // Constructor
  User(const std::string& name, const unsigned& id)
      : name_(name), id_(id) {}

  // Getters y Setters
  std::string getName() const { return name_; }
  unsigned getId() const { return id_; }
  
  // Operadores
  friend std::istream& operator>>(std::istream& in, User& user);
  
  // Contador de los ID de los usuarios global
  static unsigned contador_id_users;
 private:
  // Nombre del usuario
  std::string name_;
  // ID del usuario
  unsigned id_;
};