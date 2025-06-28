Engineering materials
====

This repository contains engineering materials of a self-driven vehicle's model participating in the WRO Future Engineers competition in the season 2025.

## Content

* `t-photos` contains 2 photos of the team (an official one and one funny photo with all team members)
* `v-photos` contains 6 photos of the vehicle (from every side, from top and bottom)
* `video` contains the video.md file with the link to a video where driving demonstration exists
* `schemes` contains one or several schematic diagrams in form of JPEG, PNG or PDF of the electromechanical components illustrating all the elements (electronic components and motors) used in the vehicle and how they connect to each other.
* `src` contains code of control software for all components which were programmed to participate in the competition
* `models` is for the files for models used by 3D printers, laser cutting machines and CNC machines to produce the vehicle elements. If there is nothing to add to this location, the directory can be removed.
* `other` is for other files which can be used to understand how to prepare the vehicle for the competition. It may include documentation how to connect to a SBC/SBM and upload files there, datasets, hardware specifications, communication protocols descriptions etc. If there is nothing to add to this location, the directory can be removed.

## Introduction

# WRO 2025 - Ingenieros del Futuro - Vehículo Autónomo

Este repositorio documenta el diseño, el proceso de ingeniería y el código fuente de nuestro vehículo autónomo construido para la categoría Future Engineers de la World Robot Olympiad 2025.

---

## 🔧 Descripción del hardware

Nuestro vehículo fue diseñado para lograr estabilidad y maniobrabilidad mediante:

- **Controlador principal**: Arduino Uno  
- **Módulo de control de motores**: Puente H  
- **Sistema de tracción**: 
  - Tracción trasera con un solo motor DC tipo C, traccion trasera 
  - El motor transmite fuerza a la otra rueda trasera a través de un eje  
  - Nuestro vehiculo emplea un sistema de traccion diferencial (2WD) con dos ruedas motrices ubicadas en la parte trasera
- **Diseño del chasis**: Bajo, para facilitar la calibración y mejorar la estabilidad en curvas  
- **Alimentación**: Sistema independiente y regulado para sensores y motores (3V a 6V) 
- **Servo motor**: Nos ofrece un control exacto de angulo de giro de las ruedas delanteras esenciales para la trayectoria que buscamos, y nos permitio tener una mayor maniobrabilidad en las curvas

---

## 🎯 Sensores

Se emplea una combinación de sensores para maximizar la capacidad de detección:

- **3 sensores de proximidad ultrasónicos**: Para detectar obstáculos y paredes,detectan rebotes contra paredes y activan maniobras de evasión    
- **2 sensores infrarrojos blanco/negro**: Complementarios, útiles para detectar bordes o alineamiento interno  
- **1 sensor de color (ubicado en la parte trasera)**: uso para reconocimiento de marcas o eventos post-vuelta  




---

## 🧠 Programación y lógica del vehículo

El vehículo opera de forma totalmente autónoma, con comportamientos como:

- Detectar obstáculos y determinar si debe girar  
- Realizar maniobras de retroceso y pivote si queda atascado  
- Girar con ángulos más bruscos por el diseño estructural del chasis  
- Integrar decisiones tipo máquina de estados según el entorno  
- Deteccion de linea naranja para saber el numero de vueltas

---

## ⚙️ Estructura del código

La estructura del programa está dividida en módulos que gestionan:

- Lectura de sensores y filtros  
- Control de motores con señales PWM  
- Lógica de navegación  
- Protocolos de emergencia y recuperación  

---

## 🛠️ Diseño mecánico

- El sistema de transmisión trasero con un solo motor permite un diseño compacto y estable  
- El chasis bajo mejora el centro de gravedad, facilitando el control del giro  
- La ubicación de sensores evita ángulos ciegos y reduce interferencias  
- El motor esta acoplado a una caja reductora plastica y opera entre 3V y 6V
- Distribucion de peso optimizada, para mantener el centro de gravedad bajo ligeramente desplazado hacia las ruedas motrices, asegurando una adherencia adecuada y previniendo el volcado


## 👥 Autores

Equipo: [Titancode]  
Entrenador: [Jesus gonzales]  
Integrantes: [Alvaro Bastidas(Presentador)
	      Andres Maninatt(Programador)
	      Sebastian Ospino(Mecanico)]  

---

## 💻 Compilación y carga

1. Abre `codigov2.ino` en Arduino IDE  
2. Selecciona la placa: Arduino Uno  
3. Conecta por USB y sube el programa  

## 📹 Videos de rendimiento

- [Video Open Challenge](https://www.youtube.com/shorts/Cdvap1Um8XQ?si=qTZ6vW1jbq6psBnX)

# WRO 2025 - Ingenieros del Futuro - Vehículo Autónomo

Este repositorio documenta el diseño, el proceso de ingeniería y el código fuente de nuestro vehículo autónomo construido para la categoría Future Engineers de la World Robot Olympiad 2025.

---




"Equipo de Robótica del Colegio Santa Rosa: Proyecto WRO 2025" 

  En noviembre de 2024, hace aproximadamente ocho meses, el Colegio Santa Rosa tomó la 
iniciativa de explorar el campo de la robótica y formar un equipo para participar en la 
competencia WRO 2025. Se evaluaron varios estudiantes para este proyecto, pero finalmente 
fuimos seleccionados nosotros (Álvaro Bastidas, Sebastián Ospino y Andrés Maninatt) debido a 
nuestro destacado desempeño en programación el año anterior. 

  Tras ser elegidos, asistimos a un taller informativo e inmersivo que nos permitió comprender 
mejor los retos que enfrentaríamos. Luego dedicamos varias semanas a construir y programar un 
prototipo basado en las regulaciones de la WRO del ciclo anterior. Una vez terminado nuestro 
primer prototipo, decidimos participar en una competencia organizada por el Instituto de 
Ingeniería de el estado carabobo, donde numerosos colegios y universidades compitieron para 
demostrar quién tenía el mejor diseño. En esta competencia obtuvimos el premio a la “Mejor 
Reparación”, gracias a que logramos resolver de forma oportuna los problemas técnicos que 
surgieron con nuestro dispositivo. 

  Después de esta experiencia, nos enfocamos en estudiar a fondo las reglas de la WRO, sabiendo 
que, por lo general, se mantienen estables cada año. Cuando se publicaron oficialmente las reglas 
de la WRO 2025, ya contábamos con la experiencia y los conocimientos necesarios para 
abordarlas de forma efectiva. Durante varias semanas, analizamos distintos lenguajes de 
programación para determinar cuál sería el más conveniente para integrar al prototipo e 
investigamos opciones de hardware para optimizar su rendimiento. Además, dedicamos tiempo a definir los roles específicos de cada integrante del equipo. Una vez 
establecidos estos roles, cada uno se concentró en su área, sin descuidar la visión general del 
proyecto. Para mostrar nuestros avances, organizamos un evento en el colegio para presentar al 
director todo lo que habíamos aprendido durante este proceso. El reto era sencillo: nuestro 
prototipo debía seguir una línea negra y detenerse en un punto exacto. La prueba fue exitosa, 
completando varias vueltas y deteniéndose en el momento indicado. Impulsados por este logro, decidimos diseñar nuevos prototipos para ponernos a prueba fuera de 
nuestra zona de confort. Trabajamos durante aproximadamente dos meses en un nuevo modelo, 
logrando armarlo y desarmarlo en pocos minutos. Cabe resaltar que todo este trabajo se realizó 
después de clases y durante los fines de semana. Aunque este prototipo no cumplía con las 
normas de la WRO 2025, nos permitió consolidar y demostrar los conocimientos adquiridos. 
Actualmente, estamos desarrollando un prototipo que cumple completamente con las reglas 
vigentes de la WRO, utilizando todos los recursos permitidos por el reglamento. Contamos con 
el apoyo de varios ingenieros que nos asisten con tareas específicas, como la impresión 3D de 
piezas y la adquisición del hardware necesario (cabe acotar que la ayuda que recibimos es 
solamente para conseguir hardware necesario, no nos dan sugerencias ni consejos, actuando 
como pratrocinadores de este proyecto y aportando los materiales). Este respaldo nos 
permite materializar nuestras ideas sin limitaciones externas, confiando plenamente en nuestra 
creatividad. 

Este es el prototipo que utilizaremos para competir en el evento que se realizará en Caracas este 
mes. 

**Perspectiva de Álvaro Bastidas:**  

  "Este proyecto nos ha dado la oportunidad de aprender, desarrollar y entender nuestra pasión, 
que en este caso sería en el ámbito robótico. Ahora, este episodio de nuestra vida, desde mi 
perspectiva (Álvaro Bastidas), me ha ayudado a terminar de comprender qué es lo que en verdad 
quiero estudiar, que sería todo lo relacionado a este campo. Y aunque sé que tiene desafíos, con 
la dedicación y esfuerzo que le hemos puesto, sé que podremos superar todo tipo de 
dificultades." 

**Perspectiva de Sebastián Ospino:** 
  
  "Este proyecto me pareció súper informativo, ayudándonos a aprender diferentes elementos 
electrónicos, además que nos puso a pensar en solución de problemas complejos, funcionamiento 
del vehículo y el trabajo en equipo." 

**Perspectiva de Andrés Maninatt:**  
 
  "Este proyecto no solo nos permitió adentrarnos en el mundo de la robótica, sino que también 
despertó mi fascinación por la innovación tecnológica aplicada. A diferencia de descubrir una 
pasión específica como Álvaro, en mi caso consolidó mi interés por la ingeniería mecatrónica 
como campo integrador, donde la electrónica, la programación y la mecánica convergen para 
resolver problemas reales. Coincido con Sebastián en que el trabajo en equipo fue crucial para 
enfrentar obstáculos técnicos como el diseño de circuitos y la optimización del código, pero 
añadiría que lo más valioso fue aprender a gestionar el fracaso: cada error en las pruebas nos 
enseñó más que cualquier manual. Estoy convencido de que estas experiencias son la base para 
emprender desafíos mayores, no solo académicos, sino también en proyectos con impacto 
social." 


  **Conclusión:**   

   Este proyecto representa mucho más que una actividad técnica: fue un catalizador de 
descubrimiento personal y profesional. Para Álvaro, significó confirmar su pasión por la robótica 
y su futuro académico; para Sebastián, la oportunidad de dominar componentes electrónicos y 
resolver problemas complejos en equipo. En el caso de Maninatt, consolidó su visión de la 
ingeniería mecatrónica como campo integrador, transformando los errores en lecciones clave 
sobre programación y optimización. Los tres coinciden en que las dificultades, desde desafíos 
técnicos hasta la coordinación grupal, se convirtieron en pruebas tangibles de su capacidad para 
innovar y perseverar.   

  En esencia, simboliza la chispa que transforma estudiantes en creadores del futuro. Les demostró 
que la robótica no se reduce a cables y código, sino que es un ecosistema donde confluyen 
vocación, rigor técnico y resiliencia. Como destaca Maninatt, esta experiencia sienta las bases 
para aplicar estos conocimientos a retos sociales relevantes. Así, el proyecto trasciende lo 
académico: se convirtió en el taller donde la teoría se hizo práctica, y donde cada obstáculo 
superado tejió su identidad como futuros profesionales comprometidos con soluciones de 
impacto.











