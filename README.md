# Smartwach

Pomysł:

Stworzyć uniwersalne narzędzie do napisania i testowania algorytmów do wykrywania  aktywności czlowieka i interakcji z nim w wygodny sposób.

Ponadto jednym z zadań urządzenia jest przekwalifikowanie się ze smartwatcha na narzędzie sportowe.
Np. rowerzysta – zegar jest montowany na kierownicy, łączy czujniki rytmu i prędkości, prędkość wiatru, akcelerometr przez bluetooth. za pomocą którego można absolutnie dokładnie opisać rowerzystę, jaką moc wykonuje w jakim czasie, jak reaguje na podjazdy i zjazdy.

Zadania sprzętowe:
   - Moduł GPS.
   - Układ do pomiaru zużycia energii elektrycznej, do obliczenia dokładnego czasu pracy.
_____________________________
Dobór komponentów elektronicznych w czasach trudnej dostępności w magazynach:

Mikrokontroler: nRF52840 
   - Wbudowany BLE co pozwala w pełni komunikować się ze smartfonem lub czujnikami pomocniczymi.
   - 32Mhz SPI, co pozwala szybko zaktualizować ekran.
   - Bardzo niskie zużycie energii w porównaniu do innych firm.

Ze względu na małą dostępność chipów na rynku lub zawyżoną cenę używam modułu firmy EBYTE E73-2G4M08S1C, który posiada chip, niezbędne części do pracy oraz antenę.

Сzujniki:
   -BMP280 pozwala zmierzyć temperaturę i ciśnienie atmosfery z dość dużą dokładnością.
   -MPU9250 3-osiowy akcelerometr, żyroskop i magnetometr.
   -MAX30100 czujnik tętna i saturacji (montowany na obudowie)
   -APDS-9960 czujnik światła, a także narzędzie do wykrywania gestów, za pomocą którego można sterować urządzeniem

Za pomocą tych dwóch czujników można dość dokładnie odczytać aktywność człowieka.
Przykład:
   -liczba wykonanych kroków + pod jakim kątem do horyzontu.
   -różne aktywności fizyczne: bieganie, jazda na rowerze, pływanie itp.

Wersja 0.9 jest stworzona do sprawdzania czujników, napisania testowego firmware w celu sprawdzenia funkcjonalności juz v1.0 PCB. 
Również w celu sprawdzenia stabilności połączeń Bluetooth i algorytmów obliczania aktywności.





_____________________________

V0.9

![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/2d%20v_0.9(prot).jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/3d%20v_0.9(prot).jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/photo1%20v_0%2C9(prot).jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/photo2%20v_0%2C9(prot).jpg)


Praca BLE VIDEO: https://youtu.be/vYCpAYbpFlk

_____________________________

V1.0 Oczekiwanie na dostawę PCB i elementów elektronicznych...

![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/2d%20v_1.0.jpg)


![Alt Text](https://github.com/mrGrodzki/Smartwach/blob/main/HW/3d%20v_1.0.jpg)

_____________________________


