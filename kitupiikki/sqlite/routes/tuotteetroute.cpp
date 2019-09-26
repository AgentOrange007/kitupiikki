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
#include "tuotteetroute.h"

TuotteetRoute::TuotteetRoute(SQLiteModel *model)
    : SQLiteRoute(model, "/tuotteet")
{

}

QVariant TuotteetRoute::get(const QString &/*polku*/, const QUrlQuery &/*urlquery*/)
{
    QSqlQuery kysely( db() );
    kysely.exec("SELECT * FROM Tuote ORDER BY nimike");
    return resultList(kysely);
}

QVariant TuotteetRoute::post(const QString &/*polku*/, const QVariant &data)
{
    QVariantMap map = data.toMap();
    QVariantMap jemma = map;
    QSqlQuery kysely( db() );
    kysely.prepare("INSERT INTO Tuote (nimike, json) VALUES (?,?)");
    kysely.addBindValue(map.take("nimike").toString());
    kysely.addBindValue(mapToJson(map));
    kysely.exec();
    jemma.insert("id", kysely.lastInsertId().toInt());
    return jemma;
}

QVariant TuotteetRoute::put(const QString &polku, const QVariant &data)
{
    QVariantMap map = data.toMap();
    QVariantMap jemma = map;
    QSqlQuery kysely( db() );
    kysely.prepare( "INSERT INTO Tuote (id, nimike,json) VALUES (?,?,?) "
                    "ON CONFLICT (id) DO UPDATE SET nimike=EXCLUDED.nimike, json=EXCLUDED.json" );
    kysely.addBindValue( polku.toInt() );
    map.remove("id");
    kysely.addBindValue(map.take("nimike").toString());
    kysely.addBindValue(mapToJson(map));
    kysely.exec();
    return jemma;
}
