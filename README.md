# Practica 3 - Buscador SSOOIIGLE Avanzado

## Autores
- David Muñoz
- Daniel Aguado

## Descripción
Ejecución paralela de hilos en búsqueda de ocurrencias de una palabra en diferentes fragmentos de un libro. El programa divide el libro en fragmentos y prepara cada fragmento para que sea procesado por un hilo de ejecución.

## Clases

### Manejador
La clase `Manejador` se encarga de dividir el libro en fragmentos y prepararlos para que cada hilo pueda realizar la búsqueda de ocurrencias de la palabra en paralelo.

### ClassBusqueda
La clase `ClassBusqueda` proporciona una abstracción para guardar las soluciones encontradas por los hilos en una cola de soluciones.

### SSOOIGLE
La clase `SSOOIGLE` es la clase principal del programa. Crea y lanza los hilos a ejecución.

## Cómo compilarlo
Para compilar el proyecto, primero ejecuta el comando Make en la carpeta src del proyecto. Esto generará los archivos ejecutables necesarios en la carpeta `exec`. A continuación, en la carpeta `exec`, proporcionamos los argumentos necesarios de la siguiente forma:

```
./SSOOIGLE <PATH/nombre_fichero> <palabra> <numero_hilos>
```

Donde:
- `<PATH/nombre_fichero>` es la ruta y el nombre del archivo que deseas procesar.
- `<palabra>` es la palabra que deseas buscar en el archivo.
- `<numero_hilos>` es el número de hilos que deseas utilizar para la búsqueda.

Existen ejemplos preestablecidos en el propio `Makefile`. En ese caso indicaríamos en el terminal, estando en la carpeta `src:

```
make solution1
```
Hay tres ejemplos: solution1, solution2 y solution3
## Otros
Se han incluido las carpetas `include` y `library` con información adicional. `include` contiene el enunciado de la práctica y `library` libros en formato txt para hacer pruebas.
