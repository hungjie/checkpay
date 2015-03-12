#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebFrame>
#include <QMessageBox>
#include <QErrorMessage>

#include <QCursor>
#include <QThread>

#include <QNetworkCookie>

#include <QWebElementCollection>

#include <QDate>

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

    timer_ = new QTimer(this);

    connect(timer_, SIGNAL(timeout()), this, SLOT(task()));
}

MainWindow::~MainWindow()
{
    myCookie()->save();
    delete ui;
    delete t_;
    delete timer_;
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

QString MainWindow::getTrLine(QWebElement const& e)
{
    QWebElement timed = e.findFirst("p[class=\"time-d\"]");
    QWebElement timeh = e.findFirst("p[class=\"time-h ft-gray\"]");

    QString line = timed.toPlainText();
    line += " ";
    line += timeh.toPlainText();
    line += ",";

    QWebElement tradeNo = e.findFirst("a[class=\"J-tradeNo-copy J-tradeNo\"]");
    line += tradeNo.attribute("title", "");
    line += ",";

    QWebElement name = e.findFirst("p[class=\"name\"]");
    line += name.toPlainText();//("value", "");
    line += ",";

    QWebElement amount = e.findFirst("span[class=\"amount-pay-in\"]");
    line += amount.toPlainText();//("value", "");
    line += ",";

    QWebElement status = e.findFirst("td[class=\"status\"] > p");
    line += status.toPlainText();//("value", "");

    return line;
}

void MainWindow::task()
{
    QString filename = QDate::currentDate().toString("yyyy-MM-dd") + ".txt";
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream stream(&file);

    QWebFrame* wf = tabWidget()->currentWebView()->webPage()->mainFrame();

    //QWebElementCollection cs = wf->findAllElements("table[class=\"ui-record-table\"]");
    //timer_->stop();
//*
    //QString fclass = QString("tr[class=\"%1\"]").arg("J-item");
    QWebElementCollection cs = wf->findAllElements("tbody > tr");
//*/
    qDebug() << cs.count() ;

    for(int i = 0; i < cs.count(); ++i)
    {
        QString line = getTrLine(cs[i]);

        stream << line << "\n";
        qDebug() << line ;
    }

    file.close();
    timer_->stop();
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
    qDebug() << "start timer";
    timer_->start(100);
}
