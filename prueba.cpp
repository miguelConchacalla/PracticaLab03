/***************************************************************************/
#include "stdio.h"
#include "io.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "ctype.h"
#include <Windows.h>

#define MAXIMO 30
#define LON sizeof(BUFFER)
#define grabar(id, a) _write(id, (char *)&a, LON)
#define lea(id, a) _read(id, (char *)&a, LON)
#define ubicar(id, a) lseek(id, a *LON, SEEK_SET)
typedef struct BUFFER BUFFER;
typedef struct CARCEL CARCEL;
/***************************************************************************/

struct CARCEL
{
    long codigo;
    char nom_recluso[50];
};
/***************************************************************************/

struct BUFFER
{
    CARCEL carcel;
    long sig;
};
/***************************************************************************/

class CURSOR
{
    int global_id;

public:
    CURSOR()
    {
        global_id = init_archivo();
    };
    ~CURSOR()
    {
        unlink("lista");
    };
    /***************************************************************************/

    int pulsar() { return global_id; };
    void Global_id(int ident) { global_id = ident; };
    void copie(BUFFER *q, BUFFER p);
    void visualizar();
    void liberar(int id, int p, BUFFER pc, BUFFER *r0);
    long disp(int id, BUFFER *r0);
    int modificar(int id, BUFFER n);
    long ValidarNumero();
    int ValidarCadena(char String[]);
    void lea1(BUFFER *p);
    void visualizar1(int id);
    int eliminar(int id, long n);
    int init_archivo();
    int insertar(int id, BUFFER n);
};

/***************************************************************************/

char c;
int sw = 0;
long n1;
BUFFER n;
CURSOR cursor;
void menu();
void marcos(int ci, int cf, int fi, int ff);
void marco(int x1, int y1, int x2, int y2);
void pisos();
void CURSOR::lea1(BUFFER *p)
{
    textbackground(1);
    textcolor(15);
    marcos(2, 78, 2, 24);
    gotoxy(21, 4);
    printf(">>>>>>>>>>  I N G R E S A R  <<<<<<<<<< ");
    gotoxy(10, 7);
    printf(" No. CODIGO DEL RECLUSO:  ");
    scanf("\n");
    p->carcel.codigo = ValidarNumero();
    gotoxy(10, 9);
    printf(" NOMBRE Y APELLIDO DEL RECLUSO: ");
    scanf("\n");
    gets(p->carcel.nom_recluso);
}

/****************************************************************************/

long CURSOR::ValidarNumero()
{
    char a[20];
    int z, p;
    do
    {
        z = 0;
        p = 0;
        gotoxy(31, (wherey() - 1) + 1);
        clreol();
        gets(a);
        while (a[z] != '\0')
        {
            if (a[z] < '0' || a[z] > '9')
                p = -1;
            z++;
        }
    } while (p == -1);
    return (atol(a));
}
/***************************************************************************/

int CURSOR::ValidarCadena(char String[])
{
    int LongitudCadena = strlen(String), i = 0, sw = 0;
    while (i <= LongitudCadena - 1)
    {
        if (String[i] >= '0' && String[i] <= '9')
        {
            sw = 1;
        }
        i++;
    }
    if (sw == 1)
        return 1;
    else
        return -1;
}

/****************************************************************************/

void CURSOR::visualizar1(int id)
{
    textbackground(1);
    textcolor(15);
    marcos(2, 78, 2, 24);
    gotoxy(6, 4);
    printf(">>>>>>  VISUALIZACION DE LOS RECLUSOS DE  <<< LA  PICOTA >>> <<<<<<\n\n");
    int fil;
    long i;
    BUFFER a;
    ubicar(id, 0);
    lea(id, a);
    i = a.carcel.codigo;
    gotoxy(22, 8);
    printf("CODIGO                    NOMBRE Y APELLIDO");
    fil = 10;

    while (i != 0)
    {

        ubicar(id, i);
        lea(id, a);
        gotoxy(22, fil);
        printf("%ld\n", a.carcel.codigo);
        gotoxy(48, fil);
        printf("%s\t", a.carcel.nom_recluso);
        i = a.sig;
        fil++;
    }
    Global_id(id);
    gotoxy(32, 23);
    printf("###### ENTER #####\n");
}

/***************************************************************************/

int CURSOR::insertar(int id, BUFFER n)
{
    long p;
    int q, enc, prox;
    BUFFER pc, qc, r0, proxc;
    ubicar(id, 0);
    lea(id, r0);
    p = r0.carcel.codigo;
    q = enc = 0;
    while (p != 0 && !enc)
    {
        ubicar(id, p);
        lea(id, pc);
        if (n.carcel.codigo > pc.carcel.codigo)
        {
            q = p;
            copie(&qc, pc);
            p = pc.sig;
        }
        else
            enc = 1;
    }
    if (enc == 1)
        if (pc.carcel.codigo == n.carcel.codigo)
            return (-1);
    prox = disp(id, &r0);
    if (prox != -1)
    {
        proxc.carcel.codigo = n.carcel.codigo;
        strcpy(proxc.carcel.nom_recluso, n.carcel.nom_recluso);
        proxc.sig = p;
        ubicar(id, prox);
        grabar(id, proxc);
        if (q == 0)
            r0.carcel.codigo = prox;
        else
        {
            qc.sig = prox;
            ubicar(id, q);
            grabar(id, qc);
        }
    }
    else
    {
        gotoxy(23, 15);
        printf("ARCHIVO LLENO...  AMPLIAR EL ARCHIVO..\n");
        getch();
        exit(1);
    }
    ubicar(id, 0);
    grabar(id, r0);
    Global_id(id);
    return (0);
}

/***************************************************************************/

void insertar()
{
    cursor.Global_id(_open("lista", O_RDWR));
    do
    {
        clrscr();
        cursor.lea1(&n);
        if (cursor.insertar(cursor.pulsar(), n) == -1)
        {
            textcolor(14 + 128);
            gotoxy(32, 14);
            cprintf("��� YA EXISTE ���");
        }
        else
        {
            gotoxy(28, 16);
            printf("RECLUSO INGRESADO:::%ld\n", n);
        }
        gotoxy(28, 23);
        printf("DESEA SEGUIR INGRESANDO [S/N] ");
        do
        {
            c = toupper(getch());
            if (c == 'S' || c == 'N')
                sw = 1;
            else
                sw = 0;
        } while (sw != 1);
    } while (c != 'N');
}

/***************************************************************************/

int CURSOR::modificar(int id, BUFFER n)
{
    gotoxy(12, 4);
    printf(">>>>>>>>>>  R E C L U S O   M O D I F I C A D O  <<<<<<<<<< ");
    long p;
    int enc, prox;
    BUFFER pc, qc, r0, proxc;
    ubicar(id, 0);
    lea(id, r0);
    p = r0.carcel.codigo;
    enc = 0;
    while (p != 0 && !enc)
    {
        ubicar(id, p);
        lea(id, pc);
        if (n.carcel.codigo > pc.carcel.codigo)
        {
            copie(&qc, pc);
            p = pc.sig;
        }
        else
            enc = 1;
    }
    if (enc == 1)
    {
        if (pc.carcel.codigo == n.carcel.codigo)
        {
            strcpy(pc.carcel.nom_recluso, n.carcel.nom_recluso);
            ubicar(id, p);
            grabar(id, pc);
        }
        else
        {
            return -1;
        }
    }
    ubicar(id, 0);
    grabar(id, r0);
    Global_id(id);
    return (0);
}

/****************************************************************************/

void modificar()
{
    do
    {
        clrscr();
        cursor.lea1(&n);
        if (cursor.modificar(cursor.pulsar(), n) == -1)
        {
            textcolor(14 + 128);
            gotoxy(32, 14);
            cprintf("��� YA EXISTE ���");
        }
        else
        {
            gotoxy(28, 16);
            printf("!!! RECLUSO MODIFICADO:::%ld\n", n);
        }
        gotoxy(28, 23);
        printf("DESEA SEGUIR MODIFICANDO [S/N]  ");
        do
        {
            c = toupper(getch());
            if (c == 'S' || c == 'N')
                sw = 1;
            else
                sw = 0;
        } while (sw != 1);
    } while (c != 'N');
}

/****************************************************************************/

long CURSOR::disp(int id, BUFFER *r0)
{
    long i;
    BUFFER r1;
    i = r0->sig;
    if (i == 0)
        return (-1);
    else
    {
        ubicar(id, i);
        lea(id, r1);
        r0->sig = r1.sig;
        return (i);
    }
}

/***************************************************************************/

void CURSOR::liberar(int id, int p, BUFFER pc, BUFFER *r0)
{
    pc.sig = r0->sig;
    ubicar(id, p);
    grabar(id, pc);
    r0->sig = p;
}

/****************************************************************************/

void CURSOR::copie(BUFFER *q, BUFFER p)
{
    q->carcel.codigo = p.carcel.codigo;
    strcpy(q->carcel.nom_recluso, p.carcel.nom_recluso);
    q->sig = p.sig;
}

/****************************************************************************/

int CURSOR::init_archivo()
{
    long i;
    int id;
    BUFFER a;
    id = _creat("lista", 32);
    close(id);
    id = _open("lista", O_RDWR);
    a.carcel.codigo = 0;
    strcpy(a.carcel.nom_recluso, "        ");
    for (i = 0; i < MAXIMO; i++)
    {
        a.sig = i + 1;
        grabar(id, a);
    }
    a.sig = 0;
    grabar(id, a);
    return (id);
}

/***************************************************************************/

int CURSOR::eliminar(int id, long n)
{
    long p;
    long q, enc, prox;
    BUFFER pc, qc, r0, proxc;
    ubicar(id, 0);
    lea(id, r0);
    p = r0.carcel.codigo;
    q = enc = 0;
    while (p != 0 && !enc)
    {
        ubicar(id, p);
        lea(id, pc);
        if (n > pc.carcel.codigo)
        {
            q = (int)p;
            copie(&qc, pc);
            p = pc.sig;
        }
        else
            enc = 1;
    }
    if (enc == 1)
        if (pc.carcel.codigo != n)
            return (-1);
    if (q == 0)
        r0.carcel.codigo = pc.sig;
    else
    {
        qc.sig = pc.sig;
        ubicar(id, q);
        grabar(id, qc);
    }
    liberar(id, p, pc, &r0);
    ubicar(id, 0);
    grabar(id, r0);
    Global_id(id);
    return (id);
}

/****************************************************************************/

void eliminar()
{
    do
    {
        clrscr();
        textbackground(1);
        textcolor(15);
        marcos(2, 78, 2, 24);
        gotoxy(15, 4);
        printf(">>>>>>>>>>  R E C L U S O  E L I M I N A D O  <<<<<<<<<< ");
        gotoxy(10, 8);
        printf("No. CODIGO ELIMINAR: ");
        n1 = cursor.ValidarNumero();
        if (cursor.eliminar(cursor.pulsar(), n1) == -1)
        {
            textcolor(14 + 128);
            gotoxy(32, 14);
            cprintf("��� NO EXISTE ���");
        }
        else
        {
            gotoxy(28, 15);
            printf("!!!!!! RECLUSO  ELIMINADO:::%ld\n", n1);
        }
        gotoxy(28, 23);
        printf("DESEA SEGUIR ELIMINANDO [S/N] ");
        do
        {
            c = toupper(getch());
            if (c == 'S' || c == 'N')
                sw = 1;
            else
                sw = 0;
        } while (sw != 1);
    } while (c != 'N');
}

/***************************************************************************/

void main()
{
    cursor.Global_id(_open("lista", O_RDWR));
    menu();
    close(cursor.pulsar());
}

/****************************************************************************/

void menu()
{
    int n, j;
    int tecla, f;
    char opciones[35][45];
    char helpline[35][45];

    clrscr();
    textbackground(1);
    strcpy(opciones[9], "  INSERTAR RECLUSOS    ");
    strcpy(opciones[10], "  MODIFICAR RECLUSOS   ");
    strcpy(opciones[11], "  ELIMINAR RECLUSOS    ");
    strcpy(opciones[12], "  VISUALIZAR RECLUSOS  ");
    strcpy(opciones[13], "  NUEVO PROCEDIMIENTO  ");
    strcpy(opciones[14], "  SALIR DEL SISTEMA   ");
    strcpy(helpline[9], " INSERTAR RECLUSOS A LA CARCEL            ");
    strcpy(helpline[10], " MODIFICAR INFORMACION DEL ARCHIVO        ");
    strcpy(helpline[11], " ELIMINA SALIDA DE UN RECLUSO DE LA CARCEL");
    strcpy(helpline[12], " VISUALIZA  PRESOS DE LA CARCEL           ");
    strcpy(helpline[13], " NUEVO PROCEDIMIENTO                      ");
    strcpy(helpline[14], ">>>>> SALIR  DEL  SISTEMA  <<<<<          ");
    do
    {
        pisos();
        for (f = 9; f <= 14; f++)
        {
            textcolor(15);
            gotoxy(28, f);
            cprintf(opciones[f]);
        }
        f = 9;
        textcolor(15);
        textbackground(1);
        gotoxy(28, f);
        cprintf(opciones[f]);
        textcolor(15);
        textbackground(1);
        do
        {
            gotoxy(17, 24);
            cprintf(helpline[f]);
            _setcursortype(_NOCURSOR);
            do
            {
                tecla = getch();
            } while ((tecla != 80) && (tecla != 72) && (tecla != 13));
            if (tecla == 80)
            {
                gotoxy(17, 24);
                cprintf(helpline[f]);
                _setcursortype(_NOCURSOR);
                textcolor(15);
                textbackground(1);
                gotoxy(28, f);
                cprintf(opciones[f]);
                if (f != 14)
                    f = f + 1;
                else
                    f = 9;
                textcolor(0);
                textbackground(11);
                gotoxy(28, f);
                cprintf(opciones[f]);
                textcolor(15);
                textbackground(1);
            }
            if (tecla == 72)
            {
                textcolor(15);
                textbackground(1);
                gotoxy(28, f);
                cprintf(opciones[f]);
                gotoxy(17, 24);
                cprintf(helpline[f]);
                textcolor(15);
                _setcursortype(_NOCURSOR);
                if (f != 9)
                    f = f - 1;
                else
                    f = 14;
                textcolor(15);
                textbackground(1);
                gotoxy(28, f);
                cprintf(opciones[f]);
                textcolor(15);
                textbackground(1);
            }
        } while (tecla != 13);
        switch (f)
        {
        case 9:
            _setcursortype(_SOLIDCURSOR);
            insertar();
            pisos();
            break;
        case 10:
            _setcursortype(_SOLIDCURSOR);
            modificar();
            pisos();
            break;
        case 11:
            _setcursortype(_SOLIDCURSOR);
            eliminar();
            pisos();
            break;
        case 12:
            _setcursortype(_SOLIDCURSOR);
            clrscr();
            cursor.visualizar1(cursor.pulsar());
            getch();
            pisos();
            break;
        case 13:
            _setcursortype(_SOLIDCURSOR);
            break;
        }
    } while (f != 14);
}

/****************************************************************************/

void marco(int x1, int y1, int x2, int y2)
{

    int n;
    textcolor(15);
    gotoxy(x1, y1);
    cprintf("%c", 201);
    gotoxy(x2, y1);
    cprintf("%c", 187);
    gotoxy(x1, y2);
    cprintf("%c", 200);
    gotoxy(x2, y2);
    cprintf("%c", 188);
    for (n = (x1 + 1); n <= (x2 - 1); n++)
    {
        gotoxy(n, y1);
        cprintf("%c", 205);
        gotoxy(n, y2);
        cprintf("%c", 205);
    }
    for (n = (y1 + 1); n <= (y2 - 1); n++)
    {
        gotoxy(x1, n);
        cprintf("%c", 186);
        gotoxy(x2, n);
        cprintf("%c", 186);
    }
}
/****************************************************************************/

void marcos(int ci, int cf, int fi, int ff)
{
    int i;
    int c, f;
    clrscr();
    textcolor(15);
    textbackground(1);
    for (i = ci; i <= cf; i++)
    {
        gotoxy(i, fi);
        cprintf("�");
        gotoxy(i, ff);
        cprintf("�");
    }
    for (i = fi; i <= ff; i++)
    {
        gotoxy(ci, i);
        cprintf("�");
        gotoxy(cf, i);
        cprintf("�");
    }
    gotoxy(ci, fi);
    cprintf("�");
    gotoxy(ci, ff);
    cprintf("�");
    gotoxy(cf, fi);
    cprintf("�");
    gotoxy(cf, ff);
    cprintf("�");
}

/***************************************************************************/

void pisos()
{
    int n, j;
    clrscr();
    textbackground(1);
    clrscr();
    for (n = 2; n <= 24; n++)
        gotoxy(6, 4);
    textcolor(15);
    cprintf(" C A R C E L  D E  M A X I M A  S E G U R I D A D  <<< LA  PICOTA >>>");
    textcolor(14 + 128);
    gotoxy(14, 19);
    cprintf("UTILICE LAS TECLAS DEL CURSOR  Y  PRESIONE � ENTER � ");
    marco(26, 7, 53, 16);
    marco(5, 2, 75, 22);
    marco(9, 5, 70, 20);
    marco(13, 23, 65, 25);
}

/***************************************************************************/