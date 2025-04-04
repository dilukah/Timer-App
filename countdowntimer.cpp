#include "countdowntimer.h"
#include "./ui_countdowntimer.h"

CountdownTimer::CountdownTimer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CountdownTimer)
    , timeLeft(10) // Initialize countdown time
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/timer.png"));

    timer = new QTimer(this);

    //Load style file
    QFile styleFile("../../style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }
    else {
        qWarning() << "Warning: Style file 'style.qss' not found!";
    }

    // Connect button click to startCountdown function
    connect(ui->startButton, &QPushButton::clicked, this, &CountdownTimer::startCountdown);

    // Connect timer to updateTimer function
    connect(timer, &QTimer::timeout, this, &CountdownTimer::updateTimer);
}

CountdownTimer::~CountdownTimer()
{
    delete ui;
    timer->stop();
    delete timer;
}

void CountdownTimer::startCountdown()
{
    timeLeft = ui->timeInput->value();
    if (timeLeft <= 0) {
        ui->label->setText("Please enter a valid time.");
        return;
    }
    ui->label->setText(QString("Time left: %1s").arg(timeLeft));

    ui->progressBar->reset();
    ui->progressBar->setMaximum(timeLeft);  // Set max value
    ui->progressBar->setValue(timeLeft);    // Start at full


    timer->start(1000); // Start timer with 1-second intervals
}

void CountdownTimer::updateTimer()
{
    if (timeLeft > 0) {
        timeLeft--;
        ui->label->setText(QString("Time left: %1s").arg(timeLeft));
        ui->progressBar->setValue(timeLeft);
        emit timeUpdated(timeLeft);  // Emit signal here
    } else {
        timer->stop();
        ui->label->setText("Time's up!");
        ui->progressBar->setValue(0);
    }
}
