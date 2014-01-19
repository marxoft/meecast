/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Other Maemo Weather(omweather) - MeeCast
 *
 * Copyright (C) 2006-2013 Vlad Vasilyeu
 * Copyright (C) 2010-2011 Tanya Makova
 *     for the code
 *
 * Copyright (C) 2008 Andrew Zhilin
 *		      az@pocketpcrussia.com 
 *	for default icon set (Glance)
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU weather-config.h General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
*/
/*******************************************************************************/

#include <sailfishapp.h>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
//#include <QtQml/qqml.h>


//#include <QtCore/QtGlobal>
//#include <QApplication>
//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QGraphicsWidget>
//#include <QGraphicsLinearLayout>
//#include <QDeclarativeComponent>
//#include <QDeclarativeContext>
//#include <QDeclarativeEngine>
//#include <QDeclarativeView>
#include <QTranslator>
#include <QLocale>
#include <QHash>
#include <QtQml>
//#include <QGraphicsGridLayout>
#include <exception>
#include <iostream>

#include "sailfishapplication.h"
#include "core.h"
#include "dataqml.h"
#include "configqml.h"
//#include "qmllayoutitem.h"
#include "dataitem.h"
#include "datamodel.h"
#include "parserqt.h"
#include "databasesqlite.h"
#include "abstractconfig.h"
#include "dbusadaptor.h" 
#include "controller.h" 
#include "meecastcover.h"

//#include <QtDebug>

#include <libintl.h>
#include <locale.h>

#include "selectmodel.h"

//#define _(String) gettext(String)


#define _(String)  QObject::trUtf8(String).toStdString().c_str()

//////////////////////////////////////////////////////////////////////////////
bool
update_weather_forecast(Core::Config *config){
    uint i;
    int success = 0;
    Core::Station* station;

    for (i = 0; i < config->stationsList().size(); i++){
        station = config->stationsList().at(i);
        if (station->updateData(true)){
            success ++;
        }
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////

Q_DECL_EXPORT int main(int argc, char* argv[])
{


    QScopedPointer<QGuiApplication> app(Sailfish::createApplication(argc, argv));
     
    qmlRegisterType<MeeCastCover>("harbour.meecast.meecastcover", 1, 0, "MeeCastCover");
    app->setProperty("NoMStyle", true);

    QDir::setCurrent(app->applicationDirPath());

    
    std::cerr<<"Begin "<<std::endl;
    std::cerr<<app->applicationDirPath().toStdString().c_str()<<std::endl;
    std::cerr<<"End "<<std::endl;


    QString str = QDir::currentPath();
    std::cerr<<str.toStdString().c_str()<<std::endl;

    str.truncate(str.length()-4);

    Core::AbstractConfig::prefix = str.toStdString();
    QDir::setCurrent(QDir::currentPath());



    /*
    //Set up a graphics scene with a QGraphicsWidget and Layout
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsWidget *widget = new QGraphicsWidget();
    QGraphicsGridLayout *layout = new QGraphicsGridLayout;
    layout->setSpacing(0);
    widget->setLayout(layout);
    scene.addItem(widget);
    view.setScene(&scene);
*/

    //Add the QML snippet into the layout

  //  QString locale = QLocale::system().name();

   // std::cerr<<"locale: "<<locale.toStdString()<<std::endl;
    
    //ConfigQml *config;
    //
    Controller *controller;
/*
    QTranslator translator;
    translator.load("ru.qml", "i18n");
    app.installTranslator(&translator);
*/
    /*
    textdomain("omweather");
    bindtextdomain("omweather", localepath.toStdString().c_str());
    std::cerr<<" Path for tanslate "<<localepath.toStdString().c_str()<<std::endl;
*/
    controller = new Controller(); 

    /* Locale */
    // Set up the translator.
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString("omweather_%1").arg(locale_string);
/*    std::cerr<<filename.toStdString().c_str()<<std::endl; */

    QString localepath =QString::fromStdString(Core::AbstractConfig::prefix + "/share/harbour-meecast/locale");
    if (translator.load(filename, localepath)) {
        /* std::cerr<<"Success TR"<<std::endl; */
        app->installTranslator(&translator);
    }

//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
   
    for (unsigned int i=1; i<controller->config()->languagesList().size(); i++){
        if (controller->config()->languagesList().at(i).first == controller->config()->Language()){
            QLocale::setDefault(QLocale(controller->config()->languagesList().at(i).second.c_str()));
            filename = QString("omweather_%1").arg(controller->config()->languagesList().at(i).second.c_str());
            std::cerr<<filename.toStdString().c_str()<<std::endl; 
            QString localepath =QString::fromStdString(Core::AbstractConfig::prefix + "/share/harbour-meecast/locale");
            if (translator.load(filename, localepath)) {
                    std::cerr<<"Success TR"<<std::endl;
                    app->installTranslator(&translator);
            }
        }
    }

    /* D-BUS */
    DbusAdaptor* dadapt = new DbusAdaptor(controller);

    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerService("org.meego.omweather");
    connection.registerObject("/org/meego/omweather", controller);
   

    //config = controller->config();
    //std::cerr<<"iconpath = "<<config->imagespath().toStdString() << std::endl;
    //update_weather_forecast(config);
    
    QQuickView *qview;
    qview = controller->qview();
    
   Sailfish::setView(qview,QString::fromStdString("file://" + Core::AbstractConfig::prefix + 
                                                   Core::AbstractConfig::sharePath +
                                                   Core::AbstractConfig::layoutqml));

   //  Sailfish::setView(qview,QString::fromStdString("file://" + Core::AbstractConfig::prefix + 
   //                                                Core::AbstractConfig::sharePath +
   //                                                Core::AbstractConfig::layoutqml));
   /* 
    QDir::setCurrent(QString::fromStdString(Core::AbstractConfig::prefix + 
                     Core::AbstractConfig::sharePath +
                     "omweather-qml/qml/"));
   */
//    Sailfish::setView(qview,QString::fromStdString("main.qml")); 
//    QScopedPointer<QQuickView> view(Sailfish::createView(QString::fromStdString(Core::AbstractConfig::prefix +
//                                                                Core::AbstractConfig::sharePath +
//                                                                Core::AbstractConfig::layoutqml)));
  //  QScopedPointer<QQuickView> view(Sailfish::createView("main.qml"));
    Sailfish::showView(qview);

    std::cerr << "qml path = " << Core::AbstractConfig::layoutqml << std::endl;
    /*
    qview->setSource(QUrl::fromLocalFile(QString::fromStdString(Core::AbstractConfig::prefix +
                                                                Core::AbstractConfig::sharePath +
                                                                Core::AbstractConfig::layoutqml)));
    */
   // QObject::connect((QObject*)qview->engine(), SIGNAL(quit()), app, SLOT(quit()));
    //qview->showFullScreen();
    /*This code provides Segmantation fault
    delete dadapt;
    dQString::fromStdString(Core::AbstractConfig::prefix +
//                                                                Core::AbstractConfig::sharePath +
//                                                                Core::AbstractConfig::layoutqml)));elete controller;
    */
    return app->exec();
//    return SailfishApp::main(argc, argv);
   
}
