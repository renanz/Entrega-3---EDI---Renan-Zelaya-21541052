#include "fileExplorer.h"

fileExplorer::fileExplorer()
{
    this->clipboard = NULL;
    this->raiz = new folder("C:","");

}
archivo * fileExplorer::crearArchivo(folder * donde, string nombre, int opc)
{
    string ruta = donde->getRuta() + "\\" + donde->getNombre() + "\\" + nombre;
    if(opc == 0)
    {
        folder * newFolder = new folder(nombre,ruta);
        donde->archivos->agregar(newFolder);
        return newFolder;
    }
    else if(opc == 1)
    {
        archivoTexto * newArchivo = new archivoTexto(nombre,ruta);
        donde->archivos->agregar(newArchivo);
        return newArchivo;
    }
}
Lista_Apuntador fileExplorer::listarArchivos(folder * donde)
{
    Lista_Apuntador newList;

    for(int x = 0; x<donde->archivos->getTamano(); x++)
    {
        archivo * temp = donde->archivos->obtener(x);
        newList.agregar(temp);
    }

    return newList;
}
archivo * fileExplorer::cargarArchivo(string nombre)
{
    return cargarArchivo(nombre, getRaiz());
}
archivo * fileExplorer::cargarArchivo(string nombre, folder * subRaiz)
{
    for(int i = 0; i<subRaiz->archivos->getTamano(); i++){
        archivo * temp = subRaiz->archivos->obtener(i);
        if(temp->getNombre() == nombre)
            return temp;
        else if(temp->getTipo() == "Folder"){
            cargarArchivo(nombre, (folder*)temp);}
    }
    if(subRaiz == raiz)
        return NULL;
}
void fileExplorer::eliminarArchivo(string ruta)
{
    eliminarArchivo(ruta, getRaiz());
}
void fileExplorer::eliminarArchivo(string ruta, folder * subRaiz)
{
    archivo * temp;
    for(int x = 0; x<subRaiz->archivos->getTamano(); x++)
    {
        temp = subRaiz->archivos->obtener(x);
        if(temp->getRuta() == ruta)
        {
            subRaiz->archivos->eliminar(subRaiz->archivos->buscar(temp));
            return;
        }
        else if(temp->getTipo() == "Folder")
        {
            eliminarArchivo(ruta,(folder*)temp);
        }
    }
}
void fileExplorer::copiar(folder * origen, string ar, folder * destino)
{
    for(int x = 0; x<origen->archivos->getTamano(); x++)
    {
        archivo * temp = origen->archivos->obtener(x);
        if(temp->getNombre() == ar){
            clipboard = temp;
            break;
        }
    }
    if(clipboard != NULL)
        destino->archivos->agregar(clipboard);
    clipboard = NULL;
}
void fileExplorer::cortar(folder * origen, string ar, folder * destino)
{
    for(int x = 0; x<origen->archivos->getTamano(); x++)
    {
        archivo * temp = origen->archivos->obtener(x);
        if(temp->getNombre() == ar){
            clipboard = temp;
            break;
        }
    }
    if(clipboard != NULL)
    {
        destino->archivos->agregar(clipboard);
        origen->archivos->eliminar(destino->archivos->buscar(clipboard));
    }
    clipboard = NULL;
}
void fileExplorer::dir()
{
    cout<<getRaiz()->getNombre()<<endl;
    dir(getRaiz(),"");
}
void fileExplorer::dir(folder * subRaiz,string space)
{
    space+="\t";
    for(int x=0; x<subRaiz->archivos->getTamano();x++)
    {
        archivo * temp = subRaiz->archivos->obtener(x);
        cout<<space<<temp->getNombre()<<endl;
        if(temp->getTipo() == "Folder")
        {
            folder * fol = (folder*)temp;
            dir(fol,space);
        }
    }
}
void fileExplorer::seed()
{
    int rand;
    QString name;
    for (int x=0; x<23; x++ )
    {
        rand = (qrand() % 4) % 2;
        (rand == 0 ? name="Folder" : name="Archivo");
        name+=QString::number(x);
        crearArchivo(raiz,name.toStdString(),rand);
    }
}

folder * fileExplorer::getRaiz()
{
    return this->raiz;
}
