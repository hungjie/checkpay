#include <QCoreApplication>

#include <iostream>

#include <QFile>
#include <QByteArray>
#include <QThread>

void process_line(QByteArray const& line)
{
    std::cout << line.data() << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != 2)
    {
        std::cout << "Usage: tailforcheck logfile" << std::endl;
        exit(1);
    }

    QString path = argv[1];
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        exit(1);

    qint64 osize = f.size();

    while(1)
    {
        QFile ftemp(path);
        if(!ftemp.open(QIODevice::ReadOnly | QIODevice::Text))
            break;

        qint64 tsize = ftemp.size();

        if(tsize != osize)
        {
            while(!f.atEnd())
            {
                QByteArray line = f.readLine();
                process_line(line);
            }
        }

        std::cout << "sleep 1" << std::endl;

        QThread::sleep(1);
    }

    return a.exec();
}
