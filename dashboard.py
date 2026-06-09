import pandas as pd
import streamlit as st

st.set_page_config(page_title="Panel Symulacji SOR", layout="wide", page_icon="🏥")

st.title("Wizualiazja symulacji SOR")
st.markdown(
    "Ten panel wizualizuje dynamiczne dane wyjściowe wygenerowane przez symulację Triage w C++."
)

try:
    df = pd.read_csv("output/simulation.csv")

    if df.empty:
        st.warning("Dane symulacji są puste.")
    else:
        st.markdown("### Kluczowe Metryki Symulacji")
        col1, col2, col3, col4 = st.columns(4)

        total_time = df["Minute"].iloc[-1]
        total_treated = df["TotalTreated"].iloc[-1]
        peak_waiting = df["WaitingPatients"].max()
        peak_rooms = df["OccupiedRooms"].max()

        col1.metric("Całkowity Czas Symulacji", f"{total_time} min")
        col2.metric("Suma Wyleczonych Pacjentów", total_treated)
        col3.metric("Szczytowa Kolejka (Oczekujący)", peak_waiting)
        col4.metric("Szczytowe Obłożenie Gabinetów", peak_rooms)

        st.divider()

        st.markdown("### Analiza Szeregów Czasowych")
        chart_col1, chart_col2 = st.columns(2)

        with chart_col1:
            st.subheader("Oczekujący Pacjenci w Czasie")
            st.markdown(
                "Pokazuje, jak kolejka priorytetowa zapełnia się z upływem czasu."
            )
            st.line_chart(df.set_index("Minute")["WaitingPatients"], color="#FF4B4B")

            st.subheader("Skumulowana Liczba Wyleczonych Pacjentów")
            st.markdown("Pokazuje całkowitą przepustowość oddziału ratunkowego.")
            st.area_chart(df.set_index("Minute")["TotalTreated"], color="#00C213")

        with chart_col2:
            st.subheader("Obłożenie Gabinetów Lekarskich")
            st.markdown(
                "Pokazuje, ile gabinetów jest obecnie zajętych przez lekarza badającego pacjenta."
            )
            st.line_chart(df.set_index("Minute")["OccupiedRooms"], color="#0074E4")

            st.subheader("Eksport Surowych Danych")
            st.markdown(
                "Dokładne metryki danych pobrane z pliku `.csv` w każdym kroku."
            )
            st.dataframe(df, use_container_width=True)

except FileNotFoundError:
    st.error("Nie znaleziono pliku z symulacji")
