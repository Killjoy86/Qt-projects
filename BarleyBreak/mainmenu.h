#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

class MainMenu : public QWidget {
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

    QPushButton* btnStart;
private:
    QLabel* name;
    QPushButton* btnExit;
    QLabel* copyright;
signals:
    void finished();
    void closed();
public slots:
    void emitSignalFinished();
    void emitClosed();
};

#endif // MAINMENU_H
