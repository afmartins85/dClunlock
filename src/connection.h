#ifndef CONNECTION_H
#define CONNECTION_H

#include <QQuickItem>
#include <QtNetwork>
#include <QString>

class Connection : public QQuickItem
{
    Q_OBJECT
public:
    explicit Connection(QQuickItem *parent = 0);
    ~Connection();

signals:

public slots:
    void newConn();
//    void resetConn();

private:
    QTcpServer *server;

    QTimer *timer;
    QList<QTcpSocket*> m_clientList;
};

#endif // CONNECTION_H
