/* Bespin widget style configurator for Qt4
   Copyright (C) 2007 Thomas Luebking <thomas.luebking@web.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "ui_uiDemo.h"
#include "dialog.h"
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QStyleFactory>
#include <QTimer>

#define CHAR(_QSTRING_) _QSTRING_.toLatin1().data()
#define RETURN_APP_ERROR int ret = app->exec(); delete window; delete app; return ret

class BStyle : public QStyle
{
public:
    BStyle() : QStyle (){}
    virtual void init(const QSettings *settings) = 0;
};

static int
error(const QString & string)
{
    qWarning("Error: %s", CHAR(string));
    return 1;
}

static int
usage(const char* appname)
{
   printf(
"Usage:\n\
==========================\n\
%s [config]\t\t\t\t\t\tConfigure the Bespin Style\n\
%s presets\t\t\t\t\t\tList the available Presets\n\
%s demo [style]\t\t\t\t\tLaunch a demo, you can pass other stylenames\n\
%s show <some_preset>\t\t\t\tOpen demo dialog with a preset\n\
%s try <some_config.bespin>\t\t\t\tTry out an exported setting\n\
%s sshot <some_file.png> [preset] [width]\t\tSave a screenshot\n\
%s load <some_preset>\t\t\t\tLoad a preset to current settings\n\
%s import <some_config.bespin>\t\t\tImport an exported setting\n\
%s update <some_config.bespin>\t\t\tLike import, but overrides existing\n\
%s export <some_preset> <some_config.bespin>\tExport an imported setting\n\
%s listStyles \t\t\t\t\tList all styles on this System\n\
%s loadPaletteFrom <style>\t\t\t\tLoad and store the default palette of a style\n",
appname, appname, appname, appname, appname, appname, appname, appname, appname, appname, appname, appname );
   return 1;
}

enum Mode
{
    Invalid = 0, Configure, Presets, Import, Update, Export, Load, Demo, Try, Screenshot, ListStyles, Show, LoadPalette
};

int
main(int argc, char *argv[])
{
    Mode mode = Configure;
    QApplication *app = 0;
    QString title;
    if (argc > 1)
    {
        mode = Invalid;
        if (!qstrcmp( argv[1], "config" )) mode = Configure;
        else if (!qstrcmp( argv[1], "presets" )) mode = Presets;
        else if (!qstrcmp( argv[1], "import" )) mode = Import;
        else if (!qstrcmp( argv[1], "update" )) mode = Update;
        else if (!qstrcmp( argv[1], "export" )) mode = Export;
        else if (!qstrcmp( argv[1], "demo" )) mode = Demo;
        else if (!qstrcmp( argv[1], "try" )) mode = Try;
        else if (!qstrcmp( argv[1], "show" )) mode = Show;
        else if (!qstrcmp( argv[1], "sshot" )) mode = Screenshot;
        else if (!qstrcmp( argv[1], "load" )) mode = Load;
        else if (!qstrcmp( argv[1], "listStyles" )) mode = ListStyles;
        else if (!qstrcmp( argv[1], "loadPaletteFrom" )) mode = LoadPalette;
    }

    switch (mode)
    {
    case Configure:
    {
        app = new QApplication(argc, argv);
        Config *config = new Config;
        BConfigDialog *window = new BConfigDialog(config, BConfigDialog::All &
                                                          ~(BConfigDialog::Import | BConfigDialog::Export));
        window->show();
        RETURN_APP_ERROR;
    }
    case Presets:
    {
        QSettings store("Bespin", "Store");
        foreach (QString name, store.childGroups())
            printf("%s\n", CHAR(name));
        return 0;
    }
    case Load:
    {
        if (argc < 3)
            return error("you lack <some_preset>");
        return Config::load(argv[2]);
    }
    case Update:
    case Import:
    {
        if (argc < 3)
            return error("you lack <some_config.bespin>");
        bool errors = false;
        for (int i = 2; i < argc; ++i)
        {
            if (!QFile::exists(argv[i]))
            {
                return error(QString("The file %1 does not exist").arg(argv[i]));
            }
            else {
                if (Config::sImport(argv[i], mode == Update).isNull())
                {
                    error(QString("Importing file %1 failed").arg(argv[i]));
                    errors = true;
                }
            }
        }
        return errors;
    }
    case Export:
    {
        if (argc < 3)
            return error("you lack <some_preset> <some_config.bespin>");
        if (argc < 4)
            return error("you lack <some_config.bespin>");
        bool suc = Config::sExport(argv[2], argv[3]);
        if (!suc)
            return error("export failed (invalid preset name?)");
        return 0;
    }
    case LoadPalette:
    {
        if (argc < 3)
            return error(QString("you lack <some_style>. Try \"%1 listStyles\"").arg(argv[0]));
        app = new QApplication(argc, argv);
        QStyle *style = QStyleFactory::create( argv[2] );
        if (!style)
        {
            delete app;
            return error(QString("Style \"%1\" does not exist. Try \"%2 listStyles\"").arg(argv[2]).arg(argv[0]));
        }
        Config::savePalette(style->standardPalette());
        delete app; delete style;
        break;
    }
    case Try:
    {
        app = new QApplication(argc, argv);
        if (argc < 3)
            return error("you lack <some_config.bespin>");

        if (!QFile::exists(argv[2]))
            return error(QString("The file %1 does not exist").arg(argv[2]));

        QSettings file(argv[2], QSettings::IniFormat);
        if (!file.childGroups().contains("BespinStyle"))
            return error(QString("%1 is not a valid Bespin configuration").arg(argv[2]));

        if (!app->setStyle("Bespin"))
            return error("Fatal: Bespin Style not found or loadable!");

        file.beginGroup("BespinStyle");
        title = file.value ( "StoreName", "" ).toString();
        // palette update =============================
        QPalette pal = app->palette();
        file.beginGroup("QPalette");
        QStringList list = file.value ( "active", Config::colors(pal, QPalette::Active) ).toStringList();
        Config::updatePalette(pal, QPalette::Active, list);
        list = file.value ( "inactive", Config::colors(pal, QPalette::Inactive) ).toStringList();
        Config::updatePalette(pal, QPalette::Inactive, list);
        list = file.value ( "disabled", Config::colors(pal, QPalette::Disabled) ).toStringList();
        Config::updatePalette(pal, QPalette::Disabled, list);
        file.endGroup();
        app->setPalette(pal);
        // ================================================
        static_cast<BStyle*>(app->style())->init(&file);

        file.endGroup();
    }
    case Show:
    case Demo:
    {
        if (title.isEmpty())
            title = "Bespin Demo";

        char *preset = 0;
        if (mode == Show)
        {
            if (argc < 3)
                return error("you lack <preset>");
#ifndef Q_WS_WIN
            setenv("BESPIN_PRESET", argv[2], 1);
            preset = argv[2];
#endif
        }
        else if (mode == Demo && argc > 2)
        {   // allow setting another style
            if (!app) app = new QApplication(argc, argv);
            app->setStyle(argv[2]);
            app->setPalette(app->style()->standardPalette());
            title = QString("Bespin Demo / %1 Style").arg(argv[2]);
        }
        else
            preset = getenv("BESPIN_PRESET");
        if (preset)
            title = QString("%1 @ Bespin Demo").arg(preset);
        if (!app)
            app = new QApplication(argc, argv);
        Dialog *window = new Dialog;
        Ui::Demo ui;
        ui.setupUi(window);
        ui.tabWidget->setCurrentIndex(0);
        QObject::connect (ui.rtl, SIGNAL(toggled(bool)), window, SLOT(setLayoutDirection(bool)));
        window->setWindowTitle ( title );
        window->show();
        RETURN_APP_ERROR;
    }
    case Screenshot:
    {
        if (argc < 3)
            return error("you lack <some_output.png>");
#ifndef Q_WS_WIN
        if (argc > 3)
            setenv("BESPIN_PRESET", argv[3], 1);
#endif
        app = new QApplication(argc, argv);
        Dialog *window = new Dialog;
        Ui::Demo ui;
        ui.setupUi(window);
        ui.tabWidget->setCurrentIndex(0);
        ui.buttonBox->button(QDialogButtonBox::Ok)->setAttribute( Qt::WA_UnderMouse );
        ui.demoBrowser->setAttribute( Qt::WA_UnderMouse );
//       ui.demoLineEdit->setFocus(Qt::MouseFocusReason);
      
        QImage image(window->size(), QImage::Format_RGB32);
        window->showMinimized();
        window->QDialog::render(&image);
        if (argc > 4)
            image = image.scaledToWidth(atoi(argv[4]), Qt::SmoothTransformation);
        image.save ( argv[2], "png" );
        delete window;
        delete app;
        return 0;
    }
    case ListStyles:
    {
        foreach (QString string, QStyleFactory::keys())
            printf("%s\n", CHAR(string));
        return 0;
    }
    default:
        return usage(argv[0]);
    }
}
