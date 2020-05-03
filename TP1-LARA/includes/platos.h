#ifndef PLATOS_H_INCLUDED
#define PLATOS_H_INCLUDED
struct Platos{
    int ID_Plato, tiempo, ID_Res, comRes, ID_Cat;
    char nombre [50];
    float costo, precio;
    bool estado;
};


//ERRORES DE EDICION/CREACION DE PLATOS

const int ID_ERROR = 0;
const int ID_REPETIDO = 1;
const int NAME_ERROR = 2;
const int COST_ERROR = 3;
const int PRICE_ERROR = 4;
const int TIME_ERROR = 5;
const int ID_REST_ERROR = 6;
const int COM_RES_ERROR = 7;
const int ID_CAT_ERROR = 8;
const int ID_INEXISTENTE = 9;
const int PLATO_INACTIVO_ERROR = 10;
const int ID_REST_SIN_PLATOS = 11;

const char  ERROR_PLATO[][80] = {
    {"El ID debe ser un número entero positivo"},
    {"El ID ingresado ya existe"},
    {"El Nombre no puede ser una cadena vacia"},
    {"El costo de preparación no puede ser negativo"},
    {"El precio de venta no puede ser negativo ni menor al costo de preparación"},
    {"El tiempo de preparación debe ser un valor positivo"},
    {"El ID del restaurante debe ser un entero positivo"},
    {"La comisión del restaurante es un número entero entre 0 y 100 %"},
    {"El ID de la categoría debe ser un número entero positivo"},
    {"No existe un plato con ese número de ID"},
    {"Registro dado de baja, contactese con el administrador"},
    {"No existen platos para ese restaurante"}
};


//PROTOTIPOS
void errorPlato(int);
int crearPlato();
int modificarPlato();
int buscar_Plato_x_id(int);
void mostrarPlato(struct Platos);
int listarPlato_x_ID();
void listarPlatos_x_Rest();
int eliminarPlato();
int contarRegistrosActivos();
int contarRegistros();
struct Platos obtenerPlato_x_Pos(int);

//DEFINICIONES
int crearPlato(){
    int id, pos, tiempo, idR, com, idC;
    char nombre[50];
    float costo, precio;
    struct Platos nuevoPlato;
    FILE *pArchivo;

    cls();
    showcursor();

    cout << "NUEVO PLATO" << endl;
    cout << "------------" << endl;
    cout << "ID: " ;
    cin >> id;

    if (id <= 0){
        errorPlato(ID_ERROR);
        return -1;
    }

    pos = buscar_Plato_x_id(id);

    if (pos >= 0){
        errorPlato(ID_REPETIDO);
        return -1;
    }

    cout << "Nombre: ";
    cin.ignore();
    cin.getline(nombre, 50);
    if (strcmp(nombre, "") == 0){
        errorPlato(NAME_ERROR);
        return -1;
    }

    cout << "Costo preparación: $" ;
    cin >> costo;
    if (costo < 0){
        errorPlato(COST_ERROR);
        return -1;
    }

    cout << "Precio de Venta: $" ;
    cin >> precio;
    if (precio < 0 || precio < costo){
        errorPlato(PRICE_ERROR);
        return -1;
    }
    cout << "Tiempo de preparación (min.): " ;
    cin >> tiempo;
    if (tiempo < 0){
        errorPlato(TIME_ERROR);
        return -1;
    }
    cout << "ID Restaurente: " ;
    cin >> idR;
    if (idR < 0) {
        errorPlato(ID_REST_ERROR);
        return -1;
    }
    cout << "Comisión (%): " ;
    cin >> com;
    if (com < 0 || com > 100){
        errorPlato(COM_RES_ERROR);
        return -1;
    }
    cout << "ID Categoría: " ;
    cin >> idC;
    if (idC < 0){
        errorPlato(ID_CAT_ERROR);
        return -1;
    }
    nuevoPlato.ID_Plato = id;
    strcpy(nuevoPlato.nombre, nombre);
    nuevoPlato.costo = costo;
    nuevoPlato.precio = precio;
    nuevoPlato.tiempo = tiempo;
    nuevoPlato.ID_Res = idR;
    nuevoPlato.comRes = com;
    nuevoPlato.ID_Cat = idC;
    nuevoPlato.estado = true;

    pArchivo = fopen(ARCHIVO_PLATOS, "ab");
    if (pArchivo == NULL){
        errorFile(ARCHIVO_PLATOS, 0);
        return -2;
    }
    if (fwrite(&nuevoPlato, sizeof nuevoPlato, 1, pArchivo) == 0){
        errorFile(ARCHIVO_PLATOS, 2);
        return -2;
    };
    fclose(pArchivo);
    return 1; //Todo OK
}

int modificarPlato(){
    int id, pos, tiempo;
    float precio;
    struct Platos plato;
    FILE *pArchivo;

    cls();
    showcursor();

    cout << "MODIFICAR PLATO" << endl;
    cout << "---------------" << endl;

    cout << "ID: " ;
    cin >> id;

    if (id <= 0){
        errorPlato(ID_ERROR);
        return -1;
    }

    pos = buscar_Plato_x_id(id);
    if (pos == -1){
        errorPlato(ID_INEXISTENTE);
        return -1;
    }

    plato = obtenerPlato_x_Pos(pos);

    if (plato.ID_Plato == -1) return -1;

    if (plato.estado == false){
        errorPlato(PLATO_INACTIVO_ERROR);
        return -1;
    }

    setBackgroundColor(GREEN);
    cout << endl << "registro encontrado" << endl;
    resetColor();

    mostrarPlato(plato);

    cout << endl << endl << "NUEVO precio de Venta: $" ;
    cin >> precio;
    if (precio < 0 || precio < plato.costo){
        errorPlato(PRICE_ERROR);
        return -1;
    }

    cout << endl << "NUEVO tiempo de preparación (min.): " ;
    cin >> tiempo;
    if (tiempo < 0){
        errorPlato(TIME_ERROR);
        return -1;
    }

    plato.precio = precio;
    plato.tiempo = tiempo;

    pArchivo = fopen(ARCHIVO_PLATOS, "rb+");
    if (pArchivo == NULL){
        errorFile(ARCHIVO_PLATOS, 0);
        return -2;
    }
    fseek(pArchivo, pos*(sizeof plato), 0);
    if (fwrite(&plato, sizeof plato, 1, pArchivo) == 0){
        errorFile(ARCHIVO_PLATOS, 2);
        fclose(pArchivo);
        return -1;
    }

    fclose(pArchivo);
    return 1; //Todo OK
}

int listarPlato_x_ID(){
    int id, pos;
    struct Platos plato;

    cls();
    showcursor();

    cout << "LISTAR PLATO" << endl;
    cout << "------------" << endl;
    cout << "ID: " ;
    cin >> id;

    pos = buscar_Plato_x_id(id);
    if (pos == -1){
        errorPlato(ID_INEXISTENTE);
        return -1;
    }

    plato = obtenerPlato_x_Pos(pos);

    if (plato.ID_Plato == -1) return -1;

    if (plato.estado == false){
        errorPlato(PLATO_INACTIVO_ERROR);
        return -1;
    }

    setBackgroundColor(GREEN);
    cout << endl << "registro encontrado" << endl ;
    resetColor();

    hidecursor();
    mostrarPlato(plato);

    return 1;
}
void listarTodos(){
    FILE *pArchivo;
    struct Platos plato;
    int contRegAct, contRegTot, indDir = 1, pos = 0, nReg = 1;
    int teclaPulsada;

    pArchivo = fopen(ARCHIVO_PLATOS, "rb+");

    if (pArchivo == NULL){
        errorFile(ARCHIVO_PLATOS, 0);
        getch();
        return;
    }

    contRegAct = contarRegistrosActivos();
    contRegTot = contarRegistros();

    while(true){
        fseek(pArchivo, pos*(sizeof plato), 0);
        if (fread(&plato, sizeof plato, 1, pArchivo) == 0){
            errorFile(ARCHIVO_PLATOS, 1);

        }
        if (plato.estado == true) {
            cls();
            cout << "PLATOS REGISTRADOS" << endl;
            cout << "------------------" << endl;

            mostrarPlato(plato);

            cout << endl << endl << "<--          " << nReg << " de " << contRegAct <<"              -->";
            cout << endl << endl << "            Esc: Salir            ";

            teclaPulsada = getkey();

            switch (teclaPulsada){
                case KEY_ESCAPE: return;
                break;
                case KEY_LEFT:
                    if (pos > 0){
                        indDir = -1;
                        pos--;
                    }
                break;
                case KEY_RIGHT:
                    if (pos < contRegTot-1){
                        indDir = 1;
                        pos++;
                    }
                break;
            }
        } else{
            if (pos > 0 && pos < contRegTot) pos += indDir; //Avanzamos al siguiente registro
            else pos = pos + indDir*-1; //Invertimos el indicador de dirección para seguir en el ultimo registro activo.
        }
    }

}
void listarPlatos_x_Rest(){
    int idR, c=0;
    struct Platos plato;
    FILE *pArchivo;

    cls();
    showcursor();

    cout << "PLATOS POR RESTAURANTE" << endl;
    cout << "----------------------" << endl;

    cout << "ID del Restaurante: " ;
    cin >> idR;

        if (idR <= 0){
        errorPlato(ID_REST_ERROR);
        return;
    }

    pArchivo = fopen(ARCHIVO_PLATOS, "rb");
    if (pArchivo == NULL){
        errorFile(ARCHIVO_PLATOS, 0);
        return;
    }

    while (fread(&plato, sizeof plato, 1, pArchivo)){
        if (plato.estado == true){
            if (plato.ID_Res == idR){
                c++;
                mostrarPlato(plato);
                cout << endl ;
            }
        }
    }
    if (c == 0) errorPlato(ID_REST_SIN_PLATOS);
    else{
        setBackgroundColor(GREEN);
        cout << endl << c << " platos encontrados para el ID Restaurante: " << idR;
        resetColor();
    }
    fclose(pArchivo);
}
struct Platos obtenerPlato_x_Pos(int pos){
    struct Platos plato;
    FILE *pArchivo;

    pArchivo = fopen(ARCHIVO_PLATOS, "rb+");

    if (pArchivo == NULL){
        errorFile(ARCHIVO_PLATOS, 0);
        plato.ID_Plato = -1; //Un plato Nulo
        return plato;
    }

    fseek(pArchivo, pos*(sizeof plato), 0);
    if (fread(&plato, sizeof plato, 1, pArchivo) == 0){
        errorFile(ARCHIVO_PLATOS, 1);
        fclose(pArchivo);
        plato.ID_Plato = -1; //Un plato Nulo
        return plato;
    }

    return plato;
}
int eliminarPlato(){
    int id, pos;
    struct Platos plato;
    FILE *pArchivo;

    cls();
    showcursor();

    cout << "ELIMINAR PLATO" << endl;
    cout << "---------------" << endl;

    cout << "ID: " ;
    cin >> id;

    if (id <= 0){
        errorPlato(ID_ERROR);
        return -1;
    }

    pos = buscar_Plato_x_id(id);
    if (pos == -1){
        errorPlato(ID_INEXISTENTE);
        return -1;
    }

    plato = obtenerPlato_x_Pos(pos);

    if (plato.ID_Plato == -1) return -1;

    if (plato.estado == false){
        errorPlato(PLATO_INACTIVO_ERROR);
        return -1;
    }

    plato.estado = false; //BAJA LOGICA

    pArchivo = fopen(ARCHIVO_PLATOS, "rb+");
    fseek(pArchivo, pos*(sizeof plato), 0);
    if (fwrite(&plato, sizeof plato, 1, pArchivo) == 0){
        errorFile(ARCHIVO_PLATOS, 2);
        fclose(pArchivo);
        return -1;
    }

    fclose(pArchivo);
    return 1; //Todo OK
}
void mostrarPlato(struct Platos plato){
    cout << endl << "ID: " << plato.ID_Plato ;
    cout << endl << "Nombre: " << plato.nombre ;
    cout << endl << "Costo preparación: $" << plato.costo ;
    cout << endl << "Precio de Venta: $" << plato.precio ;
    cout << endl << "Tiempo de preparación (min.): " << plato.tiempo ;
    cout << endl << "ID Restaurente: " << plato.ID_Res;
    cout << endl << "Comisión (%): " << plato.comRes;
    cout << endl << "ID Categoría: " << plato.ID_Cat;
}
int buscar_Plato_x_id(int id){
    FILE *pArchivo;
    struct Platos plato;
    int pos = 0;

    pArchivo = fopen(ARCHIVO_PLATOS, "rb");
    if (pArchivo == NULL){
        errorFile(ARCHIVO_PLATOS, 0);
        return -2; // Usamos -2 para error de Archivo y -1 si no existe
    }
    while (fread(&plato, sizeof plato, 1, pArchivo) != 0){
        if (plato.ID_Plato == id){
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }
    fclose(pArchivo);
    return -1; // id no encontrado
}

int contarRegistrosActivos(){
    FILE *pArchivo;
    int cont = 0;
    struct Platos plato;

    pArchivo = fopen(ARCHIVO_PLATOS, "rb");
    if  (pArchivo){
        while (fread(&plato, sizeof plato, 1, pArchivo)){
            if (plato.estado == true) cont++ ;
        }
        fclose(pArchivo);
    }
    return cont;
}
int contarRegistros(){
    FILE *pArchivo;
    int tam = 0;

    pArchivo = fopen(ARCHIVO_PLATOS, "rb");
    if (pArchivo){
        fseek(pArchivo, 0, 2);
        tam = ftell(pArchivo);
        fclose(pArchivo);
    }
    return (tam/sizeof (struct Platos));
}

void errorPlato(int nError){

    setBackgroundColor(RED);
    cout << endl << ERROR_PLATO[nError];
    resetColor();
}


#endif // PLATOS_H_INCLUDED
