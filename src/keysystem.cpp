// Funciones de la clase KEY
#include "keysystem.hpp"

/**
 * @brief Notificación de que se está abriendo la cerradura.
 */
void KeySystem::notify() {
  std::cout << "Notificación: La cerradura está siendo accedida." << '\n';
}

/**
 * @brief Añade un usuario al sistema.
 *
 * @param name Nombre del usuario.
 * @param id Identificador del usuario.
 */
void KeySystem::addUser(const std::string& name, const unsigned& id) {
  User new_user(name);
  this->users_.reserve(1);
  this->users_.emplace_back(new_user);
}

/**
 * @brief Añade una llave al sistema.
 *
 * @param id Identificador de la llave.
 * @param password Contraseña de la llave.
 * @param user Usuario con acceso a la llave.
 */
void KeySystem::addKey(const unsigned& id, const std::string& password,
                       const User& user) {
  Key new_key(password, user);
  this->keys_.reserve(1);
  this->keys_.emplace_back(new_key);
}

/**
 * @brief Añade un Usuario a la lista de accesos de x cerradura.
 *
 * @param key Cerradura a la que el usuario podra acceder
 * @param user Usuario en cuestion
 */
void KeySystem::addUserToKey(Key& key, const User& user) {
  key.setUserAccess(user, 1);
}

/**
 * @brief Elimina un Usuario de la lista de accesos de x cerradura.
 *
 * @param key Cerradura a la que el usuario no podra acceder
 * @param user Usuario en cuestion
 */
void KeySystem::delUserFromKey(Key& key, const User& user) {
  key.setUserAccess(user, 0);
}

/**
 * @brief Abre la cerradura
 *
 * @param key Cerradura a abrir
 * @param user Usuario que solicita la apertura
 */
void KeySystem::openKey(Key& key, const User& user) { key.open(user); }

/**
 * @brief Cierra la cerradura
 *
 * @param key Cerradura a cerrar
 * @param user Usuario que solicita el cierre
 */
void KeySystem::closeKey(Key& key, const User& user) { key.close(user); }

/**
 * @brief Obtener User a partir de su nombre.
 *
 * @param nombre Nombre de usuario.
 * @return Referencia a User.
 */
User& KeySystem::getUser(const std::string& nombre) {
  for (auto& user : users_) {
    if (user.getName() == nombre) return user;
  }
  throw std::out_of_range{"Usuario no encontrado en getUser()."};
}

/**
 * @brief Obtener Key a partir de su ID.
 *
 * @param id ID de llave.
 * @return Referencia a Key.
 */
Key& KeySystem::getKey(const unsigned id) {
  for (auto& key : keys_) {
    if (key.getId() == id) return key;
  }
  throw std::out_of_range{"Llave no encontrada en getKey()."};
}

/**
 * @brief Comprueba si existe un usuario en el sistema dado su nombre.
 *
 * @param nombre Nombre del usuario.
 * @return True si existe, False si no.
 */
bool KeySystem::userExists(const std::string& name) {
  for (auto& user : users_) {
    if (user.getName() == name) return true;
  }
  return false;
}

/**
 * @brief Comprueba si existe una llave en el sistema dada su ID.
 *
 * @param id ID de la llave.
 * @return True si existe, False si no.
 */
bool KeySystem::keyExists(const unsigned id) {
  for (auto key : keys_) {
    if (key.getId() == id) return true;
  }
  return false;
}

/**
 * @brief Elimina un usuario del sistema.
 *
 * @param user Usuario a eliminar.
 * @return True si se eliminó, False si no existía en la llave.
 */
bool KeySystem::delUser(const User& user) {
  for (auto i{users_.begin()}; i != users_.end(); ++i) {
    if (i->getId() == user.getId()) {
      users_.erase(i);
      return true;
    }
  }
  return false;
}

/**
 * @brief Elimina una llave del sistema
 *
 * @param key Llave a eliminar.
 * @return True si se eliminó, False si no existía.
 */
bool KeySystem::delKey(const Key& key) {
  for (auto i{keys_.begin()}; i != keys_.end(); ++i) {
    if (i->getId() == key.getId()) {
      keys_.erase(i);
      return true;
    }
  }
  return false;
}

/**
 * @brief Muestra una información resumida de las llaves del sistema.
 */
void KeySystem::mostrarLlaves() {
  std::cout << "\n*** Llaves ***\n\n";
  if (keys_.empty()) std::cout << "No hay llaves aún.\n\n";
  for (auto key : keys_) {
    std::cout << "ID/Contraseña/Estado: " << key.getId() << '/';
    for (int i{0}; i < key.getPassword().length(); ++i) std::cout << '*';
    std::cout << '/' << (key.getState() ? "Abierta" : "Cerrada");
    std::cout << "\n\n";
  }
}

/**
 * @brief Muestra una información resumida de los usuarios del sistema.
 */
void KeySystem::mostrarUsuarios() {
  std::cout << "\n*** Usuarios ***\n\n";
  if (users_.empty()) std::cout << "No hay usuarios aún.\n\n";
  for (auto usuario : users_)
    std::cout << "ID/Nombre: " << usuario.getId() << '/' << usuario.getName()
              << "\n\n";
}