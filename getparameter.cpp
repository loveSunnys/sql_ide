#include "getparameter.h"

getparameter::getparameter(QObject *parent) : QObject(parent)
{

}
//QSettings getparameter::get_Qstring(QString confile)
//{
//    QSettings settings;
//    if (QFile::exists(confile))
//    {
//        settings.setPath(QSettings::IniFormat,Settings::UserScope,confile);
//        if (settings == NULL  )
//        {

//        }
//        else
//        {

////            settings->beginGroup("PHRASECONF");
////            phrase = settings->value("PHRASE").toString().trimmed();
////            QStringList phraseList = phrase.split("^|");
////            ui->comboBox_phrase->addItems(phraseList);

////            settings->endGroup();
//        }
//    }

//}
