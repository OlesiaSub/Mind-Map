#include <iostream>
#include "menu.h"
#include "scene.h"

static int test = 0;

Scene::Scene(QObject *parent) : QGraphicsScene(parent), algo(1920, 1080, 1) {
    algo.fillGraph();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    /** Позиция мышки */
    QPointF pos = event->scenePos();

    /** Создаем активный элемент (прямоугольник) */
    if (state == SDRAW) {
        int width = 60;
        int height = 40;
        int originX = event->lastPos().rx() - width / 2;
        int originY = event->lastPos().ry() - height / 2;
        activeItem = new QGraphicsRectItem(0, 0, width, height);
        if (!activeItem)
            return;

        /** Задаем цвет прямоугольнику */
        static_cast<QGraphicsPolygonItem *>(activeItem)->setBrush(color);

        /** Добавляем элемент в сцену */
        activeItem->setZValue(1);
        addItem(activeItem);
        pos.rx() -= 30;
        pos.ry() -= 20;
        activeItem->setPos(pos);
        algo.getRectCoord(pos.rx() + 30, pos.ry() + 20, width, height); // Добавили центр прямоугольника Олесе

        activeItem->setFlag(QGraphicsItem::ItemIsFocusable);
        myItems.emplace_back(activeItem);
    }
    if (state == SLINE) {
        focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
        focusItem()->setSelected(true);

        if (this->selectedItems().count() == 2) {
            //Получили вектор с точками
            vector<pair<int, int>> points = algo.createShortestPath(this->selectedItems()[0]->pos().rx(),
                                                                    this->selectedItems()[0]->pos().ry(),
                                                                    this->selectedItems()[1]->pos().rx(),
                                                                    this->selectedItems()[1]->pos().ry());
            //Соединяем точки пока просто линиями
            for (int i = 1; i < points.size(); i++) {
                addLine(points[i - 1].first, points[i - 1].second, points[i].first, points[i].second, QPen(Qt::black));
            }

            //Снимаем пометки с выбранных прямоугольников
            for (auto it:this->selectedItems()) {
                it->setSelected(false);
            }
            this->selectedItems().clear();
            for (auto it:myItems) {
                it->setSelected(false);
                it->setFlag(QGraphicsItem::ItemIsSelectable, 0);
            }
        }
    }
}

void Scene::setColor(QColor newColor) {
    color = newColor;
}

void Scene::setFont(QFont newFont) {
    font = newFont;
}

void Scene::setWindowColor(QColor newColor) {
    setBackgroundBrush(newColor);
}

void Scene::setFontColor(QColor newColor) {
    fontcolor = newColor;
}

void Scene::printText() {
    QGraphicsTextItem *text = addText(textstr);
    text->setZValue(2);
    text->setPos(100, 200);
    text->setFont(font);
    text->setDefaultTextColor(fontcolor);
    text->setFlag(QGraphicsTextItem::ItemIsMovable);
}

void Scene::setText(QString str) {
    textstr = str;
}