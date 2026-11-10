Laboratorio 7 - Programación 1



Descripción del proyecto



Aplicación de escritorio desarrollada en C++ utilizando Qt y Visual Studio, que permite administrar contactos mediante un archivo de texto.



El programa permite registrar, visualizar, editar y eliminar contactos, manteniendo la información guardada incluso después de cerrar la aplicación.



Funcionalidades



\- Registrar: Permite ingresar nombre, teléfono y correo electrónico de un contacto.

\- Historial: Muestra los contactos registrados en una tabla.

\- Editar: Permite modificar la información de un contacto seleccionado.

\- Eliminar: Permite eliminar un contacto mediante un mensaje de confirmación.

\- Persistencia: Los datos se almacenan en un archivo .txt.



Pruebas realizadas



1\. Registro de contactos

Se registraron tres contactos y se comprobó que se almacenaran correctamente en el archivo contactos.txt. Después de cada registro, los campos se limpiaron y apareció un mensaje de confirmación.



2\. Historial de contactos

Se verificó que los tres contactos registrados aparecieran correctamente en la tabla, sin duplicarse al volver a abrir el historial.



3\. Edición de contactos

Se seleccionó el segundo contacto y se modificó su número telefónico. Se comprobó que el cambio se reflejara en la tabla y se guardara correctamente en el archivo .txt.



4\. Eliminación de contactos

Se seleccionó el tercer contacto y se confirmó su eliminación. Se verificó que desapareciera tanto de la tabla como del archivo de texto.



5\. Persistencia de datos

Se cerró y abrió nuevamente la aplicación. Se comprobó que permanecieran los dos contactos restantes y que el segundo conservara su número telefónico modificado.



6\. Pruebas adicionales

\- Se canceló una eliminación y se comprobó que el contacto permaneciera registrado.

\- Se intentó editar sin seleccionar un contacto y la aplicación mostró una advertencia.

\- Se abrió el historial vacío y se verificó que la aplicación funcionara sin errores.



Almacenamiento de datos



Los contactos se almacenan en la siguiente ruta:



`C:/Users/samue/Lab7Datos/contactos.txt`



Cada contacto se guarda con el formato:



`Nombre;Teléfono;Correo`



Tecnologías utilizadas



\- C++

\- Qt Framework

\- Visual Studio

\- Git y GitHub



Evidencias



\- Captura del registro exitoso de un contacto.

\- Captura del historial final con los dos contactos restantes.



Resultado final



La aplicación permite registrar, consultar, modificar y eliminar contactos correctamente, conservando los cambios realizados en el archivo de texto.

