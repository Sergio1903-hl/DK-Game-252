# Cómo Agregar Sprites y Audio al Juego

## 📁 Estructura de Carpetas Creada

El juego ahora tiene la siguiente estructura de assets:

```
assets/
├── textures/     # Sprites e imágenes
├── sounds/       # Efectos de sonido (.wav, .ogg)
├── music/        # Música de fondo (.ogg)
└── fonts/        # Fuentes (.ttf)
```

## 🎨 PASO 1: Agregar Sprites (Opcional pero Recomendado)

### Archivos de Sprites Necesarios:

1. **`player.png`** (20x30 píxeles) - El jugador (Mario/Jumpman)
   - Colócalo en: `assets/textures/player.png`
   
2. **`barrel.png`** (30x30 píxeles) - Los barriles rodantes
   - Colócalo en: `assets/textures/barrel.png`
   
3. **`platform.png`** (cualquier tamaño) - Textura de plataformas
   - Colócalo en: `assets/textures/platform.png`
   
4. **`ladder.png`** (30x75 píxeles) - Las escaleras
   - Colócalo en: `assets/textures/ladder.png`
   
5. **`donkey_kong.png`** (60x80 píxeles) - Donkey Kong en la cima
   - Colócalo en: `assets/textures/donkey_kong.png`
   
6. **`princess.png`** (30x50 píxeles) - La princesa a rescatar
   - Colócalo en: `assets/textures/princess.png`
   
7. **`background.png`** (800x600 píxeles) - Fondo del juego
   - Colócalo en: `assets/textures/background.png`

### ⚠️ IMPORTANTE
- Si NO agregas las texturas, el juego funcionará con formas geométricas simples (cuadrados y círculos de colores)
- Los tamaños son recomendados pero el juego los escalará automáticamente
- Usa formato PNG con transparencia para mejores resultados

## 🎵 PASO 2: Agregar Audio (Opcional)

### Efectos de Sonido (.wav recomendado):

1. **`jump.wav`** - Sonido al saltar
   - Colócalo en: `assets/sounds/jump.wav`
   
2. **`barrel_roll.wav`** - Sonido cuando DK lanza un barril
   - Colócalo en: `assets/sounds/barrel_roll.wav`
   
3. **`game_over.wav`** - Sonido de game over
   - Colócalo en: `assets/sounds/game_over.wav`
   
4. **`win.wav`** - Sonido de victoria
   - Colócalo en: `assets/sounds/win.wav`
   
5. **`menu_select.wav`** - Sonido de selección en menú
   - Colócalo en: `assets/sounds/menu_select.wav`

### Música de Fondo (.ogg recomendado):

1. **`game_music.ogg`** - Música durante el juego
   - Colócalo en: `assets/music/game_music.ogg`

### ⚠️ IMPORTANTE
- Si NO agregas audio, el juego funcionará silenciosamente
- Usa formato OGG para música (menor tamaño, mejor loop)
- Usa formato WAV para efectos cortos

## 🔤 PASO 3: Agregar Fuente (Opcional)

1. **`arial.ttf`** (o cualquier fuente .ttf)
   - Colócalo en: `assets/fonts/arial.ttf`

### ⚠️ IMPORTANTE
- Si NO agregas fuente, el texto no se mostrará (pero el juego funcionará)
- Puedes usar cualquier fuente .ttf, solo nómbrala `arial.ttf` o modifica el código

## 🎨 Dónde Conseguir Assets Gratuitos

### Sprites:
- **OpenGameArt.org** - https://opengameart.org/
- **Itch.io Assets** - https://itch.io/game-assets/free
- **Kenney.nl** - https://kenney.nl/assets (excelentes assets 2D gratuitos)
- **Pixabay** - Para backgrounds e imágenes

### Sonidos:
- **Freesound.org** - https://freesound.org/
- **Zapsplat** - https://www.zapsplat.com/
- **OpenGameArt** - También tiene sonidos

### Música:
- **Incompetech** - https://incompetech.com/music/
- **FreePD.com** - Música de dominio público
- **OpenGameArt** - También tiene música

### Fuentes:
- **Google Fonts** - https://fonts.google.com/
- **DaFont** - https://www.dafont.com/
- **1001 Fonts** - https://www.1001fonts.com/

## 🛠️ Crear Sprites Simples Rápidamente

Si quieres probar el juego rápidamente sin buscar assets, puedes crear sprites simples:

### Con cualquier editor de imágenes (Paint, GIMP, Photoshop):

1. **Player**: Rectángulo rojo 20x30
2. **Barrel**: Círculo marrón 30x30
3. **Platform**: Rectángulo café cualquier tamaño
4. **Ladder**: Rectángulos amarillos 30x75
5. **DK**: Figura marrón grande 60x80
6. **Princess**: Figura rosa con corona 30x50
7. **Background**: Imagen negra o de ladrillos 800x600

### Colores Recomendados (Estilo Retro):
- **Player**: Rojo (#FF0000)
- **Barrel**: Marrón (#CD8563)
- **Platform**: Café oscuro (#8B4513)
- **Ladder**: Amarillo (#FFD700)
- **DK**: Marrón (#654321)
- **Princess**: Rosa (#FFC0CB)

## ✅ Verificar que Funcionó

1. Ejecuta el juego: `./bin/dk.exe`
2. Si ves las texturas/sprites en lugar de formas simples, ¡funcionó!
3. Si escuchas música y sonidos, ¡el audio funcionó!
4. Si ves texto en pantalla, ¡la fuente funcionó!

## 🔧 Troubleshooting

**Problema**: No se ven las texturas
- ✅ Verifica que los archivos estén en la carpeta correcta
- ✅ Verifica que los nombres sean exactamente como se especifican
- ✅ Verifica que los archivos sean PNG válidos

**Problema**: No se escucha audio
- ✅ Verifica que SFML Audio esté instalado
- ✅ Verifica la configuración de volumen en el menú de ajustes
- ✅ Verifica que los archivos de audio sean válidos

**Problema**: No se ve el texto
- ✅ Verifica que la fuente esté en `assets/fonts/arial.ttf`
- ✅ Usa cualquier archivo .ttf válido

## 🎮 ¡Listo para Jugar!

Una vez que agregues los assets (o sin ellos), ejecuta:

```bash
./bin/dk.exe
```

¡Disfruta el juego! 🎉
