# SimulacionFisicaVideojuegos

## Aclaraciones para la Práctica 5

La escena que se muestra está formada por un suelo implementado con un RigidStatic y un generador Gaussiano de objetos RigidDynamic.

Para implementar los sólidos rígidos se ha creado una clase intermedia entre estos y las partículas, ``Actor``, y se ha adaptado todo aquello antes pensado para partículas para funcionar con esta nueva clase base.

En la demo está implementado para una fácil comprobación de que las fuerzas funcionan el siguiente input por teclado:
- Tecla: ``3``; Fuerza: Viento
- Tecla: ``4``; Fuerza: Torbellino
- Tecla: ``5``; Fuerza: Explosión

En la clase ParticleSystem están los métodos ``wind()``, ``whirlwind()`` y ``explosion()`` que provocan estas fuerzas. Se puede acceder y cambiar los valores de las mismas ahí indicados.
También en la contructora de dicha clase se encuentra la construcción de los elementos que forman la escena, pudiéndose modificar sus valores también indicados.