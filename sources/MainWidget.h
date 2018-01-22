#ifndef MAINWIDGET_
#define MAINWIDGET_

#include <QWidget>
#define VERSION_STRING "1.0.2"

namespace Ui {
    class MainWidget;
}

class ServerTabWidget;
class MainWidget : public QWidget
{
    Q_OBJECT
private:
    typedef QList<QVariantList> Servers;

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private Q_SLOTS:
	void on_pushButtonStartAll_clicked(bool checked);
	void on_pushButtonStopAll_clicked(bool checked);
	void on_pushButtonStopCurrent_clicked(bool checked);
	void on_pushButtonStartCurrent_clicked(bool checked);



private:
    //读取配置文件
    void readConfigFromLocal();

    //初始化Tab页
    void initTabWithConfig(const Servers& ss);

	//
	ServerTabWidget* tabWidgetAt(int i);

private:
    Ui::MainWidget *ui;

    Servers m_servers;
};

#endif // MAINWIDGET_
