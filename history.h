#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include<QListWidget>
namespace Ui {
class history;
}

class history : public QDialog
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    explicit history(QString user,int ct,QWidget *parent = nullptr);
    void run_web(QString url);
    void read_history(QString user);
    void add_hash(QString h);
    void addtolist(QString hash);
    ~history();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::history *ui;
};

#endif // HISTORY_H
