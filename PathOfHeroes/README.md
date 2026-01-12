# Gra w konsoli (C++)

Projekt prostej gry RPG w konsoli napisanej w C++.
Gra umo¿liwia walkê turow¹ z losowym przeciwnikiem,
wyœwietlanie ASCII-artów oraz zapis raportu walki do pliku.

## Funkcjonalnoœci
- losowy przeciwnik (Goblin / Orc / Skeleton)
- walka turowa Player vs Enemy
- skalowanie statystyk przeciwnika po levelu gracza
- ASCII-art przeciwników
- zapis raportu walki do pliku

## Struktura projektu
- `Game.cpp` – logika gry i walki
- `Character` – klasa bazowa postaci
- `Player` – gracz (level, exp)
- `Enemy` – przeciwnicy + EnemyType
- `FileManager` – obs³uga plików
- `AsciiArt` – wczytywanie ASCII
- `resources/` – pliki txt (enemies, ascii)

## Autorzy
- Wojciech Zamêta – logika gry, walka, balans
- Mateusz Zaborowski – pliki, zasoby, struktura
- Eryk ¯muda – dokumentacja, raport, organizacja
