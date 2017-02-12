/*
   Copyright (C) 2017 Arto Hyvättinen

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

#include <QSqlQuery>

#include "tositemodel.h"

#include "db/tositelajimodel.h"
#include "db/kirjanpito.h"

#include <QDebug>
#include <QSqlError>

TositeModel::TositeModel(QSqlDatabase *tietokanta, QObject *parent)
    : QObject(parent), tietokanta_(tietokanta)
{
    vientiModel_ = new VientiModel(this);
    liiteModel_ = new LiiteModel(this);
    tyhjaa();
}

Tositelaji TositeModel::tositelaji() const
{
    return kp()->tositelajit()->tositelaji( tositelaji_ );
}

int TositeModel::seuraavaTunnistenumero() const
{
    Tilikausi kausi = kp()->tilikausiPaivalle( pvm() );
    QString kysymys = QString("SELECT max(tunniste) FROM tosite WHERE "
                    " pvm BETWEEN \"%1\" AND \"%2\" "
                    " AND laji=\"%3\" ")
                                .arg(kausi.alkaa().toString(Qt::ISODate))
                                .arg(kausi.paattyy().toString(Qt::ISODate))
                                .arg( tositelaji_ );

    QSqlQuery kysely( *tietokanta_ );
    kysely.exec();
    if( kysely.next())
        return kysely.value(0).toInt() + 1;
    else
        return 1;
}

bool TositeModel::kelpaakoTunniste(int tunnistenumero) const
{
    // Tunniste ei kelpaa, jos kyseisellä kaudella se on jo

    Tilikausi kausi = kp()->tilikausiPaivalle( pvm() );
    QString kysymys = QString("SELECT id FROM tosite WHERE tunniste=\"%1\" "
                              "AND pvm BETWEEN \"%2\" AND \"%3\" AND id <> %4 "
                              "AND laji=\"%5\" ").arg( tunnistenumero )
                                                 .arg(kausi.alkaa().toString(Qt::ISODate))
                                                 .arg(kausi.paattyy().toString(Qt::ISODate))
                                                 .arg( id() )
                                                 .arg( tositelaji_ );
    QSqlQuery kysely( *tietokanta_ );
    kysely.exec(kysymys);
    return !kysely.next();
}

void TositeModel::asetaPvm(const QDate &pvm)
{
    pvm_ = pvm;
}

void TositeModel::asetaOtsikko(const QString &otsikko)
{
    otsikko_ = otsikko;
}

void TositeModel::asetaKommentti(const QString &kommentti)
{
    kommentti_ = kommentti;
}

void TositeModel::asetaTunniste(int tunniste)
{
    tunniste_ = tunniste;
}


void TositeModel::asetaTositelaji(int tositelajiId)
{
    if( tositelajiId != tositelaji_)
    {
        tositelaji_ = tositelajiId;
        // Vaihdetaan sopiva tunniste
        tunniste_ = seuraavaTunnistenumero();
    }

}

void TositeModel::asetaTiliotetili(int tiliId)
{
    tiliotetili_ = tiliId;
}

void TositeModel::lataa(int id)
{
    // Lataa tositteen

    QSqlQuery kysely(*tietokanta_);
    kysely.exec( QString("SELECT pvm, otsikko, kommentti, tunniste,"
                              "laji, tiliote, json FROM tosite "
                              "WHERE id = %1").arg(id));
    if( kysely.next())
    {
        id_ = id;
        otsikko_ = kysely.value("otsikko").toString();
        kommentti_ = kysely.value("kommentti").toString();
        tunniste_ = kysely.value("tunniste").toInt();
        tositelaji_ = kysely.value("laji").toInt();
        tiliotetili_ = kysely.value("tiliote").toInt();
        json_.fromJson( kysely.value("json").toByteArray());

        vientiModel_->lataa();
        liiteModel_->lataa();
    }
}

void TositeModel::tyhjaa()
{
    // Tyhjentää tositteen
    id_ = 0;
    pvm_ = kp()->paivamaara();
    otsikko_ = QString();
    kommentti_ = QString();
    tositelaji_ = 1;
    tunniste_ = seuraavaTunnistenumero();
    tiliotetili_ = 0;

    vientiModel_->tyhjaa();
    liiteModel_->tyhjaa();

}

void TositeModel::tallenna()
{
    // Tallentaa tositteen


    QSqlQuery kysely(*tietokanta_);
    if( id() )
    {
        kysely.prepare("UPDATE tosite SET pvm=:pvm, otsikko=:otsikko, kommentti=:kommentti, "
                       "tunniste=:tunniste, laji=:laji, tiliote=:tiliote, json=:json WHERE id=:id");
        kysely.bindValue(":id", id());
    }
    else
    {
        kysely.prepare("INSERT INTO tosite(pvm, otsikko, kommentti, tunniste, laji, tiliote, json) "
                       "VALUES(:pvm, :otsikko, :kommentti, :tunniste, :laji, :tiliote, :json)");
    }
    kysely.bindValue(":pvm", pvm());
    kysely.bindValue(":otsikko", otsikko());
    if( kommentti().isEmpty())
        kysely.bindValue(":kommentti", QVariant() );
    else
        kysely.bindValue(":kommentti", kommentti());
    kysely.bindValue(":tunniste", tunniste());
    kysely.bindValue(":laji", tositelaji().id());

    if( tiliotetili())
        kysely.bindValue(":tiliote", tiliotetili());
    else
        kysely.bindValue(":tiliote", QVariant());

    kysely.bindValue(":json", json_.toJson());


    kysely.exec();

    qDebug() << kysely.lastQuery() << " " << kysely.lastError().text();

    if( !id())
        id_ = kysely.lastInsertId().toInt();

    vientiModel_->tallenna();
    liiteModel_->tallenna();
}
