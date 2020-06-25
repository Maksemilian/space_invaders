#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsView;
class GraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    static const quint16 SCREEN_MARGIN=200;
    static const quint16 SCENE_MARGIN=100;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QSize getScreenSize();
private:
    Ui::MainWindow *ui=nullptr;
    GraphicsScene*_scene=nullptr;
    QGraphicsView *view=nullptr;
};

#endif // MAIN_WINDOW_H
