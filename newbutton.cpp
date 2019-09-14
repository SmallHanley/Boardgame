#include <QPushButton>
#include "newbutton.h"
#include "mainwindow.h"

newbutton::newbutton(QWidget *parent) : QPushButton(parent){
    chessNum = -1;
}

void newbutton::setKind(int num){
    kind = num;
}

void newbutton::setChessNum(int num){
    chessNum = num;
}

void newbutton::setI(int i){
    cellI = i;
}

void newbutton::setJ(int j){
    cellJ = j;
}

void newbutton::checkClick(){
    emit click(kind, chessNum, x(), y(), cellI, cellJ);
}

int newbutton::getKind(){
    return kind;
}
