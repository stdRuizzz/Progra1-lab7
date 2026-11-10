#include "ArchivoContactos.h"

#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QSaveFile>
#include <QStringList>

QString ArchivoContactos::ruta() const
{
    return QDir::homePath() + "/Lab7Datos/contactos.txt";
}

bool ArchivoContactos::guardar(const QString& nombre,
                              const QString& telefono,
                              const QString& correo) const
{
    QString carpeta = QDir::homePath() + "/Lab7Datos";
    if (!QDir().mkpath(carpeta))
        return false;

    QFile archivo(ruta());
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append))
        return false;

    QString linea = nombre + ";" + telefono + ";" + correo + "\n";
    QByteArray datos = linea.toUtf8();
    bool completo = archivo.write(datos) == datos.size();
    bool vaciado = archivo.flush();
    archivo.close();
    return completo && vaciado;
}

QList<Contacto> ArchivoContactos::leer() const
{
    QList<Contacto> contactos;

    QFile archivo(ruta());
    if (!archivo.open(QIODevice::ReadOnly))
        return contactos;

    const QByteArray contenido = archivo.readAll();
    archivo.close();

    const QString texto = QString::fromUtf8(contenido);
    const QStringList lineas = texto.split('\n', Qt::SkipEmptyParts);

    for (QString linea : lineas) {
        if (linea.endsWith('\r'))
            linea.chop(1);
        if (linea.trimmed().isEmpty())
            continue;

        const QStringList partes = linea.split(';');
        if (partes.size() != 3)
            continue;

        contactos.append({ partes[0], partes[1], partes[2] });
    }

    return contactos;
}

bool ArchivoContactos::actualizar(int indice,
                                  const QString& nombre,
                                  const QString& telefono,
                                  const QString& correo) const
{
    QList<Contacto> contactos = leer();
    if (indice < 0 || indice >= contactos.size())
        return false;

    contactos[indice] = { nombre, telefono, correo };
    return reescribir(contactos);
}

bool ArchivoContactos::eliminar(int indice) const
{
    QList<Contacto> contactos = leer();
    if (indice < 0 || indice >= contactos.size())
        return false;

    contactos.removeAt(indice);
    return reescribir(contactos);
}

bool ArchivoContactos::reescribir(const QList<Contacto>& contactos) const
{
    QString carpeta = QDir::homePath() + "/Lab7Datos";
    if (!QDir().mkpath(carpeta))
        return false;

    QSaveFile archivo(ruta());
    if (!archivo.open(QIODevice::WriteOnly))
        return false;

    QByteArray datos;
    for (const Contacto& contacto : contactos) {
        QString linea = contacto.nombre + ";" + contacto.telefono + ";" +
                        contacto.correo + "\n";
        datos += linea.toUtf8();
    }

    if (archivo.write(datos) != datos.size()) {
        archivo.cancelWriting();
        return false;
    }

    return archivo.commit();
}
