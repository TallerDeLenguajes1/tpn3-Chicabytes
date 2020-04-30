#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Producto{
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
}Producto;
typedef struct Cliente{
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    Producto *Productos; //El tamaño de este arreglo depende de la variable
                        // “CantidadProductosAPedir”
}Clientes;

char *TiposProductos[] = {"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};
void CargaClientes(Clientes *cliente, int canti_clientes);
void CargaProductos(Producto *Productos,int cant_productos);
float SumaPrecios(int precio_u, int cantidad);
void Mostrar(Clientes *Cliente, int canti);

int main(void)
{
    srand(time(0));
    int canti_clientes = 0;
    while (canti_clientes == 0 || canti_clientes > 5)
    {
        printf("Por favor, ingrese la cantidad de clientes (entre 1 y 5): ");
        scanf("%d", &canti_clientes);
    }
    Clientes *cliente = (Clientes*)malloc(sizeof(Clientes)*canti_clientes);
    CargaClientes(cliente, canti_clientes);    //suma = SumaPrecios(cliente[i].Productos, aux);
    Mostrar(cliente, canti_clientes);
    return 0;
}

void CargaClientes(Clientes *cliente, int canti_clientes){
    int i, aux;
    for(i = 0; i < canti_clientes; i++)
    {
        cliente[i].ClienteID = i+1;
        cliente[i].NombreCliente=(char*)malloc(sizeof(char)*100);
        printf("Ingrese los nombres de los clientes: ");
        fflush(stdin);
        gets(cliente[i].NombreCliente);
        fflush(stdin);
        cliente[i].CantidadProductosAPedir = rand()%5 + 1;
        int cant_productos = cliente[i].CantidadProductosAPedir;
        cliente[i].Productos= (Producto*)malloc(sizeof(Producto)*cliente[i].CantidadProductosAPedir);
        CargaProductos(cliente[i].Productos, cant_productos);
    }
}

void CargaProductos(Producto *Productos, int cant_productos){
    int j;
    for(j = 0; j < cant_productos; j++)
    {
        Productos[j].ProductoID = j+1;
        Productos[j].Cantidad = rand()%10 + 1;
        Productos[j].PrecioUnitario = rand()%100 + 10;
        Productos[j].TipoProducto = (char*)malloc(sizeof(char)*20);
        Productos[j].TipoProducto = *(TiposProductos + rand()%5);
    };
}

float SumaPrecios(int precio_u, int cantidad)
{
    return precio_u*cantidad;
}

void Mostrar(Clientes *Cliente, int canti){
    int k, m;
    float suma;
    for(k = 0; k < canti; k++){
        printf("------Cliente------\n");
        printf("Id del Cliente: %d\n", Cliente[k].ClienteID);
        printf("Nombre : %s\n", Cliente[k].NombreCliente);
        printf("Cantidad de productos: %d\n",Cliente[k].CantidadProductosAPedir);
        for(m = 0; m < Cliente[k].CantidadProductosAPedir; m++){
            printf("ID del producto: %d\n", Cliente[k].Productos[m].ProductoID);
            printf("Cantidad: %d\n", Cliente[k].Productos[m].Cantidad);
            printf("Precio unitario: %2.f\n", Cliente[k].Productos[m].PrecioUnitario);
            printf("Productos que lleva: %s\n", Cliente[k].Productos[m].TipoProducto);
            suma += SumaPrecios(Cliente[k].Productos[m].Cantidad, Cliente[k].Productos[m].PrecioUnitario);
            
        }
        printf("Total a pagar: %2.f\n", suma);
        suma = 0;
    }
}