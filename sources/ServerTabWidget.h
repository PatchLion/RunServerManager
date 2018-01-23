#ifndef SERVERTABWIDGET_H
#define SERVERTABWIDGET_H

#include <QtWidgets>
#include <QProcess>

class ServerTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ServerTabWidget(const QString& common, bool autostart, QWidget *parent = nullptr);
<<<<<<< HEAD
	~ServerTabWidget();

public:
	bool isRunning();

	void start();

	void stop();
=======
    ~ServerTabWidget();
>>>>>>> cb5ca479159dfe2ed887a85f07b0cafe91c2b89d

private Q_SLOTS:
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    void startCommon();
    void checkLineCount();

	void pushLogMessage(const QString& content, bool errormsg);

private:
    QString m_common;
    QProcess m_process;

    QListWidget m_logsWidget;
};

#endif // SERVERTABWIDGET_H
