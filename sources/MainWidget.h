#ifndef MAINWIDGET_
#define MAINWIDGET_

#include <QWidget>

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    typedef QList<QVariantList> Servers;

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    //读取配置文件
    void readConfigFromLocal();

    //初始化Tab页
    void initTabWithConfig(const Servers& ss);

private:
    Ui::MainWidget *ui;

    Servers m_servers;
};

#endif // MAINWIDGET_
