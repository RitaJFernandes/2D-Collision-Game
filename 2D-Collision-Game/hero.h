#ifndef HERO_H
#define HERO_H
#include <QObject>
#include "enemy.h"
#include "reward.h"

class Hero : public QObject {

    Q_OBJECT
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(QPointF position READ getPosition WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int radius READ getRadius CONSTANT)
    Q_PROPERTY(int score READ getScore CONSTANT)
    Q_PROPERTY(bool enemyCollisionFlag READ getEnemyCollisionFlag WRITE setEnemyCollisionFlag NOTIFY enemyCollisionFlagChanged)
    Q_PROPERTY(bool rewardCollisionFlag READ getRewardCollisionFlag WRITE setRewardCollisionFlag NOTIFY rewardCollisionFlagChanged)
    Q_PROPERTY(bool eatCoinFlag READ getEatCoinFlag WRITE setEatCoinFlag NOTIFY eatCoinFlagChanged)

public:
    Hero(QObject* parent = nullptr);

    // Getters
    QPointF getPosition() const;
    int getRadius() const;
    int getScore() const;
    bool getEnemyCollisionFlag() const;
    bool getRewardCollisionFlag() const;
    bool getEatCoinFlag() const;

    // Setters
    void setPosition(const QPointF &position);
    void setEnemyCollisionFlag(bool flag);
    void setRewardCollisionFlag(bool flag);
    void setEatCoinFlag(bool flag);

signals:
    void scoreChanged();
    void positionChanged();
    void enemyCollisionFlagChanged();
    void rewardCollisionFlagChanged();
    void eatCoinFlagChanged();

    void finalScore(const int finalScore);

public slots:
    void move(int direction);
    void checkEnemyCollision(Enemy* enemy);
    void checkRewardCollision(Reward* reward);
    void eatCoin(Reward* reward);

private:
    int m_score;
    QPointF m_position;
    int m_radius;
    bool m_enemyCollisionFlag;
    bool m_rewardCollisionFlag;
    bool m_eatCoinFlag;
};

#endif // HERO_H
