/*
   Copyright (C) 2018 Arto Hyvättinen

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
#include "kuvanaytin.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>


KuvaNaytin::KuvaNaytin(QObject *parent) :
    NaytinScene (parent)
{

}

KuvaNaytin::KuvaNaytin(const QByteArray &kuvadata, QObject *parent)
    : KuvaNaytin( parent )
{
    naytaKuva( kuvadata );
}

bool KuvaNaytin::naytaKuva(const QByteArray &kuvadata)
{
    kuva_.loadFromData(kuvadata);
    if( !kuva_.isNull())
    {
        emit sisaltoVaihtunut( "img" );
        return true;
    }
    return false;
}

void KuvaNaytin::piirraLeveyteen(double leveyteen)
{
    clear();
    double korkeus = leveyteen / kuva_.width() * kuva_.height();
    QPixmap pixmap = QPixmap::fromImage( kuva_.scaled( qRound( leveyteen ),  qRound(korkeus), Qt::KeepAspectRatio) );
    addPixmap( pixmap );
}


