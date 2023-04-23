// Métodos de la clase key (key.hpp)
#include "key.hpp"

// Método para abrir la cerradura
void Key::open(const User& user) {
  // Comprueba si el usuario existe en la cerradura
  if (users_.count(user.getId()) > 0) {
    // Comprueba si el usuario tiene permisos (user.getId() = 1)
    if (users_[user.getId()]) {
      // Comprueba si la cerradura esta cerrada
      if (!state_) {
        std::cout << "Cerradura " << id_ << " abierta por " << user.getName()
                  << "." << '\n';
        state_ = true;
      } else {
        std::cout << "La cerradura " << id_ << " ya está abierta." << '\n';
      }
    } else {
      std::cout << user.getName() << " no tiene acceso a la cerradura " << id_
                << "." << '\n';
    }
  } else {
    std::cout << "Usuario " << user.getName()
              << " no encontrado en la cerradura " << id_ << "." << '\n';
  }
}

// Método para cerrar la cerradura
void Key::close(const User& user) {
  // Comprueba si el usuario existe en la cerradura
  if (users_.count(user.getId()) > 0) {
    // Comprueba si el usuario tiene permisos (user.getId() = 1)
    if (users_[user.getId()]) {
      // Comprueba si la cerradura esta abierta
      if (state_) {
        std::cout << "Cerradura " << id_ << " cerrada por " << user.getName()
                  << "." << '\n';
        state_ = false;
      } else {
        std::cout << "La cerradura " << id_ << " ya está cerrada." << '\n';
      }
    } else {
      std::cout << user.getName() << " no tiene acceso a la cerradura " << id_
                << "." << '\n';
    }
  } else {
    std::cout << "Usuario " << user.getName()
              << " no encontrado en la cerradura " << id_ << "." << '\n';
  }
}

// Gestiona el acceso de un usuario (1 puede acceder, 0 no)
void Key::setUserAccess(const User& user, const bool& access) {
  users_[user.getId()] = access;
}
