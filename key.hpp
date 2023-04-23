// Gestión de la clase Key (key.hpp)
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "user.hpp"

class Key {
 public:
  // Constructor
  Key(const unsigned& id, const std::string& password, User& user)
      : id_(id), state_(0), password_(password) {
    // Añade a users_ el id del usuario que lo creo con acceso (1)
    users_[user.getId()] = 1;
  }

  // Getters y Setters
  unsigned getId() const { return id_; }
  bool getState() const { return state_; }
  void setPassword(const std::string& password) { password_ = password; };

  // Abre la cerradura
  void open(const User& user);
  // Cierra la cerradura
  void close(const User& user);
  // Edita el acceso del usuario
  void setUserAccess(const User& user, const bool& access);

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
