# Ejemplo Visual: Spritesheet de 10 Frames

## Vista del Spritesheet Completo

```
Archivo: player_spritesheet.png
Dimensiones ejemplo: 320x48 píxeles (10 frames de 32x48)

┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
│  0   │  1   │  2   │  3   │  4   │  5   │  6   │  7   │  8   │  9   │
│      │      │      │      │      │      │      │      │      │      │
│ 🚶   │ 🚶   │ 🚶   │ 🚶   │ 🚶   │ 🚶   │ 🚶   │ 🚶   │ 🚶   │ 🚶   │
│ ←────│ ←────│ ←────│ ←────│ ←────│ ←────│ ←────│ ←────│ ←────│ ←────│
│Inicio│Paso1 │Trans.│Paso2 │Trans.│Paso3 │Trans.│Paso4 │Trans.│Final │
└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
   0px   32px   64px   96px  128px  160px  192px  224px  256px  288px
```

## Animación de Caminata Frame por Frame

### Ciclo Completo (10 Frames):

```
Frame 0 - CONTACTO PIE IZQUIERDO
    O
   /|\     Talón izquierdo toca suelo
   / \     Brazo derecho adelante
  /   |    Cuerpo ligeramente inclinado

Frame 1 - EMPUJE PIE IZQUIERDO
    O
   /|\     Peso en pie izquierdo
  /  |     Pie derecho despegando
 /    \    Brazos balanceándose

Frame 2 - ELEVACIÓN
    O
   /|\     Ambos pies casi en aire
    |      Cuerpo en punto más alto
   / \     Posición neutra brazos

Frame 3 - CONTACTO PIE DERECHO
    O
   /|\     Talón derecho toca suelo
   / \     Brazo izquierdo adelante
  |   \    Cuerpo ligeramente inclinado opuesto

Frame 4 - EMPUJE PIE DERECHO
    O
   /|\     Peso en pie derecho
  |  \     Pie izquierdo despegando
 /    \    Brazos balanceándose

Frame 5 - TRANSICIÓN MEDIA
    O
   /|\     Cuerpo centrado
  | |      Piernas en movimiento
 /   \     Balance natural

Frame 6 - CONTACTO PIE IZQUIERDO (REPETICIÓN)
    O
   /|\     Similar a Frame 0
   / \     Variación sutil para suavidad
  /   |    

Frame 7 - IMPULSO
    O
   /|\     Impulso hacia adelante
  /  |     Energía en movimiento
 /    \    

Frame 8 - ELEVACIÓN ALTA
    O
   /|\     Punto más alto del paso
    |      Cuerpo extendido
   / \     

Frame 9 - PREPARACIÓN
    O
   /|\     Preparando siguiente ciclo
   / \     Transición suave a Frame 0
  |   \    Loop perfecto
```

## Medidas Específicas por Frame

### Template para 32x48 píxeles por frame:

```
Cada frame individual (32x48):
┌────────────────────────────────┐ ← 0px
│         ESPACIO SUPERIOR       │
│              (8px)             │
├────────────────────────────────┤ ← 8px
│                                │
│         CABEZA (8x8)           │
│                                │
├────────────────────────────────┤ ← 16px
│                                │
│      TORSO/BRAZOS (16px)       │
│                                │
│                                │
├────────────────────────────────┤ ← 32px
│                                │
│      PIERNAS (16px)            │
│                                │
│                                │
├────────────────────────────────┤ ← 48px
│     ESPACIO INFERIOR (0px)     │
└────────────────────────────────┘
```

### Distribución Vertical Recomendada:
- **Píxeles 0-8**: Espacio superior (para saltos)
- **Píxeles 8-16**: Cabeza/Sombrero (8px)
- **Píxeles 16-32**: Torso y Brazos (16px)
- **Píxeles 32-48**: Piernas y Pies (16px)

### Distribución Horizontal (centrado en 32px):
- **Píxeles 8-24**: Cuerpo principal (16px ancho)
- **Píxeles 4-28**: Con brazos extendidos (24px ancho)

## Paleta de Colores Estilo Donkey Kong Original

```
Jumpman/Mario clásico:

#FF0000 - Rojo (Camisa/Gorra)
#0000FF - Azul (Overol)
#FFCC99 - Piel (Cara/Manos)
#8B4513 - Marrón (Bigote/Zapatos)
#FFFFFF - Blanco (Guantes/Botones)
#000000 - Negro (Contornos)
```

## Ejemplo de Código para Crear Spritesheet Programáticamente

Si tienes Python con PIL/Pillow:

```python
from PIL import Image, ImageDraw

# Crear spritesheet vacío (320x48 con transparencia)
spritesheet = Image.new('RGBA', (320, 48), (0, 0, 0, 0))

# Crear 10 frames
for i in range(10):
    # Crear frame individual (32x48)
    frame = Image.new('RGBA', (32, 48), (0, 0, 0, 0))
    draw = ImageDraw.Draw(frame)
    
    # Dibujar personaje simple (ejemplo)
    # Cabeza
    draw.ellipse([12, 8, 20, 16], fill=(255, 204, 153))
    
    # Cuerpo (camisa roja)
    draw.rectangle([10, 16, 22, 32], fill=(255, 0, 0))
    
    # Piernas (overol azul) - variar posición según frame
    leg_offset = (i % 5) - 2  # Movimiento de piernas
    draw.rectangle([10 + leg_offset, 32, 14 + leg_offset, 44], fill=(0, 0, 255))
    draw.rectangle([18 - leg_offset, 32, 22 - leg_offset, 44], fill=(0, 0, 255))
    
    # Pegar frame en spritesheet
    spritesheet.paste(frame, (i * 32, 0))

# Guardar
spritesheet.save('player_spritesheet.png')
print("Spritesheet de 10 frames creado!")
```

## Checklist de Calidad

Antes de usar tu spritesheet de 10 frames:

### Técnico:
- [ ] Dimensiones: `ancho_frame * 10` x `alto_frame`
- [ ] Formato: PNG con canal alpha (transparencia)
- [ ] Sin espacio entre frames
- [ ] Sin padding/márgenes externos
- [ ] Tamaño de archivo razonable (<500KB recomendado)

### Visual:
- [ ] Todos los frames centrados verticalmente
- [ ] Todos los frames centrados horizontalmente
- [ ] Personaje mirando hacia la DERECHA
- [ ] Altura del personaje consistente
- [ ] Pies alineados (misma línea base)

### Animación:
- [ ] Ciclo completo de caminata
- [ ] Movimiento suave entre frames
- [ ] Balance de brazos opuesto a piernas
- [ ] Transiciones naturales
- [ ] Frame final conecta con frame inicial

### Estilo:
- [ ] Estilo consistente en todos los frames
- [ ] Paleta de colores limitada
- [ ] Pixel art limpio (sin anti-aliasing si es retro)
- [ ] Contornos definidos

## Comparación: 4 vs 10 Frames

```
4 Frames (Básico):
┌────┬────┬────┬────┐
│ 0  │ 1  │ 2  │ 3  │
└────┴────┴────┴────┘
Animación: Funcional pero brusca

10 Frames (Suave):
┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
│ 0  │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │
└────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
Animación: Muy suave y profesional
```

### Ventajas de 10 Frames:
✅ Movimiento mucho más fluido
✅ Permite transiciones sutiles
✅ Balanceo de brazos más natural
✅ Cambios de peso más realistas
✅ Look más profesional

## Ejemplo Real - Timing de Animación

Con `frameTime = 0.08f`:

```
Tiempo | Frame | Posición
-------|-------|----------
0.00s  |   0   | Contacto izq
0.08s  |   1   | Empuje izq
0.16s  |   2   | Elevación
0.24s  |   3   | Contacto der
0.32s  |   4   | Empuje der
0.40s  |   5   | Transición
0.48s  |   6   | Contacto izq
0.56s  |   7   | Impulso
0.64s  |   8   | Elevación
0.72s  |   9   | Preparación
0.80s  |   0   | LOOP (repite)

Ciclo completo: 0.8 segundos
Velocidad: 1.25 ciclos/segundo
```

## Herramientas Recomendadas

### Para Principiantes:
1. **Piskel** (piskelapp.com) - Web, gratis, fácil
2. **Pixel Studio** (iOS/Android) - App móvil

### Para Intermedio:
1. **GraphicsGale** - Windows, gratis
2. **PyxelEdit** - Pago, muy bueno para tilesets

### Para Profesionales:
1. **Aseprite** - $19.99, mejor herramienta
2. **Photoshop** - Con acciones personalizadas

## Recursos de Aprendizaje

- **Tutorial de animación walk cycle**: 
  - Busca "8-frame walk cycle pixel art" en YouTube
  - Adapta de 8 a 10 frames agregando transiciones

- **Referencias**:
  - Sprites originales de Donkey Kong (Nintendo)
  - Sprites de Super Mario Bros
  - Platformer sprite packs en OpenGameArt

¡Con estos 10 frames tu personaje se moverá súper fluido! 🎮✨
