// Gestión de la clase user (user.hpp)
#include <iostream>
#include <string>

class User {
 public:
  // Constructor
  User(const std::string& name, const unsigned& id,
       const unsigned& access_level)
      : name_(name), id_(id), access_level_(access_level) {}

  // Getters y Setters
  std::string getName() const { return name_; }
  unsigned getId() const { return id_; }
  unsigned getAccessLevel() const { return access_level_; }

 private:
  // Nombre del usuario
  std::string name_;
  // ID del usuario
  unsigned id_;
  // Nivel de acceso del usuario
  unsigned access_level_;
};