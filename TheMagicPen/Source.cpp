#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void AddText(char** CurrentTxt);
void UpdateText(char** CurrentTxt);
void DeleteText(char** CurrentTxt);
void PrintText(char** CurrentTxt);
void WriteToFile(char** CurrentTxt);

 //-----------------------------------------------------------------------------
 // The Magic Pen
 // ---------------
 // כללי: הפעולה יוצרת תפריט למשתמש שבה הוא בוחר בין פונקציות הפועלות על מחרוזת
 //
 // קלט: מספר הפעולה מהמשתמש, לאחר הקשת המספר הפעולה שהמשתמש לחץ עלייה תתבצע
 //
 // פלט: תלוי בפעולה שהמשתמש לחץ עלייה 
 //-----------------------------------------------------------------------------
 // מתכנת: ינון רפאלי
 // תעודת זהות: 216689711
 // תאריך: 03.12.25
 //-----------------------------------------------------------------------------

void main()
{
    int button = 0;
    // מאתחל את הטקסט 
    char* CurrentTxt = NULL;

    // תפריט למשתמש שכל פעולה עושה משהו אחר  
    while (1)
    {
        printf("\nChoose What To Do:\n");
        printf("1. Add Text\n");
        printf("2. Update Text\n");
        printf("3. Delete Text\n");
        printf("4. Print\n");
        printf("5. Save To File\n");
        printf("6. Exit\n");

        scanf("%d", &button);

        switch (button)
        {
        case 1:
            AddText(&CurrentTxt);
            break;
        case 2:
            UpdateText(&CurrentTxt);
            break;
        case 3:
            DeleteText(&CurrentTxt);
            break;
        case 4:
            PrintText(&CurrentTxt);
            break;
        case 5:
            WriteToFile(&CurrentTxt);
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Invalid.\n");
            break;
        }
    }
}

// מוסיף טקסט לטקסט הישן או יוצר טקסט
void AddText(char** CurrentTxt)
{
    int length;
    char* temp;

    // קולט את גודל הטקסט שהמשתמש רוצה לכתוב
    printf("Enter Text Length: ");
    scanf("%d", &length);

    // יוצר הקצאה זיכרון לקליטת הטקסט מהמשתמש 
    temp = (char*)malloc((length + 1) * sizeof(char));

    printf("Enter The Text: ");
    scanf("%s", temp);

    // בודק האם זה הפעם הראשונה שמוסיפים טקסט
    if (*CurrentTxt == NULL)
    {
        *CurrentTxt = (char*)malloc((length + 1) * sizeof(char));
        strcpy(*CurrentTxt, temp);
    }
    // אם יש טקסט אז מגדילים את הזיכרון של הטקסט הישן עם הגודל של החדש
    else
    {
        int newsize = length + strlen(*CurrentTxt) + 1;
        *CurrentTxt = (char*)realloc(*CurrentTxt, newsize);
        // שרשור של הטקסט הישן עם הטקסט החדש של המשתמש
        strcat(*CurrentTxt, temp);
    }
    free(temp);
}

// מעדכן את הטקסט מאינדקס שהמשתמש נתן
void UpdateText(char** CurrentTxt)
{
    int index, count = 0;
    char* temp;

    printf("Enter The Starting Index To Update: ");
    scanf("%d", &index);

    // בודק האם טקסט כבר קיים
    if (*CurrentTxt == NULL)
    {
        printf("Nothing To Update\n");
        return;
    }

    // בודק את התחום של האינדקס שהמשתמש נתן שלא יצא מהתחום של גודל הטקסט
    if (index < 0 || index >(int)strlen(*CurrentTxt))
    {
        printf("Out Of Bounds\n");
        return;
    }

    printf("Enter The Number Of Chars To Update: ");
    scanf("%d", &count);

    // יוצר הקצאת זכרון לטקסט שהמשתמש כתב
    temp = (char*)malloc((count + 1) * sizeof(char));

    printf("Enter The Text: ");
    scanf("%s", temp);

    for (int i = 0; i < count; i++)
    {
        if (temp[i] == '\0')
            break;

        (*CurrentTxt)[index + i] = temp[i];
    }
    free(temp);
}

// מוחק מהטקסט כמות תווים שהמשתמש נתן
void DeleteText(char** CurrentTxt)
{
    int amount;

    // בודק האם יש טקסט קיים כבר
    if (*CurrentTxt == NULL)
    {
        printf("No Text To Delete\n");
        return;
    }

    int CurrentLength = strlen(*CurrentTxt);

    printf("Enter Amount Of Chars To Delete: ");
    scanf("%d", &amount);

    // בודק האם הכמות תווים שהמשתמש כתב לא קטן או שווה לאפס
    if (amount <= 0)
        return;

    // מכניס נאל טרמינייטור בכמות תווים מהסוף בשביל למחוק הכל
    (*CurrentTxt)[CurrentLength - amount] = '\0';

    // אם מחקנו את כל הטקסט אז משחררים את הזכרון הקיים
    if (CurrentLength - amount == 0)
    {
        free(*CurrentTxt);
        *CurrentTxt = NULL;
    }
    // אם לא אז מקטינים את גודל הטקסט
    else
    {
        *CurrentTxt = (char*)realloc(*CurrentTxt, (CurrentLength - amount + 1) * sizeof(char));
    }
}
    
// מדפיס את הטקסט שנכתב עד כה
void PrintText(char** CurrentTxt)
{
    // בודק האם יש בכלל טקסט קיים
    if (*CurrentTxt == NULL)
    {
        printf("There Is No Text To Print\n");
        return;
    }

    int length = strlen(*CurrentTxt);

    // עובד בלולאה על כל הטקסט שנכתב עד כה ומדפיס אותו
    for (int i = 0; i < length; i++)
    {
        printf("%c", (*CurrentTxt)[i]);
    }
    printf("\n");

}

// כותב את כל הטקסט שנכתב עד כה לקובץ
void WriteToFile(char** CurrentTxt)
{
    char name[1000];
    FILE* fp;

    // בודק האם יש טקסט קיים כרגע
    if (*CurrentTxt == NULL)
    {
        printf("There Is No Text That Can be Written To The File\n");
        return;
    }

    printf("Choose A Name For Your File: ");
    scanf("%s", name);

    fp = fopen(name, "wt");
    // בדיקה האם הקובץ נפתח
    if (fp == NULL)
    {
        printf("File Couldnt Open.\n");
        return;
    }

    // כותב לקובץ את הטקסט
    fprintf(fp, "%s", *CurrentTxt);
    fclose(fp);
}