#ifndef NEWBUTTON_H
#define NEWBUTTON_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QString>

class newbutton : public QPushButton
{
    Q_OBJECT

public:
    newbutton(QWidget *parent = nullptr);
    void setKind(int num);
    void setChessNum(int num);
    void setI(int i);
    void setJ(int j);
    int getKind();

signals:
    void click(int k, int c, int x, int y, int I, int J);

private slots:
    void checkClick();

private:
    int kind;
    int chessNum;
    int cellI;
    int cellJ;
};

#endif // NEWBUTTON_H
