#!/usr/bin/env python3
"""
Script para verificar y validar un spritesheet de 10 frames
Uso: python verify_spritesheet.py player_spritesheet.png
"""

import sys
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    print("⚠️  PIL/Pillow no está instalado")
    print("   Instala con: pip install Pillow")
    sys.exit(1)

def verify_spritesheet(filepath, expected_columns=10, expected_rows=1):
    """Verifica que el spritesheet cumpla las especificaciones"""
    
    print(f"\n{'='*60}")
    print(f"🔍 VERIFICANDO SPRITESHEET: {filepath}")
    print(f"{'='*60}\n")
    
    # Verificar que el archivo existe
    if not Path(filepath).exists():
        print("❌ Error: El archivo no existe")
        return False
    
    try:
        img = Image.open(filepath)
    except Exception as e:
        print(f"❌ Error al abrir imagen: {e}")
        return False
    
    width, height = img.size
    print(f"📐 Dimensiones totales: {width}x{height} píxeles")
    
    # Calcular tamaño de frame
    frame_width = width // expected_columns
    frame_height = height // expected_rows
    
    print(f"📦 Tamaño por frame: {frame_width}x{frame_height} píxeles")
    print(f"📊 Columnas: {expected_columns}, Filas: {expected_rows}")
    
    # Verificaciones
    errors = []
    warnings = []
    
    # 1. Verificar dimensiones divisibles
    if width % expected_columns != 0:
        errors.append(f"El ancho ({width}) no es divisible por {expected_columns}")
    
    if height % expected_rows != 0:
        errors.append(f"El alto ({height}) no es divisible por {expected_rows}")
    
    # 2. Verificar que tiene canal alpha
    if img.mode != 'RGBA':
        warnings.append(f"No tiene transparencia (modo: {img.mode}, esperado: RGBA)")
    
    # 3. Verificar proporciones del frame
    if frame_width > 0 and frame_height > 0:
        ratio = frame_height / frame_width
        if ratio < 1.3 or ratio > 1.7:
            warnings.append(f"Proporción del frame {frame_width}:{frame_height} (ratio {ratio:.2f}) no está cerca de 2:3")
    
    # 4. Verificar tamaño recomendado
    if frame_width < 16 or frame_height < 24:
        warnings.append(f"Frames pequeños ({frame_width}x{frame_height}), pueden verse pixelados")
    
    if frame_width > 100 or frame_height > 150:
        warnings.append(f"Frames grandes ({frame_width}x{frame_height}), archivo puede ser pesado")
    
    # 5. Verificar que no esté completamente transparente
    if img.mode == 'RGBA':
        alpha_data = img.split()[-1].getdata()
        non_transparent = sum(1 for pixel in alpha_data if pixel > 0)
        coverage = (non_transparent / len(alpha_data)) * 100
        
        print(f"🎨 Cobertura de píxeles: {coverage:.1f}%")
        
        if coverage < 1:
            errors.append("Imagen completamente transparente")
        elif coverage < 5:
            warnings.append("Muy poca cobertura de píxeles (< 5%)")
    
    # 6. Verificar tamaño de archivo
    file_size = Path(filepath).stat().st_size
    file_size_kb = file_size / 1024
    
    print(f"💾 Tamaño de archivo: {file_size_kb:.1f} KB")
    
    if file_size_kb > 500:
        warnings.append(f"Archivo grande ({file_size_kb:.1f} KB)")
    
    # Mostrar resultados
    print(f"\n{'─'*60}")
    
    if errors:
        print("\n❌ ERRORES ENCONTRADOS:")
        for i, error in enumerate(errors, 1):
            print(f"   {i}. {error}")
    
    if warnings:
        print("\n⚠️  ADVERTENCIAS:")
        for i, warning in enumerate(warnings, 1):
            print(f"   {i}. {warning}")
    
    if not errors and not warnings:
        print("\n✅ PERFECTO! El spritesheet cumple todas las especificaciones")
    elif not errors:
        print("\n✅ VÁLIDO (con advertencias menores)")
    
    # Información adicional
    print(f"\n{'─'*60}")
    print("📋 INFORMACIÓN ADICIONAL:")
    print(f"   • Auto-escala en juego: Cada frame → 20x30 píxeles")
    print(f"   • Scale X: {20/frame_width:.3f}x" if frame_width > 0 else "")
    print(f"   • Scale Y: {30/frame_height:.3f}x" if frame_height > 0 else "")
    print(f"   • Frames totales: {expected_columns * expected_rows}")
    
    # Visualizar frames
    print(f"\n🎬 VISUALIZACIÓN DE FRAMES:")
    print("   " + "─" * (expected_columns * 6 + 1))
    print("   " + "".join([f"│ {i:^4}" for i in range(expected_columns)]) + "│")
    print("   " + "─" * (expected_columns * 6 + 1))
    
    print(f"\n{'='*60}\n")
    
    return len(errors) == 0

def create_test_spritesheet(output_path="test_spritesheet.png", 
                           columns=10, frame_width=32, frame_height=48):
    """Crea un spritesheet de prueba con 10 frames"""
    
    print(f"\n🎨 Creando spritesheet de prueba...")
    print(f"   Dimensiones: {frame_width*columns}x{frame_height}")
    print(f"   Frames: {columns}")
    
    # Crear imagen con transparencia
    total_width = frame_width * columns
    spritesheet = Image.new('RGBA', (total_width, frame_height), (0, 0, 0, 0))
    
    try:
        from PIL import ImageDraw, ImageFont
    except ImportError:
        print("⚠️  No se pudo importar ImageDraw")
        return False
    
    draw = ImageDraw.Draw(spritesheet)
    
    # Colores estilo Donkey Kong
    colors = [
        (255, 0, 0, 255),      # Rojo
        (0, 0, 255, 255),      # Azul
        (255, 204, 153, 255),  # Piel
        (139, 69, 19, 255),    # Marrón
        (255, 255, 0, 255),    # Amarillo
    ]
    
    # Dibujar cada frame
    for i in range(columns):
        x_offset = i * frame_width
        color = colors[i % len(colors)]
        
        # Dibujar rectángulo de marco
        draw.rectangle(
            [x_offset + 2, 2, x_offset + frame_width - 2, frame_height - 2],
            outline=(0, 0, 0, 255),
            width=2
        )
        
        # Dibujar "personaje" simple
        # Cabeza
        head_y = frame_height // 4
        draw.ellipse(
            [x_offset + frame_width//2 - 6, head_y - 6,
             x_offset + frame_width//2 + 6, head_y + 6],
            fill=colors[2]  # Color piel
        )
        
        # Cuerpo
        body_y = frame_height // 2
        draw.rectangle(
            [x_offset + frame_width//2 - 4, head_y + 6,
             x_offset + frame_width//2 + 4, body_y + 6],
            fill=color
        )
        
        # Piernas (variar según frame)
        leg_offset = (i % 5) - 2
        legs_y = body_y + 6
        
        # Pierna izquierda
        draw.rectangle(
            [x_offset + frame_width//2 - 4 + leg_offset, legs_y,
             x_offset + frame_width//2 - 2 + leg_offset, frame_height - 4],
            fill=colors[1]  # Azul
        )
        
        # Pierna derecha
        draw.rectangle(
            [x_offset + frame_width//2 + 2 - leg_offset, legs_y,
             x_offset + frame_width//2 + 4 - leg_offset, frame_height - 4],
            fill=colors[1]  # Azul
        )
        
        # Número de frame
        try:
            draw.text((x_offset + frame_width//2 - 3, 5), 
                     str(i), fill=(0, 0, 0, 255))
        except:
            pass
    
    # Guardar
    spritesheet.save(output_path)
    print(f"✅ Spritesheet de prueba creado: {output_path}")
    print(f"   Puedes usarlo para probar el juego!")
    
    return True

def main():
    if len(sys.argv) < 2:
        print("\n🎮 VERIFICADOR DE SPRITESHEET - Donkey Kong Game")
        print("="*60)
        print("\nUso:")
        print("  python verify_spritesheet.py <archivo.png>")
        print("  python verify_spritesheet.py --create-test")
        print("\nEjemplos:")
        print("  python verify_spritesheet.py player_spritesheet.png")
        print("  python verify_spritesheet.py assets/textures/player_spritesheet.png")
        print("  python verify_spritesheet.py --create-test")
        print("\nVerifica que tu spritesheet de 10 frames cumpla las especificaciones.")
        print()
        return
    
    if sys.argv[1] == "--create-test":
        # Crear spritesheet de prueba
        create_test_spritesheet()
        print("\n💡 Ahora copia 'test_spritesheet.png' a 'assets/textures/player_spritesheet.png'")
        print("   y ejecuta el juego para ver la animación!\n")
    else:
        # Verificar spritesheet existente
        filepath = sys.argv[1]
        is_valid = verify_spritesheet(filepath, expected_columns=10, expected_rows=1)
        
        if is_valid:
            print("✅ Tu spritesheet está listo para usar!")
            print("   Cópialo a: assets/textures/player_spritesheet.png\n")
        else:
            print("❌ Corrige los errores antes de usar el spritesheet.\n")
            sys.exit(1)

if __name__ == "__main__":
    main()
