#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED
int main();
void menu_platos();
int buscar_id(int );
bool modificar_plato();
void listar_platoXid();
void platosXrestaurante();
bool cargar_plato(struct plato*);
void listar_platos(plato,int);
bool guardar_plato(plato);
bool listar_platos_de_archivos(plato);
struct plato leer_plato(int );
int cantidad_registros();
bool sobreescribir_plato(plato,int );
int buscar_id_restaurante(int);
bool eliminar_plato();

struct plato
{
    int id;
    char nombre[50];
    float costo_preparacion,valor_venta;
    int tiempo_preparacion, id_restaurante, comision_restaurante,id_categoria;
    bool estado;
};
const char*PATH_PLATO="platos.dat";
#endif // PROTOTIPOS_H_INCLUDED
