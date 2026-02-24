#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    // QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    // QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "desktop_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    QFile style(":/style/style.css");
    if (style.open(QFile::ReadOnly)){

        w.setStyleSheet(style.readAll());
    }
    else {
        qDebug() << "\nCan't open style file";
    }

    w.show();

    return a.exec();
}
