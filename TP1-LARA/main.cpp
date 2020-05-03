
#include <iostream>
using namespace std;
#include <clocale>
#include "includes/rlutil.h"
using namespace rlutil;

#include "includes/func.h"
#include "includes/platos.h"


//DEFINICIONES
int main() {
    setlocale(LC_CTYPE, "Spanish");
    saveDefaultColor();

    int opc, nError;

    if (verificarArchivos() == -1) return 0;

    while (true){
        opc = mostrarMenu(MENU_PRINCIPAL, 6);

        switch (opc){
            case 1: //MENU PLATOS
                do{
                    opc = mostrarMenu(MENU_PLATOS, 7);
                    switch (opc){
                        case 1:
                            nError = crearPlato();
                            if (nError == 1){
                                setBackgroundColor(GREEN);
                                cout << endl << "El plato se generó correctamente";
                            }
                            getch();
                        break;
                        case 2:
                            nError = modificarPlato();
                            if (nError == 1){
                                setBackgroundColor(GREEN);
                                cout << endl << "El plato se modificó correctamente";
                            }
                            getch();
                        break;
                        case 3:
                            nError = listarPlato_x_ID();
                            getch();
                        break;
                        case 4:
                            listarPlatos_x_Rest();
                            getch();
                        break;
                        case 5:
                            listarTodos();
                        break;
                        case 6:
                            nError = eliminarPlato();
                            if (nError == 1){
                                setBackgroundColor(GREEN);
                                cout << endl << "El plato se dió de baja correctamente";
                            }
                            getch();
                        break;
                        case 7:
                        break;
                    }
                    resetColor();
                } while(opc != 7);
            break;
            case 6:
                return 0;
            break;
        }
        resetColor();
    }
}




