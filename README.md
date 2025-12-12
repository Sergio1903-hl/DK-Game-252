# Donkey Kong - C++ Game with SFML and Box2D

Un clon del clásico juego Donkey Kong implementado en C++ usando SFML para gráficos y Box2D para física.

## Características

### 🎮 Jugabilidad
- **Motor de física Box2D 3.x**: Física realista para el jugador, barriles y plataformas
- **Donkey Kong**: ¡El gorila está en la cima lanzando barriles!
- **Princesa**: Rescata a la princesa en la plataforma superior para ganar
- **Sistema de vidas**: 3 vidas para completar el nivel
- **Sistema de puntuación**: Rastrea tu progreso y gana puntos
- **Múltiples niveles**: El nivel aumenta al rescatar a la princesa

### 🎨 Gráficos
- **Soporte de sprites**: Texturas personalizadas para todos los elementos
- **Animaciones**: Personajes animados con sprites
- **Fondo personalizable**: Puedes agregar tu propio fondo

### 🎵 Audio
- **Música de fondo**: Música durante el juego y menú
- **Efectos de sonido**: Saltos, barriles, game over, victoria
- **Control de volumen**: Ajusta música y sonidos independientemente

### 📋 Menú
- **Menú principal**: Jugar, Ajustes, Salir
- **Menú de ajustes**: Control de volumen de música y sonidos
- **Pausa**: Sistema de pausa durante el juego

## Requisitos

- C++17 o superior
- SFML 2.5+
- Box2D 3.x (versión más reciente con la nueva API)
- Make o CMake

## Instalación de Dependencias

### Windows (MSYS2/MinGW64)
```bash
pacman -S mingw-w64-x86_64-sfml
pacman -S mingw-w64-x86_64-box2d
pacman -S mingw-w64-x86_64-gcc
pacman -S make
```

### Windows (vcpkg)
```bash
vcpkg install sfml
vcpkg install box2d
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libsfml-dev
sudo apt-get install libbox2d-dev
```

### macOS (Homebrew)
```bash
brew install sfml
brew install box2d
```

## Compilación

Con Make:
```bash
make
```

Con CMake:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

El ejecutable se generará en el directorio `bin/`.

## Ejecutar

```bash
make run
```

O directamente:
```bash
./bin/dk.exe
```

## Controles

### En el Menú
- **Flechas Arriba/Abajo**: Navegar opciones
- **Enter**: Seleccionar opción
- **Flechas Izquierda/Derecha** (en Ajustes): Cambiar volumen

### En el Juego
- **A/D o Flechas Izquierda/Derecha**: Mover
- **Espacio / W / Flecha Arriba**: Saltar
- **W / S en escalera**: Subir/bajar escaleras
- **ESC**: Pausar/Reanudar
- **M** (en pausa o game over): Volver al menú
- **R** (en game over): Reiniciar

## Estructura del Proyecto

```
dk/
├── include/          # Archivos de encabezado (.h)
│   ├── Game.h
│   ├── Player.h
│   ├── Platform.h
│   ├── Ladder.h
│   └── Barrel.h
├── src/              # Archivos de implementación (.cpp)
│   ├── dk.cpp
│   ├── Game.cpp
│   ├── Player.cpp
│   ├── Platform.cpp
│   ├── Ladder.cpp
│   └── Barrel.cpp
├── assets/           # Recursos (fuentes, texturas, etc.)
├── bin/              # Ejecutables compilados
└── CMakeLists.txt    # Configuración de CMake
```

## Mecánicas del Juego

### Jugador
- Movimiento horizontal con física realista
- Salto con gravedad de Box2D
- Capacidad para trepar escaleras
- Detección de colisiones con barriles

### Barriles
- Spawning automático desde la plataforma superior
- Física de rodamiento con Box2D
- Colisiones con plataformas
- Se eliminan al caer fuera de la pantalla

### Plataformas
- Estructuras estáticas con física de Box2D
- Múltiples niveles estilo Donkey Kong
- Fricción configurable

### Escaleras
- Permiten movimiento vertical
- Detección de proximidad para trepar
- Conectan diferentes niveles

## Desarrollo Futuro

- [ ] Agregar sprites y texturas
- [ ] Implementar Donkey Kong en la parte superior
- [ ] Añadir princesa/objetivo en el nivel superior
- [ ] Sistema de vidas múltiples
- [ ] Efectos de sonido y música
- [ ] Niveles adicionales
- [ ] Power-ups y bonus
- [ ] High scores persistentes

## Licencia

Este proyecto es de código abierto y está disponible para fines educativos.

## Créditos

Inspirado en el clásico arcade Donkey Kong de Nintendo (1981).