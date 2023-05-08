#include "client_functions.hpp"

/**
 * @brief Pausa el programa durante una cantidad de segundos (implementación
 * basada en llamadas al sistema operativo).
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
 * @brief Intenta que un usuario del sistema autentique una llave para tener
 * acceso a ella.
 *
 * @param usuario Usuario a autenticar la llave (introducido por el usuario).
 * @param llave Llave a autenticar.
 * @param sistema Sistema con todos los usuarios y llaves.
 * @return 0 si se ha autenticado correctamente o -1 si no.
 *
 * @note INTENTOS_RESTANTES es una variable global definida en
 * client_functions.hpp que determina el número de intentos antes de pausarse 3
 * segundos.
 */
int Autenticacion(User& usuario, Key& llave, KeySystem& sistema) {
  int intentos_restantes{INTENTOS_RESTANTES};
  while (intentos_restantes > 0) {
    std::cout << "\n*** Autenticación ***\n\n";
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
    std::cout << "*** Autenticación correcta como \"" << nombre << "\" ***"
              << std::endl;
    usuario = sistema.getUser(nombre);
    return 0;
  }
  return -1;
}

/**
 * @brief Menú interactivo en donde primero se autentica un usuario cualquiera
 * del sistema y una llave específica para poder realizar operaciones sobre la
 * llave.
 *
 * @param llave Llave con la que interactuar.
 * @param sistema Sistema con todos los usuarios y llaves.
 */
void MenuLlave(Key& llave, KeySystem& sistema) {
  User usuario;
  if (Autenticacion(usuario, llave, sistema) < 0) {
    std::cout << "Autenticación fallida, espere 5 segundos.\n";
    Pausar(5);
    return;
  }
  while (true) {
    std::cout
        << "*** Gestión de la llave id=" + std::to_string(llave.getId()) +
               "***\n\n[1] - Abrir.\n[2] - Cerrar.\n\n[3] - Añadir usuario a la "
               "llave.\n[4] - Eliminar usuario de la llave.\n\n[5] - Mostrar historial.\n\n[6] - Notificar incidencia.\n\n[7] - Salir.\n\n>>> ";
    std::string opcion;
    std::cin >> opcion;
    std::cout << "\n";
    switch (opcion[0]) {
      case '1':
        sistema.openKey(llave, usuario);
        break;
      case '2': {
        sistema.closeKey(llave, usuario);
        break;
      }
      case '3': {
        std::string nuevo_usuario;
        std::cout << "¿A qué usuario desea darle permisos?: ";
        std::cin >> nuevo_usuario;
        if (sistema.userExists(nuevo_usuario))
          sistema.addUserToKey(llave, sistema.getUser(nuevo_usuario));
        else
          std::cout << "Usuario no existente.\n";
        break;
      }
      case '4': {
        std::string eliminar_usuario;
        std::cout << "¿A qué usuario desea eliminar de la llave?: ";
        std::cin >> eliminar_usuario;
        if (sistema.userExists(eliminar_usuario))
          sistema.delUserFromKey(llave, sistema.getUser(eliminar_usuario));
        else
          std::cout << "Usuario no existente.\n";
        break;
      }
      case '5':
        llave.printRegistry();
        break;
      case '6': {
        std::string incidencia;
        std::cout << "Describa la incidencia: ";
        std::cin.ignore();
        std::getline(std::cin, incidencia);
        llave.addNotification(usuario, incidencia);
        std::cout << "Incidencia registrada correctamente, un administrador le contactará pronto\n";
        break;
      }
      case '7':
        return;
      default:
        std::cout << "Opción errónea\n";
    }
    std::cout << std::endl;
    Pausar(1);
  }
}

/**
 * @brief Menú interactivo donde se pueden añadir usuarios, llaves o mostrar
 * estos datos al sistema aparte de seleccionar una llave específica.
 *
 * @param sistema Sistema con todos los usuarios y llaves.
 */
void MenuSistema(KeySystem& sistema) {
  while (true) {
    std::cout << "*** Sistema de gestión de cerraduras ***\n";
    std::cout << "\n[1] - Seleccionar llave.\n\n[2] - Añadir llave al "
                 "sistema.\n[3] - Añadir usuario al sistema.\n\n[4] - Eliminar llave del "
                 "sistema.\n[5] - Eliminar usuario del sistema.\n\n[6] - Mostrar "
                 "llaves.\n[7] - Mostrar usuarios.\n\n[8] - Salir.\n\n>>> ";
    std::string opcion;
    std::cin >> opcion;
    std::cout << "\n";
    switch (opcion[0]) {
      case '1': {
        sistema.mostrarLlaves();
        if (sistema.getKeys().empty()) {
          std::cout << "Agrega una llave al sistema primero.\n";
        } else {
          unsigned key_id;
          std::string raw;
          std::cout << "Introduza la ID de la llave: ";
          std::cin >> raw;
          try {
            key_id = std::stoi(raw);
          } catch (std::invalid_argument& exp) {
            std::cout << "La ID debe ser numérica.\n\n";
            continue;
          }
          if (sistema.keyExists(key_id)) {
            MenuLlave(sistema.getKey(key_id), sistema);
          } else {
            std::cout << "¡Llave no existente!\n";
          }
        }
        break;
      }
      case '2': {
        std::string str;
        std::cout << "Introduce la contraseña de la llave >>> ";
        std::cin >> str;
        Key new_key(str);
        sistema.addKey(new_key);
        break;
      }
      case '3': {
        std::string str;
        std::cout << "Introduce el nombre del usuario >>> ";
        std::cin >> str;
        User new_user(str);
        sistema.addUser(new_user);
        break;
      }
      case '4': {
        unsigned key_id;
        std::string str;
        std::cout << "Introduce la ID de la llave a eliminar >>> ";
        std::cin >> str;
        try {
          key_id = std::stoi(str);
        } catch (std::invalid_argument& exp) {
          std::cout << "La ID debe ser numérica.\n\n";
          continue;
        }
        if (sistema.keyExists(key_id)) {
          sistema.delKey(sistema.getKey(key_id));
        } else {
          std::cout << "¡Llave no existente!\n";
        }
        break;
      }
      case '5': {
        std::string str;
        std::cout << "Introduce el nombre del usuario >>> ";
        std::cin >> str;
        if (sistema.userExists(str)) {
          sistema.delUser(sistema.getUser(str));
        } else {
          std::cout << "Usuario no existente.\n";
        }
        break;
      }
      case '6': {
        sistema.mostrarLlaves();
        break;
      }
      case '7': {
        sistema.mostrarUsuarios();
        break;
      }
      case '8':
        return;
      default:
        std::cout << "Opción errónea\n";
    }
    std::cout << std::endl;
    Pausar(1);
  }
}