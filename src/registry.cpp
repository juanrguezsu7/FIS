#include "registry.hpp"

/**
 * @brief Imprime por pantalla el contenido del historial.
 */
void Registry::printRegistry() const {
  for (auto entrada : entradas_) std::cout << entrada << '\n';
}

/**
 * @brief Añade una entrada de acciones sobre la llave al historial.
 *
 * @param usuario Usuario que cierra/abre la llave.
 * @param modo Modo de acción; False para cerrar, True para abrir.
 */
void Registry::addActionEntry(std::string usuario, bool modo) {
  std::string entrada{"\"" + usuario + "\" " + (modo ? "abrió" : "cerró") + " la llave el " + actual_timestamp_()};
  entradas_.push_back(entrada);
}

/**
 * @brief Añade una entrada de notificaciones/incidencias sobre la llave al historial.
 * @param usuario Usuario que registra la incidencia.
 * @param notificacion Notificacion registrada.
 */
void Registry::addNotificationEntry(std::string usuario, std::string notificacion) {
  std::string entrada{"\"" + usuario + "\" " + "el " + actual_timestamp_()};
  entrada.pop_back(); // Quitar el salto de línea.
  entrada += " notificó: \"" + notificacion + "\"\n";
  entradas_.push_back(entrada);
}

/**
 * @brief Calcula la fecha e instante donde se produjo la acción sobre la llave.
 * 
 * @return String con la marca de tiempo formateado.
 */
std::string Registry::actual_timestamp_() const {
  // Obtener el tiempo actual en segundos desde 00:00:00 GMT, Jan 1, 1970.
  time_t raw_tiempo_actual{time(nullptr)};
  // La struct 'tm' separa el tiempo en segundos, minutos, horas, días, etc.
  struct tm* tiempo_actual{localtime(&raw_tiempo_actual)};
  // Devuelve el tiempo formateado como "Fri Sep 16 13:29:51 1994".
  return asctime(tiempo_actual);
}