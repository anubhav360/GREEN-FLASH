#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebEngineWidgets>
#include<QWebEngineView>
#include<QObject>
#include"sign_up.h"
#include"ui_sign_up.h"
#include"history.h"
#include"ui_history.h"
#include<QDialog>
#include<QFile>
#include<QCryptographicHash>
#include<QInputDialog>
#include<regex>
#include<QFileDialog>
void changetitle();
QString usern="default";
QString File="File.dat";
QString ssdir=QDir::currentPath();
int ct=0;
MainWindow::MainWindow(QString url,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view= new QWebEngineView(parent);
  ui->centralwidget->setWindowTitle("Welcome to Green Flash");


        QVBoxLayout lay;
        QMainWindow::setWindowTitle("Welcome to Green Flash");

        lay.setSpacing(0);
    view->load(QUrl(url));
default_theme();


      view->setSizePolicy(ui->centralwidget->sizePolicy());
      view->setGeometry(ui->label->geometry());
      view->setParent(ui->centralwidget);

      view->show();
//important connections
   connect(ui->actionHistory,SIGNAL(triggered()),this,SLOT(sign_in()));
 connect(view,SIGNAL(loadFinished(bool)),this,SLOT(website_changed()));
   connect(ui->actionHistory_2,SIGNAL(triggered()),this, SLOT(loadhistory()));
   connect(ui->actionSign_Up,SIGNAL(triggered()),this, SLOT(signup()));
    connect(ui->actionScreenshot_directory,SIGNAL(triggered()),this, SLOT(ssd()));
    connect(ui->actionThemes,SIGNAL(triggered()),this, SLOT(settheme()));
    connect(ui->actionOpen,SIGNAL(triggered()),this, SLOT(open()));
    connect(ui->actionExit,SIGNAL(triggered()),this, SLOT(fexit()));
    connect(ui->actionSave_as_image,SIGNAL(triggered()),this, SLOT(ss()));
}
void MainWindow::open()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Select File"),"/home/","Browser supported files (*.html *.hbs *.pdf)");
    if (!filename.isEmpty())
    {ui->addressbar->setText(filename);
    view->load(QUrl(filename));
   // website_changed();
    }
    else
        return;
}
void MainWindow:: default_theme()
{
       QPalette ad=ui->addressbar->palette();
        QPalette me=ui->menubar->palette();
        QPalette bt=ui->pushButton->palette();
        QPalette la=ui->label_2->palette();
    ad.setColor(QPalette::Base,Qt::green);
    ad.setColor(QPalette::Text,Qt::black);
    me.setColor(QPalette::ButtonText,Qt::green);
    me.setColor(QPalette::Window,Qt::black);
    bt.setColor(QPalette::Button,Qt::yellow);
    bt.setColor(QPalette::ButtonText,Qt::black);
    la.setColor(QPalette::WindowText,Qt::green);
    ui->addressbar->setPalette(ad);
    ui->menubar->setPalette(me);
    ui->pushButton->setPalette(bt);
    ui->label_2->setPalette(la);

}
void MainWindow:: fexit()
{
    exit(0);
}
void MainWindow::ssd()
{
    bool ok;
   QString text = QInputDialog::getText(this, tr("Current directory"),
                                           tr("Current directory"), QLineEdit::Normal,
                                           ssdir, &ok);
    if (ok && !text.isEmpty())
    {   if (QFile(text).exists())
        ssdir=text;
        else
        {
         QMessageBox ni;
         ni.setText("Directory Invalid.");
         ni.exec();
        }
     }
}

void MainWindow:: settheme()
{
    QPalette ad=ui->addressbar->palette();
    QPalette me=ui->menubar->palette();
    QPalette bt=ui->pushButton->palette();
    QPalette la=ui->label_2->palette();
    bool ok;
    QStringList s;
    s<<"Default"<<"Moonlight"<<"American Flag"<<"Tropical"<<"Magentic";
    QString w= QInputDialog::getItem(this,tr("Select theme"),tr("Theme"),s,0,false,&ok);
int a=-1;
a=(w=="Moonlight"?1:a);
a=(w=="American Flag"?2:a);
a=(w=="Tropical"?3:a);
a=(w=="Magentic"?4:a);
ct=a;
    switch (a)
{
case 1:
        ad.setColor(QPalette::Base,Qt::black);
        ad.setColor(QPalette::Text,Qt::white);
        me.setColor(QPalette::ButtonText,Qt::white);
        me.setColor(QPalette::Window,Qt::black);
        bt.setColor(QPalette::Button,Qt::black);
        bt.setColor(QPalette::ButtonText,Qt::white);
        la.setColor(QPalette::WindowText,Qt::white);
        break;
    case 2:
        ad.setColor(QPalette::Base,Qt::darkBlue);
        ad.setColor(QPalette::Text,Qt::red);
        me.setColor(QPalette::ButtonText,Qt::red);
        me.setColor(QPalette::Window,Qt::darkBlue);
        bt.setColor(QPalette::Button,Qt::red);
        bt.setColor(QPalette::ButtonText,Qt::darkBlue);
        la.setColor(QPalette::WindowText,Qt::white);
        break;
    case 3:
        ad.setColor(QPalette::Base,Qt::darkGreen);
        ad.setColor(QPalette::Text,Qt::yellow);
        me.setColor(QPalette::ButtonText,Qt::darkYellow);
        me.setColor(QPalette::Window,Qt::green);
        bt.setColor(QPalette::Button,Qt::darkGreen);
        bt.setColor(QPalette::ButtonText,Qt::yellow);
        la.setColor(QPalette::WindowText,Qt::yellow);
        break;
        case 4:
            ad.setColor(QPalette::Base,Qt::darkMagenta);
            ad.setColor(QPalette::Text,Qt::cyan);
            me.setColor(QPalette::ButtonText,Qt::black);
            me.setColor(QPalette::Window,Qt::magenta);
            bt.setColor(QPalette::Button,Qt::black);
            bt.setColor(QPalette::ButtonText,Qt::magenta);
            la.setColor(QPalette::WindowText,Qt::magenta);
            break;
default:
ad.setColor(QPalette::Base,Qt::green);
ad.setColor(QPalette::Text,Qt::black);
me.setColor(QPalette::ButtonText,Qt::green);
me.setColor(QPalette::Window,Qt::black);
bt.setColor(QPalette::Button,Qt::yellow);
bt.setColor(QPalette::ButtonText,Qt::black);
la.setColor(QPalette::WindowText,Qt::green);
        break;
}
ui->addressbar->setPalette(ad);
ui->menubar->setPalette(me);
ui->pushButton->setPalette(bt);
ui->label_2->setPalette(la);
}
MainWindow::~MainWindow()
{
    if (view->history()->count()>1)
    savehistory();
    savetheme();
    delete ui;
}
void MainWindow::usrtheme()
{
  // QMessageBox deb;


   QFile File ("ut.txt") ;
    File.open(QIODevice::ReadOnly);
    QTextStream in(&File);

    QString usew=QCryptographicHash::hash(usern.toUtf8(),QCryptographicHash::Md5).toHex();
    std::string regreq="("+usew.toStdString()+"~)" + "(.*)";
 while (!in.atEnd())
    {
    QString line=in.readLine();
    if (std::regex_match(line.toStdString(),std::regex(regreq)))
    {

        int i=0;
    while (line[i]!="~")
     i++;
    i++;
    auto w=line[i];
    int a= w.digitValue();
    QPalette ad=ui->addressbar->palette();
    QPalette me=ui->menubar->palette();
    QPalette bt=ui->pushButton->palette();
    QPalette la=ui->label_2->palette();
ct=a;
    switch (a)
{
case 1:
        ad.setColor(QPalette::Base,Qt::black);
        ad.setColor(QPalette::Text,Qt::white);
        me.setColor(QPalette::ButtonText,Qt::white);
        me.setColor(QPalette::Window,Qt::black);
        bt.setColor(QPalette::Button,Qt::black);
        bt.setColor(QPalette::ButtonText,Qt::white);
        la.setColor(QPalette::WindowText,Qt::white);
        break;
    case 2:
        ad.setColor(QPalette::Base,Qt::darkBlue);
        ad.setColor(QPalette::Text,Qt::red);
        me.setColor(QPalette::ButtonText,Qt::red);
        me.setColor(QPalette::Window,Qt::darkBlue);
        bt.setColor(QPalette::Button,Qt::red);
        bt.setColor(QPalette::ButtonText,Qt::darkBlue);
        la.setColor(QPalette::WindowText,Qt::white);
        break;
    case 3:
        ad.setColor(QPalette::Base,Qt::darkGreen);
        ad.setColor(QPalette::Text,Qt::yellow);
        me.setColor(QPalette::ButtonText,Qt::darkYellow);
        me.setColor(QPalette::Window,Qt::green);
        bt.setColor(QPalette::Button,Qt::darkGreen);
        bt.setColor(QPalette::ButtonText,Qt::yellow);
        la.setColor(QPalette::WindowText,Qt::yellow);
        break;
        case 4:
            ad.setColor(QPalette::Base,Qt::darkMagenta);
            ad.setColor(QPalette::Text,Qt::cyan);
            me.setColor(QPalette::ButtonText,Qt::black);
            me.setColor(QPalette::Window,Qt::magenta);
            bt.setColor(QPalette::Button,Qt::black);
            bt.setColor(QPalette::ButtonText,Qt::magenta);
            la.setColor(QPalette::WindowText,Qt::magenta);
            break;
default:
ad.setColor(QPalette::Base,Qt::green);
ad.setColor(QPalette::Text,Qt::black);
me.setColor(QPalette::ButtonText,Qt::green);
me.setColor(QPalette::Window,Qt::black);
bt.setColor(QPalette::Button,Qt::yellow);
bt.setColor(QPalette::ButtonText,Qt::black);
la.setColor(QPalette::WindowText,Qt::green);
        break;
}
ui->addressbar->setPalette(ad);
ui->menubar->setPalette(me);
ui->pushButton->setPalette(bt);
ui->label_2->setPalette(la);
    }

}
    File.close();
}
void MainWindow::website_changed()
{
 ui->centralwidget->setWindowTitle(view->title());
 ui->addressbar->setText(view->url().toString());
 ui->addressbar->setCursorPosition(0);
}
void MainWindow::sign_in()
{
if (ui->actionHistory->text()=="Sign out")
{
    ui->actionHistory->setText("Sign in");
    ui->label_2->setText("Not signed in");
    ui->actionSign_Up->setEnabled(true);
    if (view->history()->count()>1)
    savehistory();
    savetheme();
    usern="defaut";
    usrtheme();
    return;
}
      bool ok;
    QString username;
    QString pass;
    if (view->history()->count()>1)
    {QMessageBox d;
    d.setText("Beware!. Signing in now will wipe previous history of the session, which will be saved to previous user's account");
    d.exec();
    }
     QString text = QInputDialog::getText(this, tr("Enter Username"),
                                             tr("User name:"), QLineEdit::Normal,
                                             "", &ok,Qt::Dialog);
     if (ok && !text.isEmpty())
        username=text;
     QFile Fil ("usern.txt") ;
     Fil.open(QIODevice::ReadOnly);
     QTextStream inf(&Fil);
     QString usew=QCryptographicHash::hash(username.toUtf8(),QCryptographicHash::Md5).toHex();
     bool flag=false;
     while (!inf.atEnd())
     {
        QString l=inf.readLine();
        if (l==usew)
        {
            flag=true;
        }
     }
     Fil.close();
    if (!flag)
    {
        QMessageBox nf;
        nf.setText("Username not found");
        nf.exec();
        return;
    }
      text = QInputDialog::getText(this, tr("Enter Password"),
                                             tr("Password:"), QLineEdit::Password,
                                             "", &ok);
      if (ok && !text.isEmpty())
         pass=text;
      QString st=username+text;
    auto hash=QCryptographicHash::hash(st.toUtf8(),QCryptographicHash::Md5).toHex();
    QFile File ("user.txt") ;
    File.open(QIODevice::ReadOnly);
    QTextStream in(&File);
    while (!in.atEnd())
    {
    QString line=in.readLine();
    if (line==hash)
    {
        QMessageBox w;
        w.setText("Signed in as "+username);
        w.exec();
        if(view->history()->count()>1)
            savehistory();
        savetheme();
        usern=username;

        view->history()->clear();
        ui->label_2->setText(usern);

        ui->actionHistory->setText("Sign out");
        ui->actionSign_Up->setEnabled(false);
      File.close();
      usrtheme();
      return;
    }

    }

    QMessageBox w;
    w.setText("Wrong username or password");
    w.exec();




    File.close();


}
void MainWindow::signup()
{
    if (ui->actionHistory->text()=="Sign out")
    {
        QMessageBox w;
        w.setText("Please sign out first");
        return;
    }
    sign_up f(this);
    f.exec();
}

void MainWindow:: histo(QString a)
{
   QString hist_url;
    ui->addressbar->setText(a);
    on_pushButton_clicked();
}
void MainWindow::loadhistory()
{
  if (view->history()->count()>1)
   savehistory();
   history h(usern,ct);
   QString a;
   connect(&h,SIGNAL(windowTitleChanged(QString)),this,SLOT(histo(QString)));
   h.exec();

}
void MainWindow::on_pushButton_clicked()
{
   if(ui->addressbar->text().left(6)!="https:")
    view->load("https:/"+ui->addressbar->text());
   else
     view->load(ui->addressbar->text());
    MainWindow::website_changed();
}


void MainWindow:: ss()
{
QPixmap p=view->grab();
p.save(ssdir+"/"+QDate::currentDate().toString()+QTime::currentTime().toString()+".png");
QMessageBox s;
s.setText(ssdir+"/"+QDate::currentDate().toString()+QTime::currentTime().toString()+".png");
s.exec();
}
QString secure_hash()
{
QString a= usern+time(NULL);
auto hash=QCryptographicHash::hash(a.toUtf8(),QCryptographicHash::Md5).toHex();

return hash;
}
void addtodb(QString hash)
{
    QFile File ("db.txt");
    File.open(QIODevice::Append);
    QTextStream out(&File);
    out<<(usern+"~"+hash+"~"+time(NULL)+"\n");

}
void MainWindow::savehistory()
{
//if (QDir("vault").exists());
//    else {
//    QDir("vault").mkdir("vault");
//}
QString sh=secure_hash();
QString Fil="vault/"+sh+".txt";
addtodb(sh);
QFile File(Fil);
File.open(QIODevice::WriteOnly);
QTextStream out(&File);
for (auto q:view->history()->items())
    out<<q.title()+">"+q.url().toString();

}

void MainWindow::readhistory()
{
QFile File ("db.txt") ;  //needs work
File.open(QIODevice::ReadOnly);
QDataStream in(&File);
auto w=view->history();
w->clear();
in >> *w;
}
void MainWindow::on_back_clicked()
{
     view->back();


}

void MainWindow::on_forward_clicked()
{
    view->forward();
}

void MainWindow::on_SS_clicked()
{
    ss();
}
void  MainWindow:: savetheme()
{
    QFile File ("ut.txt") ;
    QFile tem("temp.txt");
     File.open(QIODevice::ReadOnly);
    tem.open(QIODevice::WriteOnly);
     QTextStream in(&File);
     QTextStream out(&tem);
     bool flag=false;
     QString usew=QCryptographicHash::hash(usern.toUtf8(),QCryptographicHash::Md5).toHex();
     std::string regreq="("+usew.toStdString()+"~)" + "(.*)";
  while (!in.atEnd())
     {
     QString line=in.readLine();
     if (std::regex_match(line.toStdString(),std::regex(regreq)))
     {
         out<<usew+"~"+QString::number(ct)<<"\n";
         flag=true;
     }
     else
     {
         out<<line<<"\n";
     }
     }
  if (!flag)
       out<<usew+"~"+QString::number(ct)<<"\n";
  File.close();
  tem.close();
  QFile::remove("ut.txt");
  QFile::rename("temp.txt","ut.txt");
}
