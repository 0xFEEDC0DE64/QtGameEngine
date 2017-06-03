#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Qt3DExtras/qt3dwindow.h>

class QModelIndex;
class QPropertyAnimation;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void customContextMenuRequested(const QPoint &pos);
    void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void returnPressed();
    void start();
    void pause();
    void stop();

private:
    Ui::MainWindow *ui;

    Qt3DExtras::Qt3DWindow m_view;
    QList<QPropertyAnimation *> m_animations;
};

#endif // MAINWINDOW_H
