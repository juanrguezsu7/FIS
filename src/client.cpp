#include "client_functions.hpp"

int main(int argc, char* argv[]) {
  #ifndef _WIN32
    system("clear");
  #endif

  KeySystem sistema;

  // Hay que tener una llave y un usuario para pruebas
  User user_test("test");
  sistema.addUser(user_test);
  Key key_test("test", user_test);
  sistema.addKey(key_test);

  MenuSistema(sistema);

  #ifndef _WIN32
    system("clear");
  #endif

  return EXIT_SUCCESS;
}