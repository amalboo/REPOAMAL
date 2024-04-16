#ifndef CALENDAR_H
#define CALENDAR_H
#include <QCalendarWidget>
#include <QCalendarWidget>
#include <QPainter>

class CustomCalendarWidget : public QCalendarWidget {
public:
    CustomCalendarWidget(QWidget *parent = nullptr) : QCalendarWidget(parent) {}

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date);

};




#endif // CALENDAR_H
