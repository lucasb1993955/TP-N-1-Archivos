#include <iostream>
#include<cstring>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "prototipos.h"
#include "platos.h"
#include<cstdio>

int main(){
    setlocale(LC_ALL,"spanish");
int opc;
    while(true)
    {
        setColor(CYAN);
        cls();
        cout<<"MENÚ PRINCIPAL"<<endl;
        cout<<"----------------------"<<endl;
        cout<<"1) PLATOS"<<endl;
        cout<<"2) CLIENTES"<<endl;
        cout<<"3) PEDIDOS"<<endl;
        cout<<"4) REPORTES"<<endl;
        cout<<"5) CONFIGURACIÓN"<<endl;
        cout<<"----------------------"<<endl;
        cout<<"0) SALIR DEL PROGRAMA"<<endl;

        cout<< "ingrese una opcion: "<<endl;
        cin>>opc;
        cls();
        switch (opc)
        {
        case 1:
            menu_platos();
            break;
        case 2:
            //menu_clientes();
            break;
        case 3:
            //menu_pedidos();
            break;
        case 4:
            //reportes();
            break;
        case 5:
            //configuracion();
            break;
        case 0:
            return 0;
            break;
        default:
            cout<< "opcion incorrecta"<<endl;
            break;
        }
        anykey();
    }
    return 0;
};


