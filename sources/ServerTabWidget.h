#ifndef SERVERTABWIDGET_H
#define SERVERTABWIDGET_H

#include <QtWidgets>
#include <QProcess>

class ServerTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ServerTabWidget(const QString& common, bool autostart, QWidget *parent = nullptr);
    ~ServerTabWidget();

private Q_SLOTS:
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    void startCommon();
    void checkLineCount();

private:
    QString m_common;
    QProcess m_process;

    QListWidget m_logsWidget;
};

#endif // SERVERTABWIDGET_H
