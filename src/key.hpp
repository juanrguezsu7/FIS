#pragma once

// Gestión de la clase Key (key.hpp)

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "user.hpp"

class Key {
 public:
  // Constructor por defecto
  Key(){};
  // Constructor
  Key(const std::string& password) : state_(0), password_(password) {
    id_ = contador_id_keys;
    ++contador_id_keys;
  }
  Key(const std::string& password, const User& user)
      : state_(0), password_(password) {
    // Añade a users_ el id del usuario que lo creo con acceso (1)
    users_[user.getId()] = 1;
    id_ = contador_id_keys;
    ++contador_id_keys;
  }

  // Getters y Setters
  unsigned getId() const { return id_; }
  bool getState() const { return state_; }
  std::string getPassword() const { return password_; }
  void setPassword(const std::string& password) { password_ = password; };

  // Abre la cerradura
  void open(const User& user);
  // Cierra la cerradura
  void close(const User& user);
  // Edita el acceso del usuario
  void setUserAccess(const User& user, const bool& access);

  // Operadores
  // friend std::istream& operator>>(std::istream& in, Key& key);

  // Contador de los ID de las llaves globales
  static unsigned contador_id_keys;

 private:
  // Identificador de la cerradura
  unsigned id_;
  // Estado de la cerradura (1 open, 0 close)
  bool state_;
  // Constraseña de la cerradura
  std::string password_;
  // Usuarios con acceso a la cerradura
  std::map<unsigned, bool> users_;
};