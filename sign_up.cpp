#include "sign_up.h"
#include "ui_sign_up.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QCryptographicHash>
#include<regex>
sign_up::sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
   ui->comboBox->addItem("Default theme");
   ui->comboBox->addItem("Moonlight");
   ui->comboBox->addItem("American Flag");
   ui->comboBox->addItem("Tropical");
   ui->comboBox->addItem("Magentic");

}


sign_up::~sign_up()
{
    delete ui;
}
void  savetheme(QString usern,int ct);
void sign_up::on_pushButton_clicked()
{

    QFile File ("usern.txt") ;
    File.open(QIODevice::ReadOnly);
    QTextStream in(&File);
    QString username=QCryptographicHash::hash(ui->usrname->text().toUtf8(),QCryptographicHash::Md5).toHex();
    QString pwd=QCryptographicHash::hash(ui->pwd->text().toUtf8(),QCryptographicHash::Md5).toHex();
    while (!in.atEnd())
    {
       QString l=in.readLine();
       if (l==username)
       {
           QMessageBox w;
           w.setText("Uername already exists. Please try another.");
           w.exec();
           return;
       }
    }
    File.close();
    QFile writeu ("usern.txt") ;
    writeu.open(QIODevice::Append);
    QTextStream fw(&writeu);
      fw<<username+"\n";
     writeu.close();
      QString ch=QCryptographicHash::hash((ui->usrname->text()+ui->pwd->text()).toUtf8(),QCryptographicHash::Md5).toHex();
      QFile writec ("user.txt") ;
      writec.open(QIODevice::Append);
      QTextStream fc(&writec);
        fc<<ch+"\n";
       writec.close();
      int a=0;
      QString s=ui->comboBox->currentText();
      a=(s=="Moonlight"?1:a);
      a=(s=="American Flag"?2:a);
      a=(s=="Tropical"?3:a);
      a=(s=="Magentic"?4:a);
      savetheme(ui->usrname->text(),a);
       QMessageBox w;
       w.setText("Signed up successfully. Sign in to use account");
       w.exec();
       this->destroy();
    }
void  savetheme(QString usern,int ct)
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

