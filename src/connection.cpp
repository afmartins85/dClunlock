#include "connection.h"
#include <QDebug>

/**
 * @brief Connection::Connection
 * @param parent
 */
Connection::Connection(QQuickItem *parent) : QQuickItem(parent)
{
    // Aguarda conexão de algum equipamento
    server = new QTcpServer(this);

    int porta  = 3003;

    if (!server->listen(QHostAddress::Any, porta)) {
        qDebug() << "Não é possível iniciar o servidor" ;
    } else {
        qDebug() << "Servidor iniciado com sucesso!" ;
    }

     qDebug("Aguardando Handshake...");

     // Criação do timer, para comandos ciclicos
     timer = new QTimer(this);
}

/**
 * @brief Connection::~Connection
 */
Connection::~Connection()
{

}

void Connection::newConn()
{
    QTcpSocket *client = new QTcpSocket;
    client = server->nextPendingConnection();

    if (client) {
        return;
    }

    m_clientList.append(client);

    QString ip = client->peerAddress().toString().section(':',3,3);

    if(ip.isEmpty()) {
        ip = client->peerAddress().toString();
    }

    qDebug() << "Status: On-line :: Porta: 3003 :: IP: " << ip;

//    connect(client, SIGNAL(disconnected()),this, SLOT(reset_conn()));
//    connect(client, SIGNAL(readyRead()), this, SLOT(recv_data()));
}
