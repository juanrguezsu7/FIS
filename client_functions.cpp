#include "client_functions.hpp"

/**
 * @brief Pausa el programa durante una cantidad de segundos (implementación basada en llamadas al sistema operativo).
 * 
 * @param segundos Segundos a pausar.
 */
void Pausar(const unsigned segundos) {
  #ifdef _WIN32
    Sleep(segundos * 1000);
  #else
    sleep(segundos);
  #endif
}

/**
 * @brief Intenta que un usuario del sistema autentique una llave para tener acceso a ella.
 * 
 * @param usuario Usuario a autenticar la llave (introducido por el usuario).
 * @param llave Llave a autenticar.
 * @param sistema Sistema con todos los usuarios y llaves.
 * @return 0 si se ha autenticado correctamente o -1 si no.
 * 
 * @note INTENTOS_RESTANTES es una variable global definida en client_functions.hpp que determina el número de intentos antes de pausarse 3 segundos.
 */
int Autenticacion(User& usuario, Key& llave, KeySystem& sistema) {
  int intentos_restantes{INTENTOS_RESTANTES};
  std::cout << "\t***Autenticación***\n";
  while (intentos_restantes > 0) {
    std::cout << "Nombre: ";
    std::string nombre;
    std::cin >> nombre;
    if (!sistema.userExists(nombre)) {
      --intentos_restantes;
      std::cout << "El usuario NO existe en el sistema.\n";
      std::cout << intentos_restantes << " intentos restantes.\n";
      continue;
    }
    std::cout << "Contraseña de llave: ";
    std::string contraseña;
    std::cin >> contraseña;
    if (llave.getPassword() != contraseña) {
      --intentos_restantes;
      std::cout << "Contraseña incorrecta.\n";
      std::cout << intentos_restantes << " intentos restantes.\n";
      continue;
    }
    std::cout << "***Autenticación correcta como \"" << nombre << "\"***" << std::endl;
    usuario = sistema.getUser(nombre);
    return 0;
  }
  return -1;
}

/**
 * @brief Menú interactivo en donde primero se autentica un usuario cualquiera del sistema y una llave específica para poder realizar operaciones sobre la llave. 
 * 
 * @param llave Llave con la que interactuar.
 * @param sistema Sistema con todos los usuarios y llaves.
 */
void MenuLlave(Key& llave, KeySystem& sistema) {
  User usuario;
  if (Autenticacion(usuario, llave, sistema) < 0) {
    std::cout << "Autenticación fallida, espere 3 segundos.\n";
    Pausar(3);
    return;
  }
  while (true) {
    std::cout << "[1] Abrir.\n[2] Cerrar.\n[3] Añadir usuario a la llave.\n[4] Salir\n";
    std::string opcion;
    std::cin >> opcion;
    switch (opcion[0]) {
      case '1':
        sistema.openKey(llave, usuario);
        break;
      case '2':
        {
        sistema.closeKey(llave, usuario);
        break;
        }
      case '3':
        {
        std::string nuevo_usuario;
        std::cout << "¿A qué usuario desea darle permisos?: ";
        std::cin >> nuevo_usuario;
        if (sistema.userExists(nuevo_usuario)) sistema.addUserToKey(llave, usuario);
        else std::cout << "Usuario no existente.\n";
        break;
        }
      case '4':
        return;
      default:
        std::cout << "Opción errónea\n";
    }
    std::cout << std::endl;
    Pausar(1);
  }
}

/**
 * @brief Menú interactivo donde se pueden añadir usuarios, llaves o mostrar estos datos al sistema aparte de seleccionar una llave específica.
 * 
 * @param sistema Sistema con todos los usuarios y llaves.
 */
void MenuSistema(KeySystem& sistema) {
  std::cout << "\t***Sistema de gestión de cerraduras***\n";
  while (true) {
    std::cout << "[1] Seleccionar llave.\n[2] Añadir llave al sistema.\n[3] Añadir usuario al sistema.\n[4] Mostrar llaves.\n[5] Mostrar usuarios.\n[6] Salir\n";
    std::string opcion;
    std::cin >> opcion;
    switch (opcion[0]) {
      case '1':
        {
        unsigned key_id;
        std::string raw;
        std::cout << "Introduza la ID de la llave: ";
        std::cin >> raw;
        try {
          key_id = std::stoi(raw);
        }
        catch (std::invalid_argument& exp) {
          std::cout << "La ID debe ser numérica.\n\n";
          continue;
        }
        if (key_id >= Key::contador_id_keys) {
          std::cout << "¡Llave no existente!\n";
        } else {
          MenuLlave(sistema.getKey(key_id), sistema);
        }
        break;
        }
      case '2':
        {
        Key llave;
        std::cin >> llave;
        sistema.addKey(llave);
        break;
        }
      case '3':
        {
        User usuario;
        std::cin >> usuario;
        sistema.addUser(usuario);
        break;
        }
      case '4':
        {
        sistema.mostrarLlaves();
        break;
        }
      case '5':
        {
        sistema.mostrarUsuarios();
        break;
        }
      case '6':
        return;
      default:
        std::cout << "Opción errónea\n";
    }
    std::cout << std::endl;
    Pausar(1);
  }
}