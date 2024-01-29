#ifndef COLLISION_H
#define COLLISION_H

#include <QObject>

class Collision : public QObject {
    Q_OBJECT

public:
    Collision(QObject* source, QObject* target) : m_source(source), m_target(target) {}

    QObject* source() const { return m_source; }
    QObject* target() const { return m_target; }

signals:
    void handleCollision();

private:
    QObject* m_source;
    QObject* m_target;
};

#endif // COLLISION_H
