#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_defalutParameter();


}

QSqlDatabase MainWindow::init_db()
{
    //连接数据库
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase(curr_db.db_driver);
    /**连接Oracle数据库
              *数据库名：abc
              *表名：my_oracle
              *用户名：sys
              *密码：123
              *端口号：（默认）1521
            */
    db.setPort(curr_db.db_port);
    db.setHostName(curr_db.db_hostname);
    db.setDatabaseName(curr_db.db_name);
    db.setUserName(curr_db.db_user);
    db.setPassword(curr_db.db_pass);
    if (!db.open())
    {
        //链接数据库失败";
        db.lastError().text();
    }
    return db;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    QString trancode;
    trancode = ui->int_tran_code_Edit->text().toUpper().trimmed().remove("'");
    if( trancode.isEmpty() )
    {

        QMessageBox::warning(NULL,tr(u8"警告"), tr(u8"交易码为空"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    QString func_id;
    func_id = ui->func_id_comboBox->currentText().toUpper().trimmed().remove("'");

    QString t_name;
    t_name =ui->t_name_Edit->text().trimmed().remove("'");
    if( t_name.isEmpty() )
    {

        QMessageBox::warning(NULL,tr(u8"警告"), tr(u8"备注为空"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    QString tranid;
    tranid = ui->tranid_Edit->text().toUpper().trimmed().remove("'");
    if( tranid.isEmpty() )
    {

        QMessageBox::warning(NULL,tr(u8"警告"), tr(u8"业务类型为空"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
    }
    QString uiid;
    uiid = ui->uiid_Edit->text().toLower().trimmed();

    if(!uiid.isEmpty())
    {
        formmag_sql = QString("INSERT INTO FORMMAG (SEQ_NO, BANK_CD, UIID, FILENAME, MD5, TRANID, UIMOD, U_NAME, DESCRIBE1, REFRESH, STATUS, EFF_DATE, EXP_DATE, VERSION, CREATED_BY, CREATED_DATE, LAST_UPD_BY, LAST_UPD_DATE) VALUES ("
                              "(select max(SEQ_NO)+1 from FORMMAG),"
                              " '00000000000000', "
                              "'%1', "
                              "'%2', "
                              "'0                               ', "
                              "'%3',"
                              " '0', "
                              "'%4', "
                              "'%5', "
                              "'1', '1',  sysdate, TO_DATE('2099-12-31', 'YYYY-MM-DD'), '1.00.00', 'system', TO_DATE('2014-01-01', 'YYYY-MM-DD'), 'system', sysdate)")
                .arg(uiid).arg(uiid).arg(tranid).arg(t_name).arg(t_name);

    }else
    {
        formmag_sql.clear();
    }

    if( !func_id.isEmpty() )
    {

        traninfo_sql = QString("INSERT INTO  TRANINFO (SEQ_NO, INT_TRAN_CODE, FUNC_ID, BIZID, T_NAME, DESCRIBE1, STATUS, VERSION, EFF_DATE, EXP_DATE, CREATED_BY, CREATED_DATE, LAST_UPD_BY, LAST_UPD_DATE) VALUES ("
                               "(select max(SEQ_NO)+1 from TRANINFO), "
                               "'%1',"
                               " '%2', "
                               "'B%3', "
                               "'%4',"
                               " '%5', "
                               "'1', '1.00.00', sysdate, TO_DATE('2099-12-01', 'YYYY-MM-DD'), 'system', sysdate, 'system', sysdate)")
                .arg(trancode).arg(func_id).arg(trancode).arg(t_name).arg(t_name);


        business_sql = QString("INSERT INTO  BUSINESS (SEQ_NO, BANK_CD, BIZID, TRANID, INPUT1, INPUT2, INPUT3, INPUT5, INPUT4, OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, OUTPUT5, UIID, B_NAME, DESCRIBE1, STATUS, FLAG, EFF_DATE, EXP_DATE, VERSION, CREATED_BY, CREATED_DATE, LAST_UPD_BY, LAST_UPD_DATE) VALUES ("
                               "'0', '00000000000000', "
                               "'B%1', "
                               "'%2', "
                               "'%3', "
                               "' ', 'DEFAULT', 'DEFAULT', 'DEFAULT', 'DEFAULT', 'DEFAULT', 'DEFAULT', 'DEFAULT', 'DEFAULT',"
                               " '%4',"
                               " '%5', "
                               "'%6', '1', '1', sysdate, TO_DATE('2099-12-31', 'YYYY-MM-DD'), '1.00.00', 'system', sysdate, 'system', sysdate)")
                .arg(trancode).arg(tranid).arg(trancode.toLower()).arg(uiid).arg(t_name).arg(t_name);

    }else
    {
        traninfo_sql.clear();
        business_sql.clear();
    }

    bktran_sql = QString("INSERT INTO BKTRAN (SEQ_NO, INT_TRAN_CODE, BANK_CD, FLOWID, UIID, TRANID, CHECKFLAG, T_NAME, DESCRIBE1, STATUS, FLAG, EFF_DATE, EXP_DATE, VERSION, CREATED_BY, CREATED_DATE, LAST_UPD_BY, LAST_UPD_DATE) VALUES ("
                         "(select max(SEQ_NO)+1 from BKTRAN), "
                         "'%1', "
                         "'00000000000000', "
                         "'DEFAULT', "
                         "'%2', "
                         "'%3', "
                         "'00', '%4',"
                         " '%5',"
                         " '1', '0',sysdate, TO_DATE('2999-12-31', 'YYYY-MM-DD'), '1.0.0', 'system', sysdate, 'systm', sysdate)")
            .arg(trancode).arg(uiid).arg(tranid).arg(t_name).arg(t_name);


    ui->textEdit->setText(formmag_sql + QString(";\n")+traninfo_sql + QString(";\n") +business_sql+ QString(";\n") + bktran_sql +  QString(";"));
}



void MainWindow::on_clear_Button_clicked()
{
    bktran_sql.clear();
    business_sql.clear();
    traninfo_sql.clear();
    formmag_sql.clear();
    ui->textEdit->clear();
}

void MainWindow::on_fx_json_Button_clicked()
{
    QString hdjson;
    hdjson = ui->hjson_Edit->toPlainText().toUpper();
    qint32 is_select =0;
    qint32 is_from =0;

    if(ui->mselect_radioButton->isChecked())
    {
        if((is_select = hdjson.indexOf(QString("SELECT"),0)) ==-1)
        {
            QMessageBox::warning(NULL,tr(u8"警告"), tr(u8"[SELECT]关键字为空"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return ;
        }
        if((is_from = hdjson.indexOf(QString("FROM"),0)) ==-1)
        {
            QMessageBox::warning(NULL,tr(u8"警告"), tr(u8"[FROM]关键字为空"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return ;
        }
        QString hdjson_select = hdjson.mid(is_select + 6,is_from-6).trimmed();
        multienq_select( hdjson_select);
    }else if (ui->sselect_radioButton->isChecked()) {
        if((is_select = hdjson.indexOf(QString("SELECT"),0)) ==-1)
        {
            QMessageBox::warning(NULL,tr(u8"警告"), tr(u8"[SELECT]关键字为空"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return ;
        }
        if((is_from = hdjson.indexOf(QString("FROM"),0)) ==-1)
        {
            QMessageBox::warning(NULL,tr(u8"警告"), tr(u8"[FROM]关键字为空"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return ;
        }
        QString hdjson_select = hdjson.mid(is_select + 6,is_from-6).trimmed();
        single_select( hdjson_select);
    }else if (ui->update_radioButton->isChecked()) {





        QString hdjson_select = hdjson.mid(is_select + 6,is_from-6).trimmed();
        update_json( hdjson_select);
    }else if (ui->new_radioButton->isChecked()) {



        QString hdjson_select = hdjson.mid(is_select + 6,is_from-6).trimmed();
        new_json( hdjson_select);
    }else if (ui->del_radioButton->isChecked()) {




        QString hdjson_select = hdjson.mid(is_select + 6,is_from-6).trimmed();
        del_json( hdjson_select);
    }
    //    qDebug()<<  "mselect_radioButton" <<ui->mselect_radioButton->isChecked();
    //    qDebug()<<  "sselect_radioButton" <<ui->sselect_radioButton->isChecked();
    //    qDebug()<<  "update_radioButton" <<ui->update_radioButton->isChecked();
    //    qDebug()<<  "new_radioButton" <<ui->new_radioButton->isChecked();
    //    qDebug()<<  "del_radioButton" <<ui->del_radioButton->isChecked();



    return ;
}

void MainWindow::multienq_select(QString sql)
{
    QStringList hdjson_list = sql.split(",");

    qint32 count = hdjson_list.count();

    QJsonObject where_json_obj;
    where_json_obj.insert("COUNT" , "");
    where_json_obj.insert("FLAG" , "");
    for (qint32 i = 0; i < count; i++)
    {
        QJsonObject temp_json_obj;
        temp_json_obj.insert("NAME" , "f_reg_code");
        temp_json_obj.insert("REQUIRED" , "TRUE");
        temp_json_obj.insert("FEILD" , "CS010111.IN_PRO");
        where_json_obj.insert(QString("CLS%1").arg(i) , temp_json_obj);
    }
    QJsonObject result_json_obj;
    result_json_obj.insert("RESULTFEILD" , "");
    result_json_obj.insert("COUNTNUM" , "50");


    QJsonObject sql_json_obj;
    sql_json_obj.insert("ROWSEPAREATOR" , "");
    sql_json_obj.insert("TYPE" , "MULTIENQ");
    sql_json_obj.insert("SQLDATA" , "select reg_code||','|| reg_code||'--'|| fname from CI_REGIONCODE where reg_level=2");
    sql_json_obj.insert("WHERE" , where_json_obj);
    sql_json_obj.insert("ORDER" , "order");
    sql_json_obj.insert("RESULT" , result_json_obj);
    sql_json_obj.insert("SPACE_RETOK" , "2");
    sql_json_obj.insert("RETOK" , "2");

    //顶层SQL
    QJsonObject json_obj;

    json_obj.insert("SQL" , sql_json_obj);

    QJsonDocument complex_document;
    complex_document.setObject(json_obj);
    QByteArray complex_byte_array = complex_document.toJson(QJsonDocument::Indented);
    QString complex_json_str(complex_byte_array);
    qDebug() <<"\n"<< QString::fromLocal8Bit("复杂的QTJson数据：") << complex_json_str;
    ui->hdjson_out_Edit->clear();
    ui->hdjson_out_Edit->append(complex_json_str);
    return;
}

void MainWindow::single_select(QString sql)
{
    QStringList hdjson_list = sql.split(",");

    qint32 count = hdjson_list.count();

    QJsonObject where_json_obj;
    where_json_obj.insert("COUNT" , "");
    where_json_obj.insert("FLAG" , "");
    for (qint32 i = 0; i < count; i++)
    {
        QJsonObject temp_json_obj;
        temp_json_obj.insert("NAME" , "f_reg_code");
        temp_json_obj.insert("REQUIRED" , "TRUE");
        temp_json_obj.insert("FEILD" , "CS010111.IN_PRO");
        where_json_obj.insert(QString("CLS%1").arg(i) , temp_json_obj);
    }
    QJsonObject result_json_obj;
    result_json_obj.insert("RESULTFEILD" , "");
    result_json_obj.insert("COUNTNUM" , "50");


    QJsonObject sql_json_obj;
    sql_json_obj.insert("ROWSEPAREATOR" , "");
    sql_json_obj.insert("TYPE" , "MULTIENQ");
    sql_json_obj.insert("SQLDATA" , "select reg_code||','|| reg_code||'--'|| fname from CI_REGIONCODE where reg_level=2");
    sql_json_obj.insert("WHERE" , where_json_obj);
    sql_json_obj.insert("ORDER" , "order");
    sql_json_obj.insert("RESULT" , result_json_obj);
    sql_json_obj.insert("SPACE_RETOK" , "2");
    sql_json_obj.insert("RETOK" , "2");

    //顶层SQL
    QJsonObject json_obj;

    json_obj.insert("SQL" , sql_json_obj);

    QJsonDocument complex_document;
    complex_document.setObject(json_obj);
    QByteArray complex_byte_array = complex_document.toJson(QJsonDocument::Indented);
    QString complex_json_str(complex_byte_array);
    qDebug() <<"\n"<< QString::fromLocal8Bit("复杂的QTJson数据：") << complex_json_str;
    ui->hdjson_out_Edit->clear();
    ui->hdjson_out_Edit->append(complex_json_str);
}

void MainWindow::new_json(QString sql)
{
    QStringList hdjson_list = sql.split(",");

    qint32 count = hdjson_list.count();

    QJsonObject where_json_obj;
    where_json_obj.insert("COUNT" , "");
    where_json_obj.insert("FLAG" , "");
    for (qint32 i = 0; i < count; i++)
    {
        QJsonObject temp_json_obj;
        temp_json_obj.insert("NAME" , "f_reg_code");
        temp_json_obj.insert("REQUIRED" , "TRUE");
        temp_json_obj.insert("FEILD" , "CS010111.IN_PRO");
        where_json_obj.insert(QString("CLS%1").arg(i) , temp_json_obj);
    }
    QJsonObject result_json_obj;
    result_json_obj.insert("RESULTFEILD" , "");
    result_json_obj.insert("COUNTNUM" , "50");


    QJsonObject sql_json_obj;
    sql_json_obj.insert("ROWSEPAREATOR" , "");
    sql_json_obj.insert("TYPE" , "MULTIENQ");
    sql_json_obj.insert("SQLDATA" , "select reg_code||','|| reg_code||'--'|| fname from CI_REGIONCODE where reg_level=2");
    sql_json_obj.insert("WHERE" , where_json_obj);
    sql_json_obj.insert("ORDER" , "order");
    sql_json_obj.insert("RESULT" , result_json_obj);
    sql_json_obj.insert("SPACE_RETOK" , "2");
    sql_json_obj.insert("RETOK" , "2");

    //顶层SQL
    QJsonObject json_obj;

    json_obj.insert("SQL" , sql_json_obj);

    QJsonDocument complex_document;
    complex_document.setObject(json_obj);
    QByteArray complex_byte_array = complex_document.toJson(QJsonDocument::Indented);
    QString complex_json_str(complex_byte_array);
    qDebug() <<"\n"<< QString::fromLocal8Bit("复杂的QTJson数据：") << complex_json_str;
    ui->hdjson_out_Edit->clear();
    ui->hdjson_out_Edit->append(complex_json_str);
}

void MainWindow::update_json(QString sql)
{
    QStringList hdjson_list = sql.split(",");

    qint32 count = hdjson_list.count();

    QJsonObject where_json_obj;
    where_json_obj.insert("COUNT" , "");
    where_json_obj.insert("FLAG" , "");
    for (qint32 i = 0; i < count; i++)
    {
        QJsonObject temp_json_obj;
        temp_json_obj.insert("NAME" , "f_reg_code");
        temp_json_obj.insert("REQUIRED" , "TRUE");
        temp_json_obj.insert("FEILD" , "CS010111.IN_PRO");
        where_json_obj.insert(QString("CLS%1").arg(i) , temp_json_obj);
    }
    QJsonObject result_json_obj;
    result_json_obj.insert("RESULTFEILD" , "");
    result_json_obj.insert("COUNTNUM" , "50");


    QJsonObject sql_json_obj;
    sql_json_obj.insert("ROWSEPAREATOR" , "");
    sql_json_obj.insert("TYPE" , "MULTIENQ");
    sql_json_obj.insert("SQLDATA" , "select reg_code||','|| reg_code||'--'|| fname from CI_REGIONCODE where reg_level=2");
    sql_json_obj.insert("WHERE" , where_json_obj);
    sql_json_obj.insert("ORDER" , "order");
    sql_json_obj.insert("RESULT" , result_json_obj);
    sql_json_obj.insert("SPACE_RETOK" , "2");
    sql_json_obj.insert("RETOK" , "2");

    //顶层SQL
    QJsonObject json_obj;

    json_obj.insert("SQL" , sql_json_obj);

    QJsonDocument complex_document;
    complex_document.setObject(json_obj);
    QByteArray complex_byte_array = complex_document.toJson(QJsonDocument::Indented);
    QString complex_json_str(complex_byte_array);
    qDebug() <<"\n"<< QString::fromLocal8Bit("复杂的QTJson数据：") << complex_json_str;
    ui->hdjson_out_Edit->clear();
    ui->hdjson_out_Edit->append(complex_json_str);
}

void MainWindow::del_json(QString sql)
{
    QStringList hdjson_list = sql.split(",");

    qint32 count = hdjson_list.count();

    QJsonObject where_json_obj;
    where_json_obj.insert("COUNT" , "");
    where_json_obj.insert("FLAG" , "");
    for (qint32 i = 0; i < count; i++)
    {
        QJsonObject temp_json_obj;
        temp_json_obj.insert("NAME" , "f_reg_code");
        temp_json_obj.insert("REQUIRED" , "TRUE");
        temp_json_obj.insert("FEILD" , "CS010111.IN_PRO");
        where_json_obj.insert(QString("CLS%1").arg(i) , temp_json_obj);
    }
    QJsonObject result_json_obj;
    result_json_obj.insert("RESULTFEILD" , "");
    result_json_obj.insert("COUNTNUM" , "50");


    QJsonObject sql_json_obj;
    sql_json_obj.insert("ROWSEPAREATOR" , "");
    sql_json_obj.insert("TYPE" , "MULTIENQ");
    sql_json_obj.insert("SQLDATA" , "select reg_code||','|| reg_code||'--'|| fname from CI_REGIONCODE where reg_level=2");
    sql_json_obj.insert("WHERE" , where_json_obj);
    sql_json_obj.insert("ORDER" , "order");
    sql_json_obj.insert("RESULT" , result_json_obj);
    sql_json_obj.insert("SPACE_RETOK" , "2");
    sql_json_obj.insert("RETOK" , "2");

    //顶层SQL
    QJsonObject json_obj;

    json_obj.insert("SQL" , sql_json_obj);

    QJsonDocument complex_document;
    complex_document.setObject(json_obj);
    QByteArray complex_byte_array = complex_document.toJson(QJsonDocument::Indented);
    QString complex_json_str(complex_byte_array);
    qDebug() <<"\n"<< QString::fromLocal8Bit("复杂的QTJson数据：") << complex_json_str;
    ui->hdjson_out_Edit->clear();
    ui->hdjson_out_Edit->append(complex_json_str);
}

void MainWindow::set_defalutParameter()
{
    QSettings *settings;
    QString phrase;
    QString ConFile = QCoreApplication::applicationDirPath()+ QString("/etc/db.conf");
    if (!QFile::exists(ConFile) )
    {
        return;
    }
    settings = new QSettings(ConFile, QSettings::IniFormat);
    if (settings == NULL) {
        return;
    }


    qDebug()<<"------------settings != NULL---------------";

    QStringList db_list_item = settings->childGroups();

    Conndb con_db;
    QStringList db_select_list;
    foreach (QString db_conf, db_list_item) {
        settings->beginGroup(db_conf);
        db_select_list << settings->value("name").toString().trimmed();



        con_db.name = settings->value("name").toString().trimmed();
        con_db.db_driver = settings->value("driver").toString().trimmed();
        con_db.db_hostname = settings->value("hostName").toString().trimmed();
        con_db.db_port = settings->value("port").toInt();
        con_db.db_name = settings->value("databaseName").toString().trimmed();
        con_db.db_user = settings->value("userName").toString().trimmed();
        con_db.db_pass = settings->value("password").toString().trimmed();
        con_db.crypt = settings->value("crypt").toInt();
        db_list.append(con_db);
        settings->endGroup();
    }

    ui->db_select_Box->addItems(db_select_list);
    ui->textEdit->setText(phrase);
    delete  settings;
    set_func_id_Parameter();
}

void MainWindow::set_func_id_Parameter()
{
    /*数据库获得默认选择*/
    QSqlDatabase dd = init_db();
    if(!dd.isValid())
    {
        return;
    }
    curr_db = db_list.at(0);
    QSqlQuery query(dd); //以下执行相关QSL语句
    QStringList func_id_list;
    bool is_ok;
    //    is_ok = query.exec(QString("select func_id from(select count(func_id) as counts,func_id from traninfo group by func_id order by counts desc) b where counts =( select max(counts) from (select count(func_id) as counts,func_id from traninfo group by func_id)) "));
    //    if( is_ok )
    //    {
    //      query.next();
    //      ui->func_id_comboBox->setText( query.value(QString("func_id")).toString().trimmed());
    //    }
    is_ok = query.exec(QString(" select func_id from(select count(func_id) as counts,func_id from traninfo group by func_id )order by counts desc "));
    if( is_ok )
    {
        qDebug()<<"isokkkkkkkkkk";
        while(query.next())
        {
            func_id_list << query.value(QString("func_id")).toString().trimmed();
        }
        ui->func_id_comboBox->addItems(func_id_list);
    }
    dd.close();
    return;
}

void MainWindow::on_ins_db_Button_clicked()
{
    ui->ins_db_Button->setEnabled(false);
    if(ui->textEdit->toPlainText().isEmpty())
    {
        return;
    }
    QSqlDatabase dd = init_db();
    if(!dd.isValid())
    {
        return;
    }

    QSqlQuery query(dd); //以下执行相关QSL语句
    if(db.transaction())
    {
        qDebug()<<"------------transaction---------------";
    }
    bool formmag_is_ok =true;
    bool traninfo_is_ok;
    bool bktran_is_ok;
    bool business_is_ok;
    query.exec("START TRANSACTION");//开始事务。使用BEGIN也可以

    formmag_is_ok = query.exec(formmag_sql);
    if(! formmag_is_ok )
    {
        if (query.lastError().isValid())
            QMessageBox::warning(NULL,tr(u8"提示:FORMMAG"), query.lastError().text(), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        qDebug() << query.lastError()<<formmag_sql;
        ui->ins_db_Button->setEnabled(true);
    }
    if(! ui->uiid_Edit->text().trimmed().isEmpty())
    {
        business_is_ok = query.exec(business_sql);
        if(! business_is_ok)
        {
            if (query.lastError().isValid())
                QMessageBox::warning(NULL,tr(u8"提示:BUSINESS"), query.lastError().text(), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

            qDebug() << query.lastError()<<business_sql;
            ui->ins_db_Button->setEnabled(true);
        }

        traninfo_is_ok = query.exec(traninfo_sql);
        if(! traninfo_is_ok )
        {
            if (query.lastError().isValid())
                QMessageBox::warning(NULL,tr(u8"提示:TRANINFO"), query.lastError().text(), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

            qDebug() << query.lastError()<<traninfo_sql;
            ui->ins_db_Button->setEnabled(true);
        }



    }
    bktran_is_ok = query.exec(bktran_sql);
    if(! bktran_is_ok )
    {
        if (query.lastError().isValid())
            QMessageBox::warning(NULL,tr(u8"提示:BKTRAN"), query.lastError().text(), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        qDebug() << query.lastError()<<bktran_sql;
        ui->ins_db_Button->setEnabled(true);
    }


    if(formmag_is_ok && traninfo_is_ok && bktran_is_ok && business_is_ok)
    {
        query.exec("COMMIT");//提交
        //db.commit();

        QMessageBox::warning(NULL,tr(u8"提示"), tr(u8"数据插入成功！"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }else
    {
        //        query.exec("ROLLBACK");//回滚
        if( query.exec("ROLLBACK"))
        {
            qDebug()<<"------------rollback_ok---------------";
        }else
        {
            qDebug()<<"------------rollback_bad---------------";
        }

    }



    ui->ins_db_Button->setEnabled(true);
    dd.close();
}

void MainWindow::on_db_select_Box_currentIndexChanged(const QString &arg1)
{
    qDebug()<<arg1;
}

void MainWindow::on_db_select_Box_currentIndexChanged(int index)
{
    curr_db = db_list.at(index);
    ui->ip_label->setText(QString(u8"IP: ") + curr_db.db_hostname);
    ui->db_uname_label->setText(QString(u8"用户: ") + curr_db.db_user);

    qDebug()<<curr_db.db_driver;
    qDebug()<<curr_db.db_port;
    qDebug()<<curr_db.db_hostname;
    qDebug()<<curr_db.db_name;
    qDebug()<<curr_db.db_user;
    qDebug()<<curr_db.db_pass;
}


void MainWindow::on_rf_jydmtj_Button_clicked()
{
    set_func_id_Parameter();
    return;
}
