#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

  //Errores de FILE
 const int FILE_OPEN_ERROR = 1;
 const int FILE_READ_ERROR = 2;
 const int FILE_WRITE_ERROR = 3;

 const char ERROR_FILE[][50]{
    {"Error al abrir el archivo"},
    {"Error al leer del archivo"},
    {"Error al escribir en el archivo"}
 };

//MENUES
 const char  MENU_PRINCIPAL[][30] = {
    {" MENÚ PRINCIPAL "},
    {" -------------- "},
    {" 1 - PLATOS "},
    {" 2 - CLIENTES "},
    {" 3 - PEDIDOS "},
    {" 4 - REPORTES "},
    {" 5 - CONFIGURACIÓN "},
    {" 6 - SALIR "}
};
 const char  MENU_PLATOS[][30] = {
    {" PLATOS "},
    {" -------------- "},
    {" 1 - NUEVO PLATO "},
    {" 2 - MODIFICAR PLATO "},
    {" 3 - LISTAR PLATO POR ID "},
    {" 4 - PLATOS POR RESTAURANT "},
    {" 5 - LISTAR TODOS LOS PLATOS "},
    {" 6 - ELIMINAR PLATO "},
    {" 7 - VOLVER AL MENÚ PRINCIPAL"}
};

//ARCHIVOS
const char ARCHIVO_PLATOS [] = "platos.dat";

//PROTOTIPOS
int mostrarMenu(char (*)[30], int cantOpc);
void errorFile(const char [][50], const char*, int);
int verificarArchivos();

//DEFINICIONES
int verificarArchivos(){
    FILE *pArchivo;

    pArchivo = fopen(ARCHIVO_PLATOS, "rb");
    if (pArchivo == NULL){
        setBackgroundColor(RED);
        cout << endl << "Falta el archivo '" << ARCHIVO_PLATOS <<"'." << "Contactese con el administrador" << endl;
        resetColor();
        return -1;
    }
    fclose(pArchivo);
    return 1;
}
int mostrarMenu(const char (*menu)[30], int cantOpc){

    int opc = 1, i;
    int teclaPulsada;

    hidecursor();

    do{
        cls();
        for (i=0;i<cantOpc+2;i++){
            if (i == opc + 1){ //Opción que tiene el foco
              setBackgroundColor(GREY);
              setColor(BLACK);
              cout << menu[i] << endl;
              resetColor();
            }
            else cout << menu[i] << endl;
        }


        teclaPulsada = getkey();

        switch (teclaPulsada){
            case KEY_DOWN:
                if(opc < cantOpc)opc++;
            break;
            case KEY_UP:
                if(opc > 1)opc--;
            break;
        };
    } while (teclaPulsada != KEY_ENTER);

    return opc;
}
void errorFile(const char *fileName ,int nError){

    setBackgroundColor(RED);
    cout << endl << ERROR_FILE[nError] << " '" << fileName << "'";
    resetColor();

}
#endif // FUNC_H_INCLUDED
