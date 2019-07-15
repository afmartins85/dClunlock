#include "authentication.h"
#include <QCryptographicHash>
#include <QDebug>

/**
 * @brief Authentication::Authentication
 * @param parent
 */
Authentication::Authentication(QQuickItem *parent) : QQuickItem(parent)
{
    qDebug("Authentication CONSTRUCTOR");
}

/**
 * @brief Authentication::~Authentication
 */
Authentication::~Authentication()
{

}

/**
 * @brief Authentication::checkAccessRequest
 * @param login
 * @param password
 * @return
 */
int Authentication::checkAccessRequest(QString login, QString password)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    QByteArray result;
    unsigned char p[17] = { 0x48, 0x46, 0x26, 0xF4, 0xC4, 0xD1, 0xBE, 0x5C,
                            0x12, 0x48, 0x8F, 0x86, 0x93, 0xB3, 0x3D, 0x8A};

    result = md5.hash(password.toLatin1(), QCryptographicHash::Md5);
    qDebug() << "MD5SUM: " << result.toHex();

    if ((!login.compare(login, "Acesso")) && (!memcmp(result.constData(), p, 16))) {
        setLogin(login);
        return 0;
    }
    return -1;
}

/**
 * @brief Authentication::genMD5
 * @param passwd
 * @return
 */
QByteArray Authentication::genMD5(QString passwd)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    QByteArray result;

    result = md5.hash(passwd.toLatin1(), QCryptographicHash::Md5);
    qDebug() << "MD5SUM: " << result.toHex();

    return result;
}

/**
 * @brief Authentication::getUserName
 * @return
 */
QString Authentication::getUserName()
{
    return login();
}
