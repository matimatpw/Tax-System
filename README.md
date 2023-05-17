---Podatki PROI---


System Podatkow: /  -KLIENT
    *vector  kilentow

    *wyliczenie calego podatku (wszystkich klientow razem)

    *dodac nowy wplyw
    *dodac uzytkownika/usunac po ID_
    *szukanie Klienta po wplywie



Wpływ:  /- PODATEK
    *kwota wplywu $ $ $ $
    *kwota do oddania 
    *id


    *liczenie ile do zaplacenia podatku z tego wplywu (np 200) -> Klient->vecotr_wplywy<>
    


                    **---KAROL---**
Klient: / -WPLYW
**class Firma , Osoba:

    *wplywy ( vector<wpływ> )
    *ID_

    *mozliwe podatki jakie ma miec(Osoba/Firma)


    *wyliczyc laczna sume podatkow ze WSZYSTKICH wpływow (zliczenie wszystkich wplywow)



                    **---MATEUSZ---**
class Podatek:
    *virtual oblicz cos xd()

  **class Vat, Pit, Cit
      operator(Wpływ)
      Vat v;
      int x = v(Wplływ);



    











