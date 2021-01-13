#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"history.h"
#include<QWebEngineView>
#include<QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString url="http://www.google.com/",QWidget *parent = nullptr);
    friend history;
    QWebEngineView *view;
    QWebEngineHistory *hist;

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void open();
   void fexit();

    void histo(QString a);




    void on_back_clicked();

    void on_forward_clicked();

    void sign_in();
    void ss();
    void website_changed();
    void signup();
    void savehistory();
     void readhistory();
    void loadhistory();

    void on_SS_clicked();
    void ssd();
    void settheme();
    void usrtheme();
    void savetheme();
private:
    void default_theme();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
