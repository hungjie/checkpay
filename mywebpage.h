#ifndef MYWEBPAGE_H
#define MYWEBPAGE_H

#include <QWebPage>
#include <QWebView>
#include <QAction>
#include <QMouseEvent>
#include <QLabel>
#include <QMap>
#include <QTimer>

#include <QNetworkCookie>
#include <QNetworkCookieJar>

#include <QScrollBar>

#include <QTabWidget>
#include <QTabBar>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QStringList>

class WebPage;
class WebView;

class KeyBdOperateor
{
public:

    void CtrlA();
    void Backspace();
};

class MouseOperator
{
public:
    explicit MouseOperator(int x, int y)
    {
        x_ = x;
        y_ = y;
    }

    void LBClick();

    void Move(int x, int y);

    //中键按下
    void MBClick();

    //中键滚动
    void MBRoll(int ch);

private:
    int x_;
    int y_;
};

class TabBar : public QTabBar
{
    Q_OBJECT

signals:
    void closeTab(int index);

public:
    TabBar(QWidget *parent = 0);

private slots:
    void closeTab();

private:
    friend class TabWidget;
};

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = 0);

    WebView *webView(int index) const;
    WebView *currentWebView() const;

public slots:
    WebView *newTab(bool makeCurrent = true);
    void closeTab(int index = -1);

    void loadUrlInCurrentTab(const QUrl &url);

private slots:
    void currentChanged(int index);

private:
    TabBar *m_tabBar;
};

class JsobjectInterface : public QObject
{
    Q_OBJECT
public:
    explicit JsobjectInterface(QObject *parent = 0);
    ~JsobjectInterface();

    int move_x(){ return this->move_x_; }
    void move_x(int x){ this->move_x_ = x; }

    int move_y(){ return this->move_y_; }
    void move_y(int y){ this->move_y_ = y; }

    int scroll_x(){ return this->scroll_x_; }
    void scroll_x(int x){ this->scroll_x_ = x; }

    int scroll_y(){ return this->scroll_y_; }
    void scroll_y(int y){ this->scroll_y_ = y; }

    QMap<QString, QVariant> emitSignal(){ return this->m_emitSignal; }
    void emitSignal(QMap<QString, QVariant> const& emitSig){ this->m_emitSignal = emitSig; }

signals:
    void Sendtojs(QMap<QString, QVariant> object);

    void LBClick(QMap<QString, QVariant> object);
    void Move(QMap<QString, QVariant> object);
    void MBClick(QMap<QString, QVariant> object);
    void MBRoll(QMap<QString, QVariant> object);

    void Scroll(const QMap<QString, QVariant>& object);

public slots:
    //供javascript调用的槽
    //QMap<QString, QVariant> slotThatReturns(const QMap<QString, QVariant>& object);
//    void slotThatEmitsSignal();
    QVariant get_search_input_array();
    QVariant get_search_input_id();

    //interface call for js
    void timerInput(const QMap<QString, QVariant> &object);

    void scroll(const QMap<QString, QVariant>& object);
    void lbclick(const QMap<QString, QVariant>& object);
    void move(const QMap<QString, QVariant>& object);
    void mbclick(const QMap<QString, QVariant>& object);
    void mbroll(const QMap<QString, QVariant>& object);

    void sleep(const QVariant &object);
    void switchtab(const QVariant & object);

    void waitLoadFinished(const QMap<QString, QVariant>& object);

    void whileMBRoll(const QMap<QString, QVariant>& object);

    void exit(const QMap<QString, QVariant>& object);

    void forfunc(const QMap<QString, QVariant>& object);
    void randomoption(const QMap<QString, QVariant>& object);
    QMap<QString, QVariant> randomoption();

    QMap<QString, QVariant> cur_parms();

    QVariant isLoadFinished();

    void randomscrollandmoveandmbclick(const QMap<QString, QVariant>& object);
    void randomScrollAndMoveAndMbclickTimer();

    void retry();

    void testlog(QVariant const& log);

    //-----------------------
    void updateMouseMove();
    void updateMouseScroll();
    void updateTimerInput();
    void updateSleep();
    void updateLoadFinish();
    void whileMBRoll();
    void emitTimer();

protected:
    QVariant emit_func(QString const& func);
    void emitToJs(QString const& sender, QMap<QString, QVariant> const& object);

    void nativeToGlobal(int& x, int& y);

    void disemited();
    bool need_emited(){return need_emited_;}

private:
    static int m_signalEmited;
    //QMap<QString, QVariant> m_returnObject;
    QMap<QString, QVariant> m_emitSignal;

    static QMap<QString, QVariant> m_emitOption;
    static QMap<QString, QVariant> m_randomOption;

    QObject* page_;

    QTimer* mouseMoveTimer_;
    QTimer* mouseScrollTimer_;
    QTimer* inputTimer_;

    QTimer* sleepTimer_;

    QTimer* waitLoadFinishTimer_;

    QTimer* whilembroll_;

    QTimer* emitTimer_;

    QTimer* randomScrollAndMoveAndMbclickTimer_;

    int move_x_;
    int move_y_;

    int scroll_x_;
    int scroll_y_;

    int loadFinishedTimes_;
    int mbroll_times_;

    static bool emit_increasement_;

    int scrollmovembclickstep_;
    QMap<QString, QVariant> scrollmovembclickmap_;

    bool need_emited_;
};

class MyCookieJar : public QNetworkCookieJar
{
    Q_OBJECT

public:
    explicit MyCookieJar(QObject *parent = 0);
    ~MyCookieJar();

    QList<QNetworkCookie> mycookies();

    void setCookies(const QList<QNetworkCookie>& cookieList);

    void addCookie(QString name,QString value);
    void changeCookie(QString name,QString value);

    void clearCookies();

    QList<QNetworkCookie> cookieByUrl(QString const& url);

    bool save();
    bool load();

private:

};

class WebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit WebPage(QObject *parent = 0);
    ~WebPage();

    void lefeMouseClicked();
    void scrollBar(int left, int right);

    void excuteJS(QString const& func);
    void excuteJS();

    QPoint scrollBar();

    int maxVerticalScrollBar();
    int maxHorizontalScrollBar();

    JsobjectInterface* jsObjectInterface()
    {
        return jsQObject_;
    }

    bool isLoadFinished()
    {
        return is_load_finished_;
    }

signals:
    /*
    void loadLink(const QUrl & url);
    void openLink(const QUrl & url);
    */
    void loadingUrl(const QUrl &url);

protected:
    bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);//重写
    QString userAgentForUrl( const QUrl & url ) const;

    int maxScrollBar(Qt::Orientation orientation);

private slots:
    void addJavaScriptObject();
    void loadFinished(bool ok);

private:
    friend class WebView;

    // set the webview mousepressedevent
    Qt::KeyboardModifiers m_keyboardModifiers;
    Qt::MouseButtons m_pressedButtons;
    bool m_openInNewTab;
    QUrl m_loadingUrl;

    QString jQuery;
    //QString jscript_;
    JsobjectInterface* jsQObject_;

    bool is_load_finished_;

    bool is_added_;
 };

class WebView : public QWebView {
    Q_OBJECT

public:
    WebView(QWidget *parent = 0);
    ~WebView();

    WebPage *webPage() const { return m_page; }

    void loadUrl(const QUrl &url);
    QUrl url() const;

    QString lastStatusBarText() const;
    inline int progress() const { return m_progress; }

    MyCookieJar* myCookie();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    //void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void setProgress(int progress);
    void loadFinished(bool ok);
    void setStatusBarText(const QString &string);
    void downloadRequested(const QNetworkRequest &request);
    void openLinkInNewTab();
    void linkClicked(const QUrl &);
    void loadStarted();

private:
    QString m_statusBarText;
    QUrl m_initialUrl;
    int m_progress;
    WebPage *m_page;
};

#endif // MYWEBPAGE_H
