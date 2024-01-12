
## TODO

### Hauptziele
* [x] Map parsing
* [ ] Basic rendering nur Farben
* [ ] Movement
* [ ] Textures

### Bugs

* [ ] Map parsing Segfault fixen bei tabs/leerzeichen nachpfad

---

Notes:
* Nur neu rendern wenn der spieler sich bewegt hat oder umgeschaut hat. (Nach keyhook).


---

MAP:

* wenn eine zelle um sich ein leer hat dann muss es eine wand sein
* es muss genau ein n s w oder e geben

-1 für leerzeichen
0 boden
1 wand
N S W E spieler