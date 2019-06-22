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
#include "pilvikysely.h"
#include "db/kirjanpito.h"
#include "pilvimodel.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QApplication>

#include <QDebug>

PilviKysely::PilviKysely(PilviModel *parent, KpKysely::Metodi metodi, QString polku)
    : KpKysely (parent, metodi, polku)
{

}

void PilviKysely::kysy(const QVariant &data)
{
    PilviModel *model = qobject_cast<PilviModel*>( parent() );
    QNetworkRequest request( QUrl( model->pilviosoite() + polku() ) );

    request.setRawHeader("Authorization", QString("bearer %1").arg( model->token() ).toLatin1());
    request.setRawHeader("User-Agent", QString(qApp->applicationName() + " " + qApp->applicationVersion() ).toLatin1()  );

    QNetworkReply *reply = nullptr;

    if( metodi() == GET)    {
        reply = kp()->networkManager()->get( request );
    } else if(metodi() == DELETE) {
        reply = kp()->networkManager()->deleteResource( request );
    } else  {
        request.setRawHeader("Content-Type","application/json");
        QByteArray ba = QJsonDocument::fromVariant(data).toJson(QJsonDocument::Compact);

        if( metodi() == POST )
            reply = kp()->networkManager()->post(request, ba);
        else if( metodi() == PATCH)
            reply = kp()->networkManager()->sendCustomRequest(request, "PATCH", ba);
        else if( metodi() == PUT)
            reply = kp()->networkManager()->put(request, ba);
    }

    connect( reply, &QNetworkReply::finished, this, &PilviKysely::vastausSaapuu );

}

void PilviKysely::vastausSaapuu()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>( sender());
    if( reply->error()) {
        vastaa( VIRHE );
        qDebug() << " (VIRHE!) " << reply->error() << " " << reply->request().url().toString();
        return;
    } else {
        QByteArray vastaus = reply->readAll();
        vastaus_ = QJsonDocument::fromJson( vastaus ).toVariant();
        vastaa( OK );
        qDebug() << " (OK) " << vastaus.left(20);
    }
    this->deleteLater();
}
