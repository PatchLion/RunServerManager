#include "ServerTabWidget.h"

ServerTabWidget::ServerTabWidget(const QString& common, bool autostart, QWidget *parent)
    : QWidget(parent)
{
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));
    connect(&m_process, SIGNAL(readyReadStandardError()), this, SLOT(onReadyReadStandardError()));
    connect(&m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)));

    m_common = common;
    if(autostart){
        startCommon();
    }

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    mainLayout->addWidget(&m_logsWidget);
}

ServerTabWidget::~ServerTabWidget()
{
    if(m_process){
        m_process.close();
    }
}

void ServerTabWidget::onReadyReadStandardOutput()
{
    const QString content = m_process.readAllStandardOutput();
    QListWidgetItem* item = new QListWidgetItem(content);
    item->setForeground(Qt::blue);

    m_logsWidget.addItem(item);

    checkLineCount();
}

void ServerTabWidget::onReadyReadStandardError()
{
    const QString content = m_process.readAllStandardError();
    QListWidgetItem* item = new QListWidgetItem(content);
    item->setForeground(Qt::red);

    m_logsWidget.addItem(item);

    checkLineCount();
}

void ServerTabWidget::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Progress finished: " << exitCode << exitStatus;
}

void ServerTabWidget::startCommon()
{
    if(!m_process.isOpen() && !m_common.isEmpty()){
        m_process.start(m_common, QProcess::ReadWrite);
    }
}

void ServerTabWidget::checkLineCount()
{
    if(m_logsWidget.count() > 2000){
        m_logsWidget.clear();
    }
}
