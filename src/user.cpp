#include "user.hpp"

unsigned User::contador_id_users = 0;

/* std::istream& operator>>(std::istream& in, User& user) {
  std::cout << "Introduzca el nombre del nuevo usuario con ID " << User::contador_id_users << " >>> ";
  std::string nombre;
  in >> nombre;
  user = User{nombre, User::contador_id_users};
  ++User::contador_id_users;
  return in;
} */