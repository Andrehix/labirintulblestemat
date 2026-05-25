# Labirintul Blestemat

Un joc text-based in care esti un explorator blocat intr-un labirint intunecat. Ai o lanterna cu baterie limitata, niste obiecte imprastiate pe harta si cativa inamici care se plimba aiurea. Trebuie sa gasesti cheia, apoi sa ajungi la iesire. Daca ramai fara energie sau te prinde vreun inamic, ai pierdut. Daca ajungi la iesire fara cheie, tot ai pierdut, ca usa e incuiata. 

## Cum se joaca

Controalele se dau de la tastatura, cate o litera pe tura:

- w, a, s, d — miscare (sus, stanga, jos, dreapta)
- e — foloseste primul obiect din inventar (ca sa recuperezi energie)
- t — teleportor (doar daca ai gasit unul, te arunca aleator pe harta)
- q — abandon

Pe harta apar simboluri:

- J — tu (jucatorul)
- C — Chaser (te urmareste direct)
- F — Fantoma (se misca haotic)
- G — Gardian (patruleaza, dar te urmareste daca esti prea aproape)
- L — Mimic (arata ca loot, dar e un inamic nemiscat care te ataca daca treci peste el)
- B — Baterie (recuperezi energie)
- E — Elixir (recuperezi mai multa energie)
- P — Teleportor (un obiect rar, foarte util)
- K — Cheia (obligatorie ca sa poti iesi)
- T — Capcana (pierzi energie)
- D — Iesirea (destinatia finala)
- # — Zid (nu treci prin el)
- ? — Celula nevazuta (ceata de razboi)

Castigi daca ajungi la iesire cu cheia in posesie. Pierzi daca ramai fara energie sau daca vreun inamic ajunge pe aceeasi pozitie cu tine. La final primesti un scor in functie de energia ramasa.

Jocul tine un istoric al evenimentelor prin Observer pattern (LoggerJoc): fiecare obiect cules, capcana activata sau cheie gasita este inregistrata.

## Structura proiectului

```
include/            — headerele
  Obiect.h          — clasa de baza pentru iteme
  Inventar.h        — rucsacul cu capacitate limitata
  Harta.h           — labirintul propriu-zis (BFS pentru verificare drum)
  Jucator.h         — exploratorul
  VanatorAI.h       — baza abstracta pentru inamici (virtual pur)
  Chaser.h          — inamic care urmareste direct jucatorul
  Fantoma.h         — inamic care se misca aleatoriu
  Gardian.h         — inamic care patruleaza, ataca doar in raza
  Mimic.h           — inamic static deghizat in loot
  MotorJoc.h        — engine-ul jocului (bucla principala + Observer/SubiectEvenimente)
  ConfiguratorJoc.h — Singleton pentru setari
  FactoryInamici.h  — Factory Method + template pentru creat inamici
  ManagementResurse.h — clasa sablon (template) pentru colectii
  Exceptii.h        — ierarhia de exceptii (7 clase, 2 ramuri)
  GeneratorRandom.h — Singleton pentru generatorul de numere aleatoare
  ObserverJoc.h     — interfata Observer
  LoggerJoc.h       — implementare Observer pentru logare evenimente
  SubiectEvenimente.h — clasa de baza pentru subiectul observabil
src/                — implementarile
assets/             — fisiere de configurare
  config_joc.txt    — setari (dimensiune harta, energie, numar inamici)
  config_joc.json   — aceleasi setari in format JSON (biblioteca externa)
  inamici.txt       — lista de inamici (tip, coordonate, parametri)
ext/                — biblioteci externe (nlohmann/json, fmt)
```
