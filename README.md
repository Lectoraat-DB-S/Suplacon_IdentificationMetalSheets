# Identification Metal Plates (IDM) 🦾
Vision system for reading codes on metal plates!
This project is done in cooperation with Suplacon in Emmeloord.

## Benodigde software
- MVTec HALCON 23.11 Progress Student Edition 
- Visual Studio 2019
- GitHub Desktop
- Git
- Python 3.10
- CMake
- Open62541pp

### Installatiestappen
Stappenplan voor installeren benodigde software
#### HALCON
1. Vraag als student een activatietoken aan: [Request-Form-Student](https://www.mvtec.com/company/mvtec-on-campus/licenses/student/request-form-student)
2. Doorloop de volgende studenthandleiding: [Manual-For-Students](https://go.mvtec.com/acton/attachment/43208/f-8e7a684d-596d-4852-a07e-1e08c28b31b0/1/-/-/-/-/Campus%20manual%20for%20students_EN.pdf)
3. Installeer alle beschikbare packages.

#### Visual Studio 2019
1. Selecteer en installeer workload *'Desktop development with C++'*
2. Indien nodig, start de PC opnieuw op.

#### GitHub Desktop
1. Installeer
2. Clone deze repository

#### Git
1. Installeer Git

#### Python
1. Installeer Python 3.10

#### CMake
1. Installeer CMake

#### Open62541pp
1. Navigeer binnen GitHub Desktop naar: 'Repository'->'Open in Command Prompt'.
2. Build de *open62541pp* repository met de volgende opdrachten:
```
# navigate
cd open62541pp

# build
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DUAPP_BUILD_EXAMPLES=ON -DUAPP_BUILD_TESTS=ON ..
cmake --build . --config Release

# run tests
ctest --output-on-failure
```
3. Navigeer in Windows Verkenner naar (REPO_ROOT)\open62541pp\build
4. Start 'open62541++.sln' met Visual Studio
5. Navigeer binnen Visual Studio naar 'Build'->'Build'->'PACKAGE'

**NB** Na het bouwen staan de volgende twee errors in de Error List van Visual Studio: 'XXX' en 'XXX'. Dit kan geen kwaad voor het succesvol runnen van het Vision Systeem.

## Testen software
Doorloop de volgende stappen om de correcte werking van het project te valideren:
1. Navigeer in Windows Verkenner naar (REPO_ROOT)\Fotoanalyses_Application
2. Start 'Vision_Systeem.sln' met Visual Studio
3. Run het project
Dit is de verwachte uitkomst bij een correcte werking: Plaatjes & toelichting juiste output

# Testen camera
1. Plug de camera in via USB poort
2. Navigeer binnen Visual Studio naar Fotoanalyse_Settings.h
3. Verander 'USING_CAMERA false' naar 'USING_CAMERA true'
4. De gemaakte foto's komen te staan in (REPO_ROOT)\Fotoanalyses_Application


# template-repository 
codering
Tijdens het opleveren van code zien we graag dat er een README bestand wordt meegeleverd, dit maakt het gemakkelijker voor een ander om met jouw code verder te gaan of er gebruik van te maken.
Deze README beschrijft het project, wat je nodig hebt om de code te gebruiken en hoe je de code kunt gebruiken. Uiteraard kan dit ietsje afwijken aan de hand van welke taal je hebt geprogrammeerd, maar blijf het liefst zo dicht bij mogelijk bij deze standaarden.

De volgende dingen zien we graag in een README:
- beschrijving: graag zien we een korte beschrijving van je project. dus een korte uitleg wat je code doet als je het gebruikt.
- imports en versies: graag zien we een lijst met alle imports, packages, software, etc die je hebt gebruikt met de versies. Denk hierbij aan je python versie, dat je iets met "pip install" hebt geinstalleerd of dat je ubuntu 23.04 als operating system hebt gebruikt (dus ook welke versie je hebt geinstalleerd). (test dus ook je code op een andere laptop!!! hierdoor weet je zeker dat je alles genoteerd hebt)
- architectuur: graag zien we een korte beschrijving van de architectuur van je project. welke bestanden hebben welke bestanden nodig en wat kun je in welk bestand vinden.
- reference: graag zien we een lijst met welke code je niet zelf hebt gemaakt of gebaseerd hebt op een ander zijn code met daarbij een link naar de originele code en een datum waarop je die code hebt geraadpleegd. Dit zorgt ervoor dat de juiste mensen credit krijgen. (let op, ook als je een functie ergens vandaan haalt en aanpast hoor je nog steeds te zeggen wie daar credit voor krijgt).
- usage: op het moment dat je extra hardware zoals een robot gebruikt is het fijn als er ook iets uitgelegd wordt over hoe je alles hebt aangesloten en opgestart. Misschien is het wel van belang dat je eerst het programma op de cobot start voordat je de python code op je laptop start.

- commenting: in code is het vrij normaal om comments te gebruiken om je code duidelijker te maken. Graag zien we dan ook dat dit gedaan wordt.
	- functie beschrijving: Liefst zien we dat er per functie met een comment uitgelegd wordt hoe de functie werkt en waarvoor ie bedoeld wordt (dit kan vaak in 1 zin). mocht de functie lang zijn dan zien we ook graag comments tussendoor.
	- Bestand beschrijving: Liefst zien we bovenaan elk bestand dat er een korte beschrijving staat van welke functies er in het bestand geprogrammeerd zijn.
	- Variabele beschrijving:

Een ReadMe schrijf je in Markdown. in de volgende link vind je wat voorbeelden over hoe je deze kunt stylen:
https://github.com/lifeparticle/Markdown-Cheatsheet

mocht je wat inspiratie willen kun je op de github hieronder even kijken.
https://github.com/matiassingers/awesome-readme

https://integrity.mit.edu/handbook/academic-integrity-handbook
