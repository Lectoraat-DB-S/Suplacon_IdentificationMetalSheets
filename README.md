# Identificatie en Detectie Metaalplaten (IDM) <img src="https://github.com/user-attachments/assets/e7c92833-1d47-47f4-a2fb-d34824f52796" width="50" height="50"/> <img src="https://github.com/user-attachments/assets/78b8f6cd-a2cb-4590-8b41-225efad372bc" width="50" height="50"/>
Project IDM is in samenwerking met [Suplacon](https://suplacon.com/over-ons/) te Emmeloord uitgevoerd. Deze repository bevat code voor het lezen van nummers op metalen platen bij Suplacon.

## Benodigde software
- MVTec HALCON 23.11 Progress Student Edition 
- Visual Studio 2019
- GitHub Desktop
- Git
- Python 3.10
- CMake
- Open62541pp

### Installatiestappen
Stappenplan voor het installeren van de benodigde software

#### HALCON
1. Vraag als student een activatietoken aan: [Request-Form-Student](https://www.mvtec.com/company/mvtec-on-campus/licenses/student/request-form-student)
2. Doorloop de volgende studenthandleiding: [Manual-For-Students](https://go.mvtec.com/acton/attachment/43208/f-8e7a684d-596d-4852-a07e-1e08c28b31b0/1/-/-/-/-/Campus%20manual%20for%20students_EN.pdf)
3. Installeer alle beschikbare packages.

#### Visual Studio 2019
1. Installeer Visual Studio 2019
1. Selecteer en installeer workload *'Desktop development with C++'*
2. Indien nodig, start de PC opnieuw op.

#### GitHub Desktop
1. Installeer GitHub Desktop
2. Clone deze repository

#### Git
1. Installeer Git

#### Python
1. Installeer Python 3.10

#### CMake
1. Installeer CMake

#### Open62541pp
1. Navigeer binnen GitHub Desktop naar: *'Repository'*->*'Open in Command Prompt'*.
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
4. Start *'open62541++.sln'* met Visual Studio
5. Navigeer binnen Visual Studio naar *'Build'*->*'Build'*->*'PACKAGE'*

**N.B.** Na het bouwen staan de volgende twee errors in de *'Error List'* van Visual Studio: *'Could not create CPack generator: RPM'* en *'The command "setlocal...'*. Dit kan geen kwaad voor het succesvol runnen van de code.

# Testen code
Doorloop de volgende stappen om de correcte werking van de code te valideren:

1. Navigeer in Windows Verkenner naar (REPO_ROOT)\Fotoanalyses_Application
2. Start *'Vision_Systeem.sln'* met Visual Studio
3. Run het project

In de console verschijnt bij een correcte werking de onderstaande tekst:
![Output_Testen_Software](https://github.com/user-attachments/assets/965860c5-22f3-42df-bb8f-9ce35500d1de)


# Testen camera
1. Plug een [Basler acA1280-60gm](https://www.baslerweb.com/en/shop/aca1280-60gm/) camera in via een Gigabit Ethernet poort van de PC
2. Navigeer binnen Visual Studio naar *'Fotoanalyse_Settings.h'*
3. Verander ```#define USING_CAMERA false``` in ```#define USING_CAMERA true```
4. Run het project

De gemaakte foto's komen te staan in (REPO_ROOT)\Fotoanalyses_Application


