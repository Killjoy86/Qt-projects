#ifndef WINWIDGET_H
#define WINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class WinWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WinWidget(QWidget *parent = 0);
    ~WinWidget();

    void setGameTime(QString newTime);
    QPushButton *getBtnYes() const;

private:
    QString gameTime;
    QVBoxLayout *vbox;
    QHBoxLayout *hbox;
    QLabel *lbl;
    QPushButton *btnYes;
    QPushButton *btnNo;

signals:
    void signalMainMenu();
    void signaGame();

public slots:
    void emitClose();
    void nextGame();
};

#endif // WINWIDGET_H
