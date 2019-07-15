#include <QDateTime>
#include <QDebug>
#include "unlock.h"
#include "authentication.h"

/* Para acessar inteiros byte a byte */
union hash_union {
    unsigned char uc_data[8];
    unsigned long long ull_data;
};

/* Numero primo usado no hash */
#define PRIME 773

/* Vetor de valores para salgar o hash */
unsigned int salts[] = {
    0x81c6da92,
    0x7eb2a09a,
    0x14e8de4d,
    0x1525b2cd,
    0x2f46b01e,
    0x001b1b8c,
    0xf1e24491,
    0x5a5c0b76,
    0xd5d92858,
    0xa299a53b,
    0xac8f6cb8,
    0x9094330e,
    0x2d5d36a9,
    0xe8ad1935,
    0x27836120,
    0x73f8a5c7
};

/**
 * @brief Unlock::Unlock
 * @param parent
 */
Unlock::Unlock(QQuickItem *parent) : QQuickItem(parent)
{

}

/**
 * @brief Unlock::~Unlock
 */
Unlock::~Unlock()
{

}

/**
 * @brief Unlock::generate_hash
 * @param serial
 * @param key
 * @param hash
 * @return
 */
unsigned int Unlock::generate_hash(const char *serial, const char *key, unsigned int *hash)
{
    int i;
    union hash_union random, salt, snumber;
    unsigned int salt_index = 0;
    unsigned long long temp_hash;

    if (strlen(key) != 8) {
        return -1;
    }
    random.ull_data = strtoll(key, NULL, 16);
    /* Baseado no c?digo de viola??o adiciona um "sal" ao hash */
    for (i = 0; i < 8; i++) {
        salt_index ^= random.uc_data[i];
    }
    salt_index %= 16;
    salt.ull_data = salts[salt_index];

    if (strlen(serial) != 7) {
        return -2;
    }
    snumber.ull_data = strtoll(serial, NULL, 10);
    /* Calcula o hash */
    temp_hash = salt.ull_data + snumber.ull_data + random.ull_data;
    temp_hash = temp_hash * PRIME;

    *hash = (((unsigned int)temp_hash) % 0xffffffff);
/*
    printf("snumber: %.10u\n", snumber.ull_data);
    printf("random: %.10u\n", random.ull_data);
    printf("salt_index: %d\n", salt_index);
    printf("salt: %.10u\n", salt.ull_data);
    printf("hash: %.10u\n", *hash);
*/
    return 0;
}

/**
 * @brief Unlock::result
 * @return
 */
QString Unlock::result() const
{
    return m_result;
}

/**
 * @brief Unlock::setResult
 * @param result
 */
void Unlock::setResult(QString result)
{
    m_result = result;
    emit resultChanged(result);
}

/**
 * @brief Unlock::gen_code
 * @param serial
 * @param codeBlock
 */
void Unlock::gen_code(QString serial, QString codeBlock)
{
    QString /*temp,*/ strCode;
    int err=0, intSerial;
    unsigned int code;
    char snumber[10];
    char key[10];

    qDebug() << "Gerador de chaves...";
    if((serial.isEmpty()) || (codeBlock.isEmpty())) {
        setResult(QString("ERRO empty"));
    }

    if (serial.size() < 7) {
        intSerial = serial.toInt();
        sprintf(snumber, "%07d", intSerial);
//        temp.sprintf("%07d", intSerial);
//        serial = temp;
    }

//    qDebug() << serial.toLatin1().data();
//     = serial.toLatin1().data();
    qDebug() << snumber;

    sprintf(key, "%s", codeBlock.toLatin1().data());
    qDebug() << codeBlock.toLatin1().data();

    err = generate_hash(snumber, key, &code);
    if (err < 0) {
        qDebug() << "ERRO";
        setResult(QString("ERRO"));
        return;
    }

    qDebug() << "Codigo: " << code;
    strCode.sprintf("%.10u", code);

    setResult(strCode);
}

/**
 * @brief Unlock::checkAccessRequest
 * @param login
 * @param password
 * @return
 */
int Unlock::checkAccessRequest(QString login, QString password)
{
    Authentication auth;

    return auth.checkAccessRequest(login, password);
}

/**
 * @brief Unlock::checkTime
 * @param time
 * @return
 */
bool Unlock::checkTime(QDate date)
{
    QDateTime d_time(date);
    unsigned int base_stamp = (86400 * 90);

    qDebug() << d_time.toTime_t();
    QDateTime temp;
    temp.setDate(QDate::currentDate());
    temp.setTime(QTime::currentTime());
    qDebug() << temp.toTime_t();

    qDebug() << "Diferenca " << (temp.toTime_t() - d_time.toTime_t());
    qDebug() << "base_stamp " << base_stamp;
    if ((temp.toTime_t() - d_time.toTime_t()) > base_stamp ) {
        qDebug() << "FIRMWARE EXPIROU!";
        return false;
    }

    qDebug() << "PODE EXECUTAR!";
    return true;
}
