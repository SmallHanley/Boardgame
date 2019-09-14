#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->board->setGeometry(430, 40, 500, 500);
    start = new QPushButton(this);
    start->setGeometry(135, 220, 171, 71);
    start->setText(tr("Start"));
    start->setFont(QFont("Ubuntu Regular", 25));
    QPalette pal1 = start->palette();
    pal1.setColor(QPalette::Button, QColor(255, 69, 0));
    start->setPalette(pal1);
    pal1.setColor(QPalette::ButtonText, QColor(248, 248, 255));
    start->setPalette(pal1);
    setboard = new QPushButton(this);
    setboard->setGeometry(135, 340, 171, 71);
    setboard->setText(tr("Setboard"));
    setboard->setFont(QFont("Ubuntu Regular", 25));
    QPalette pal2 = setboard->palette();
    pal2.setColor(QPalette::Button, QColor(255, 69, 0));
    setboard->setPalette(pal2);
    pal2.setColor(QPalette::ButtonText, QColor(248, 248, 255));
    setboard->setPalette(pal2);
    restart = new QPushButton(this);
    restart->setGeometry(135, 220, 171, 71);
    restart->setText(tr("Restart"));
    restart->setFont(QFont("Ubuntu Regular", 25));
    restart->setVisible(false);
    QPalette pal3 = restart->palette();
    pal3.setColor(QPalette::Button, QColor(255, 69, 0));
    restart->setPalette(pal3);
    pal3.setColor(QPalette::ButtonText, QColor(248, 248, 255));
    restart->setPalette(pal3);
    mode = 0;
    connect(start, SIGNAL(clicked()), this, SLOT(startSlots()));
    connect(setboard, SIGNAL(clicked()), this, SLOT(setboardSlots()));
    connect(restart, SIGNAL(clicked()), this, SLOT(restartSlots()));
    chessPics.push_back(QPixmap(":/img/img/1.png"));
    chessPics.push_back(QPixmap(":/img/img/2.png"));
    chessPics.push_back(QPixmap(":/img/img/3.png"));
    chessPics.push_back(QPixmap(":/img/img/4.png"));
    chessPics.push_back(QPixmap(":/img/img/5.png"));
    chessPics.push_back(QPixmap(":/img/img/6.png"));
    chessPics.push_back(QPixmap(":/img/img/7.png"));
    chessPics.push_back(QPixmap(":/img/img/8.png"));
    chessPics.push_back(QPixmap(":/img/img/9.png"));
    chessPics.push_back(QPixmap(":/img/img/10.png"));
    chessPics.push_back(QPixmap(":/img/img/11.png"));
    chessPics.push_back(QPixmap(":/img/img/12.png"));
    chessPics.push_back(QPixmap(":/img/img/13.png"));
    chessPics.push_back(QPixmap(":/img/img/14.png"));
    cellPics.push_back(QPixmap(":/img/img/tp.png"));
    cellPics.push_back(QPixmap(":/img/img/green.png"));
    cellPics.push_back(QPixmap(":/img/img/red.png"));
    int index = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 9; j++){
            if(map[i][j]){
                chess[index] = new newbutton(this);
                chess[index]->setKind(map[i][j]);
                chess[index]->setGeometry(443 + j * 53, 68 + i * 48, 50, 50);
                QIcon ButtonIcon(chessPics[map[i][j] - 1]);
                chess[index]->setIcon(ButtonIcon);
                chess[index]->setIconSize(QSize(50, 50));
                chess[index]->setFlat(true);
                index++;
            }
        }
    }
    index = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 9; j++){
            cell[i][j] = new newbutton(this);
            cell[i][j]->setKind(map[i][j]);
            if(map[i][j]){
                if(map[i][j] >= 8){
                    cell[i][j]->setChessNum(index);
                    index++;
                }
                else{
                    cell[i][j]->setChessNum(index);
                    cell[i][j]->setVisible(false);
                    index++;
                }
            }
            else{
                cell[i][j]->setVisible(false);
            }
            cell[i][j]->setI(i);
            cell[i][j]->setJ(j);
            cell[i][j]->setGeometry(443 + j * 53, 68 + i * 48, 50, 50);
            QIcon ButtonIcon(cellPics[0]);
            cell[i][j]->setIcon(ButtonIcon);
            cell[i][j]->setIconSize(QSize(50, 50));
            cell[i][j]->setFlat(true);
            connect(cell[i][j], SIGNAL(clicked()), cell[i][j], SLOT(checkClick()));
            connect(cell[i][j], SIGNAL(click(int, int, int, int, int, int)), this, SLOT(move(int, int, int, int, int, int)));
        }
    }
    QPixmap p1(":/img/img/redwin");
    redWin = new QLabel(this);
    redWin->setGeometry(553, 251, 271, 111);
    redWin->setPixmap(p1.scaled(271, 111, Qt::KeepAspectRatio));
    redWin->setVisible(false);
    QPixmap p2(":/img/img/blackwin");
    blackWin = new QLabel(this);
    blackWin->setGeometry(553, 251, 271, 111);
    blackWin->setPixmap(p2.scaled(271, 111, Qt::KeepAspectRatio));
    blackWin->setVisible(false);
    isClick = false;
    color = true;
}

void MainWindow::blackGeneral(int i, int j){
    int temp;
    bool check;
    if(j >= 4 && (!map[i][j - 1] || map[i][j - 1] >= 8)){
        temp = i + 1;
        check = false;
        while(!map[temp][j - 1] && temp < 10){
            temp++;
        }
        if(temp < 10 && map[temp][j - 1] == 8) check = true;
        if(!check){
            cell[i][j - 1]->setVisible(true);
            if(!map[i][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(j <= 4 && (!map[i][j + 1] || map[i][j + 1] >= 8)){
        temp = i + 1;
        check = false;
        while(!map[temp][j + 1] && temp < 10){
            temp++;
        }
        if(temp != 10 && map[temp][j + 1] == 8) check = true;
        if(!check){
            cell[i][j + 1]->setVisible(true);
            if(!map[i][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(i >= 1 && (!map[i - 1][j] || map[i - 1][j] >= 8)){
        cell[i - 1][j]->setVisible(true);
        if(!map[i - 1][j]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 1][j]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 1][j]->setIcon(ButtonIcon);
        }
    }
    if(i <= 1 && (!map[i + 1][j] || map[i + 1][j] >= 8)){
        cell[i + 1][j]->setVisible(true);
        if(!map[i + 1][j]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 1][j]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 1][j]->setIcon(ButtonIcon);
        }
    }
}

void MainWindow::blackGuards(int i, int j){
    if(i <= 1 && j <= 4 && (!map[i + 1][j + 1] || map[i + 1][j + 1] >= 8)){
        cell[i + 1][j + 1]->setVisible(true);
        if(!map[i + 1][j + 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 1][j + 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 1][j + 1]->setIcon(ButtonIcon);
        }
    }
    if(i <= 1 && j >= 4 && (!map[i + 1][j - 1] || map[i + 1][j - 1] >= 8)){
        cell[i + 1][j - 1]->setVisible(true);
        if(!map[i + 1][j - 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 1][j - 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 1][j - 1]->setIcon(ButtonIcon);
        }
    }
    if(i >= 1 && j <= 4 && (!map[i - 1][j + 1] || map[i - 1][j + 1] >= 8)){
        cell[i - 1][j + 1]->setVisible(true);
        if(!map[i - 1][j + 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 1][j + 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 1][j + 1]->setIcon(ButtonIcon);
        }
    }
    if(i >= 1 && j >= 4 && (!map[i - 1][j - 1] || map[i - 1][j - 1] >= 8)){
        cell[i - 1][j - 1]->setVisible(true);
        if(!map[i - 1][j - 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 1][j - 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 1][j - 1]->setIcon(ButtonIcon);
        }
    }
    checkKing(i, j);
}

void MainWindow::blackMinisters(int i, int j){
    if(i <= 2 && j <= 6 && !map[i + 1][j + 1] && (!map[i + 2][j + 2] || map[i + 2][j + 2] >= 8)){
        cell[i + 2][j + 2]->setVisible(true);
        if(!map[i + 2][j + 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 2][j + 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 2][j + 2]->setIcon(ButtonIcon);
        }
    }
    if(i <= 2 && j >= 2 && !map[i + 1][j - 1] && (!map[i + 2][j - 2] || map[i + 2][j - 2] >= 8)){
        cell[i + 2][j - 2]->setVisible(true);
        if(!map[i + 2][j - 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 2][j - 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 2][j - 2]->setIcon(ButtonIcon);
        }
    }
    if(i >= 2 && j <= 6 && !map[i - 1][j + 1] && (!map[i - 2][j + 2] || map[i - 2][j + 2] >= 8)){
        cell[i - 2][j + 2]->setVisible(true);
        if(!map[i - 2][j + 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 2][j + 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 2][j + 2]->setIcon(ButtonIcon);
        }
    }
    if(i >= 2 && j >= 2 && !map[i - 1][j - 1] && (!map[i - 2][j - 2] || map[i - 2][j - 2] >= 8)){
        cell[i - 2][j - 2]->setVisible(true);
        if(!map[i - 2][j - 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 2][j - 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 2][j - 2]->setIcon(ButtonIcon);
        }
    }
    checkKing(i, j);
}

void MainWindow::blackChariots(int i, int j){
    int temp;
    temp = j + 1;
    while(!map[i][temp] && temp < 9){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp++;
    }
    if(temp != 9 && map[i][temp] >= 8){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = j - 1;
    while(!map[i][temp] && temp >= 0){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp--;
    }
    if(temp != -1 && map[i][temp] >= 8){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = i + 1;
    while(!map[temp][j] && temp < 10){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp++;
    }
    if(temp != 10 && map[temp][j] >= 8){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    temp = i - 1;
    while(!map[temp][j] && temp >= 0){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp--;
    }
    if(temp != -1 && map[temp][j] >= 8){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    checkKing(i, j);
}

void MainWindow::blackHorses(int i, int j){
    if(i >= 2 && !map[i - 1][j]){
        if(j >= 1 && (!map[i - 2][j - 1] || map[i - 2][j - 1] >= 8)){
            cell[i - 2][j - 1]->setVisible(true);
            if(!map[i - 2][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 2][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 2][j - 1]->setIcon(ButtonIcon);
            }
        }
        if(j <= 7 && (!map[i - 2][j + 1] || map[i - 2][j + 1] >= 8)){
            cell[i - 2][j + 1]->setVisible(true);
            if(!map[i - 2][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 2][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 2][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(i <= 7 && !map[i + 1][j]){
        if(j >= 1 && (!map[i + 2][j - 1] || map[i + 2][j - 1] >= 8)){
            cell[i + 2][j - 1]->setVisible(true);
            if(!map[i + 2][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 2][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 2][j - 1]->setIcon(ButtonIcon);
            }
        }
        if(j <= 7 && (!map[i + 2][j + 1] || map[i + 2][j + 1] >= 8)){
            cell[i + 2][j + 1]->setVisible(true);
            if(!map[i + 2][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 2][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 2][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(j >= 2 && !map[i][j - 1]){
        if(i >= 1 && (!map[i - 1][j - 2] || map[i - 1][j - 2] >= 8)){
            cell[i - 1][j - 2]->setVisible(true);
            if(!map[i - 1][j - 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 1][j - 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 1][j - 2]->setIcon(ButtonIcon);
            }
        }
        if(i <= 8 && (!map[i + 1][j - 2] || map[i + 1][j - 2] >= 8)){
            cell[i + 1][j - 2]->setVisible(true);
            if(!map[i + 1][j - 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 1][j - 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 1][j - 2]->setIcon(ButtonIcon);
            }
        }
    }
    if(j <= 6 && !map[i][j + 1]){
        if(i >= 1 && (!map[i - 1][j + 2] || map[i - 1][j + 2] >= 8)){
            cell[i - 1][j + 2]->setVisible(true);
            if(!map[i - 1][j + 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 1][j + 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 1][j + 2]->setIcon(ButtonIcon);
            }
        }
        if(i <= 8 && (!map[i + 1][j + 2] || map[i + 1][j + 2] >= 8)){
            cell[i + 1][j + 2]->setVisible(true);
            if(!map[i + 1][j + 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 1][j + 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 1][j + 2]->setIcon(ButtonIcon);
            }
        }
    }
    checkKing(i, j);
}

void MainWindow::blackCannons(int i, int j){
    int temp;
    temp = j + 1;
    while(!map[i][temp] && temp < 9){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp++;
    }
    temp++;
    while(!map[i][temp] && temp < 9){
        temp++;
    }
    if(map[i][temp] >= 8 && temp < 9){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = j - 1;
    while(!map[i][temp] && temp >= 0){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp--;
    }
    temp--;
    while(!map[i][temp] && temp >= 0){
        temp--;
    }
    if(map[i][temp] >= 8 && temp >= 0){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = i + 1;
    while(!map[temp][j] && temp < 10){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp++;
    }
    temp++;
    while(!map[temp][j] && temp < 10){
        temp++;
    }
    if(map[temp][j] >=8 && temp < 10){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    temp = i - 1;
    while(!map[temp][j] && temp >= 0){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp--;
    }
    temp--;
    while(!map[temp][j] && temp >= 0){
        temp--;
    }
    if(map[temp][j] >= 8 && temp >= 0){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    checkKing(i, j);
}

void MainWindow::blackSoldiers(int i, int j){
    if(i <= 4 && (!map[i + 1][j] || map[i + 1][j] >= 8)){
        cell[i + 1][j]->setVisible(true);
        if(!map[i + 1][j]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 1][j]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 1][j]->setIcon(ButtonIcon);
        }
    }
    else{
        if(!map[i + 1][j] || map[i + 1][j] >= 8){
            cell[i + 1][j]->setVisible(true);
            if(!map[i + 1][j]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 1][j]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 1][j]->setIcon(ButtonIcon);
            }
        }
        if(!map[i][j - 1] || map[i][j - 1] >= 8){
            cell[i][j - 1]->setVisible(true);
            if(!map[i][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
        }
        if(!map[i][j + 1] || map[i][j + 1] >= 8){
            cell[i][j + 1]->setVisible(true);
            if(!map[i][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    checkKing(i, j);
}

void MainWindow::redGeneral(int i, int j){
    int temp;
    bool check;
    if(j >= 4 && map[i][j - 1] <= 7){
        temp = i - 1;
        check = false;
        while(!map[temp][j - 1] && temp >= 0){
            temp--;
        }
        if(temp >= 0 && map[temp][j - 1] == 1) check = true;
        if(!check){
            cell[i][j - 1]->setVisible(true);
            if(!map[i][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(j <= 4 && map[i][j + 1] <= 7){
        temp = i - 1;
        check = false;
        while(!map[temp][j + 1] && temp >= 0){
            temp--;
        }
        if(temp != -1 && map[temp][j + 1] == 1) check = true;
        if(!check){
            cell[i][j + 1]->setVisible(true);
            if(!map[i][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(i >= 8 && map[i - 1][j] <= 7){
        cell[i - 1][j]->setVisible(true);
        if(!map[i - 1][j]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 1][j]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 1][j]->setIcon(ButtonIcon);
        }
    }
    if(i <= 8 && map[i + 1][j] <= 7){
        cell[i + 1][j]->setVisible(true);
        if(!map[i + 1][j]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 1][j]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 1][j]->setIcon(ButtonIcon);
        }
    }
}

void MainWindow::redGuards(int i, int j){
    if(i <= 8 && j <= 4 && map[i + 1][j + 1] <= 7){
        cell[i + 1][j + 1]->setVisible(true);
        if(!map[i + 1][j + 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 1][j + 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 1][j + 1]->setIcon(ButtonIcon);
        }
    }
    if(i <= 8 && j >= 4 && map[i + 1][j - 1] <= 7){
        cell[i + 1][j - 1]->setVisible(true);
        if(!map[i + 1][j - 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 1][j - 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 1][j - 1]->setIcon(ButtonIcon);
        }
    }
    if(i >= 8 && j <= 4 && map[i - 1][j + 1] <= 7){
        cell[i - 1][j + 1]->setVisible(true);
        if(!map[i - 1][j + 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 1][j + 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 1][j + 1]->setIcon(ButtonIcon);
        }
    }
    if(i >= 8 && j >= 4 && map[i - 1][j - 1] <= 7){
        cell[i - 1][j - 1]->setVisible(true);
        if(!map[i - 1][j - 1]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 1][j - 1]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 1][j - 1]->setIcon(ButtonIcon);
        }
    }
    checkKing(i, j);
}

void MainWindow::redMinisters(int i, int j){
    if(i <= 7 && j <= 6 && !map[i + 1][j + 1] && map[i + 2][j + 2] <= 7){
        cell[i + 2][j + 2]->setVisible(true);
        if(!map[i + 2][j + 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 2][j + 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 2][j + 2]->setIcon(ButtonIcon);
        }
    }
    if(i <= 7 && j >= 2 && !map[i + 1][j - 1] && map[i + 2][j - 2] <= 7){
        cell[i + 2][j - 2]->setVisible(true);
        if(!map[i + 2][j - 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i + 2][j - 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i + 2][j - 2]->setIcon(ButtonIcon);
        }
    }
    if(i >= 7 && j <= 6 && !map[i - 1][j + 1] && map[i - 2][j + 2] <= 7){
        cell[i - 2][j + 2]->setVisible(true);
        if(!map[i - 2][j + 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 2][j + 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 2][j + 2]->setIcon(ButtonIcon);
        }
    }
    if(i >= 7 && j >= 2 && !map[i - 1][j - 1] && map[i - 2][j - 2] <= 7){
        cell[i - 2][j - 2]->setVisible(true);
        if(!map[i - 2][j - 2]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 2][j - 2]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 2][j - 2]->setIcon(ButtonIcon);
        }
    }
    checkKing(i, j);
}

void MainWindow::redChariots(int i, int j){
    int temp;
    temp = j + 1;
    while(!map[i][temp] && temp < 9){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp++;
    }
    if(temp != 9 && map[i][temp] <= 7){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = j - 1;
    while(!map[i][temp] && temp >= 0){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp--;
    }
    if(temp != -1 && map[i][temp] <= 7){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = i + 1;
    while(!map[temp][j] && temp < 10){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp++;
    }
    if(temp != 10 && map[temp][j] <= 7){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    temp = i - 1;
    while(!map[temp][j] && temp >= 0){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp--;
    }
    if(temp != -1 && map[temp][j] <= 7){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    checkKing(i, j);
}

void MainWindow::redHorses(int i, int j){
    if(i >= 2 && !map[i - 1][j]){
        if(j >= 1 && (map[i - 2][j - 1] <= 7)){
            cell[i - 2][j - 1]->setVisible(true);
            if(!map[i - 2][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 2][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 2][j - 1]->setIcon(ButtonIcon);
            }
        }
        if(j <= 7 && (map[i - 2][j + 1] <= 7)){
            cell[i - 2][j + 1]->setVisible(true);
            if(!map[i - 2][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 2][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 2][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(i <= 7 && !map[i + 1][j]){
        if(j >= 1 && (map[i + 2][j - 1] <= 7)){
            cell[i + 2][j - 1]->setVisible(true);
            if(!map[i + 2][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 2][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 2][j - 1]->setIcon(ButtonIcon);
            }
        }
        if(j <= 7 && (map[i + 2][j + 1] <= 7)){
            cell[i + 2][j + 1]->setVisible(true);
            if(!map[i + 2][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 2][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 2][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    if(j >= 2 && !map[i][j - 1]){
        if(i >= 1 && (map[i - 1][j - 2] <= 7)){
            cell[i - 1][j - 2]->setVisible(true);
            if(!map[i - 1][j - 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 1][j - 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 1][j - 2]->setIcon(ButtonIcon);
            }
        }
        if(i <= 8 && (map[i + 1][j - 2] <= 7)){
            cell[i + 1][j - 2]->setVisible(true);
            if(!map[i + 1][j - 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 1][j - 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 1][j - 2]->setIcon(ButtonIcon);
            }
        }
    }
    if(j <= 6 && !map[i][j + 1]){
        if(i >= 1 && (map[i - 1][j + 2] <= 7)){
            cell[i - 1][j + 2]->setVisible(true);
            if(!map[i - 1][j + 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 1][j + 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 1][j + 2]->setIcon(ButtonIcon);
            }
        }
        if(i <= 8 && (map[i + 1][j + 2] <= 7)){
            cell[i + 1][j + 2]->setVisible(true);
            if(!map[i + 1][j + 2]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i + 1][j + 2]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i + 1][j + 2]->setIcon(ButtonIcon);
            }
        }
    }
    checkKing(i, j);
}

void MainWindow::redCannons(int i, int j){
    int temp;
    temp = j + 1;
    while(!map[i][temp] && temp < 9){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp++;
    }
    temp++;
    while(!map[i][temp] && temp < 9){
        temp++;
    }
    if(map[i][temp] <= 7 && map[i][temp] && temp < 9){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = j - 1;
    while(!map[i][temp] && temp >= 0){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[i][temp]->setIcon(ButtonIcon);
        temp--;
    }
    temp--;
    while(!map[i][temp] && temp >= 0){
        temp--;
    }
    if(map[i][temp] <= 7 && map[i][temp] && temp >= 0){
        cell[i][temp]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[i][temp]->setIcon(ButtonIcon);
    }
    temp = i + 1;
    while(!map[temp][j] && temp < 10){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp++;
    }
    temp++;
    while(!map[temp][j] && temp < 10){
        temp++;
    }
    if(map[temp][j] <= 7 && temp < 10){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    temp = i - 1;
    while(!map[temp][j] && temp >= 0){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[1]);
        cell[temp][j]->setIcon(ButtonIcon);
        temp--;
    }
    temp--;
    while(!map[temp][j] && temp >= 0){
        temp--;
    }
    if(map[temp][j] <= 7 && temp >= 0){
        cell[temp][j]->setVisible(true);
        QIcon ButtonIcon(cellPics[2]);
        cell[temp][j]->setIcon(ButtonIcon);
    }
    checkKing(i, j);
}

void MainWindow::redSoldiers(int i, int j){
    if(i >= 5 && map[i - 1][j] <= 7){
        cell[i - 1][j]->setVisible(true);
        if(!map[i - 1][j]){
            QIcon ButtonIcon(cellPics[1]);
            cell[i - 1][j]->setIcon(ButtonIcon);
        }
        else{
            QIcon ButtonIcon(cellPics[2]);
            cell[i - 1][j]->setIcon(ButtonIcon);
        }
    }
    else{
        if(map[i - 1][j] <= 7){
            cell[i - 1][j]->setVisible(true);
            if(!map[i - 1][j]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i - 1][j]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i - 1][j]->setIcon(ButtonIcon);
            }
        }
        if(map[i][j - 1] <= 7){
            cell[i][j - 1]->setVisible(true);
            if(!map[i][j - 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j - 1]->setIcon(ButtonIcon);
            }
        }
        if(map[i][j + 1] <= 7){
            cell[i][j + 1]->setVisible(true);
            if(!map[i][j + 1]){
                QIcon ButtonIcon(cellPics[1]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
            else{
                QIcon ButtonIcon(cellPics[2]);
                cell[i][j + 1]->setIcon(ButtonIcon);
            }
        }
    }
    checkKing(i, j);
}

void MainWindow::checkKing(int I, int J){
    bool check1 = false, check2 = false;
    int temp;
    temp = I + 1;
    while(!map[temp][J] && temp < 10){
        temp++;
    }
    if((map[temp][J] == 1 || map[temp][J] == 8) && temp < 10){
        check1 = true;
    }
    temp = I - 1;
    while(!map[temp][J] && temp >= 0){
        temp--;
    }
    if((map[temp][J] == 1 || map[temp][J] == 8) && temp >= 0){
        check2 = true;
    }
    if(check1 && check2){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                if(j != J){
                    cell[i][j]->setVisible(false);
                }
            }
        }
    }
}

void MainWindow::startSlots(){
    if(mode == 0){
        mode = 1;
        start->setVisible(false);
        setboard->setVisible(false);
        restart->setVisible(true);
        restart->move(125, 275);
    }
    if(mode == 2){
        mode = 1;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 4; j++){
                setboardTemp[i][j]->setVisible(false);
            }
        }
        for(int i = 0; i < 32; i++){
            if(chess[i]->x() < 440){
                chess[i]->setVisible(false);
            }
        }
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                if(map[i][j] >= 8){
                    cell[i][j]->setVisible(true);
                }
            }
        }
        start->setVisible(false);
        restart->move(125, 275);
    }
}

void MainWindow::setboardSlots(){
    mode = 2;
    start->setVisible(true);
    start->move(40, 520);
    restart->setVisible(true);
    restart->move(220, 520);
    setboard->setVisible(false);
    int index = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++){
            chess[index]->setVisible(true);
            chess[index]->move(100 + j * 60, 55 + i * 55);
            setboardTemp[i][j] = new newbutton(this);
            setboardTemp[i][j]->setGeometry(100 + j * 60, 55 + i * 55, 50, 50);
            QIcon ButtonIcon(cellPics[0]);
            setboardTemp[i][j]->setIcon(ButtonIcon);
            setboardTemp[i][j]->setIconSize(QSize(50, 50));
            setboardTemp[i][j]->setKind(chess[index]->getKind());
            setboardTemp[i][j]->setChessNum(index);
            setboardTemp[i][j]->setI(i);
            setboardTemp[i][j]->setJ(j);
            setboardTemp[i][j]->setVisible(true);
            setboardTemp[i][j]->setFlat(true);
            connect(setboardTemp[i][j], SIGNAL(clicked()), setboardTemp[i][j], SLOT(checkClick()));
            connect(setboardTemp[i][j], SIGNAL(click(int, int, int, int, int, int)), this, SLOT(move(int, int, int, int, int, int)));
            index++;
        }
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 9; j++){
            cell[i][j]->setVisible(true);
            QIcon ButtonIcon(cellPics[0]);
            cell[i][j]->setIcon(ButtonIcon);
            cell[i][j]->setKind(0);
            cell[i][j]->setChessNum(-1);
            map[i][j] = 0;
        }
    }
}

void MainWindow::restartSlots(){
    int index;
    if(mode == 1){
        mode = 0;
        restart->setVisible(false);
        start->setVisible(true);
        start->move(135, 220);
        setboard->setVisible(true);
        setboard->move(135, 340);
        redWin->setVisible(false);
        blackWin->setVisible(false);
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                map[i][j] = originalMap[i][j];
            }
        }
        index = 0;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                if(map[i][j]){
                    chess[index]->setVisible(true);
                    chess[index]->setKind(map[i][j]);
                    chess[index]->move(443 + j * 53, 68 + i * 48);
                    index++;
                }
            }
        }
        index = 0;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                cell[i][j]->setKind(map[i][j]);
                if(map[i][j]){
                    if(map[i][j] >= 8){
                        cell[i][j]->setChessNum(index);
                        cell[i][j]->setVisible(true);
                        index++;
                    }
                    else{
                        cell[i][j]->setChessNum(index);
                        cell[i][j]->setVisible(false);
                        index++;
                    }
                }
                else{
                    cell[i][j]->setVisible(false);
                }
            }
        }
        isClick = false;
        color = true;
    }
    if(mode == 2){
        int index = 0;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 4; j++){
                chess[index]->setVisible(true);
                chess[index]->move(100 + j * 60, 55 + i * 55);
                setboardTemp[i][j]->setKind(chess[index]->getKind());
                QIcon ButtonIcon(cellPics[0]);
                setboardTemp[i][j]->setIcon(ButtonIcon);
                setboardTemp[i][j]->setChessNum(index);
                setboardTemp[i][j]->setI(i);
                setboardTemp[i][j]->setJ(j);
                setboardTemp[i][j]->setVisible(true);
                index++;
            }
        }
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                cell[i][j]->setVisible(true);
                cell[i][j]->setKind(0);
                cell[i][j]->setChessNum(-1);
                map[i][j] = 0;
            }
        }
        isClick = false;
    }
}

void MainWindow::move(int kind, int chessNum, int x, int y, int i, int j){
    if(mode == 1){
        if(!isClick){
            QIcon ButtonIcon(cellPics[2]);
            cell[i][j]->setIcon(ButtonIcon);
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 9; j++){
                    cell[i][j]->setVisible(false);
                }
            }
            cell[i][j]->setVisible(true);
            switch(kind){
                case 1:
                    blackGeneral(i, j);
                    break;
                case 2:
                    blackGuards(i, j);
                    break;
                case 3:
                    blackMinisters(i, j);
                    break;
                case 4:
                    blackChariots(i, j);
                    break;
                case 5:
                    blackHorses(i, j);
                    break;
                case 6:
                    blackCannons(i, j);
                    break;
                case 7:
                    blackSoldiers(i, j);
                    break;
                case 8:
                    redGeneral(i, j);
                    break;
                case 9:
                    redGuards(i, j);
                    break;
                case 10:
                    redMinisters(i, j);
                    break;
                case 11:
                    redChariots(i, j);
                    break;
                case 12:
                    redHorses(i, j);
                    break;
                case 13:
                    redCannons(i, j);
                    break;
                case 14:
                    redSoldiers(i, j);
                    break;
            }
            clickKind = kind;
            clickChessNum = chessNum;
            cellI = i;
            cellJ = j;
            isClick = true;
            color = !color;
        }
        else{
            if(i == cellI && j == cellJ){
                QIcon ButtonIcon(cellPics[0]);
                cell[i][j]->setIcon(ButtonIcon);
                color = !color;
                if(color){
                    for(int i = 0; i < 10; i++){
                        for(int j = 0; j < 9; j++){
                            if(map[i][j] >= 8 && map[i][j] <= 14){
                                cell[i][j]->setVisible(true);
                            }
                            else {
                                cell[i][j]->setVisible(false);
                            }
                        }
                    }
                }
                else{
                    for(int i = 0; i < 10; i++){
                        for(int j = 0; j < 9; j++){
                            if(map[i][j] >= 1 && map[i][j] <= 7){
                                cell[i][j]->setVisible(true);
                            }
                            else {
                                cell[i][j]->setVisible(false);
                            }
                        }
                    }
                }
                isClick = false;
            }
            else{
                QIcon ButtonIcon(cellPics[0]);
                cell[cellI][cellJ]->setIcon(ButtonIcon);
                chess[clickChessNum]->move(x, y);
                cell[cellI][cellJ]->setChessNum(-1);
                cell[cellI][cellJ]->setKind(0);
                map[cellI][cellJ] = 0;
                cell[i][j]->setChessNum(clickChessNum);
                cell[i][j]->setKind(clickKind);
                map[i][j] = clickKind;
                for(int i = 0; i < 10; i++){
                    for(int j = 0; j < 9; j++){
                        QIcon ButtonIcon(cellPics[0]);
                        cell[i][j]->setIcon(ButtonIcon);
                        if(!map[i][j]){
                            cell[i][j]->setVisible(false);
                        }
                    }
                }
                if(kind){
                    chess[chessNum]->setVisible(false);
                    if(kind == 1){
                        redWin->setVisible(true);
                    }
                    if(kind == 8){
                        blackWin->setVisible(true);
                    }
                }
                isClick = false;
                if(color){
                    for(int i = 0; i < 10; i++){
                        for(int j = 0; j < 9; j++){
                            if(map[i][j] >= 8 && map[i][j] <= 14){
                                cell[i][j]->setVisible(true);
                            }
                            else {
                                cell[i][j]->setVisible(false);
                            }
                        }
                    }
                }
                else{
                    for(int i = 0; i < 10; i++){
                        for(int j = 0; j < 9; j++){
                            if(map[i][j] >= 1 && map[i][j] <= 7){
                                cell[i][j]->setVisible(true);
                            }
                            else {
                                cell[i][j]->setVisible(false);
                            }
                        }
                    }
                }
            }
        }
        return;
    }
    if(mode == 2){
        if(!isClick){
            clickChessNum = chessNum;
            clickKind = kind;
            QIcon ButtonIcon(cellPics[1]);
            setboardTemp[i][j]->setIcon(ButtonIcon);
            clickX = i;
            clickY = j;
            isClick = true;
        }
        else{
            setboardTemp[clickX][clickY]->setVisible(false);
            chess[clickChessNum]->move(x, y);
            isClick = false;
            map[i][j] = clickKind;
            cell[i][j]->setVisible(false);
            cell[i][j]->setKind(clickKind);
            cell[i][j]->setChessNum(clickChessNum);
            isClick = false;
        }
    }
}

MainWindow::~MainWindow(){
    delete ui;
}
