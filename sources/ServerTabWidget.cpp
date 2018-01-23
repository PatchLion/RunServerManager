#include "ServerTabWidget.h"

ServerTabWidget::ServerTabWidget(const QString& common, bool autostart, QWidget *parent)
    : QWidget(parent)
{
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));
    connect(&m_process, SIGNAL(readyReadStandardError()), this, SLOT(onReadyReadStandardError()));
    connect(&m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)));

    m_common = common;
    if(autostart){
		start();
    }

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    mainLayout->addWidget(&m_logsWidget);
}

ServerTabWidget::~ServerTabWidget()
<<<<<<< HEAD
{
	stop();
}
=======
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
>>>>>>> cb5ca479159dfe2ed887a85f07b0cafe91c2b89d

bool ServerTabWidget::isRunning()
{
	return m_process.isOpen();
}

void ServerTabWidget::start()
{
	if (!isRunning()){
		startCommon();
		pushLogMessage("Server started!!!", true);
	}
}

void ServerTabWidget::stop()
{
	if (isRunning()){
#ifdef Q_OS_WIN
		//pushLogMessage(QString("taskkill /F /PID %1").arg(m_process.processId()).toLatin1().data(), false);
		//system(QString("taskkill  /F /PID %1").arg(m_process.processId()).toLatin1().data());
#endif
		m_process.kill();
		m_process.close();
		m_process.waitForFinished();
		pushLogMessage("Server stopped!!!", true);
	}
}

void ServerTabWidget::onReadyReadStandardOutput()
{
	const QString content = QString::fromLocal8Bit(m_process.readAllStandardOutput()).trimmed();
	pushLogMessage(content, false);
}

void ServerTabWidget::onReadyReadStandardError()
{
	const QString content = QString::fromLocal8Bit(m_process.readAllStandardError()).trimmed();
	pushLogMessage(content, true);
}

void ServerTabWidget::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    //pushLogMessage("Progress finished: " +  exitCode, exitCode!=0);
}

void ServerTabWidget::startCommon()
{
    if(!m_process.isOpen() && !m_common.isEmpty()){
        m_process.start(m_common, QProcess::ReadWrite);
		qDebug() << "PID = " << m_process.processId() << m_process.pid();
		pushLogMessage("PID = " + QString::number(m_process.processId()), true);
    }
}

void ServerTabWidget::checkLineCount()
{
    if(m_logsWidget.count() > 2000){
        m_logsWidget.clear();
    }
}

void ServerTabWidget::pushLogMessage(const QString& content, bool errormsg)
{
	if (content.isEmpty())
	{
		return;
	}

	QListWidgetItem* item = new QListWidgetItem(content);
	if (errormsg){
		item->setForeground(Qt::red);
	}

	m_logsWidget.addItem(item);

	m_logsWidget.scrollToBottom();

	checkLineCount();
}
