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
#ifndef TOSITE_H
#define TOSITE_H


#include <QObject>
#include <QVariant>
#include <map>
#include <QDate>

class TositeViennit;
class TositeLiitteet;
class TositeLoki;
class Asiakas;
class Toimittaja;

/**
 * @brief Kirjanpitotosite
 *
 * @author Arto Hyvättinen
 * @since 2.0
 */
class Tosite : public QObject
{
    Q_OBJECT
public:
    enum Avain {
        ID,
        PVM,
        TYYPPI,
        TILA,
        TUNNISTE,
        OTSIKKO,
        KUMPPANI,
        KOMMENTIT,
        ALV,
        SARJA,
        TILIOTE,
        LASKU,
        RIVIT,
        LASKUPVM,
        ERAPVM,
        VIITE,
        KIERTO,
        PORTAALI
    };

    enum Virheet {
        PVMPUUTTUU      = 0b1,
        PVMLUKITTU      = 0b10,
        PVMALV          = 0b100,
        EITASMAA        = 0b1000,
        TILIPUUTTUU     = 0b100000,
        EIAVOINTAKUTTA  = 0b1000000
    };

    enum Tila {
        POISTETTU       = 0,
        MALLIPOHJA      = 5,
        HYLATTY         = 10,
        SAAPUNUT        = 20,
        TARKASTETTU     = 30,
        HYVAKSYTTY      = 40,
        LUONNOS         = 50,
        LASKULUONNOS    = 60,
        VALMISLASKU     = 80,
        LAHETETAAN      = 101,
        LAHETYSVIRHE    = 102,
        KIRJANPIDOSSA   = 100,
        LAHETETTYLASKU  = 110,
        TOIMITETTULASKU = 113,
        MUISTUTETTU     = 120
    };


    explicit Tosite(QObject *parent = nullptr);

    QVariant data(int kentta) const;
    void setData(int kentta, QVariant arvo);

    TositeViennit* viennit() { return viennit_; }
    TositeLiitteet* liitteet() { return liitteet_;}
    TositeLoki* loki() { return loki_;}

    bool resetoidaanko() const { return resetointiKaynnissa_; }

    static QString tilateksti(int tila);
    static QIcon tilakuva(int tila);

    int id() const { return data(ID).toInt();}
    int tyyppi() const { return data(TYYPPI).toInt();}
    QDate pvm() const;
    QString otsikko() const { return data(OTSIKKO).toString();}
    int kumppani() const { return data(KUMPPANI).toMap().value("id").toInt();}
    QString kumppaninimi() const { return data(KUMPPANI).toMap().value("nimi").toString();}
    int tunniste() const { return data(TUNNISTE).toInt();}
    QString kommentti() const { return data(KOMMENTIT).toString();}
    QString sarja() const { return data(SARJA).toString();}
    int tositetila() const { return data(TILA).toInt();}
    QDate laskupvm() const { return data(LASKUPVM).toDate();}
    QDate erapvm() const { return data(ERAPVM).toDate();}
    QString viite() const { return data(VIITE).toString();}
    int kierto() const { return data(KIERTO).toInt();}
    int tila() const { return data(TILA).toInt();}

    void asetaOtsikko(const QString& otsikko);
    void asetaTyyppi(int tyyppi);
    void asetaPvm(const QDate& pvm);
    void asetaKommentti(const QString& kommentti);
    void asetaSarja(const QString& sarja);
    void asetaLaskupvm(const QDate& pvm) { setData(LASKUPVM, pvm);}
    void asetaErapvm(const QDate& pvm) { setData(ERAPVM, pvm);}
    void asetaViite(const QString& viite) { setData(VIITE, viite);}
    void asetaKierto(int kierto) { setData(KIERTO, kierto);}

    void asetaKumppani(int id);
    void asetaKumppani(const QString& nimi);
    void asetaKumppani(const QVariantMap& map);

    void pohjaksi(const QDate& paiva, const QString& uusiotsikko, bool sailytaerat = false);

    void asetaLaskuNumero(const QString& laskunumero);
    QString laskuNumero() const;

    /**
     * @brief Tiedot tallennettavassa muodossa
     * @return
     */
    QVariantMap tallennettava() const;

signals:
    void ladattu();
    void talletettu(int id, int tunniste, const QDate& pvm, const QString& sarja, int tila);
    void tallennusvirhe(int virhe);
    void tilaTieto(bool muokattu, int virheet, double debet, double kredit);

    void pvmMuuttui(const QDate& pvm);
    void otsikkoMuuttui(const QString& otsikko);
    void tunnisteMuuttui(const int tunniste);
    void sarjaMuuttui(const QString& sarja);
    void tyyppiMuuttui(int tyyppi);
    void eraPvmMuuttui(const QDate& erapvm);
    void kommenttiMuuttui(const QString& kommentti);    

    void tarkastaSarja(bool kateinen);


public slots:
    void lataa(int tositeid);
    void lataaData(QVariant *variant);
    void tallenna(int tilaan = Tosite::KIRJANPIDOSSA);
    void tarkasta();
    void nollaa(const QDate& pvm, int tyyppi);

protected slots:
    void tallennusValmis(QVariant *variant);
    void tallennuksessaVirhe(int virhe);
    void liitteetTallennettu();
    void laitaTalteen();
    void latausValmis();

private:


private:
    QVariantMap data_;
    QVariantMap tallennettu_;

    TositeViennit* viennit_;
    TositeLiitteet* liitteet_;
    TositeLoki* loki_;    

    bool resetointiKaynnissa_ = false;
    bool tallennusKaynnissa_ = false;

    static std::map<int,QString> avaimet__;
};

#endif // TOSITE_H
