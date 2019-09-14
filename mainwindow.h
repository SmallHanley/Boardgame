#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <newbutton.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void blackGeneral(int i, int j);
    void blackGuards(int i, int j);
    void blackMinisters(int i, int j);
    void blackChariots(int i, int j);
    void blackHorses(int i, int j);
    void blackCannons(int i, int j);
    void blackSoldiers(int i, int j);
    void redGeneral(int i, int j);
    void redGuards(int i, int j);
    void redMinisters(int i, int j);
    void redChariots(int i, int j);
    void redHorses(int i, int j);
    void redCannons(int i, int j);
    void redSoldiers(int i, int j);
    void checkKing(int I, int J);
    ~MainWindow();

private slots:
    void startSlots();
    void setboardSlots();
    void restartSlots();
    void move(int kind, int chessNum, int x, int y, int i, int j);

private:
    Ui::MainWindow *ui;
    QPushButton *start;
    QPushButton *setboard;
    QPushButton *restart;
    newbutton *chess[32];
    newbutton *setboardTemp[8][4];
    newbutton *cell[10][9];
    QList<QPixmap> chessPics;
    QList<QPixmap> cellPics;
    QLabel *redWin;
    QLabel *blackWin;
    int map[10][9] = {{ 4,  5,  3,  2,  1,  2,  3,  5,  4},
                      { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                      { 0,  6,  0,  0,  0,  0,  0,  6,  0},
                      { 7,  0,  7,  0,  7,  0,  7,  0,  7},
                      { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                      { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                      {14,  0, 14,  0, 14,  0, 14,  0, 14},
                      { 0, 13,  0,  0,  0,  0,  0, 13,  0},
                      { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                      {11, 12, 10,  9,  8,  9, 10, 12, 11},
                     };
    const int originalMap[10][9] = {{ 4,  5,  3,  2,  1,  2,  3,  5,  4},
                                    { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                                    { 0,  6,  0,  0,  0,  0,  0,  6,  0},
                                    { 7,  0,  7,  0,  7,  0,  7,  0,  7},
                                    { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                                    { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                                    {14,  0, 14,  0, 14,  0, 14,  0, 14},
                                    { 0, 13,  0,  0,  0,  0,  0, 13,  0},
                                    { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                                    {11, 12, 10,  9,  8,  9, 10, 12, 11},
                                   };
    bool isClick;
    int clickKind;
    int clickChessNum;
    int clickX;
    int clickY;
    int cellI;
    int cellJ;
    bool color;     //true := red, false := black
    int mode;
};

#endif // MAINWINDOW_H
