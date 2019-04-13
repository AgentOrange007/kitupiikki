/*
   Copyright (C) 2019 Arto Hyvättinen

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KPYHTEYS_H
#define KPYHTEYS_H


#include "kpkysely.h"
#include <QObject>
#include <QUrl>

class Kirjanpito;

/**
 * @brief Taustayhteyksien kantaluokka
 * @since 2.0
 */
class KpYhteys : public QObject
{
    Q_OBJECT
public:
    KpYhteys(QObject *parent);

    virtual KpKysely* kysely(const QString& polku = QString(), KpKysely::Metodi metodi = KpKysely::GET ) = 0;


signals:
    void yhteysAvattu(bool onnistuiko);

public slots:
    virtual void alustaYhteys() = 0;


};

#endif // KPYHTEYS_H
