#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QLCDNumber>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QMenu>
#include <QLabel>
#include <QSound>
#include <QMessageBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>

#include "slots.h"
#include "info.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int compare(int arr[]);
    void initLCD();
    void initButtons();
    void initSlots();
    void createMenu();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

    QLineEdit* line;
    QDialog *dialog;
    QPixmap* imgField;
    QPushButton* btnSpin;
    QPushButton* btnMaxBet;
    QPushButton* btnBet;
    QLabel* lblWin;
    QLCDNumber* lcdBet;
    QLCDNumber* lcdCash;
    QLCDNumber* lcdWin;
    Slots *slot;
    Slots *slot1;
    Slots *slot2;
    Slots *slot3;
    Slots *slot4;
    QTimer *timerStop;
    bool isSpin;
    bool isMute;
    int arSlots[5] = {0, 0, 0, 0, 0};
    QAction* soundMute;
    QImage* image;

    Info* infoWidget;

private slots:   
    void betSlot();
    void maxBetSlot();
    void startSlot();
    void stopSlots();

    void slotNewGame();
    void slotPayTable();

    void slotSetCash();
    void slotClearLine();
    void slotCloseDialog();
    void slotMute();

    void slotAbout();
};

#endif // MAINWINDOW_H
