# 🎮 Sistema de Animación con 10 Frames - LISTO

## ✅ Estado Actual

El juego ahora está **configurado para usar spritesheets de 10 frames**.

### Cambios Aplicados:
- ✅ Configuración actualizada: `sheetColumns = 10`
- ✅ Sistema de animación multi-frame implementado
- ✅ Auto-escalado automático a 20×30 píxeles
- ✅ Soporte para spritesheet o frames individuales
- ✅ Compilación exitosa

## 📁 Documentación Creada

1. **SPRITESHEET_10_FRAMES.md**
   - Guía completa para crear spritesheet de 10 frames
   - Especificaciones técnicas
   - Velocidad de animación
   - Tips y troubleshooting

2. **EJEMPLO_VISUAL_10_FRAMES.md**
   - Representación visual frame por frame
   - Template con medidas exactas
   - Paleta de colores Donkey Kong
   - Comparación 4 vs 10 frames

3. **verify_spritesheet.py**
   - Script Python para verificar tu spritesheet
   - Genera spritesheet de prueba
   - Valida dimensiones y formato

4. **SISTEMA_ANIMACION.md** (actualizado previamente)
   - Sistema completo de animación
   - Estados: IDLE, WALK, JUMP, CLIMB

## 🚀 Cómo Usar tu Spritesheet de 10 Frames

### Opción 1: Spritesheet Simple (Recomendado)

1. **Crea tu spritesheet** con 10 frames en una fila:
   ```
   Dimensiones: (ancho_frame × 10) x alto_frame
   Ejemplo: 320×48 (10 frames de 32×48)
   ```

2. **Guárdalo como PNG** con transparencia

3. **Nómbralo**: `player_spritesheet.png`

4. **Colócalo en**: `assets/textures/`

5. **¡Listo!** El juego lo detectará automáticamente

### Opción 2: Verificar antes de usar

```bash
# Verificar tu spritesheet
python verify_spritesheet.py tu_spritesheet.png

# O crear uno de prueba
python verify_spritesheet.py --create-test
```

## 📐 Especificaciones del Spritesheet

### Estructura:
```
┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
│ 0  │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │
└────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
```

### Dimensiones Recomendadas:
| Frame Size | Spritesheet Total | Calidad |
|-----------|-------------------|---------|
| 20×30     | 200×30           | Mínima  |
| 32×48     | 320×48           | ⭐ Buena |
| 40×60     | 400×60           | ⭐⭐ Muy Buena |
| 64×96     | 640×96           | ⭐⭐⭐ Excelente |

**Recomendado**: 32×48 o 40×60

## 🎨 Distribución de Frames Sugerida

### Para Caminata Fluida (10 frames):
```
Frame 0-1: Contacto y empuje pie izquierdo
Frame 2:   Transición/elevación
Frame 3-4: Contacto y empuje pie derecho  
Frame 5:   Transición central
Frame 6-7: Contacto y empuje pie izquierdo (variación)
Frame 8:   Elevación alta
Frame 9:   Preparación para loop
```

## ⚙️ Configuración de Velocidad

En el código (opcional):

```cpp
// En Game.cpp, después de crear el jugador:

// Ajustar velocidad de animación
player->setFrameTime(0.08f);  // Recomendado para 10 frames

// Otras velocidades:
// 0.05f = Rápido (20 FPS)
// 0.08f = Normal-suave (12.5 FPS) ⭐
// 0.10f = Normal (10 FPS)
// 0.12f = Lento (8.3 FPS)
```

## 🛠️ Herramientas para Crear

### Online (Gratis):
- **Piskel** (piskelapp.com) - Recomendado para principiantes
  1. Crea 10 frames
  2. Export → Sprite Sheet
  3. Columns: 10, Rows: 1

### Desktop:
- **Aseprite** ($19.99) - Mejor opción profesional
- **GraphicsGale** (Gratis) - Windows
- **LibreSprite** (Gratis) - Fork de Aseprite
- **GIMP/Photoshop** - Con grid de 32px

## 📋 Checklist Rápido

Antes de copiar tu spritesheet:

- [ ] 10 frames en fila horizontal
- [ ] Ancho total = `frame_width × 10`
- [ ] Formato PNG con transparencia (RGBA)
- [ ] Sin espacio entre frames
- [ ] Personaje centrado en cada frame
- [ ] Personaje mirando hacia la DERECHA
- [ ] Guardado como `player_spritesheet.png`
- [ ] Colocado en `assets/textures/`

## 🎯 Ejemplo Rápido con Python

Si tienes Python y Pillow instalado:

```bash
# Crear spritesheet de prueba
python verify_spritesheet.py --create-test

# Copiar a la ubicación correcta
copy test_spritesheet.png assets\textures\player_spritesheet.png

# Ejecutar el juego
.\bin\dk.exe
```

## 🔍 Verificación en Consola

Al ejecutar el juego, verás:

```
Player spritesheet loaded: 320x48 (10 columns)
```

Esto confirma que el spritesheet se cargó correctamente.

## 🎮 Probar sin Assets

Si aún no tienes tu spritesheet:

```bash
# El juego funciona con formas geométricas
.\bin\dk.exe

# Verás un rectángulo rojo como jugador
# La animación de "frame change" funciona igual
```

## 📚 Documentación Completa

Lee estos archivos para más detalles:

1. `SPRITESHEET_10_FRAMES.md` - Guía técnica completa
2. `EJEMPLO_VISUAL_10_FRAMES.md` - Visualización y ejemplos
3. `SISTEMA_ANIMACION.md` - Sistema de animación general
4. `ASSETS_GUIDE.md` - Guía de todos los assets

## 🎨 Recursos de Sprites

### Assets Gratuitos:
- **OpenGameArt.org** - "platformer character spritesheet"
- **Itch.io** - Free Game Assets → 2D → Platformer
- **Kenney.nl** - Platformer Pack

### Tutoriales:
- YouTube: "pixel art walk cycle tutorial"
- YouTube: "how to make spritesheet animation"

## 💡 Tips Finales

### Para Mejor Resultado:
1. **Usa pixel art** estilo retro
2. **Paleta limitada** (4-6 colores)
3. **Sin anti-aliasing** para look clásico
4. **Centrado consistente** en todos los frames
5. **Loop perfecto**: Frame 9 → Frame 0 suave

### Animación Profesional:
- **Balanceo de brazos** opuesto a piernas
- **Altura variable** (+/- 2px arriba/abajo)
- **Timing correcto**: Contacto → Empuje → Elevación
- **Squash & Stretch** sutil en aterrizajes

## 🔧 Troubleshooting

| Problema | Solución |
|----------|----------|
| No se carga spritesheet | Verifica nombre y ruta: `assets/textures/player_spritesheet.png` |
| Animación muy rápida | Aumenta frameTime: `player->setFrameTime(0.12f)` |
| Animación muy lenta | Disminuye frameTime: `player->setFrameTime(0.06f)` |
| Sprite distorsionado | Usa proporciones 2:3 (ej: 32×48, 40×60) |
| Frames cortados | Verifica que ancho sea exactamente `frame_width × 10` |

## ✨ Ejemplo Completo

```bash
# 1. Crear spritesheet de prueba
python verify_spritesheet.py --create-test

# 2. Mover a carpeta correcta
move test_spritesheet.png assets\textures\player_spritesheet.png

# 3. Compilar (si modificaste código)
make

# 4. Ejecutar juego
.\bin\dk.exe

# 5. Verifica en consola:
# "Player spritesheet loaded: 320x48 (10 columns)"
```

## 🎊 ¡Listo para Animar!

Tu juego ahora soporta spritesheets de 10 frames con:
- ✅ Auto-escalado inteligente
- ✅ Volteo automático izquierda/derecha
- ✅ Velocidad configurable
- ✅ Fallback a formas geométricas
- ✅ Detección automática

**Solo necesitas colocar tu spritesheet en** `assets/textures/player_spritesheet.png` **¡y funcionará!** 🎮✨

---

**¿Dudas?** Revisa la documentación completa en los archivos .md creados.
