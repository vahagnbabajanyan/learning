#include <QNetworkAccessManager>
#include <QString>
#include <QNetworkReply>
#include <QList>

#include <iostream>

#include "connector.hpp"

namespace net
{

connector::connector(const QString& url)
        : m_url(url)
{
        initQuery();
        m_network_manager = new QNetworkAccessManager(this);
        connect(m_network_manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(readData(QNetworkReply *)));
}

void connector::translate(const std::string& words)
{
        m_query.addQueryItem("q", words.c_str());
        m_url.setQuery(m_query);
        QNetworkRequest request(m_url);
        QNetworkReply* reply = m_network_manager->get(request);
//        connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));
}

void connector::initQuery()
{
        m_query.addQueryItem("alttl", "en");
        m_query.addQueryItem("client", "t");
        m_query.addQueryItem("hl", "UTF-8");
        m_query.addQueryItem("oe", "UTF-8");
        m_query.addQueryItem("prev", "btn");
        m_query.addQueryItem("rom", "1");
        m_query.addQueryItem("sc", "2");
        m_query.addQueryItem("sl", "auto");
        m_query.addQueryItem("ssel", "0");
        m_query.addQueryItem("tl", "ru");
        m_query.addQueryItem("tsel", "0");
        m_query.addQueryItem("uptl", "ru");
}

void connector::readData(QNetworkReply* reply)
{
        std::cout << "finished. got reply" << std::endl;
        std::cout << qPrintable(reply->readAll()) << std::endl;
}

void connector::slotError(QNetworkReply::NetworkError)
{
        std::cout << "network error" << std::endl;
}
void connector::slotSslErrors(QList<QSslError>)
{
        std::cout << "Ssl Error" << std::endl;
}

} // end of namespace net
