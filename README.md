# Simulationsplatine
Simulations-Platine der AP Teil 1 Frühjahr 2022 Elektroniker für Betriebstechnik

WICHTIG:
Niemals mit angeschlossener 9V Batterie den Arduino mit einem PC verbinden
Nicht Widerstände kurzschließen

Pulldown Widerstände:
Spannungsteiler mit R1 = 10kOhm, R2 = 2,6kOhm

Bypass:
Bypass Pin (A5) auf High bringen (Schalter umlegen)
in void Bypass () gewünschte Sensorstellung, delay und was auch immer eingeben
Das Programm wird nichts machen, nur void Bypass () wird laufen
Will man nach Bypass Modus das normale Programm verwenden muss man Reset auf dem Arduino drücken
und die -S1 an und wieder aus machen

Programmablauf:
-S1 betätigen
Warten bis Heizung -E1 auf Temperatur
-S2 betätigen
Warten bis -M1 genug Druck aufgebaut hat
Warten bis der Sprühturm gefüllt ist -Ventil -M4 offen
-S3 betätigen
Warten bis der Sprühturm leer ist Förderschnecke -M3 Rechtslauf
(Optional: -S4 betätigen Förderschnecke -M3 Linkslauf)

Programmablauf ende:
Ist der Sprühturm entleert worden ist der Milchvorrat aufgebraucht, um ihn wieder zu befüllen 
muss man -S1 an und wieder aus machen oder den Reset Knopf auf dem Arduino betätigen

Video:
[OneDrive](https://teslamotorsinc-my.sharepoint.com/:v:/g/personal/jameiers_tesla_com/EWfWZ_1vczZIn2BTZ4c2_aIBz9P3oaltJH9rHhPaBXDcUQ?e=iOcd5x)

3D-Modelle:
[Propeller](https://www.thingiverse.com/thing:5759720),
[Heizung](https://www.thingiverse.com/thing:5759743),
[Pumpe](https://www.thingiverse.com/thing:4839) und
[Motorkasten](https://www.thingiverse.com/thing:6028704)

![image](https://github.com/jannikm00/Simulationsplatine/assets/72359748/ee48bddd-4f4d-479e-a79b-93b71e543304)
![image](https://github.com/jannikm00/Simulationsplatine/assets/72359748/48ea0c0c-f4d4-462e-9f71-ff79296fa3b2)

Nachfolgende Bilder sortiert alt zu neu:
![IMG_20230502_143259](https://user-images.githubusercontent.com/72359748/235667674-413427d6-76e5-45da-92e3-bc5e609134c4.jpg)
![IMG_20230502_143334](https://user-images.githubusercontent.com/72359748/235667682-f955ff6d-0cb8-44c8-9c63-67b8838b343b.jpg)
![IMG_0286](https://user-images.githubusercontent.com/72359748/236739008-77955bb5-66fb-41b1-887a-69eeff3da364.jpeg)
![IMG_0287](https://user-images.githubusercontent.com/72359748/236787044-71727af6-b92a-4585-8eb0-5de142fdc054.jpeg)
![image](https://user-images.githubusercontent.com/72359748/236829033-c9b3594d-17f7-47a6-9985-9c44b15eaa32.jpeg)
![image](https://user-images.githubusercontent.com/72359748/236829058-6bd225ee-e96b-4f57-a808-cc4fbe53402e.jpeg)
![IMG_20230511_125253](https://github.com/jannikm00/Simulationsplatine/assets/72359748/2afc9e6a-0887-4590-9ea8-de0c5748f7e8)
![IMG_20230511_125351](https://github.com/jannikm00/Simulationsplatine/assets/72359748/0cfbd4b1-da22-404a-9e61-6422eb57880f)
![IMG_0291](https://github.com/jannikm00/Simulationsplatine/assets/72359748/e35d2b30-ecdc-422d-a4f6-166d372e4e4f)



