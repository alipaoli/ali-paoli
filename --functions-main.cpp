#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Name{    //---------------------------------------------------
    string nombre;
    string apellido;
};
struct NomData{
    string fecha;
    Name name;
    string ss;
    double horas;
    double rate;
    double base;            
    double overtime;    
    double deduccion;      
    double neto;
};

string intro();
vector<NomData> Leer(string);
void Write(vector<double>);
void Menu();
void CalcSelect();
void CalcSingle();
void Sort();
void Nomina(int);
double Pay(double, double);
Salary bSalary(double;
Salary nSalary(double);
Salary Sal(double, double);

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
    if (!empleados.is_open()){
        cout << "ERROR: No se pudo encontrar un archivo con el nombre " << csv << endl;
        //insertar funcion que pregunta si desea leer otro archivo --------------------------------------------------
    }
    vector<NomData> nom;
    string line;
    while (getline(empleados, line)){
           NomData data(line);      //----------------------------funcion data -----------------------
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
        Sal();
        break;
    }
}


//============================================ SALARY FUNCTIONS ================================================

const double deductions = 0.18;
    //Establece el porcentaje de deducciones asumido,
    //de manera accesible para cambiarse facilmente.


//DEBUGGING
const double hrs = 45, r8 = 7.25; //------------------
//DEBUGGING

double Pay(double hours, double rate){ //Funcion para
    return (hours * rate);  //reducir la cantidad de
}                           //lineas de codigo usadas.

Salary bSalary(double hours, double rate){
    //Calcula slario bruto y overtime, si aplica.
        //La validacion if/else que verifica si le
        //empleadx hizo horas overtime (>40) y
        //se refiere a Pay() para multiplicarlas.

    Salary wage; //Variable Salary temporera.
    if (hours > 40){
        wage.overtime = Pay((hours-40),(rate*2));
        wage.base = Pay(40, rate) + wage.overtime;
    }       //Calcula el salario de le empleadx
            //empezando por las horas overtime y
            //luego sumandolas al total bruto.
    else {
        wage.base = Pay(hours, rate);
    }       //Calcula el salario directamente.
    return wage;
}       //Devuelve emp a la variable Salary principal.

Salary nSalary(double base){
    //Calcula el salario neto y las deducciones.

    Salary wage; //Variable Salary temporera.
    wage.deduccion = base * deductions;
    wage.neto = base * (1.0 - deductions);
    return wage;     //Equivalente a restar dSal.
}

Salary Sal(double hours, double rate) {

    //DEBUGGING
    hours = hrs; //------------------------------------
    rate = r8;   //------------------------------------
    //DEBUGGING

    Salary employee; //Define una variable Salary que
    //recibe las los calculos al llamar las funciones.

    employee = bSalary(hours,rate);    //Llama bSalary
    employee = nSalary(employee.base); //Llama nSalary

    //DEBUGGING COUTS
    cout << employee.base << endl; //------------------
    cout << employee.overtime << endl; //------------------
    cout << employee.deduccion << endl; //------------------
    cout << employee.neto << endl; //------------------
    cout << endl;
    //DEBUGGING COUTS

    return employee;    //Devuelve los calculos a
}                       //la funcion principal.
