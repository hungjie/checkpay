#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebFrame>
#include <QMessageBox>
#include <QErrorMessage>

#include <QCursor>
#include <QThread>

#include <QNetworkCookie>

MainWindow* MainWindow::owner_  = 0;
MyCookieJar* MainWindow::mycookie_ = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //v_ = new WebView(this);
    t_ = new TabWidget(this);
    t_->setAutoFillBackground(true);

    ui->verticalLayout->addWidget(t_);
    ui->verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);

    msgLabel = new QLabel();
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addWidget(msgLabel);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border:0px}"));//去掉label的边

    setMouseTracking(true);
    //v_->setStatusBarLable(msgLabel);
    t_->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    myCookie()->save();
    delete ui;
    delete t_;
    //delete timer_;
    //delete mycookie_;
    QWebSettings::globalSettings()->clearIconDatabase();
    QWebSettings::globalSettings()->clearMemoryCaches();
}

QPoint MainWindow::viewPos()
{
    WebView* wv = MainWindow::Instance()->tabWidget()->currentWebView();
    if(wv)
    {
        QPoint p(0, 0);
        int window_x = wv->mapToGlobal(p).x();
        int window_y = wv->mapToGlobal(p).y();

        return QPoint(window_x, window_y);
    }

    return QPoint(0,0);
}


void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    msgLabel->setText("("+QString::number(e->x())+","+QString::number(e->y())+")");
}

void MainWindow::on_pushButton_clicked()
{
    QString url = ui->lineEdit->text();
    if(url.isEmpty())
        return;

    tabWidget()->currentWebView()->loadUrl(QUrl(url));
}

void MainWindow::on_actionTask_triggered()
{
    QWebFrame* wf = tabWidget()->currentWebView()->webPage()->mainFrame();
}
