#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>
#include "mywebpage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    static MainWindow* Instance()
    {
        if(!owner_)
        {
            owner_ = new MainWindow();
        }

        return owner_;
    }

    static MyCookieJar* myCookie()
    {
        if(!mycookie_)
        {
            mycookie_ = new MyCookieJar();
            mycookie_->load();
        }

        return mycookie_;
    }

    TabWidget* tabWidget()
    {
        return t_;
    }

    QPoint viewPos();

    QLabel* statusLabel()
    {
        return msgLabel;
    }

    QString main_script()
    {
        return main_script_;
    }

    void main_script(QString const& main_script)
    {
        main_script_ = main_script;
    }

    QString js_script()
    {
        return js_script_;
    }

    void load_addr(QString const& addr)
    {
        load_addr_ = addr;
    }

    QString load_addr()
    {
        return load_addr_;
    }

private slots:
    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionTask_triggered();

    void task();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    QString getTrLine(const QWebElement &e);

private:
    Ui::MainWindow *ui;
    //WebView* v_;
    TabWidget* t_;
    QString jQuery;
    QLabel* msgLabel;

    QTimer* timer_;
    int timers_;

    static MainWindow* owner_;
    static MyCookieJar* mycookie_;

    QString main_script_;
    QString load_addr_;

    QString js_script_;
};

#endif // MAINWINDOW_H
