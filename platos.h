#ifndef PLATOS_H_INCLUDED
#define PLATOS_H_INCLUDED

plato leer_plato(int pos) ///devuelve un registro ingresando la posicion
{
    plato reg;
    FILE*p;
    p=fopen(PATH_PLATO,"rb");
    fseek(p,pos*sizeof(plato),SEEK_SET);
    fread(&reg,sizeof(plato),1,p);
    fclose(p);

    return reg;
}
void menu_platos()
{
    int opc;
    plato reg;
    while(true)
    {
        setColor(GREEN);

        cls();
        cout<<"MENÚ PLATOS"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"1) NUEVO PLATO"<<endl;
        cout<<"2) MODIFICAR PLATO"<<endl;
        cout<<"3) LISTAR PLATO POR ID"<<endl;
        cout<<"4) PLATOS POR RESTAURANT"<<endl;
        cout<<"5) LISTAR TODOS LOS PLATOS"<<endl;
        cout<<"6) ELIMINAR PLATO"<<endl;
        cout<<"0) VOLVER AL MENÚ PRINCIPAL"<<endl<<endl;
        cout<<"--------------------------------"<<endl;
        cout<< "ingrese una opcion: "<<endl;
        cin>>opc;
        cls();
        switch (opc)
        {
        case 1:
            if(cargar_plato(&reg)==true)
            {
                if (guardar_plato(reg)==true)
                {
                    cout<< "nuevo plato guardado";
                }
                else
                {
                    cout<< "no se pudo guardar el plato";
                }
            }
            else
            {
                cout<< "no se pudo cargar el plato"<<endl;
            }
            break;
        case 2:
            if(cantidad_registros()>0)
            {
                if(modificar_plato()==true)
                {
                    cout<< "plato modificado"<<endl;
                }
                else
                {
                    cout<< "no se pudo modificar el plato"<<endl;
                }
            }
            else
            {
                cout<< "no hay productos guardados"<<endl;
            }
            break;
        case 3:
            if(cantidad_registros()>0)
            {
                listar_platoXid();
            }
            else
            {
                cout<< "no hay platos cargados"<<endl;
            }
            break;
        case 4:
            if(cantidad_registros()>0)
            {
                platosXrestaurante();
            }
            else
            {
                cout<< "no hay platos cargados"<<endl;
            }
            break;
        case 5:
            if(cantidad_registros()>0)
            {
                listar_platos_de_archivos(reg);
            }
            else
            {
                cout<< "no hay platos cargados"<<endl;
            }
            break;
        case 6:
            if(cantidad_registros()>0)
            {
                if (eliminar_plato()==true)
                {
                    cout<< "eliminacion realizada"<<endl;
                }

                else
                {
                    cout<< "eliminacion no realizada"<<endl;
                }
            }
            else
            {
                cout<< "no hay platos cargados"<<endl;
            }
            break;
        case 0:
            return;
            break;

        default:
            cout<< "opcion incorrecta."<<endl;
            break;
        }
        anykey();
    }

}
bool cargar_plato(struct plato*pl)
{
    setColor(WHITE);
    int pos;
    cout<< "ingrese el id: ";
    cin>>pl->id;
    pos=buscar_id(pl->id);
    if(pos>=0)
    {
        setColor(RED);
        cout<< "id ya existente."<<endl;
        return false;
    }
    else if(pl->id<=0)
    {
        setColor(RED);
        cout<< "id no valido"<<endl;
        return false;
    }

    cout<< "ingrese el nombre: ";
    cin.ignore();
    cin.getline(pl->nombre,50);
    if(strcmp(pl->nombre,"\0")==0)
    {
        setColor(RED);
        cout<< "nombre invalido."<<endl;
        return false;
    }

    cout<< "costo de preparacion: $";
    cin>>pl->costo_preparacion;
    if(pl->costo_preparacion<0)
    {
        setColor(RED);
        cout<< "costo de preparacion invalido"<<endl;
        return false;
    }

    cout<< "valor de venta: ";
    cin>>pl->valor_venta;
    if(pl->valor_venta<0 || pl->valor_venta<pl->costo_preparacion)
    {
        setColor(RED);
        cout<< "valor de venta invalido"<<endl;
        return false;
    }

    cout<< "tiempo de preparacion: ";
    cin>>pl->tiempo_preparacion;
    if(pl->tiempo_preparacion<0)
    {
        setColor(RED);
        cout<< "tiempo de preparacion invalido"<<endl;
        return false;
    }

    cout<< "id restaurante: ";
    cin>>pl->id_restaurante;
    if(pl->id_restaurante<=0)
    {
        setColor(RED);
        cout<< "id restaurante invalido"<<endl;
        return false;
    }

    cout<< "comision restaurante: ";
    cin>>pl->comision_restaurante;
    if(pl->comision_restaurante<0 && pl->comision_restaurante>100)
    {
        setColor(RED);
        cout<< "comision invalida"<<endl;
        return false;
    }

    cout<< "id categoria: ";
    cin>>pl->id_categoria;
    if(pl->id_categoria<=0)
    {
        setColor(RED);
        cout<< "id categoria invalido"<<endl;
        return false;
    }

    pl->estado=true;
    return true;
}
int buscar_id(int id)
{
    plato reg;
    FILE*p;
    int i=0;
    p=fopen(PATH_PLATO,"rb");
    if(p==NULL)
    {
        return -1;
    }
    while(fread(&reg,sizeof(plato),1,p)==1)
    {
        if(reg.estado==true)
        {
            if(reg.id==id)
            {
                fclose(p);
                return i;
            }
        }
        i++;
    }
    fclose(p);
    return -1;
}
bool modificar_plato()
{
    int id;
    cout<< "ingrese un id: "<<endl;
    cin>>id;
    anykey();
    cls();
    int indice=buscar_id(id);
    if(indice>=0)
    {
        plato reg=leer_plato(indice);
        listar_platos(reg,0);
        cout<< "ingrese el nuevo costo de venta: "<<endl;
        cin>>reg.valor_venta;
        if(reg.valor_venta<0 || reg.valor_venta<reg.costo_preparacion)
        {
            setColor(RED);
            cout<< "valor de venta invalido"<<endl;
            return false;
        }
        cout<< "ingrese nuevo tiempo de preparacion: "<<endl;
        cin>>reg.tiempo_preparacion;
        if(reg.tiempo_preparacion<0)
        {
            setColor(RED);
            cout<< "tiempo de preparacion invalido"<<endl;
            return false;
        }
        if(sobreescribir_plato(reg,indice)==true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout<< "id no existente."<<endl;
        return false;
    }
    return true;
}
void listar_platoXid()
{
    cls();
    int id;
    cout<< "ingrese el id a listar: "<<endl;
    cin>>id;
    cls();
    if(buscar_id(id)>=0)
    {
        plato reg=leer_plato(buscar_id(id));
        listar_platos(reg,0);
    }
    else
    {
        cout<< "no existe el id buscado"<<endl;
    }
}
void platosXrestaurante()
{
    cls();
    int id;
    plato reg;
    cout<< "ingrese el id restaurante: "<<endl;
    cin>>id;
    cls();
    int indice=buscar_id_restaurante(id);
    if(indice>=0)
    {
        reg=leer_plato(indice);
        listar_platos(reg,0);
    }
    else
    {
        cout<< "id restaurante no existente"<<endl;
    }
}
void listar_platos(plato v,int c)
{
    setColor(LIGHTBLUE);
    if(c==0)
    {
        cout<<"*================================================================================================================================*"<<endl;
        cout<<"*ID  ° NOMBRE       °       COSTO PREP.    °   VALOR VENTA   °   TIEMPO PREP.   °   ID REST.  °   COMISION REST.    °   ID CAT.  *"<<endl;
        cout<<"*================================================================================================================================*"<<endl;
        if(v.estado==true)
        {

            cout<<"*";
            gotoxy(2,4);
            cout<<v.id;

            gotoxy(8,4);
            cout<<v.nombre;

            gotoxy(29,4+c);
            cout<<v.costo_preparacion;

            gotoxy(48,4);
            cout<<v.valor_venta;

            gotoxy(67,4);
            cout<<v.tiempo_preparacion;

            gotoxy(85,4);
            cout<<v.id_restaurante;

            gotoxy(99,4);
            cout<<v.comision_restaurante;

            gotoxy(121,4);
            cout<<v.id_categoria;

            gotoxy(130,4);
            cout<< "*" <<endl;
            cout<<"*================================================================================================================================*"<<endl;
        }
    }
    else
    {
        if(v.estado==true)
        {
            setColor(LIGHTBLUE);
            cout<<"*";
            gotoxy(2,4+c*2);/// multiplico por 2 para que no se pise con la linea divisoria (=======)
            cout<<v.id;

            gotoxy(8,4+c*2);
            cout<<v.nombre;

            gotoxy(29,4+c*2);
            cout<<v.costo_preparacion;

            gotoxy(48,4+c*2);
            cout<<v.valor_venta;

            gotoxy(67,4+c*2);
            cout<<v.tiempo_preparacion;

            gotoxy(85,4+c*2);
            cout<<v.id_restaurante;

            gotoxy(99,4+c*2);
            cout<<v.comision_restaurante;

            gotoxy(121,4+c*2);
            cout<<v.id_categoria;

            gotoxy(130,4+c*2);
            cout<< "*" <<endl;
            cout<<"*================================================================================================================================*"<<endl;

        }
    }
}
bool guardar_plato(plato reg)
{
    FILE*p;
    p=fopen(PATH_PLATO,"ab");
    if(p==NULL)
    {
        cout<< "no se puedo abrir en el archivo."<<endl;
        return false;
    }
    fwrite(&reg,sizeof(plato),1,p);
    fclose(p);
    return true;
}
bool listar_platos_de_archivos(plato reg)
{
    setColor(LIGHTBLUE);
    FILE*p;
    p=fopen(PATH_PLATO,"rb");
    if(p==NULL)
    {
        cout<< "no pudo abrir el archivo"<<endl;
        return false;
    }
    else
    {
        int i=0;
        while(fread(&reg,sizeof(plato),1,p)==1)
        {
            if(reg.estado==true)
            {
                listar_platos(reg,i);
                i++;
            }
        }
    }
    fclose(p);

    anykey();
    return true;
}
int cantidad_registros()
{
    int bytes, cant_registros;
    FILE*p;
    p=fopen(PATH_PLATO, "rb");
    if(p==NULL)
    {
        return 0;
    }
    fseek(p,0,SEEK_END);
    fclose(p);
    bytes=ftell(p);
    cant_registros=bytes/sizeof(plato);

    return cant_registros;
}
bool sobreescribir_plato(plato reg,int pos)
{
    FILE*p;
    bool escribio;
    p=fopen(PATH_PLATO, "rb+");
    if(p==NULL)
    {
        cout<< "no se pudo abrir el archivo"<<endl;
        return false;
    }
    fseek(p,pos*sizeof(plato),SEEK_SET);
    escribio=fwrite(&reg,sizeof(plato),1,p);
    fclose(p);
    return escribio;/// devuelve 0 o 1
}
int buscar_id_restaurante(int id)
{
    int i=0;
    FILE*p;
    plato reg;
    p=fopen(PATH_PLATO, "rb");
    if(p==NULL)
    {
        cout<< "no se pudo abrir el archivo"<<endl;
        return -1;
    }
    while(fread(&reg,sizeof(plato),1,p)==1)
    {
        if(reg.id_restaurante==id)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    return -2;
}
bool eliminar_plato()
{
    int id;
    plato reg;
    cout<< "ingrese el id a eliminar: "<<endl;
    cin>>id;
    cls();
    int pos=buscar_id(id);
    if(pos<0)
    {
        cout<< "id invalido"<<endl;
        return false;
    }
    else
    {
        reg=leer_plato(pos);
        listar_platos(reg,0);
    }
    reg.estado=false;
    if(sobreescribir_plato(reg,pos)==false)
    {
        return false;
    }
    return true;
}
#endif // PLATOS_H_INCLUDED
