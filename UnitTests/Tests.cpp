#include <QtTest>
#include <qtmetamacros.h>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QPushButton>
#include "../countdowntimer.h"

class CountdownTimerTest : public QObject
{
    Q_OBJECT

private slots:
    void testInitialUIState();
    void testStartButton();
    void testTimerAccuracy();
};

void CountdownTimerTest::testInitialUIState()
{
    CountdownTimer app;

    QLabel* label = app.findChild<QLabel*>("label");
    QVERIFY(label);
    QCOMPARE(label->text(), QString("Time left:"));

    QProgressBar* progressBar = app.findChild<QProgressBar*>("progressBar");
    QVERIFY(progressBar);
    QCOMPARE(progressBar->value(), 0);
}

void CountdownTimerTest::testStartButton()
{
    CountdownTimer app;
    app.show();
    QSpinBox* timeInput = app.findChild<QSpinBox*>("timeInput");
    QPushButton* startButton = app.findChild<QPushButton*>("startButton");
    QLabel *label = app.findChild<QLabel *>("label");

    QVERIFY(timeInput);
    QVERIFY(startButton);

    timeInput->setValue(5);

    QTest::mouseClick(startButton, Qt::LeftButton);

    QCOMPARE(label->text(), "Time left: 5s");  // Check label update

}


void CountdownTimerTest::testTimerAccuracy()
{
    CountdownTimer app;
    app.show();
    QSpinBox* timeInput = app.findChild<QSpinBox*>("timeInput");
    QPushButton* startButton = app.findChild<QPushButton*>("startButton");

    QVERIFY(timeInput);
    QVERIFY(startButton);

    timeInput->setValue(5);
    int initialTime = app.findChild<QSpinBox *>("timeInput")->value();

    QElapsedTimer elapsedTimer;
    QTest::mouseClick(startButton, Qt::LeftButton);
    elapsedTimer.start();

    QTest::qWait(3000);  // Wait for 3 seconds

    QLabel *label = app.findChild<QLabel *>("label");
    QVERIFY(label);
    qDebug() << "Label text: [" << label->text() << "]";
    qDebug() << "Label text: [" << label->text() << "]";
    QStringList labelParts = label->text().split(" ");
    QVERIFY(labelParts.size() >= 3);  // Check list size before accessing

    int remainingTime = labelParts[2].remove("s").toInt();

    int expectedTime = initialTime - 3;

    //Allow ±1 second tolerance
    QVERIFY(remainingTime >= expectedTime - 1 && remainingTime <= expectedTime + 1);

}

// Run all test cases
QTEST_MAIN(CountdownTimerTest)
#include "Tests.moc"
