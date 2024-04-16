#include <QMainWindow>
#include "calendar.h"

#include <QCalendarWidget>// Inclure le fichier d'en-tête de la sous-classe CustomCalendarWidget

void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const override {
    QCalendarWidget::paintCell(painter, rect, date);

    // Définir la date spécifique
    QDate dateSpecifique(2024, 4, 14);

    // Vérifier si la date actuelle est la date spécifique
    if (date == dateSpecifique) {
        // Dessiner la cellule avec une couleur de fond verte
        painter->fillRect(rect, Qt::green);
    }
}
