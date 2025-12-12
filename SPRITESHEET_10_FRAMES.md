# Guía: Spritesheet de 10 Frames

## Configuración Actual

El juego está configurado para usar un **spritesheet de 10 frames** en una fila horizontal.

## Estructura del Spritesheet

### Archivo Requerido
```
assets/textures/player_spritesheet.png
```

### Layout del Spritesheet

```
┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
│ 0  │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │
└────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
  ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑
Frame 0-9: Ciclo completo de animación de caminata
```

## Especificaciones Técnicas

- **Número de columnas**: 10
- **Número de filas**: 1
- **Tamaño total del spritesheet**: `ancho_frame × 10` x `alto_frame`
- **Ejemplo**: Si cada frame es 32×32, el spritesheet será 320×32

### Ejemplo de Dimensiones

| Resolución por Frame | Tamaño Total del Spritesheet |
|---------------------|------------------------------|
| 16×24 píxeles       | 160×24 píxeles              |
| 20×30 píxeles       | 200×30 píxeles              |
| 32×32 píxeles       | 320×32 píxeles              |
| 32×48 píxeles       | 320×48 píxeles              |
| 64×64 píxeles       | 640×64 píxeles              |

**Nota**: El juego auto-escalará cada frame a 20×30 píxeles.

## Distribución Recomendada de Frames

Con 10 frames puedes crear una animación muy suave:

### Opción 1: Solo Caminata (10 frames)
```
Frame 0: Contacto pie izquierdo
Frame 1: Empuje pie izquierdo
Frame 2: Posición neutra (transición)
Frame 3: Contacto pie derecho
Frame 4: Empuje pie derecho
Frame 5: Posición neutra (transición)
Frame 6: Contacto pie izquierdo (repetición suave)
Frame 7: Empuje pie izquierdo
Frame 8: Posición neutra
Frame 9: Preparación para repetir ciclo
```

### Opción 2: Múltiples Estados
Puedes dividir los 10 frames para diferentes estados (requiere modificar código):

```
Frames 0-5: Caminata (6 frames)
Frames 6-7: Idle/Parado (2 frames)
Frame 8: Salto
Frame 9: Escalando
```

**Para usar Opción 2, necesitas modificar el código** (ver sección "Configuración Avanzada").

## Auto-Escalado

Cada frame del spritesheet se auto-escala a **20×30 píxeles** sin importar el tamaño original:

```
Spritesheet de 320×32 (10 frames de 32×32)
    ↓ auto-escala cada frame
Cada frame se muestra como 20×30
```

## Creando tu Spritesheet de 10 Frames

### Método 1: Editor de Imágenes Manual

**GIMP / Photoshop / Paint.NET:**

1. Crea un nuevo canvas:
   - Ancho: `tamaño_frame × 10`
   - Alto: `tamaño_frame`
   - Ejemplo: 320×32 para frames de 32×32

2. Divide el canvas en 10 secciones iguales:
   - Usa guías cada 32 píxeles (o tu tamaño de frame)

3. Dibuja o coloca cada frame de animación:
   - Frame 0 en posición X=0
   - Frame 1 en posición X=32
   - Frame 2 en posición X=64
   - ... y así sucesivamente

4. Asegúrate de que:
   - El fondo sea **transparente** (canal alpha)
   - Todos los frames estén **centrados verticalmente**
   - El personaje mire hacia la **derecha** (el juego lo voltea automáticamente)

5. Exporta como PNG con transparencia

### Método 2: Herramientas de Animación

**Aseprite (Recomendado):**
```
1. Crea animación de 10 frames
2. File → Export Sprite Sheet
3. Configura:
   - Layout: Horizontal Strip
   - Frames: 10
   - Include: Visible Layers
4. Exporta como player_spritesheet.png
```

**Piskel (Online, Gratis):**
```
1. Crea animación de 10 frames en piskelapp.com
2. Export → PNG → Sprite Sheet
3. Columns: 10, Rows: 1
4. Descarga y renombra a player_spritesheet.png
```

## Ejemplo de Código para Prueba

Si quieres probar temporalmente con un spritesheet diferente:

```cpp
// En Game.cpp, después de crear el jugador:
player->loadSpritesheet("assets/textures/mi_sprite_10frames.png", 10, 1);
```

## Velocidad de Animación

Con 10 frames, puedes ajustar la velocidad para que se vea fluida:

```cpp
// Más lento (más suave)
player->setFrameTime(0.08f);  // Cambia cada 0.08 segundos = 12.5 FPS

// Normal
player->setFrameTime(0.1f);   // Cambia cada 0.1 segundos = 10 FPS

// Más rápido
player->setFrameTime(0.05f);  // Cambia cada 0.05 segundos = 20 FPS
```

**Recomendado para 10 frames**: `0.08f` (velocidad media-lenta para animación suave)

## Plantilla para Crear Spritesheet

### Tamaño Recomendado: 320×48 (10 frames de 32×48)

**Guía de cuadrícula:**
```
┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│  0   │  32  │  64  │  96  │ 128  │ 160  │ 192  │ 224  │ 256  │ 288  │
│      │      │      │      │      │      │      │      │      │      │
│  32  │  64  │  96  │ 128  │ 160  │ 192  │ 224  │ 256  │ 288  │ 320  │
└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
Cada cuadro: 32×48 píxeles
```

## Tips para Animación de 10 Frames

### Para Caminata Suave:
1. **Frames 0-1**: Contacto del talón (pie izquierdo)
2. **Frames 2-3**: Peso en pie izquierdo, pie derecho levantándose
3. **Frame 4**: Posición neutra (ambos pies semi-aire)
4. **Frames 5-6**: Contacto del talón (pie derecho)
5. **Frames 7-8**: Peso en pie derecho, pie izquierdo levantándose
6. **Frame 9**: Posición neutra (preparación para repetir)

### Consejos de Animación:
- **Balanceo de brazos**: Opuestos a las piernas (cuando pie izquierdo adelante, brazo derecho adelante)
- **Altura del cuerpo**: Pequeñas variaciones (1-2 píxeles arriba/abajo)
- **Velocidad consistente**: Mantén el personaje centrado horizontalmente en cada frame
- **Timing**: Prueba diferentes velocidades con `setFrameTime()`

## Verificación

Al iniciar el juego, verás en consola:

```
Player spritesheet loaded: 320x48 (10 columns)
```

Esto confirma que el spritesheet de 10 frames se cargó correctamente.

## Troubleshooting

### "Player spritesheet loaded: 320x32 (10 columns)" pero se ve mal
- Verifica que **cada frame esté centrado** en su sección de 32 píxeles
- Asegúrate de que no haya **espacio entre frames**
- Comprueba que el fondo sea **completamente transparente**

### La animación es muy rápida/lenta
- Ajusta con `player.setFrameTime(0.08f)` en Game.cpp
- Para 10 frames, usa valores entre 0.06 y 0.12

### El personaje se ve distorsionado
- Usa proporciones cercanas a 2:3 (ancho:alto)
- Ejemplos buenos: 20×30, 32×48, 40×60

### Los frames se cortan o se superponen
- Verifica que el ancho total sea exactamente `frame_width × 10`
- No dejes padding/márgenes entre frames
- Usa herramientas con grid/snap activado

## Configuración Avanzada (Opcional)

Si quieres usar diferentes rangos de frames para diferentes estados:

```cpp
// En Player.cpp, modifica updateAnimation() para:

// Frames 0-5: Caminata
if (currentState == AnimationState::WALK) {
    currentFrame = (currentFrame % 6);  // Solo usa frames 0-5
}

// Frame 6-7: Idle
if (currentState == AnimationState::IDLE) {
    currentFrame = 6 + (currentFrame % 2);  // Alterna entre 6-7
}

// Frame 8: Salto
if (currentState == AnimationState::JUMP) {
    currentFrame = 8;  // Usa solo frame 8
}

// Frame 9: Escalando
if (currentState == AnimationState::CLIMB) {
    currentFrame = 9;  // Usa solo frame 9
}
```

## Recursos para Crear Sprites

- **Piskel** (piskelapp.com) - Editor online gratuito
- **Aseprite** ($19.99) - Mejor herramienta para pixel art
- **GraphicsGale** - Gratuito para Windows
- **LibreSprite** - Fork gratuito de Aseprite
- **Krita** - Gratuito, soporta animación

## Checklist Final

Antes de exportar tu spritesheet de 10 frames:

- [ ] Ancho total = frame_width × 10
- [ ] Alto = frame_height
- [ ] Fondo transparente (canal alpha)
- [ ] Personaje centrado en cada frame
- [ ] Personaje mirando hacia la derecha
- [ ] Sin padding entre frames
- [ ] Guardado como PNG
- [ ] Nombrado como `player_spritesheet.png`
- [ ] Colocado en `assets/textures/`

¡Con estos 10 frames tendrás una animación muy suave y profesional! 🎮✨
