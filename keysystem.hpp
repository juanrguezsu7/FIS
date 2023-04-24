// Gestión de la clase KeySystem -> Gestionar cerradura y usuarios
#include <iostream>
#include <string>
#include <vector>

#include "key.hpp"
#include "user.hpp"

class KeySystem {
 public:
  // Añadir usuario
  void addUser(const std::string& name, const unsigned& id,
               const unsigned& access_level);
  // Eliminar usuario
  void delUser(const User& user);

  // Añadir cerradura
  void addKey(const unsigned& id, const std::string& password,
              const User& user);
  // Eliminar cerradura
  void delKey(const Key& key);

  // Añadir Usuario a Cerradura
  void addUsertoKey(const Key& key, const User& user);
  
  // Abrir cerradura
  void openKey(const Key& key, const User& user);
  // Cerrar cerradura
  void closeKey(const Key& key,const User& user);

  void setEncryptedCard(std::vector<int>& encrypted_card);
  void notify();
  void setTemporalAccess(const User& user, int minutes);

 private:
  // Cerraduras
  std::vector<Key> keys_;
  // Usuarios
  std::vector<User> users_;
};
