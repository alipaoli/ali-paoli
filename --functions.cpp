#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int lines = 0;

struct Name{    //---------------------------------------------------
    string nombre;
    string apellido;
};
struct Empleado{    //-----------------------------------------------
    string fecha;
    Name name;
    string ss;
    double horas;
    double rate;
};
struct Salary{
    double base;            //Establece un struct
    double overtime;        //que facilita utilizar
    double deduccion;       //multiples funciones para
    double neto;            //realizar los calculos.
};
struct NomData{
    Empleado empleado;  // fecha, name.nombre, name.apellido, ss, horas, rate
    Salary salario;     // base, overtime, deduccion, neto
};

string intro();
vector<NomData> Leer(string);
void Write(vector<double>);
void Menu();
void CalcSelect();
void CalcSingle();
void Sort();
void Nomina(int);


int main(){
    string archivo = "text.txt"; //-------- DEBUGGING ------------------------
    vector<NomData> nomData;
    nomData = Leer(archivo);
    return 0;
}


// ================================ FUNCIONES ================================

string intro(){
    string nombre;
    cout << "Saludos, este programa recibe un archivo de nomina CSV con: ";
    cout << "fecha, nombre, seguro social, horas trabajadas y paga por hora.";
    cout << "Luego, calcula el salario bruto, horas sobre-tiempo, deducciones y";
    cout << " salario neto de cada empleado; mas el salario neto total." << endl;
    cout << "Para comenzar, indique el nombre del archivo que desea leer: ";
    cin >> nombre;
    return nombre;
}

vector<NomData> Leer(string csv){
    ifstream empleados(csv);
    if (!empleados.is_open())
        cout << "ERROR: No se pudo encontrar unarchivo con el nombre " << csv << endl;
    vector<NomData> nom;
    string line;
    while (getline(empleados, line)){
           NomData data(line);
           nom.push_back(data);
    }
  empleados.close();
}

void Write(vector<double> nomData){
  fstream nomina;
  nomina.open("out_temp.csv");

  for (int i=0;i < nomData.size();i++)
  {
    nomina << nomData[i]<<",";
  }
  nomina.close();
}

void ShowMenu(){
    cout << "MENU PRINCIPAL: De las siguientes opciones, entre su seleccion y oprima ENTER: \n " << endl;
    cout << "\tPara calcular la nomina de una porcion del archivo oprima A\n" << endl;
    cout << "\tPara calcular la nomina de un empleado especifico oprima B\n" << endl;
    cout << "\tPara calcular el archivo completo solo oprima ENTER\n" << endl;
}
void CalcSelect(){
    cout << "Usted selecciono calcular una porcion de la nomina. Empezando por ";
    cout << "elcomienzo, entre la cantidad empleados desea calcular." << endl;
    cout << "Para retornar al menu principal solo oprima ENTER." << endl << endl;
    cin >> lines;
    if (lines > 0){
        Nomina(lines); //Lama la funcion salario y calcula la nomina.
    }
    else {
        Menu();     //En ausecia de una seleccion, el valor
    }               //el usuario regresa al menu principal.

}
void CalcSingle(){
    string answer;
    cout << "Usted selecciono calcular la nomina de un individuo especifico. Para proseguir, entre";
    cout << " el nombre completo del empleado. \nPara retornar al menu principal entre RETORNAR.\n";
    getline(cin, answer);
    if(answer == "RETORNAR"){
        Menu();
    }
    else Nomina(1); //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% INCOMPLETO
}
void Menu(){
    char choice;
    ShowMenu();
    cin >> choice;

    switch(choice){
    case 'A':
    case 'a':
        CalcSelect();
        break;
    case 'B':
    case 'b':
        CalcSingle();
        break;
    default:
        Nomina();
        break;
    }
}
