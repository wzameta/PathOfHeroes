# Architektura projektu

## Character
Klasa bazowa zawieraj¹ca HP, AP oraz metody isAlive(), takeDamage().

## Player
Dziedziczy po Character.
Zawiera level, exp oraz metodê gainExp().

## Enemy
Dziedziczy po Character.
Posiada EnemyType oraz metodê getAsciiArtPath().

## Game
Steruje przebiegiem gry:
- wczytuje przeciwników
- losuje enemy
- prowadzi walkê
- zapisuje raport
