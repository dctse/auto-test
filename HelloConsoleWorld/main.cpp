#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QObject>
#include <QTextStream>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QTextStream textStream(stdout);

    QTranslator qTran;
    bool result = qTran.load("CH_Tran");

    if (!result)
    {
        textStream << "Error: failed to load translator file." << endl;
    }
    else {
        a.installTranslator(&qTran);
    }
    QString msg = "This is a String";
    QString msg2 (QObject::tr( "2nd String"));
    int n = 5;
    qWarning() << msg+msg2 << n << endl;
    qWarning("Hello console");
    qWarning(msg.toStdString().c_str());
    qWarning(qPrintable(msg) + 1);


    textStream.setFieldWidth(2);
    textStream.setPadChar('*');
    textStream << msg+" " +msg2 << endl;

    textStream << "1234567890" << endl;

    //    std::cout <<  qPrintable(QObject::tr(msg)) << std::endl;
    std::cout << qPrintable(msg+msg2) << std::endl;

    return a.exec();
}



