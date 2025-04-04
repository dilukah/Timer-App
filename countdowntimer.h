#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class CountdownTimer; }
QT_END_NAMESPACE

class CountdownTimer : public QMainWindow
{
    Q_OBJECT

public:
    CountdownTimer(QWidget *parent = nullptr);
    ~CountdownTimer();

signals:
    void timeUpdated(int secondsLeft);

private slots:
    void startCountdown();
    void updateTimer();

private:
    Ui::CountdownTimer *ui;
    QTimer *timer;
    int timeLeft;


};

#endif // COUNTDOWNTIMER_H
