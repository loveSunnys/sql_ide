#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSettings>
#include <QFile>
#include <QStringList>
#include <QList>

typedef struct {
    QString db_driver = QString("QOCI");
    qint32 db_port = 1521;
    QString db_hostname = QString("127.0.0.1");
    QString db_name = QString("bkserver");
    QString db_user;
    QString db_pass;
    QString name;
    qint32 crypt = 0;
} Conndb;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
  QSqlDatabase init_db();
  //
  QString bktran_sql;//"交易码配置信息表，对交易码进行配置管理。如果流程编码为DEFAULT，则此交易不通过流程进行控制，直接通过相关模块进行处理。"
  QString business_sql;//对业务规则进行配置管理
  QString traninfo_sql;//"对单交易进行配置管理，即对单交易（非流程管理的交易）的节点信息进行配置。由内部交易码和功能码唯一确定"
  QString formmag_sql;//对业务的UI界面进行配置管理


   QSqlDatabase db;
    ~MainWindow();

private slots:

    void on_generateButton_clicked();

    void on_clear_Button_clicked();

    void on_fx_json_Button_clicked();

    void on_ins_db_Button_clicked();

    void on_db_select_Box_currentIndexChanged(const QString &arg1);

    void on_db_select_Box_currentIndexChanged(int index);



    void on_rf_jydmtj_Button_clicked();

private:
    Ui::MainWindow *ui;
void multienq_select(QString sql);
void single_select(QString sql);
void new_json(QString sql);
void update_json(QString sql);
void del_json(QString sql);

void set_defalutParameter();
void set_func_id_Parameter();


/*dbconf*/

typedef QList<Conndb> DBLists;

DBLists db_list;
Conndb curr_db;
Conndb ll;

Conndb ldns;
};

#endif // MAINWINDOW_H
