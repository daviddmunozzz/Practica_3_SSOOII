# Practica 3 - Buscador SSOOIIGLE Avanzado

## Autores
- David Muñoz
- Daniel Aguado

## Enlace a video explicativo
- [Explicación del funcionamiento](https://pruebasaluuclm-my.sharepoint.com/:v:/g/personal/daniel_aguado3_alu_uclm_es/ES4Uh9mYbfJEkYH1k9rFGbQBqNvjgFTZpoiM4FDwXyETkA?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=52rUN6)
- [Prueba de ejecución](https://pruebasaluuclm-my.sharepoint.com/:v:/g/personal/daniel_aguado3_alu_uclm_es/EaGQfZTbp0FKjGU2n2eaWUsBIkPd-U80ZPaENPUd1ast2g?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=KqsxWw)

## Descripción
Creacion paralela de hilos cliente e hilos buscadores para la búsqueda de palabras simultánea en una serie de libros.


## Cómo compilarlo
Para compilar el proyecto, primero ejecuta el comando Make en la carpeta src del proyecto. Esto generará el archivo SSOOIIGLE, que es el ejecutable.

```
./SSOOIIGLE
```
En caso de no poder ejecutar el makefile, puedes usar el siguiente comando de terminal, situándote en la carpeta "src".

```
g++ -std=c++17 -pthread -o SSOOIIGLE Buscador.cpp Cliente.cpp manager.cpp Utilidades.cpp -I ../include
```
## Otros
- En la carpeta 'util' se incluye la autoevaluación de la práctica.
- La carpeta 'include' contiene todas las cabeceras de las clases.
- La carpeta 'library' contiene los libros sobre los que se buscan palabras.
