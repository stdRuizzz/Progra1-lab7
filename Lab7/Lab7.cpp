#include "Lab7.h"

#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAction>
#include <QStackedWidget>

namespace
{
bool validarContacto(QWidget* padre,
                     const QString& nombre,
                     const QString& telefono,
                     const QString& correo)
{
    if (nombre.isEmpty() || telefono.isEmpty() || correo.isEmpty()) {
        QMessageBox::warning(padre, "Datos incompletos",
                             "Completá los tres campos.");
        return false;
    }

    const QStringList datos{ nombre, telefono, correo };
    for (const QString& dato : datos) {
        if (dato.contains(';') || dato.contains('\n') ||
            dato.contains('\r')) {
            QMessageBox::warning(padre, "Dato no permitido",
                "No usés punto y coma ni saltos de línea.");
            return false;
        }
    }

    return true;
}
}

Lab7::Lab7(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.btnGuardar, &QPushButton::clicked,
            this, &Lab7::guardarContacto);
    connect(ui.btnRefrescar, &QPushButton::clicked,
            this, &Lab7::mostrarHistorial);
    connect(ui.btnActualizar, &QPushButton::clicked,
            this, &Lab7::actualizarContacto);
    connect(ui.btnEliminar, &QPushButton::clicked,
            this, &Lab7::eliminarContacto);
    connect(ui.tblEditar, &QTableWidget::itemSelectionChanged,
            this, &Lab7::cargarSeleccionEnFormulario);

    connect(ui.actionRegistrar, &QAction::triggered,
            this, &Lab7::mostrarRegistrar);
    connect(ui.actionHistorial, &QAction::triggered,
            this, &Lab7::mostrarHistorial);
    connect(ui.actionEditar, &QAction::triggered,
            this, &Lab7::mostrarEditar);
    connect(ui.actionEliminar, &QAction::triggered,
            this, &Lab7::mostrarEliminar);

    mostrarRegistrar();
}

Lab7::~Lab7()
{}

void Lab7::guardarContacto()
{
    QString nombre = ui.txtNombre->text().trimmed();
    QString telefono = ui.txtTelefono->text().trimmed();
    QString correo = ui.txtCorreo->text().trimmed();

    if (!validarContacto(this, nombre, telefono, correo))
        return;

    if (!archivoContactos.guardar(nombre, telefono, correo)) {
        QMessageBox::critical(this, "No se pudo guardar",
            "Revisá permisos y espacio disponible.\nArchivo: "
            + archivoContactos.ruta());
        return;
    }

    ui.txtNombre->clear();
    ui.txtTelefono->clear();
    ui.txtCorreo->clear();
    QMessageBox::information(this, "Guardado completo",
        "El contacto se guardó correctamente.\nArchivo: "
        + archivoContactos.ruta());
    ui.txtNombre->setFocus();
}

void Lab7::mostrarRegistrar()
{
    ui.stackPages->setCurrentWidget(ui.pageRegistrar);
    ui.txtNombre->setFocus();
}

void Lab7::mostrarHistorial()
{
    cargarTabla(ui.tblHistorial);
    ui.stackPages->setCurrentWidget(ui.pageHistorial);
}

void Lab7::mostrarEditar()
{
    ui.txtEditarNombre->clear();
    ui.txtEditarTelefono->clear();
    ui.txtEditarCorreo->clear();
    cargarTabla(ui.tblEditar);
    ui.tblEditar->clearSelection();
    ui.tblEditar->setCurrentCell(-1, -1);
    ui.stackPages->setCurrentWidget(ui.pageEditar);
}

void Lab7::mostrarEliminar()
{
    cargarTabla(ui.tblEliminar);
    ui.tblEliminar->clearSelection();
    ui.tblEliminar->setCurrentCell(-1, -1);
    ui.stackPages->setCurrentWidget(ui.pageEliminar);
}

void Lab7::cargarTabla(QTableWidget* tabla)
{
    const QList<Contacto> contactos = archivoContactos.leer();

    tabla->horizontalHeader()->setStretchLastSection(true);
    tabla->clearContents();
    tabla->setRowCount(static_cast<int>(contactos.size()));

    for (int fila = 0; fila < contactos.size(); ++fila) {
        const Contacto& contacto = contactos.at(fila);
        tabla->setItem(fila, 0, new QTableWidgetItem(contacto.nombre));
        tabla->setItem(fila, 1, new QTableWidgetItem(contacto.telefono));
        tabla->setItem(fila, 2, new QTableWidgetItem(contacto.correo));
    }
}

void Lab7::cargarSeleccionEnFormulario()
{
    const int fila = ui.tblEditar->currentRow();
    if (fila < 0)
        return;

    QTableWidgetItem* itemNombre = ui.tblEditar->item(fila, 0);
    QTableWidgetItem* itemTelefono = ui.tblEditar->item(fila, 1);
    QTableWidgetItem* itemCorreo = ui.tblEditar->item(fila, 2);

    if (!itemNombre || !itemTelefono || !itemCorreo)
        return;

    ui.txtEditarNombre->setText(itemNombre->text());
    ui.txtEditarTelefono->setText(itemTelefono->text());
    ui.txtEditarCorreo->setText(itemCorreo->text());
}

void Lab7::actualizarContacto()
{
    const int fila = ui.tblEditar->currentRow();
    if (fila < 0) {
        QMessageBox::information(this, "Sin selección",
            "Seleccioná un contacto de la tabla para editarlo.");
        return;
    }

    QString nombre = ui.txtEditarNombre->text().trimmed();
    QString telefono = ui.txtEditarTelefono->text().trimmed();
    QString correo = ui.txtEditarCorreo->text().trimmed();

    if (!validarContacto(this, nombre, telefono, correo))
        return;

    if (!archivoContactos.actualizar(fila, nombre, telefono, correo)) {
        QMessageBox::critical(this, "No se pudo actualizar",
            "Revisá permisos y espacio disponible.\nArchivo: "
            + archivoContactos.ruta());
        return;
    }

    cargarTabla(ui.tblEditar);
    ui.tblEditar->clearSelection();
    ui.tblEditar->setCurrentCell(-1, -1);
    ui.txtEditarNombre->clear();
    ui.txtEditarTelefono->clear();
    ui.txtEditarCorreo->clear();

    QMessageBox::information(this, "Contacto actualizado",
        "El contacto se actualizó correctamente.");
}

void Lab7::eliminarContacto()
{
    const int fila = ui.tblEliminar->currentRow();
    if (fila < 0) {
        QMessageBox::information(this, "Sin selección",
            "Seleccioná un contacto de la tabla para eliminarlo.");
        return;
    }

    QTableWidgetItem* itemNombre = ui.tblEliminar->item(fila, 0);
    const QString nombre = itemNombre ? itemNombre->text() : QString();

    const QMessageBox::StandardButton respuesta = QMessageBox::question(
        this, "Confirmar eliminación",
        "¿Eliminar el contacto \"" + nombre + "\"?",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (respuesta != QMessageBox::Yes)
        return;

    if (!archivoContactos.eliminar(fila)) {
        QMessageBox::critical(this, "No se pudo eliminar",
            "Revisá permisos y espacio disponible.\nArchivo: "
            + archivoContactos.ruta());
        return;
    }

    cargarTabla(ui.tblEliminar);
    ui.tblEliminar->clearSelection();
    ui.tblEliminar->setCurrentCell(-1, -1);

    QMessageBox::information(this, "Contacto eliminado",
        "El contacto se eliminó correctamente.");
}
