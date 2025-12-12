# Sistema de Animación del Jugador

## Descripción

El juego ahora soporta animación de sprites con múltiples frames para el jugador (Jumpman/Mario). Puedes usar **dos métodos diferentes**:

1. **Spritesheet** - Una sola imagen con todos los frames en una cuadrícula
2. **Frames individuales** - Múltiples archivos PNG separados

## Estados de Animación

El jugador tiene 4 estados diferentes de animación:

- **IDLE** (Parado/Quieto) - Cuando no se mueve
- **WALK** (Caminando) - Cuando se mueve izquierda/derecha
- **JUMP** (Saltando) - Cuando está en el aire
- **CLIMB** (Escalando) - Cuando sube/baja escaleras

## Método 1: Spritesheet (Recomendado)

### Estructura del Spritesheet

Crea un archivo PNG con todos los frames en una fila horizontal:

```
player_spritesheet.png
┌────┬────┬────┬────┐
│ 1  │ 2  │ 3  │ 4  │  <- Frames de caminata
└────┴────┴────┴────┘
```

**Ejemplo con 4 frames:**
- Frame 0: Paso 1 (pie izquierdo adelante)
- Frame 1: Posición neutra
- Frame 2: Paso 2 (pie derecho adelante)
- Frame 3: Posición neutra

### Especificaciones:

- **Nombre del archivo**: `player_spritesheet.png`
- **Ubicación**: `assets/textures/`
- **Columnas**: 4 (por defecto, configurable)
- **Filas**: 1 (por defecto, configurable)
- **Tamaño de cada frame**: Cualquier tamaño (se auto-escala a 20x30)
- **Formato**: PNG con transparencia

### Ejemplo de Uso:

```cpp
// El juego automáticamente detecta y carga player_spritesheet.png
// Para usar un spritesheet personalizado:
player.loadSpritesheet("assets/textures/mi_spritesheet.png", 6, 2);
//                       ruta del archivo                    columnas, filas
```

## Método 2: Frames Individuales

### Estructura de Archivos

Crea archivos PNG separados para cada estado:

```
assets/textures/
├── player_walk_0.png    # Caminata frame 1
├── player_walk_1.png    # Caminata frame 2
├── player_walk_2.png    # Caminata frame 3
├── player_walk_3.png    # Caminata frame 4
├── player_idle_0.png    # Parado frame 1
├── player_idle_1.png    # Parado frame 2 (opcional, para respiración)
├── player_jump.png      # Saltando
├── player_climb_0.png   # Escalando frame 1
└── player_climb_1.png   # Escalando frame 2
```

### Nomenclatura Importante:

| Estado | Patrón de Nombre | Frames Requeridos |
|--------|-----------------|-------------------|
| **Caminando** | `player_walk_X.png` | 4 (X = 0, 1, 2, 3) |
| **Parado** | `player_idle_X.png` | 2 (X = 0, 1) |
| **Saltando** | `player_jump.png` | 1 |
| **Escalando** | `player_climb_X.png` | 2 (X = 0, 1) |

**Nota**: Si faltan algunos frames, el juego usará formas geométricas como respaldo.

## Auto-Escalado

**Todas las texturas se auto-escalan automáticamente** a 20x30 píxeles, sin importar su tamaño original:

- Spritesheet de 400x100 → Cada frame se escala a 20x30
- Frames individuales de 64x64 → Se escalan a 20x30
- Frames de 16x24 → Se escalan a 20x30

El sistema **preserva el aspecto original** usando escala independiente X/Y.

## Velocidad de Animación

Por defecto, los frames cambian cada **0.1 segundos** (10 FPS).

Para cambiar la velocidad:

```cpp
player.setFrameTime(0.05f);  // Más rápido (20 FPS)
player.setFrameTime(0.2f);   // Más lento (5 FPS)
```

## Creando tu Spritesheet

### Opción A: Editor de Imágenes (GIMP, Photoshop, etc.)

1. Crea un canvas del tamaño: `ancho_frame × num_frames` x `alto_frame`
   - Ejemplo 4 frames de 32x32: Canvas de 128x32
2. Coloca cada frame lado a lado
3. Exporta como PNG con transparencia
4. Guarda en `assets/textures/player_spritesheet.png`

### Opción B: Herramientas Online

- **Piskel** (piskelapp.com) - Editor de pixel art con exportación de spritesheet
- **Aseprite** - Software profesional para pixel art y animación
- **GraphicsGale** - Editor gratuito para sprites

### Opción C: Assets Prehechos

Busca "platformer character spritesheet" en:
- OpenGameArt.org
- Itch.io (Free Game Assets)
- Kenney.nl

## Ejemplo de Código Personalizado

```cpp
// En Game.cpp, después de crear el jugador:

// Método 1: Cargar spritesheet personalizado de 8 frames x 2 filas
player->loadSpritesheet("assets/textures/hero_sheet.png", 8, 2);

// Método 2: Ajustar velocidad de animación
player->setFrameTime(0.08f);  // Animación más suave
```

## Prioridad de Carga

El sistema intenta cargar en este orden:

1. **Spritesheet** (`player_spritesheet.png`) - Si existe, usa este
2. **Frames de caminata** (`player_walk_X.png`) - Si no hay spritesheet, busca estos
3. **Otros frames** - Intenta cargar idle, jump, climb
4. **Formas geométricas** - Si no hay texturas, usa rectángulo rojo

## Voltear Sprite (Flipping)

El sprite **automáticamente se voltea horizontalmente** según la dirección:
- Mirando a la derecha → Normal
- Mirando a la izquierda → Volteado (espejo)

**No necesitas crear frames separados para izquierda/derecha**, el juego los voltea automáticamente.

## Tips para Mejores Resultados

1. **Usa PNG con transparencia** - Fondo transparente (canal alpha)
2. **Mantén proporciones consistentes** - Todos los frames del mismo tamaño
3. **Usa pixel art** - Para estilo retro auténtico
4. **4-8 frames para caminar** - Mínimo 4, ideal 6-8 para suavidad
5. **Centro de masa consistente** - El personaje debe estar centrado en cada frame
6. **Respeta el estilo Donkey Kong** - Colores limitados, píxeles grandes

## Resolución Recomendada por Frame

Para mejor calidad visual con auto-escalado a 20x30:

- **Mínimo**: 20x30 (1:1, sin escalado)
- **Ideal**: 40x60 o 60x90 (escala 2x-3x para mejor detalle)
- **Máximo práctico**: 80x120 (escala 4x, más detalle pero archivo grande)

## Troubleshooting

### "Warning: Could not load player animations, using shape"
- Verifica que los archivos existan en `assets/textures/`
- Verifica los nombres de archivo (distingue mayúsculas/minúsculas)
- Asegúrate que sean PNG válidos

### La animación es muy rápida/lenta
- Ajusta con `player.setFrameTime(0.1f)`
- Valores comunes: 0.05 (rápido), 0.1 (normal), 0.2 (lento)

### El sprite se ve distorsionado
- Verifica que las proporciones sean similares a 2:3 (ancho:alto)
- El juego escala a 20x30, diseña tus sprites cerca de esa proporción

### El sprite no se voltea correctamente
- Asegúrate que el centro de masa esté en el centro del frame
- El sistema automáticamente voltea, no necesitas frames de izquierda

## Ejemplo Completo: Pack de Assets Mínimo

```
assets/textures/
└── player_spritesheet.png    # 128x32 (4 frames de 32x32)
    Frame 0: Paso izquierdo
    Frame 1: Posición central
    Frame 2: Paso derecho
    Frame 3: Posición central
```

¡Con solo este archivo tendrás animación de caminar fluida!

## Consola de Debug

Al iniciar el juego verás mensajes como:

```
Player spritesheet loaded: 128x32 (4 columns)
```

O si usas frames individuales:

```
Player walk frames loaded: 4 frames
```

Esto confirma que las animaciones se cargaron correctamente.
