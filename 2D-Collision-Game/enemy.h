#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>
#include <QPointF> //Class used to represent a 2D point in a Cartesian coordinate system


class Enemy : public QObject
{
    Q_OBJECT

public:

    Enemy(QObject *parent = nullptr);

    QPointF m_position;
    QTimer m_movementTimer;

    Q_PROPERTY(int radius READ getRadius CONSTANT)
    int getRadius() const;

    Q_PROPERTY(QPointF position READ getPosition WRITE setPosition NOTIFY positionChanged)
    QPointF getPosition() const;
    void setPosition(const QPointF &position);

signals:
    void positionChanged();

public slots:
    void initializeRandomPosition();
    void updateEnemyPosition();

private:
    int m_radius;
    QPointF m_initialDirection;
};

#endif // ENEMY_H
