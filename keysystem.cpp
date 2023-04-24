// Funciones de la clase KEY
#include "keysystem.hpp"

void KeySystem::notify() {
  std::cout << "Notificación: La cerradura está siendo accedida." << '\n';
}

void KeySystem::addUser(const std::string& name, const unsigned& id, const unsigned& access_level){
  User new_user (name, id, access_level);
  this->users_.reserve(1);
  this->users_.emplace_back(new_user);
}

void KeySystem::addKey(const unsigned& id, const std::string& password, const User& user){
  Key new_key (id, password, user);
  this->keys_.reserve(1);
  this->keys_.emplace_back(new_key);
}
