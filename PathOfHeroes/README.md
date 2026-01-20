# Gra w konsoli (C++)

Projekt prostej gry RPG w konsoli napisanej w C++.
Gra umo¿liwia walkê turow¹ z losowym przeciwnikiem,
wyœwietlanie ASCII-artów oraz zapis raportu walki do pliku.

## Funkcjonalnoœci
- wczytanie przeciwników i ich statystyk z pliku txt
- losowy przeciwnik (Goblin / Orc / Skeleton)
- walka turowa Player vs Enemy
- losowanie statystk przeciwników (ka¿da gra jest inna)
- ASCII-art przeciwników
- zapis raportu walki do pliku

## Struktura projektu
- `Game.cpp` – logika gry i walki
- `Character` – klasa bazowa postaci
- `Player` – gracz
- `Enemy` – przeciwnicy + EnemyType
- `FileManager` – obs³uga plików
- `AsciiArt` – wczytywanie ASCII
- `Resource Files/` – pliki txt (enemies, ascii)

## Autorzy
- Wojciech Zamêta 
- Mateusz Zaborowski
- Eryk ¯muda