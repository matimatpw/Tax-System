
# Projekt Z Przedmiotu Programowanie Obiekowe 

## System podatkowy 

#### Karol Kuc, Mateusz Matukiewicz, Przemysław Walecki
---

## 1. Uruchomienie projektu
Projekt został wykonany przy pomocy Visual Studio 2022. Na repozytorium, na gałęzic master znajduje sie gotowy plik z wszystkimi potrzebnymi plikami, w tym .vcxproj oraz .sln. Aby uruchomić projekt (aplikację z systemem podatkowym) należy zklonować repozytorium do Visual Studio, przejść na gałęź master, wejść w plik .sln, następnie oznaczyć katalog  PROI_PODATKI_App jako domyślny katalog startowy i skompilować projekt.

# 2. Opis Projektu
## 2.1 Klasy zawarte w projekcie
- ## Tax
    > Klasa reprezentująca różne formy opodatkowania zawarte w systemie podatkowym.  
    > Klasa Tax jest klasą bazową zawierającą abstrakcyjne metody nadpisywane w klasach dziedziczących   
    
    > Zawartość klas dziedziczących:
    > - Przeciążony operator wywoływania funkcji () służący do obliczania podatku od podanej kwoty
    > - Funkcja getName zwracajaca nazwe podatku
- ## Income
    > Struktura reprezentująca opodatkowane wpływy w systemie podatkowym
    
    > Zawartość struktury:
    > - ID, wielkość wływu (w zł),
    > - Wskazanie na podatek, którym obciążony jest wpływ
    > - Wysokość podatku do zapłacenia (w zł)
    > - Status zapłacenia podatku przez podatnika  
- ## Client
    > Klasa bazowa reprezentująca podatników w systemie podatkowym  
    > Klasy dziedziczące po Client: Company oraz Person (podział na osoby fizyczne i firmy)
    
    > Zawartość klasy Client:
    > - Atrybuty:
    >   - Nazwa, ID, wektor przychodów
    > - Metody:
    >   - abstrakcyjne getTaxes (zwracanie wektora dostępnych podatków, klasa bazowa go nie ma)
    >   - "gettery" do atrybutów
    >   -  dodawanie wpływu 
    >   -  oznaczanie wpływu jako opłacony (podatek) (jerdnorazowe, próba oznaczenia tego samego wpływu jako opłacony skutkuje błędem)
    >   -  sprawdzanie, czy Klient posiada wpływ o danym ID  
    >   -  wyliczenie łącznej sumy podatków do zapłacenia przez klienta (jeszcze nie opłaconych)
    > ---

    > ---
    > Dodatkowa zawartość klas Person oraz Company:
    > - Atrybuty:
    >   - statyczne wektory wskazań na obiekty reprezentujące poszczególne podatki (jeden wektor dla wszystkich instancji, inicjalizowany przy powstaniu pierwszego obiektu danej klasy, niszczony(razem z obiektami podatków) przy usunięciu jedynej instancji klasy)
    >   - liczniki ilości istniejących instancji (do obsługi w/w wektora)
    >  - Metody:
    >    - implementacja abstrakcyjnych metod z klasy bazowej
    >    - metody do obsługi wektora wskazań na podatki
    >    - wypisywanie informacji o obiekcie do strumienia
- ## TaxSystem
    > Klasa reprezentująca docelowy system podatkowy  
    > Zawartość klasy:
    > - Atrybuty:
    >   - wektor wskazań na klientów
    >   - current_income_ID przechowujące numer ID dla następnego dodanego wpływu
    > - Metody:
    >   - "getter" do wektora wskazań na klientów
    >   - destruktor usuwający obiekty klientów
    >   - dodanie wpływu (przekazywane ID klienta, wysokość wpływu i rodzaj podatku (wskazanie na podatek))
    >   - szukanie klienta po jego ID
    >   - szukanie klienta po ID wpływu
    >   - usuwanie klienta po ID
    >   - dodawanie klienta (przekazywane wskazanie na klienta, sprawdzanie, czy klient o danym ID już istnieje(błąd))
    >   - wyliczenie łącznej sumy podatków do zapłacenia przez wszystkich klientów

## 2.2 Dodatkowe elementy projektu
> --- 
> Dodatkowe elementy zaimplementowane do obsługi klas oraz aplikacji:
> - Enumeratory podatków oraz wydarzeń w aplikacji
> - Zapis i odczyt do pliku w formacie JSON (biblioteka nlohmann)
> - Mapy przejścia ze stringa na enumerator

  

## 2.3 Aplikacja
### Aplikacja do systemu podatkowego zaimplementowana w terminalu  
### Możliwe opcje:
- Dodanie klienta (wybór firma/osoba, nazwa, ID)
- Usunięcie klienta po ID
- Dodanie wpływu (wybór klienta, wielkości wpływu oraz rodzaju podatku)
- Wyszukanie klienta i wyświetlenia informacji o nim
- Zapisanie i wczytywanie z pliku w formacie JSON
- Zaznaczenie podatku od wpływu jako zapłacony (po ID wpływu)
