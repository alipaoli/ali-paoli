#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

struct Empleado{
    string fecha;
    string apellido;
    string nombre;
    string ss;
    double horas;
    double payRate;
    double payBase;
    double payOvertime;
    double payDeduction;
    double netPay;
};

void Nomina();
        //Funcion que llama las otras funciones y puede ser llamada, a diferencia de 'main'.
string intro(string);
        //Funcion que le da instrucciones al usuario y recibe el nombre del archivo.
bool read(const string, vector<Empleado>);
        //Funcion que abre y lee el archivo indicado. Si no lo puede abrir le informa al usuario.
void headerCheck(ifstream& archivo);
        //Corrobora si el archivo tiene header o footer y
void Sal(double, double);
        //  Funcionque calcula lo que se gano cada empleado, con las siguientes tres funciones.
void bSalary(double);
        // Calcula salario bruto y salario por overtime
void nSalary(double);
        // Calcula deducciones y salario neto de cada empleado
double Pay(double, double);
        // Calcula multiplicacion reduntante
bool ordenApellido(const Empleado &lhs, const Empleado &rhs);
        // Establece crterio de ordenamiento
void sort(vector<Empleado> &empleado);
        // Ordena el vector alfabeticamente, por apellidos.
void print(const int, const vector<Empleado>& empleado);
        // Despliega la nomina de un empleado en pantalla
void Write(const vector<Empleado>& empleado);
        // Escribe el CSV de la nomina
void Menu(const vector<Empleado> &empleado);
        // Despliega un menu de opciones adicionales post-calculo
void getIndex(int& ID);
        // Obtiene el indice del usuario
int findIndex(const vector<Empleado>& empleado);
        // Encuentra el indice provisto el nombre o apellido del empleado
void employeeRange(const vector<Empleado>& empleado);
        // Despliega un rango de empleados solicitado por el usuario
void employeeSingle(const vector<Empleado>& empleado);
        // Despliega un empleado indicado por el usuario

int main(){
    Nomina();           // Itera la nomina al menos una vez
    return 0;
}

void Nomina(){
    vector<Empleado> empleado;
    string archivo;
    intro(archivo);
    if(read(archivo, empleado)){
        sort(empleado);
        Write(empleado);
        Menu(empleado);
    }
}
bool ordenApellido(const Empleado &lhs, const Empleado &rhs) {
    return lhs.apellido < rhs.apellido; }
void sort(vector<Empleado> empleado){
    sort(empleado.begin(), empleado.end(), ordenApellido);
}
string intro(string &nombre){
    cout << "Saludos, este programa recibe un archivo de nomina CSV con: ";
    cout << "fecha, apellido, nombre, seguro social, horas trabajadas y paga por hora.";
    cout << "Luego, calcula el salario bruto, horas sobre-tiempo, deducciones y";
    cout << " salario neto de cada empleado; mas el salario neto total." << endl;
    cout << "Para comenzar, indique el nombre del archivo que desea leer: ";
    cin >> nombre;
    return nombre;      //Recibe y devuelve elnombre del archivo
}
bool read(const string &csv, vector<Empleado> &empleado){
    ifstream archivo(csv);                  //Abre el archivo CSV.

    if (archivo.is_open()){     //Corrobora que el archivo abrio antes de intentar leerlo.
        headerCheck();

        Empleado empData;                       //Variables temporeras que reciben los
        string empLine, dataPoint;              //resultados en el correcto data type.

        while(getline(archivo, empLine)){       //Para cada linea del archivo, la lee
            stringstream lineStream(empLine);   //y la convierte a un string stream.
            getline(lineStream, empData.fecha, ',');        //Recibe cada elemento de la
            getline(lineStream, empData.apellido, ',');     //linea del archivo en su
            getline(lineStream, empData.nombre, ',');       //struct correspondiente para
            getline(lineStream, empData.ss, ',');           //luego pasarlo al vector.
            getline(lineStream, dataPoint, ',');
                empData.horas = atof(dataPoint.c_str());    //Lee los elementos como strings
            getline(lineStream, dataPoint, ',');            //los convierte a double y luego
                empData.payRate = atof(dataPoint.c_str());  //los pasa al struct de NomData.
            empleado.push_back(empData);    // Asigna los valores leidos al vector original,
        }                                   //en el indice original, pasados por referencia.
        archivo.close();
        return true;                    //Cierra el archivo CSV e indica que leyo elarchivo.
    }
    else {
        int tryAgain = 0;
        cout << "ERROR: No se pudo encontrar unarchivo con el nombre " << csv << endl;
        cout << "Si esea intentar de nuevo, entre cualquier numero. De lo contrario,";
        cout << " solo oprima ENTER." << endl;
        cin >> tryAgain;
        if(tryAgain > 0){
            Nomina();
        }
        else
            return false;
    }
}
void headerCheck(ifstream& archivo){
    int header = 0, footer = 0;
    string throwAway;
    cout << "Archivo abierto exitosamente.\n" << endl << "Si su archivo tiene encabezado, favor";
    cout << " indique de cuantas lineas es:\t";
    cin >> header;
    while(header > 0){
        getline(archivo, throwAway);
        header--;
    }
    cout << "\nSi su archivo tiene pie de pagina (footer), favor indique cuantas lineas tiene:\t";
    cin >> footer;
    while(footer > 0){
        getline(archivo, throwAway);
        footer--;
    }
}
void print(const int n, const vector<Empleado>& empleado){
    cout << "[" << n << "]\t";                      //Para todos los elementos en empleados:
    cout << empleado[n].fecha << ", ";              //imprime los datos de cada empleado
    cout << empleado[n].apellido << ", ";           //separado por comas, hasta que llega al
    cout << empleado[n].nombre << ", ";             //final de la data de ese empleado.
    cout << empleado[n].ss << ", ";                 //Donde, entonces, separa a los empleados
    cout << empleado[n].horas << ", ";              //por una linea nueva
    cout << empleado[n].payRate << ", ";
    cout << empleado[n].payBase << ", ";            //Con mas tiempo hubiera hecho una funcion
    cout << empleado[n].payOvertime << ", ";        //que combinara parte de write y print a una
    cout << empleado[n].payDeduction << ", ";       //sola funcion que recibe la instruccion
    cout << empleado[n].netPay << "\n";             //'cout', 'nomina', etc. >:/
}
void Write(const vector<Empleado> & empleado){
    string nombreArchivo;
    cout << "Obviando la extension de tipo, entre el nombre que desea ponerle a su archivo de nomina: ";
    getline(cin, nombreArchivo);
    nombreArchivo += ".csv";

    ofstream nomina;                        //Crea y abre el nuevo archivo.
    nomina.open(nombreArchivo.c_str());

    nomina << "Fecha, Apellido, Nombre, Seguro Social, Horas Trabajadas, Salario por Hora, ";
    nomina << "Salario Grueso, Salario por Overtime, Deducciones Semanales, Salario Neto\n";
    cout << "Fecha, Apellido, Nombre, Seguro Social, Horas, Salario, Paga Gruesa, Overtime, ";
    cout << "Deducciones, Salario Neto" << endl;

    double nominaTotal = 0;                 //Cuenta el total pagado a todos los empleados

    for (int i=0; i < empleado.size(); i++)
    {
    nomina << empleado[i].fecha << ", ";
    nomina << empleado[i].apellido << ", ";         //Para todos los elementos en empleados:
    nomina << empleado[i].nombre << ", ";           //escribe los datos de cada empleado
    nomina << empleado[i].ss << ", ";               //separado por comas, hasta que llega al
    nomina << empleado[i].horas << ", ";            //final de la data de ese empleado.
    nomina << empleado[i].payRate << ", ";          //Donde, entonces, separa a los empleados
    nomina << empleado[i].payBase << ", ";          //por una linea nueva
    nomina << empleado[i].payOvertime << ", ";
    nomina << empleado[i].payDeduction << ", ";
    nomina << empleado[i].netPay << "\n";

    print(i, empleado);
    nominaTotal += empleado[i].netPay;      //Sumatoria de la paga neta de cada empleado.
    }

    nomina << endl << "Total de nomina:\t" << nominaTotal;  //Escribe footer con sumatoria.
    cout << endl << "Total de nomina:\t\t" << nominaTotal;  //Despliega sumatoria en pantalla
    nomina.close();
}
void Menu(vector<Empleado> empleado){
    char choice;
    cout << "OPCIONES ADICIONALES: Entre su seleccion y oprima ENTER. \n " << endl;
    cout << "\tPara calcular la nomina de una Porcion del archivo, oprima P.\n" << endl;
    cout << "\tPara calcular la nomina de un Empleado especifico, oprima E.\n" << endl;
    cout << "\tPara calcular otra Nomina, oprima N.\n" << endl;
    cout << "Para terminar, solo oprima ENTER.";
    cin >> choice;

    switch(choice){
    case 'P':
    case 'p':
        employeeRange(empleado);
        break;
    case 'E':
    case 'e':
        employeeSingle(empleado);
        break;
    case 'N':
    case 'n':
        Nomina();
        break;
    default:
        cout << "Fin de programa de nominas. Presione ENTER para terminar." << endl;
        break;
    }
}
void employeeRange(const vector<Empleado>& empleado){
    int ind, indexL = -1, indexR = -1;
    cout << "Usted selecciono mirar las nominas de un rango de empleados." << endl;
    cout << "Primer empleado: ";        //Obtiene el rango
    getIndex(indexL);
    if(indexL < 0)
        indexL = findIndex(empleado);

    cout << endl << "Segundo empleado: ";
    getIndex(indexR);
    if(indexR < 0)
        indexR = findIndex(empleado);

    for(ind = indexL; ind <= indexR; ind++){
        print(ind, empleado);
    }
    for(ind = indexR; ind < indexL; ind++){
        print(ind, empleado);
    }
}
void employeeSingle(const vector<Empleado>& empleado){
    string answer;
    int empIndex = -1;

    cout << "Usted selecciono calcular la nomina de un empleado especifico.";
    getIndex(empIndex);

    if(empIndex < 0){
        empIndex = findIndex(empleado);
    }
    print(empIndex, empleado);
}
void getIndex(int& ID){
    cout << "Si conoce el indice del empleado que busca, entrelo a continuacion. De lo contrario, ";
    cout << "oprima ENTER" << endl << "\t \t";
    cin >> ID;
}
int findIndex(vector<Empleado>& empleado){
    string name;
    cout << "Por favor entre el nombre o el apellido delempleado:\t";
    getline(cin, name);
    for(int i=0; i < empleado.size(); i++){
        if(name == empleado[i].nombre || name == empleado[i].apellido)
            return i;
    }
    return -1;
}
