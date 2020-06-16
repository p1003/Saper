Chciałbym przedstawić mój projekt pod tytułem Saper.

Jest to w pełni funkcjonalna wersja gry.
Występują pojedyncze bugi, którymi zajmę się w wolnej chwili.

Menu startowe:

Po uruchomieniu programu otwiera się okienko menu w którym można wybrać tryb gry.
Naciśnięcie którejkolwiek buźki albo piaskownicy powoduje zamknięcie menu i otworzenie okna gry.
Zielona buźka - poziom łatwy 8x8 i 10 bomb.
Żółta buźka - poziom normalny 16x16 i 46 bomb.
Czerwona buźka - poziom trudny 32x32 i 205 bomb.
Piaskownica generuje sapera z poniższymi wartościami.

Wartości przyjmowane przez piaskownice Można zmieniać w granicach odgórnie narzuconych:
Szerokość od 8 do 50.
Wysokość od 5 do 32.
Bomby od 1 do Szerokość * Wysokość.

Okno gry:

Naciśnięcie pierwszego pola planszy startuje czasomierz.
Naciśnięcie danego pola lewym przyciskiem myszy na planszy powoduje odsłonięcie go.
W przypadku trafienia na bombę pokazują się wszystkie bomby i gra się kończy.
Po trafieniu bomby przegrywamy.
Wygrywamy po odsłonięciu wszystkich pól na których nie ma bomb.
Jeśli wiemy, gdzie znajduje się bomba, na dane pole klikamy prawym przyciskiem myszy i pole staje się oflagowane.
Maksymalna liczba flag do postawienia jest równa ilości bomb.
Po zakończeniu gry (wygrana lub przegrana) czas się zatrzymuje.

Koniec gry:

Po zakończeniu rozgrywki możemy zamknąć okno, wtedy ponownie otworzy się okno menu lub nacisnąć martwą buźkę, żeby zrestartować grę z tymi samymi ustawieniami.

Program kończy swoje działanie po zamknięciu okna menu (jeśli gra trwa należy najpierw zamknąć okno gry)
