#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QQuickItem>
#include <QDebug>

class Authentication : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString login READ login WRITE setLogin)
    Q_PROPERTY(QString password READ password WRITE setPassword)

public:
    explicit Authentication(QQuickItem *parent = 0);
    ~Authentication();

    Q_INVOKABLE int checkAccessRequest(QString login, QString password);
    Q_INVOKABLE QString getUserName(void);
    QByteArray genMD5(QString passwd);

    QString login() const
    {
        return m_login;
    }
    QString password() const
    {
        return m_password;
    }

public slots:
    void setLogin(QString login)
    {
        qDebug() << "Login: " << login;
        m_login = login;
    }
    void setPassword(QString password)
    {
        qDebug() << "Password: " << password;
        m_password = password;
    }

private:
    QString m_login;
    QString m_password;
    bool m_isAcvive;

};

#endif // AUTHENTICATION_H
