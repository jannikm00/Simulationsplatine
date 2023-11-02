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
[Youtube](https://www.youtube.com/shorts/GwFtLFMLBFg)

3D-Modelle:
[Propeller](https://www.thingiverse.com/thing:5759720),
[Heizung](https://www.thingiverse.com/thing:5759743),
[Pumpe](https://www.thingiverse.com/thing:1045003) und
[Motorkasten](https://www.thingiverse.com/thing:6028704)

![simulationsplatine-1](https://github.com/jannikm00/Simulationsplatine/assets/72359748/a6111278-5352-410b-a640-0d669bc0cccd)
![simulationsplatine-2](https://github.com/jannikm00/Simulationsplatine/assets/72359748/af946f0b-1c59-4bb1-91e8-3118eea84a6b)
![simulationsplatine-3](https://github.com/jannikm00/Simulationsplatine/assets/72359748/67e134e4-173d-4697-a63e-ac77a48a0314)
![simulationsplatine-4](https://github.com/jannikm00/Simulationsplatine/assets/72359748/4c7b6bb0-a935-4775-af69-0c3818892e8a)
![simulationsplatine-5](https://github.com/jannikm00/Simulationsplatine/assets/72359748/3acb1029-d664-47ce-9e06-05edfb09ce90)
![simulationsplatine-6](https://github.com/jannikm00/Simulationsplatine/assets/72359748/c99b9c63-fa8f-43f1-8caa-ae05a726fa7a)
![simulationsplatine-7](https://github.com/jannikm00/Simulationsplatine/assets/72359748/d9b07b1d-4720-4f11-952e-8ef7593f69df)



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
![IMG_20230921_143559911](https://github.com/jannikm00/Simulationsplatine/assets/72359748/461867c5-9adc-48e3-a3d8-57e750ccab11)
![IMG_20230921_143540485](https://github.com/jannikm00/Simulationsplatine/assets/72359748/cd63eca4-9788-4cf5-b987-6372ed7be05b)
![IMG_20230928_114233787](https://github.com/jannikm00/Simulationsplatine/assets/72359748/a5415738-9185-4cc5-ac45-4e8735803692)
![IMG_20230928_114030302](https://github.com/jannikm00/Simulationsplatine/assets/72359748/afa0ae1d-e45c-4629-95fd-fe59207334a3)
![IMG_20230928_114151827](https://github.com/jannikm00/Simulationsplatine/assets/72359748/bd15ba51-dcc7-4e60-9fa8-adf7a63bf1fa)



