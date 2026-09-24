# 💣 Buscaminas en C++ (Consola)

Un juego interactivo de **Buscaminas** desarrollado en C++ orientada a objetos (POO). Incluye soporte para jugadores humanos y una IA (Modo Máquina), además de un sistema de persistencia para guardar y consultar el historial de partidas y estadísticas por jugador.

---

## 🎮 Características Principales

* **Modos de Juego:**
    * 🧑‍💻 **Humano:** Permite revelar casillas y colocar banderas de forma manual.
    * 🤖 **Máquina (IA):** Algoritmo de deducción lógica básica que infiere posiciones de minas y resuelve celdas seguras automáticamente.
* **Dificultades Configurarables:**
    * Fácil (18 minas)
    * Medio (40 minas)
    * Difícil (60 minas)
    * Personalizado (1 a 80 minas)
* **Persistencia de Datos:**
    * Registro de partidas finalizadas con fecha, hora, duración y resultado (Victoria/Derrota) en `historial.txt`.
    * Consulta de historial general e historial de puntuación/estadísticas agrupado por jugador.
    * Opción para vaciar el historial existente.
* **Mecanismos Clásicos:**
    * Revelado expansivo automático (flood fill) al seleccionar casillas sin minas vecinas.

---

## 🛠️ Tecnologías y Requisitos

* **Lenguaje:** C++20 (o superior)
* **Sistema de Construcción:** CMake (v4.1 o superior)
* **Compilador:** Compatible con GCC, Clang o MSVC

---

## 📂 Estructura del Proyecto

```text
.
├── CMakeLists.txt     # Configuración del proyecto CMake
├── main.cpp           # Menú principal y bucle de ejecución
├── Celda.h            # Clase para el manejo del estado individual de cada celda
├── Fecha.h            # Clase para gestión de estampa de tiempo
├── Historial.h        # Gestión de archivos, lectura y renderizado de resultados
├── Juego.h            # Control del flujo de una partida activa
├── Jugador.h          # Clases base y derivadas para Humano y IA (Polimorfismo)
├── Partida.h          # Representación de un registro individual de partida
├── Tablero.h          # Matriz de celdas y lógica del tablero
└── historial.txt      # Archivo plano de persistencia de partidas