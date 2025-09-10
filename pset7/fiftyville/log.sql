-- Keep a log of any SQL queries you execute as you solve the mystery.

-- usando o codigo:
SELECT description
   ...> FROM crime_scene_reports
   ...> WHERE month = 7 AND day = 28; --vemos quais crimes ocorreram no dia 28 de julho

-- o patinho foi roubado na Humphrey Street bakery as 10:15 da manha, 3 testemunhas presentes

SELECT activity
   ...> FROM bakery_security_logs
   ...> WHERE month = 7 AND day = 28 AND hour = 10;

+----------+
| activity |
+----------+
| entrance |
| entrance |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| exit     |
| entrance |
| entrance |
| entrance |
+----------+

sqlite> SELECT license_plate
   ...> FROM bakery_security_logs
   ...> WHERE month = 7 AND day = 28 AND hour = 10 AND minute IN (14, 15, 16);

+---------------+
| license_plate |
+---------------+
| 13FNH73       |
| 5P2BI95       |
+---------------+
