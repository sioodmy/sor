# SOR Symulacja

Celem projektu jest stworzenie symulacji dyskretnej, która pozwala obserwować, jak zmienia się obciążenie oddziału ratunkowego w czasie. Model umożliwia odpowiedź na kilka
prostych pytań badawczych:

- ile pacjentów dociera do SOR-u w zadanym okresie,
- jak rośnie kolejka oczekujących,
- ile gabinetów jest jednocześnie zajętych,
- ile osób zostaje ostatecznie wyleczonych.

## Zakres funkcjonalny
Program realizuje następujące zadania:
- wczytanie parametrów symulacji z pliku konfiguracyjnego config.ini,
- losowe generowanie pacjentów o różnych typach klinicznych,
- triaż wykonywany przez pielęgniarkę (przypisanie priorytetu),
- kolejkowanie pacjentów w poczekalni według priorytetu,
- leczenie w gabinetach konsultacyjnych prowadzonych przez lekarzy,
- symulację pogorszenia stanu pacjentów oczekujących (zależnie od typu),
- logowanie stanu systemu do pliku CSV po każdym kroku czasowym,
- wizualizację wyników w panelu Streamlit.
