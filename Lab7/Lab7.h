#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab7.h"
#include "ArchivoContactos.h"

class QTableWidget;

class Lab7 : public QMainWindow
{
    Q_OBJECT

public:
    Lab7(QWidget *parent = nullptr);
    ~Lab7();

private:
    Ui::Lab7Class ui;
    ArchivoContactos archivoContactos;

    void guardarContacto();
    void mostrarRegistrar();
    void mostrarHistorial();
    void mostrarEditar();
    void mostrarEliminar();
    void cargarTabla(QTableWidget* tabla);
    void cargarSeleccionEnFormulario();
    void actualizarContacto();
    void eliminarContacto();
};
