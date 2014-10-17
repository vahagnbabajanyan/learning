#ifndef _CONNECTOR_HPP_
#define _CONNECTOR_HPP_

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QList>
#include <QSslError>

#include <string>

namespace net
{

class connector : public QObject
{
        Q_OBJECT
public:
        connector(const QString& url);
        void translate(const std::string&);
public slots:
        void readData(QNetworkReply* reply);
        void slotError(QNetworkReply::NetworkError);
        void slotSslErrors(QList<QSslError>);
private:
        void initQuery();
private:
        QUrlQuery m_query;
        QUrl m_url;
        QNetworkAccessManager *m_network_manager;
};

} // end of namespace net

#endif
