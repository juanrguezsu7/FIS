#pragma once

// Gestión de la clase KeySystem -> Gestionar cerradura y usuarios

#include <iostream>
#include <string>
#include <vector>

#include "key.hpp"
#include "user.hpp"

class KeySystem {
 public:
  // Añadir usuario
  void addUser(const std::string& name, const unsigned& id);
  void addUser(const User& user) { users_.emplace_back(user); }

  // Añadir cerradura
  void addKey(const unsigned& id, const std::string& password,
              const User& user);
  void addKey(const Key& key) { keys_.emplace_back(key); }

  // Eliminar cerradura
  bool delKey(const Key& key);
  // Eliminar usuario
  bool delUser(const User& user);

  // Añadir Usuario a Cerradura
  void addUserToKey(Key& key, const User& user);
  // Eliminar Usuario a Cerradura
  void delUserFromKey(Key& key, const User& user);

  // Abrir cerradura
  void openKey(Key& key, const User& user);
  // Cerrar cerradura
  void closeKey(Key& key, const User& user);

  // Obtener un User a partir de su nombre (referencia)
  User& getUser(const std::string& nombre);
  // Obtener una Key a partir de su ID (referencia)
  Key& getKey(const unsigned id);

  // Comprobar si existen usuarios o llaves
  bool userExists(const std::string& name);
  bool keyExists(const unsigned id);

  // void setEncryptedCard(std::vector<int>& encrypted_card);
  void notify();
  // void setTemporalAccess(const User& user, int minutes);

  // Mostrar los datos de forma "bonita"
  void mostrarLlaves();
  void mostrarUsuarios();

  // Getter
  std::vector<Key> getKeys() const { return keys_; }

 private:
  // Cerraduras
  std::vector<Key> keys_;
  // Usuarios
  std::vector<User> users_;
};