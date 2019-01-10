#ifndef DBGABOUTSOURCETYPE_H
#define DBGABOUTSOURCETYPE_H


//#include <QVariantHash>

#define DBGEXT_METERMANAGER         101
#define DBGEXT_METERSCHEDULER       102
#define DBGEXT_THELORDOFMETERS      103
#define DBGEXT_THELOCALSOCKET       104

////an application depended file
//class DbgAboutSourceType
//{
//public:
//    static QVariantHash getAboutSourcType(){
//        QVariantHash h;
//        h.insert("appName", "zbyrator-bbb");

//        /*
//         * appName firefly-bbb
//         * sourceType
//         * 0 - compressed packed
//         * 1 - QVH about sourceType to className
//         * .
//         * . reserved space
//         * 101 - client4command
//         * 102 - dbgextserver
//         * 103 - firefly
//         * 104 - fireflysocket
//         * 105 - lightingsocket
//         * 106 - lightingscheduler
//         * 107 - server4command
//         * 108 - thelordofboos
//    */
//        QStringList l = QString("lampmanager lampscheduler thelordoflamps localsocket").split(" ");
//        for(int i = 0, iMax = l.size(), j = 101; i < iMax; i++ , j++)
//            h.insert(QString::number(j), l.at(i));
//        return h;
//    }

//    static QString varHash2str(const QVariantHash &h, const bool ignoreEmpty = true){
//        QList<QString> lk = h.keys();
//        std::sort(lk.begin(), lk.end());
//        QStringList l;
//        for(int i = 0, iMax = lk.size(); i < iMax; i++){
//            if(ignoreEmpty && h.value(lk.at(i)).toString().isEmpty())
//                continue;
//            l.append(QString("%1=%2").arg(lk.at(i)).arg(h.value(lk.at(i)).toString()));
//        }
//        return l.join("\n");
//    }
//};

#endif // DBGABOUTSOURCETYPE_H
