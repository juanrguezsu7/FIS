#include "client_functions.hpp"

int main(int argc, char* argv[]) {
  system("clear");

  KeySystem sistema;

  // Hay que tener una llave y un usuario para pruebas
  User user_test("test");
  sistema.addUser(user_test);
  Key key_test("test", user_test);
  sistema.addKey(key_test);

  MenuSistema(sistema);

  system("clear");

  return EXIT_SUCCESS;
}