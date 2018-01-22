#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "ServerTabWidget.h"

#define SERVERS_FILENAME "servers.json"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);



	setWindowTitle(QString::fromLocal8Bit("Server Run Manager v%1").arg(VERSION_STRING));

    ui->tabWidgetServers->clear();

    readConfigFromLocal();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButtonStartAll_clicked(bool checked)
{
	for (int i = 0; i < ui->tabWidgetServers->count(); i++){
		ServerTabWidget* tab = tabWidgetAt(i);
		if (tab){
			tab->start();
		}
	}
}

void MainWidget::on_pushButtonStopAll_clicked(bool checked)
{
	for (int i = 0; i < ui->tabWidgetServers->count(); i++){
		ServerTabWidget* tab = tabWidgetAt(i);
		if (tab){
			tab->stop();
		}
	}
}

void MainWidget::on_pushButtonStopCurrent_clicked(bool checked)
{
	ServerTabWidget* tab = tabWidgetAt(ui->tabWidgetServers->currentIndex());
	if (tab){
		tab->stop();
	}
}

void MainWidget::on_pushButtonStartCurrent_clicked(bool checked)
{
	ServerTabWidget* tab = tabWidgetAt(ui->tabWidgetServers->currentIndex());
	if (tab){
		tab->start();
	}
}

void MainWidget::readConfigFromLocal()
{
#ifdef Q_OS_WIN
    const QString fullpath = QApplication::applicationDirPath() + "/" + SERVERS_FILENAME;
#else
    const QString fullpath = QApplication::applicationDirPath() + "/../../../" + SERVERS_FILENAME;
#endif

    m_servers.clear();

    QFile file(fullpath);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不能打开配置文件: %1").arg(fullpath));
    }
   QByteArray b= file.readAll();
   QJsonParseError error;
   QJsonDocument doc = QJsonDocument::fromJson(b, &error);
   if(error.error==QJsonParseError::NoError)
   {
       if(doc.isObject())
       {
            QJsonObject obj=doc.object();//取得最外层这个大对象
           //这里放代码，对json数据进行取值

            if (obj.contains("servers")){
                QJsonArray server_objs = obj.value("servers").toArray();

                Q_FOREACH(QJsonValue sobj, server_objs){
                    const QString name = sobj.toObject().value("name").toString();
                    const QString common = sobj.toObject().value("common").toString();
                    bool autostart = sobj.toObject().value("autostart").toBool();

                    qDebug() << name << common << autostart;

                    if(name.isEmpty() || common.isEmpty()){
                        continue;
                    }
                    QVariantList listvar;
                    listvar << name;
                    listvar << common;
                    listvar << autostart;

                    m_servers << listvar;

                    //qDebug() << m_servers;

                }

                initTabWithConfig(m_servers);
            }
       }

   }
   else
   {
       qDebug()<<error.errorString();
   }

}

void MainWidget::initTabWithConfig(const MainWidget::Servers &ss)
{
    ui->tabWidgetServers->clear();

    Q_FOREACH(QVariantList listvar, ss){
        Q_ASSERT(listvar.size() == 3);

        const QString name = listvar[0].toString();
        const QString common = listvar[1].toString();
        bool autostart = listvar[2].toBool();

        ServerTabWidget* newTabWidget = new ServerTabWidget(common, autostart);
        ui->tabWidgetServers->addTab(newTabWidget, name);
    }
}

ServerTabWidget* MainWidget::tabWidgetAt(int i)
{
	return dynamic_cast<ServerTabWidget*>(ui->tabWidgetServers->widget(i));
}
