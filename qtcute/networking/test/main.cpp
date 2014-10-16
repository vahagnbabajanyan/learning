#include <QApplication>
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <iostream>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        QString str = "http://translate.google.com/translate_a/t";
        QUrl url(str);
        QUrlQuery qveri(url);
        qveri.addQueryItem("alttl", "en");
        qveri.addQueryItem("client", "t");
        qveri.addQueryItem("hl", "UTF-8");
        qveri.addQueryItem("oe", "UTF-8");
        qveri.addQueryItem("prev", "btn");
        qveri.addQueryItem("q", "obvious");
        qveri.addQueryItem("rom", "1");
        qveri.addQueryItem("sc", "2");
        qveri.addQueryItem("sl", "auto");
        qveri.addQueryItem("ssel", "0");
        qveri.addQueryItem("tl", "ru");
        qveri.addQueryItem("tsel", "0");
        qveri.addQueryItem("uptl", "ru");
        url.setQuery(qveri);

        QNetworkRequest request(url);
        QNetworkAccessManager *nm = new QNetworkAccessManager;
        QNetworkReply *reply = nm->get(request);
        std::cout << "waiting to qeury result" << std::endl;
        std::cout << qPrintable(reply->readAll()) << std::endl;
        app.exec();
}
