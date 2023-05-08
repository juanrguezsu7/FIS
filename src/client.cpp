#include "client_functions.hpp"

int main(int argc, char* argv[]) {
  system("clear");

  KeySystem sistema;
  /*User user_test("test");
  sistema.addUser(user_test);
  Key key_test("1234", user_test);
  sistema.addKey(key_test);*/
  MenuSistema(sistema);

  system("clear");

  return EXIT_SUCCESS;
}