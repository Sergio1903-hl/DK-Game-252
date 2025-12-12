# Guía para Agregar Sprites y Audio

## Estructura de Assets

El juego ahora soporta texturas, sonidos y música. Coloca tus archivos en estas carpetas:

```
assets/
├── textures/
│   ├── OPCIÓN 1: Spritesheet (Recomendado para animación)
│   ├── player_spritesheet.png   # Spritesheet con frames de animación (4+ frames)
│   │
│   ├── OPCIÓN 2: Frames individuales
│   ├── player_walk_0.png        # Frame 0 de caminata - 20x30 píxeles
│   ├── player_walk_1.png        # Frame 1 de caminata
│   ├── player_walk_2.png        # Frame 2 de caminata
│   ├── player_walk_3.png        # Frame 3 de caminata
│   ├── player_idle_0.png        # Frame 0 parado
│   ├── player_idle_1.png        # Frame 1 parado
│   ├── player_jump.png          # Frame de salto
│   ├── player_climb_0.png       # Frame 0 escalando
│   ├── player_climb_1.png       # Frame 1 escalando
│   │
│   ├── platform.png        # Textura de plataforma - cualquier tamaño (se repetirá)
│   ├── ladder.png          # Textura de escalera - 30x75 píxeles
│   ├── barrel.png          # Sprite del barril - 30x30 píxeles
│   ├── donkey_kong.png     # Sprite de Donkey Kong - 60x80 píxeles
│   ├── princess.png        # Sprite de la princesa - 30x50 píxeles
│   └── background.png      # Fondo del juego - 800x600 píxeles
├── sounds/
│   ├── jump.wav            # Sonido de salto
│   ├── barrel_roll.wav     # Sonido de barril rodando
│   ├── game_over.wav       # Sonido de game over
│   ├── win.wav             # Sonido de victoria
│   └── menu_select.wav     # Sonido de selección en menú
├── music/
│   ├── game_music.ogg      # Música durante el juego
│   └── menu_music.ogg      # Música del menú
└── fonts/
    └── arial.ttf           # Fuente para texto (o cualquier otra fuente .ttf)
```

## Cómo Crear/Obtener Sprites

### Opción 1: Crear Sprites Simples
Puedes crear sprites simples usando cualquier editor de imágenes (GIMP, Paint.NET, Photoshop):

1. **Player (Spritesheet)**: Canvas de 128x32 con 4 frames de 32x32 lado a lado
2. **Player (Frames individuales)**: 4 imágenes de 20x30 para caminata
3. **Barrel**: Círculo marrón de 30x30 píxeles
4. **Platform**: Rectángulo café de cualquier tamaño
5. **Ladder**: Rectángulos amarillos verticales de 30x75
6. **Donkey Kong**: Figura marrón grande de 60x80
7. **Princess**: Figura rosada con corona de 30x50

### Opción 2: Sprites Pixelados Estilo Retro
Para un look más auténtico de Donkey Kong:
- Usa paletas de colores limitadas (3-5 colores por sprite)
- Mantén resoluciones bajas
- Usa pixeles grandes sin anti-aliasing

### Opción 3: Sprites de Ejemplo Gratuitos
Busca "donkey kong sprites" o "platformer sprites" en sitios como:
- OpenGameArt.org
- Itch.io (sección de assets)
- Kenney.nl (assets gratuitos)

## Formatos Soportados

- **Texturas**: PNG, JPG, BMP, TGA
- **Sonidos**: WAV, OGG (recomendado WAV para efectos cortos)
- **Música**: OGG, FLAC (recomendado OGG para música de fondo)
- **Fuentes**: TTF, OTF

## Notas Importantes

1. Si no colocas las texturas, el juego funcionará con formas geométricas simples (cuadrados y círculos de colores)
2. Los sonidos y música son opcionales - el juego funcionará sin audio
3. Las rutas son relativas a la carpeta del ejecutable
4. Para mejores resultados, usa archivos OGG comprimidos para música (menor tamaño)
5. **NUEVO**: El jugador soporta animación con múltiples frames - ver `SISTEMA_ANIMACION.md` para detalles
6. Puedes usar un spritesheet o frames individuales para la animación del jugador

## Ejemplo de Comandos para Obtener Assets

Si tienes imagemagick instalado, puedes crear sprites de prueba rápidamente:

```bash
# Crear sprites simples de colores
magick -size 20x30 xc:red assets/textures/player.png
magick -size 30x30 xc:brown assets/textures/barrel.png
magick -size 800x600 xc:black assets/textures/background.png
```

## Controles del Juego

- **Menú**: Flechas Arriba/Abajo, Enter para seleccionar
- **Juego**: 
  - A/D o Flechas: Mover izquierda/derecha
  - W/Flecha Arriba/Espacio: Saltar
  - W/S en escalera: Subir/Bajar
  - ESC: Pausar
  - R: Reiniciar (después de Game Over)

## Ajustes de Volumen

El menú de ajustes permite controlar:
- **Volumen de Música**: 0-100%
- **Volumen de Sonidos**: 0-100%

Usa las flechas Izquierda/Derecha para ajustar los volúmenes.
