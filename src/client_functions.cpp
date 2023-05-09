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
    #ifndef _WIN32
      system("clear");
    #endif
    std::cout << "*** Autenticación en el sistema ***\n\n";
    std::cout << "Nombre de usuario >>> ";
    std::string nombre;
    std::cin >> nombre;
    if (!sistema.userExists(nombre)) {
      --intentos_restantes;
      std::cout << "El usuario NO existe en el sistema.\n";
      std::cout << intentos_restantes << " intentos restantes.\n";
      continue;
    }
    std::cout << "Contraseña de llave >>> ";
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
  User user;
  if (Autenticacion(user, llave, sistema) < 0) {
    std::cout << "Autenticación fallida, espere 5 segundos.\n";
    Pausar(5);
    return;
  }
  while (true) {
    #ifndef _WIN32
      system("clear");
    #endif
    std::cout << "*** Gestión de la llave ID(" << llave.getId()
              << ") como USER(" << user.getName()
              << ") ***\n\n"
                 "[0] - Mostrar llave.\n"
                 "[1] - Cambiar contraseña.\n"
                 "[2] - Abrir/Cerrar.\n\n"
                 "[3] - Mostrar si el usuario tiene acceso.\n"
                 "[4] - Añadir usuario a la llave.\n"
                 "[5] - Eliminar usuario de la llave.\n\n"
                 "[6] - Mostrar historial de incidencias.\n"
                 "[7] - Notificar incidencia.\n\n"
                 "[8] - Salir.\n\n>>> ";
    std::string opcion;
    std::cin >> opcion;
    std::cout << "\n";
    switch (opcion[0]) {
      case '0': {  // Mostrar llave
        std::cout << "ID/Contraseña/Estado: " << llave.getId() << '/';
        for (int i{0}; i < llave.getPassword().length(); ++i) {
          std::cout << '*';
        }
        std::cout << '/' << (llave.getState() ? "Abierta" : "Cerrada");
        break;
      }
      case '1':{  // Cambiar contraseña
      std::string str_old, str_new;
        std::cout << "Introduce la contraseña actual >>> ";
        std::cin >> str_old;
        if (str_old != llave.getPassword()) {
          std::cout << "Contraseña incorrecta.";
        } else {
          std::cout << "Contraseña correcta.\n";
          std::string str_new;
          std::cout << "Introduce la contraseña nueva >>> ";
          std::cin >> str_new;
          llave.setPassword(str_new);
          std::cout << "Contraseña cambiada correctamente.";
        }
        std::cout << '\n';
        break;
      }
      case '2': {  // Abrir/Cerrar
        if (llave.getUserAccess(user)) {
          !llave.getState() ? sistema.openKey(llave, user)
                            : sistema.closeKey(llave, user);
        } else {
          std::cout << "Comprueba primero si tienes acceso a la cerradura\n";
        }
        break;
      }
      case '3': {  // Muestra si el usuario tiene acceso
        std::cout << "ID/Nombre/Acceso:" << user.getName() << '/'
                  << user.getId() << "/"
                  << (llave.getUserAccess(user) ? "Si" : "No") << "\n";
        Pausar(2);
        break;
      }
      case '4': {  // Conceder acceso a usuario
        std::string user;
        sistema.mostrarUsuarios();
        std::cout << "¿A qué usuario desea darle permisos?: ";
        std::cin >> user;
        if (sistema.userExists(user))
          sistema.addUserToKey(llave, sistema.getUser(user));
        else
          std::cout << "Usuario no existente.\n";
        break;
      }
      case '5': {  // Denegar acceso a usuario
        std::string user;
        sistema.mostrarUsuarios();
        std::cout << "¿A qué usuario desea eliminar de la llave?: ";
        std::cin >> user;
        if (sistema.userExists(user))
          sistema.delUserFromKey(llave, sistema.getUser(user));
        else
          std::cout << "Usuario no existente.\n";
        break;
      }
      case '6': {  // Muestra las incidencias
        llave.printRegistry();
        Pausar(2);
        break;
      }
      case '7': {  // Notifica una incidencia
        std::string incidencia;
        std::cout << "Describa la incidencia: ";
        std::cin.ignore();
        std::getline(std::cin, incidencia);
        llave.addNotification(user, incidencia);
        std::cout << "Incidencia registrada correctamente, un administrador le "
                     "contactará pronto\n";
        break;
      }
      case '8':  // Salir
        return;
      default:  // Opción incorrecta
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
    #ifndef _WIN32
      system("clear");
    #endif
    std::cout << "*** Sistema de gestión de cerraduras ***\n";
    std::cout
        << "\n[1] - Seleccionar llave.\n\n[2] - Añadir llave al "
           "sistema.\n[3] - Añadir usuario al sistema.\n\n[4] - Eliminar llave "
           "del "
           "sistema.\n[5] - Eliminar usuario del sistema.\n\n[6] - Mostrar "
           "llaves.\n[7] - Mostrar usuarios.\n\n[8] - Salir.\n\n>>> ";
    std::string opcion;
    std::cin >> opcion;
    std::cout << "\n";
    switch (opcion[0]) {
      case '1': {  // Seleccionar llave
        sistema.mostrarLlaves();
        if (sistema.getKeys().empty()) {
          std::cout << "Agrega una llave al sistema primero.\n";
        } else {
          unsigned key_id;
          std::string raw;
          std::cout << "Introduza la ID de la llave >>> ";
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
      case '2': {  // Añadir llave al sistema
        std::string str;
        std::cout << "Introduce la contraseña de la llave >>> ";
        std::cin >> str;
        Key new_key(str);
        sistema.addKey(new_key);
        break;
      }
      case '3': {  // Añadir usuario al sistema
        std::string str;
        std::cout << "Introduce el nombre del usuario >>> ";
        std::cin >> str;
        User new_user(str);
        sistema.addUser(new_user);
        break;
      }
      case '4': {  // Eliminar llave del sistema
        unsigned key_id;
        std::string str;
        sistema.mostrarLlaves();
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
      case '5': {  // Eliminar usuario del sistema
        std::string str;
        sistema.mostrarUsuarios();
        std::cout << "Introduce el nombre del usuario >>> ";
        std::cin >> str;
        if (sistema.userExists(str)) {
          sistema.delUser(sistema.getUser(str));
        } else {
          std::cout << "Usuario no existente.\n";
        }
        break;
      }
      case '6': {  // Muestra llaves del sistema
        sistema.mostrarLlaves();
        Pausar(2);
        break;
      }
      case '7': {  // Muestra usuarios del sistema
        sistema.mostrarUsuarios();
        Pausar(2);
        break;
      }
      case '8':  // Salir
        return;
      default:  // Opción incorrecta
        std::cout << "Opción errónea\n";
    }
    std::cout << std::endl;
    Pausar(1);
  }
}