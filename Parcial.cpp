// Wilbert Rodríguez Riascos
// Katherin Tatiana Rivas Naranjo

#include <iostream>
#include <cstring>
using namespace std;

// Estructura Cliente
struct cliente {
    int id;
    char nombre[30];
    int edad;
    char genero; // 'M' o 'F'
    char motivo[50];
    cliente* siguiente;
};

//esta es una estructuras para manejar la cola FIFO manualmente
struct Cola {
    cliente* frente;
    cliente* final;
    int tamano;
};

//esta es una  estructuras para manejar la pila LIFO manualmente
struct Pila {
    cliente* tope;
    int tamano;
};

Cola colaEspera = {nullptr, nullptr, 0};
Pila pilaHistorial = {nullptr, 0};
Pila pilaDeshacer = {nullptr, 0};

//esta es una función para agregar clientes
void agregarCliente(int &contador) {
    cliente* nuevoCliente = new cliente;
    nuevoCliente->id = ++contador;
    nuevoCliente->siguiente = nullptr;
    cin.ignore();
    cout << "Nombre: ";
    cin.getline(nuevoCliente->nombre, 30);
    cout << "Edad: ";
    cin >> nuevoCliente->edad;
    cin.ignore();
    if (nuevoCliente->edad < 18) {
        cout << "No se permite atención a menores de edad.\n";
        delete nuevoCliente;
        return;
    }
    cout << "Género (M/F): ";
    cin >> nuevoCliente->genero;
    cin.ignore();
    cout << "Motivo: ";
    cin.getline(nuevoCliente->motivo, 50);
    
    if (colaEspera.final) {
        colaEspera.final->siguiente = nuevoCliente;
    } else {
        colaEspera.frente = nuevoCliente;
    }
    colaEspera.final = nuevoCliente;
    colaEspera.tamano++;
    cout << "El cliente ha sido agregado a la cola.\n";
}

// esta es la función para mostrar clientes en espera
void mostrarClientes() {
    if (!colaEspera.frente) {
        cout << "No hay clientes en espera.\n";
        return;
    }
    cliente* actual = colaEspera.frente;
    while (actual) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << ", Edad: " << actual->edad << ", Motivo: " << actual->motivo << "\n";
        actual = actual->siguiente;
    }
}

// Función para contar clientes en espera
void contarClientes() {
    cout << "Clientes en espera: " << colaEspera.tamano << "\n";
}

// Función para atender clientes
void atenderCliente() {
    if (!colaEspera.frente) {
        cout << "No hay clientes para atender.\n";
        return;
    }
    cliente* clienteAtendido = colaEspera.frente;
    colaEspera.frente = clienteAtendido->siguiente;
    if (!colaEspera.frente) {
        colaEspera.final = nullptr;
    }
    colaEspera.tamano--;
    
    clienteAtendido->siguiente = pilaHistorial.tope;
    pilaHistorial.tope = clienteAtendido;
    pilaHistorial.tamano++;
    
    clienteAtendido->siguiente = pilaDeshacer.tope;
    pilaDeshacer.tope = clienteAtendido;
    pilaDeshacer.tamano++;
    
    cout << "El cliente " << clienteAtendido->nombre << " ha sido atendido " <<endl;
}

// función para mostrar el historial
void mostrarHistorial() {
    if (!pilaHistorial.tope) {
        cout << "No hay historial de atenciones.\n";
        return;
    }
    cliente* actual = pilaHistorial.tope;
    while (actual) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << "\n";
        actual = actual->siguiente;
    }
}

// función para deshacer última atención
void deshacerAtencion() {
    if (!pilaDeshacer.tope) {
        cout << "No hay atenciones para deshacer.\n";
        return;
    }
    cliente* clienteDevuelto = pilaDeshacer.tope;
    pilaDeshacer.tope = clienteDevuelto->siguiente;
    pilaDeshacer.tamano--;
    
    clienteDevuelto->siguiente = nullptr;
    if (colaEspera.final) {
        colaEspera.final->siguiente = clienteDevuelto;
    } else {
        colaEspera.frente = clienteDevuelto;
    }
    colaEspera.final = clienteDevuelto;
    colaEspera.tamano++;
    
    cout << "Atención de " << clienteDevuelto->nombre << " deshecha, devuelto a la cola.\n";
}

// menú del sistema
void menu() {
    int opcion, contador = 0;
    do {
        cout << "\nMENU:\n";
        cout << "1. Agregar cliente\n2. Mostrar clientes en espera\n3. Contar clientes\n4. Atender cliente\n5. Mostrar historial\n6. Deshacer última atención\n7. Salir\nOpción: ";
        cin >> opcion;
        switch (opcion) {
            case 1: agregarCliente(contador); break;
            case 2: mostrarClientes(); break;
            case 3: contarClientes(); break;
            case 4: atenderCliente(); break;
            case 5: mostrarHistorial(); break;
            case 6: deshacerAtencion(); break;
            case 7: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 7);
}

int main() {
    menu();
    return 0;
}