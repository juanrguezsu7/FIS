#pragma once

// Este fichero contiene todas las funciones del menú principal y del programa
// cliente.

// Directivas para la función Pausar() que depende del SO.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "keysystem.hpp"

int constexpr INTENTOS_RESTANTES{3};

void Pausar(const unsigned segundos);
int Autenticacion(User& usuario, Key& llave, KeySystem& sistema);
void MenuLlave(Key& llave, KeySystem& sistema);
void MenuSistema(KeySystem& sistema);