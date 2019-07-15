#ifndef UNLOCK_H
#define UNLOCK_H

#include <QDate>
#include <QQuickItem>

class Unlock : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString result READ result WRITE setResult NOTIFY resultChanged)

public:
    explicit Unlock(QQuickItem *parent = 0);
    ~Unlock();

    Q_INVOKABLE void gen_code(QString serial, QString codeBlock);
    Q_INVOKABLE int checkAccessRequest(QString login, QString password);
    Q_INVOKABLE bool checkTime(QDate date);
    unsigned int generate_hash(const char *serial, const char *key, unsigned int *hash);

    QString result() const;

public slots:
    void setResult(QString result);

signals:
    void resultChanged(QString result);

private:
    QString m_result;
};

#endif // UNLOCK_H
