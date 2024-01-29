#ifndef REWARD_H
#define REWARD_H

#include <QObject>
#include <QPointF>
#include <QTimer>

class Reward : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int radius READ getRadius CONSTANT)
    Q_PROPERTY(QPointF position READ getPosition WRITE setPosition NOTIFY positionChanged)

public:
    Reward(QObject *parent = nullptr);

    QPointF m_position;
    QTimer m_movementTimer;
    QTimer m_resetTimer;
    QTimer m_collisionTimer;

    int getRadius() const;
    int getEatRadius() const;
    void setPosition(const QPointF &position);
    QPointF getPosition() const;

    void limitDistance(const QPointF &otherRewardPosition);
    void adjustPositionForMinimumDistance(const QPointF &otherPosition);

public slots:
    void initializeRandomPosition();
    void moveReward();
    void resetRewardPosition();
    void resetRewardPositionOnCollision();


signals:
    void positionChanged();
    void reachedEdge();
    void limitDistanceDetected();

private:
    int m_radius;
    QPointF m_initialDirection;
};

#endif // REWARD_H
