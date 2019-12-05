#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const double deductions = 0.18;
    //Establece el porcentaje de deducciones asumido,
    //de manera accesible para cambiarse facilmente.


//DEBUGGING
const double hrs = 45, r8 = 7.25; //------------------
//DEBUGGING


struct Salary{
    double base;            //Establece un struct
    double overtime;        //que facilita utilizar
    double deduccion;       //multiples funciones para
    double neto;            //realizar los calculos.
};


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
