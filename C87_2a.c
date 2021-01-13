#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define hh_mm 4

int main(void)
{
    FILE *Data;                                             //Dateideskriptor 
    char Buffer [15];                                       //temporärer Speicher zum Zeilenweisen einlesen
    char Arbeitszeiterfassung[2][5];                        //2-Dimensionaler Array [2]Felder je[4]Chars
    float Anwesenheitszeit = 0.0;                               //Zur ermittlung und ausgabe

    printf("<ARBEITSZEITERFASSUNG AUS C87A>\n");

    //Absoluterpfad zur Datei "\" doppelt um nicht als steuerzeichen zu interpretieren
    Data = fopen("C:\\Projekte\\C\\C87\\arbeitszeit.txt","rb");             //"rb" r =read also lesend oeffnen, b= binary. Wir wollen ja eh nur die Bytes einlesen keine Textformatierung 

    if (Data != NULL)   //Dateideskriptor ist auf einer Adresse also ungleich NULL
    {
        //Datei ueber den Dateideskriptor (Data) einlesen, lese einen String + LF(Windows LF/CR), speichere den Inhalt in die Adresse von Buffer.
        while (fscanf(Data, "%s\n", &Buffer) != EOF)        //Lese bis EOF (endoffile) eingelesen wurde, definiert -1
        {  
            //Speicherbereich muss abgelöscht bzw. initialisiert werden, memcpy trägt nur ein. Dazu memset (Ziel, Wert, Laenge/größe in Byte(siezof ist Standart dazu))
            memset(&Arbeitszeiterfassung[0][0],0, sizeof(Arbeitszeiterfassung[0]));
            memset(&Arbeitszeiterfassung[1][0],0, sizeof(Arbeitszeiterfassung[1]));
            
            //Speicherbereich binaer kopieren. Ziel, Groeße des Zieles, von bzw. target, anzahl definiert siehe Zeile 6
            memcpy_s(&Arbeitszeiterfassung[0][0],sizeof(Arbeitszeiterfassung[0]),&Buffer[6],hh_mm);
            memcpy_s(&Arbeitszeiterfassung[1][0],sizeof(Arbeitszeiterfassung[0]),&Buffer[10],hh_mm);
            
            //Ausgaben 
            printf("Arbeitsbeginn: %s -- Arbeitsende: %s\n",Arbeitszeiterfassung[0], Arbeitszeiterfassung[1]);
            //Ascii TO Interger 
            Anwesenheitszeit = atoi(Arbeitszeiterfassung[1]) - atoi(Arbeitszeiterfassung[0]);
            //Differenz auf Minuten umrechnen
            Anwesenheitszeit = (Anwesenheitszeit /100) * 60;
            printf("Anwesenheitszeit = %0.0f\n",Anwesenheitszeit);

        }
        fclose(Data);                                           //Datei schließen, nie vergessen leute
        Sleep(2000);                                            //windwos.h
    }else
    {
        printf("nope\n");
        perror(NULL);                                           //Wenn Datei nicht geöffnet werden konnte gib fehlermeldung auf stderror aus
    }
    

    

}