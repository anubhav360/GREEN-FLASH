#include "history.h"
#include "ui_history.h"
#include<QFile>
#include<QTextStream>
#include<regex>
#include<regex.h>
#include<string>
#include<qqueue.h>
#include<QtWebEngineWidgets>
#include<QWebEngineHistory>
#include<QWebEngineHistoryItem>
#include<mainwindow.h>
history::history(QString user,int ct,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);

    ui->label->setText("History of "+user);
    history::setWindowTitle("History of "+user);
    read_history(user);
//list-base,text,, label-windowtext. history base
QPalette li=ui->listWidget->palette();
QPalette la=ui->label->palette();
QPalette ba=history::palette();
    switch (ct)
{
case 1:
        li.setColor(QPalette::Base,Qt::black);
        li.setColor(QPalette::Text,Qt::white);
        la.setColor(QPalette::WindowText,Qt::white);
        ba.setColor(QPalette::Window,Qt::darkGray);
        break;
case 2:
        li.setColor(QPalette::Base,Qt::darkBlue);
        li.setColor(QPalette::Text,Qt::white);
        la.setColor(QPalette::WindowText,Qt::red);
        ba.setColor(QPalette::Window,Qt::darkBlue);
        break;
case 3:
        li.setColor(QPalette::Base,Qt::darkGreen);
        li.setColor(QPalette::Text,Qt::yellow);
        la.setColor(QPalette::WindowText,Qt::green);
        ba.setColor(QPalette::Window,Qt::darkYellow);
        break;
case 4:
        li.setColor(QPalette::Base,Qt::darkMagenta);
        li.setColor(QPalette::Text,Qt::cyan);
        la.setColor(QPalette::WindowText,Qt::cyan);
        ba.setColor(QPalette::Window,Qt::darkMagenta);
        break;
default:
        li.setColor(QPalette::Base,Qt::black);
        li.setColor(QPalette::Text,Qt::green);
        la.setColor(QPalette::WindowText,Qt::green);
        ba.setColor(QPalette::Window,Qt::black);
        break;

}
    ui->listWidget->setPalette(li);
    ui->label->setPalette(la);
    history::setPalette(ba);
}

void history::addtolist(QString hash)
{
    QFile File ("vault/"+hash+".txt") ;

    File.open(QIODevice::ReadOnly);
    QTextStream in(&File);
   while(!in.atEnd())
    { QString q=in.readLine();
      ui->listWidget->addItem(q);
      //ui->listWidget->addItem("Working");
   }

}
void history::read_history(QString a)
{
QFile File ("db.txt") ;  //needs work
File.open(QIODevice::ReadOnly);
QTextStream in(&File);
std::string regreq="("+a.toStdString()+"~)" + "(.*)";

QQueue <QString> q;
while (!in.atEnd())
{
QString line=in.readLine();
if (std::regex_match(line.toStdString(),std::regex(regreq)))
{
int i=0;
while (line[i]!="~")
 i++;
i++;
QString hs="";
hs="";
while (line[i]!="~")
{hs=hs+line[i];
i++;}
q.push_back(hs);
}

}

File.close();

while (!q.empty())
{
    auto w=q.front();
    addtolist(w);
    q.pop_front();
}
//in >> *w;
}

history::~history()
{
    delete ui;
}

void history::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString it=item->text();
     int l=it.length();
    l--;
    while (it[l]!=">")
    {
         l--;
    }
l++;
    int reqc=it.length()-l;
    QString url=it.right(reqc);
   //run_web(url);
   this->windowTitleChanged(url);

}
void history:: run_web(QString url)
{
   //
}
