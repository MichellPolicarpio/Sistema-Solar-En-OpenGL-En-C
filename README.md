# 🌌 Sistema Solar Interactivo con OpenGL/C
[![OpenGL](https://img.shields.io/badge/OpenGL-3.3-blue.svg)](https://www.opengl.org/)
[![GLUT](https://img.shields.io/badge/GLUT-3.0-green.svg)](https://www.opengl.org/resources/libraries/glut/)
[![C](https://img.shields.io/badge/language-C-orange.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](LICENSE)

> Simulación interactiva del Sistema Solar desarrollada en C con OpenGL, incluyendo planetas, lunas, cinturones de asteroides y objetos transneptunianos.

## 🚀 Características

- Representación a escala del Sistema Solar completo
- Animaciones suaves de rotación y traslación planetaria
- Cinturón de asteroides y Cinturón de Kuiper con partículas dinámicas
- Sistema de cámara interactivo
- Iluminación realista desde el Sol
- Anillos detallados para Júpiter y Saturno
- Más de 1400 asteroides renderizados

## 🎮 Controles

| Tecla | Acción |
|-------|---------|
| `W` | Mover cámara hacia arriba |
| `S` | Mover cámara hacia abajo |
| `A` | Mover cámara hacia la izquierda |
| `D` | Mover cámara hacia la derecha |
| `R` | Aumentar rotación general en 5° |
| `Espacio` | Activar/Desactivar animación |
| `Q` | Salir del programa |

## 🌍 Cuerpos Celestes Incluidos

- ☀️ Sol (con iluminación dinámica)
- 🌎 Planetas terrestres (Mercurio, Venus, Tierra, Marte)
- 🌌 Cinturón de asteroides principal
- ⭐ Planetas gigantes (Júpiter, Saturno, Urano, Neptuno)
- ☄️ Cinturón de Kuiper
- 🌑 Planetas enanos (Plutón, Ceres, Haumea, Makemake)
- 🛸 Lunas principales (Luna terrestre, Europa)

## 🛠️ Requisitos del Sistema

- Sistema operativo macOS (proyecto configurado con frameworks de Apple)
- Compilador de C (GCC recomendado)
- OpenGL y GLUT instalados
- Xcode Command Line Tools (para macOS)

## ⚙️ Compilación e Instalación

1. Clona el repositorio:
```bash
git clone https://github.com/[tu-usuario]/sistema-solar-opengl.git
```

2. Navega al directorio del proyecto:
```bash
cd sistema-solar-opengl
```

3. Compila el proyecto (macOS):
```bash
gcc -o sistema_solar main.c -framework OpenGL -framework GLUT
```

4. Ejecuta el programa:
```bash
./sistema_solar
```

## 🎯 Características Técnicas

- Implementación en C puro
- Uso de estructuras (structs) para manejo de asteroides
- Renderizado 3D completo con manejo de profundidad
- Sistema de iluminación dinámica con GL_LIGHT0
- Gestión de materiales y colores con GL_COLOR_MATERIAL
- Array de 200 asteroides en el cinturón principal
- Array de 1200 objetos en el Cinturón de Kuiper
- Sistemas de partículas para representación de asteroides
- Ventana redimensionable con ajuste de perspectiva automático

## 💻 Estructura del Código

```c
// Estructuras principales
typedef struct {
    float distancia;
    float angulo;
    float tamano;
} Asteroide;

// Funciones principales
void inicializarAsteroides();
void dibujarAnillo();
void dibujarAsteroides();
void display();
void actualizar();
void keyboard();
void resize();
```

## 👨‍💻 Autor

- **Policarpio Moran Michell Alexis** - [GitHub](https://github.com/[tu-usuario])
- Universidad Veracruzana
- Ingeniería en Informática
- zS21002379

## 📄 Licencia

Este proyecto está bajo la Licencia MIT - consulta el archivo [LICENSE](LICENSE) para más detalles.

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Para cambios importantes:

1. Haz Fork del repositorio
2. Crea una nueva rama
3. Realiza tus cambios
4. Envía un Pull Request

## ✨ Agradecimientos

- Universidad Veracruzana
- Facultad de Ingeniería en Informática
- Comunidad OpenGL

## 📝 Notas de Implementación

- El proyecto utiliza GLUT para la gestión de ventanas y eventos
- La simulación incluye cálculos de órbitas y rotaciones planetarias
- Los asteroides se generan aleatoriamente dentro de rangos específicos
- Se implementa un sistema de cámara móvil para mejor visualización
- Los anillos planetarios se generan mediante GL_QUADS
