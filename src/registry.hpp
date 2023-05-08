#pragma once

// Gestión de la clase Registry -> Implementar el historial de las llaves.

#include <iostream>
#include <list>
#include <ctime>

class Registry {
  public:
    void printRegistry() const;
    void addActionEntry(std::string usuario, bool modo);
    void addNotificationEntry(std::string usuario, std::string notificacion);
  private:
    std::string actual_timestamp_() const;
    std::list<std::string> entradas_;
};