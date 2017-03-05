#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>

class MainWidget : public QStackedWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

signals:

public slots:
};

#endif // MAINWIDGET_H
