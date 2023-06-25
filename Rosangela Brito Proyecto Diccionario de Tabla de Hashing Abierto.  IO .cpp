#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#define HASHCLASES 26

using namespace std;

typedef struct celda{
	int valor;				
	string  cadena;			
	struct celda *sig;
}CELDAS;

class Hash_Abierto_Tabla{
private:
	vector<CELDAS*> HashTabla; // Vector de nodos de la lista	
	int HASH_ABIERTO=26;
	int hash; 
	
public:
	//Constructor de la clase o inicializar
	Hash_Abierto_Tabla(int HASH_ABIERTO) {
        this->HASH_ABIERTO = HASH_ABIERTO;
        HashTabla.resize(HASH_ABIERTO);}
    
    unsigned int hash_(int clase){	// Se crea una clave para los modulos		
		unsigned int hash_value=0;

		hash_value = clase % HASHCLASES;	// Se crea el modulo para las palabras 
		return hash_value;}
		
    void Crear_tablas(string nombrearchivo,string texto); //Permite crear la Tabla de Hash y generar sus modulos
	void insertar (int valor, string cadena); //Carga las palabras a la Tabla de Hash
	CELDAS buscar(int eleccion); //Busca elementos en el diccionario y verifica que forma parte de la lista de los modulos 					
	string agregar (int eleccion); //Agrega una palabra al diccionario y lo lleva a su modulo					
	CELDAS eliminar (int valor,string cadena); //Elimina un elemento del diccionario y verifica si lo pudo eliminar
	int modificar ();//Modifica una palabra del diccionario				
	void agrupacion_alfab(int valor, char letra); 	//Recorre las palabras de la tabla y las agrupa en sus claves 
	void Imprimir_tabla(); 	//Imprime la Tabla de Hash de manera alfabetica
};

//Funcion de insertar (inserta el texto del archivo en la Tabla de Hash)
void Hash_Abierto_Tabla::insertar(int valor, string cadena){	
	CELDAS* nodo = new CELDAS;		// Crea un nuevo nodo;
	nodo->valor = valor;			// Guarda la informacion en el nodo
	nodo->cadena = cadena;
	nodo->sig = NULL;				// El primero ya no apunta a NULL, el siguiente apunta ahora a NULL
	int Ascii_cod;
	char carac ;
	
	if (HashTabla[valor] == NULL){
		HashTabla[valor] = nodo;}
	else{
		CELDAS *nodo_presente = HashTabla[valor];
		while(nodo_presente->sig != NULL){
			nodo_presente = nodo_presente->sig;	}
		nodo_presente->sig = nodo;
	}
}

// Verifica si la palabra pertenece a la lista y permite buscarla
 CELDAS Hash_Abierto_Tabla::buscar(int eleccion) {
    int valor;
    CELDAS *nodo_presente;
	CELDAS nodo_vacio;
		// Obtenemos la posicion en la tabla	
	if (eleccion == 1){ //Muestra todos los elementos pertenecientes a una clave
		cout<<endl<<endl<<"Ingrese la clave que desea buscar buscar en la tabla: ";	
		cin>>valor;
		// Recorremos la lista enlazada buscando la clave
        nodo_presente = HashTabla[valor];
        while (nodo_presente != NULL) {
       	if (nodo_presente-> valor == valor) {  
	    	while (nodo_presente != NULL) {	
              		cout << "(" << nodo_presente->valor << ", " << nodo_presente->cadena << ")\n";
               		nodo_presente = nodo_presente->sig;
           		}    
           	}
       	}
        return nodo_vacio; // Si no se encuentra la clave, se retorna -1		
		}
		if (eleccion == 2){ //Se debe ingresar un elemento con una clave y verifica que pertenece o no 
			cout<<endl<<endl<<"Ingrese la clave que desea buscar: ";
			cin>>valor;
			string palabraBuscada;
			cout<<endl<<endl<<"Ingrese la palabra que desea buscar: ";
			fflush(stdin);
			getline(cin,palabraBuscada);
			fflush(stdin);
			nodo_presente = HashTabla[valor];
			while(nodo_presente!=NULL){
				if (nodo_presente-> valor == valor) { 
		 			while (nodo_presente-> valor != NULL) {
						//buscamos la palabra en cadena de caraces del nuevo nodo
						if(nodo_presente->cadena.find(palabraBuscada) != string::npos) {
            			cout<<nodo_presente->cadena <<endl;
        				return *nodo_presente; }
        				nodo_presente= nodo_presente->sig; // Pasamos al siguiente nodo en la lista	
						}	
    				return nodo_vacio; }
					}
			return nodo_vacio; // Si no se encuentra la clave, se retorna 
			}
}

//Agrega una palabra al diccionario
string Hash_Abierto_Tabla::agregar(int eleccion){
	CELDAS T;
	int valor, Ascii_cod;
	string cadena,palabra,significado;	
	string corchete1="[";
	string corchete2="]. ";
	char carac;
	if(eleccion == 1){
		cout<<"Digite la nueva palabra: "<<endl;
		fflush(stdin);
		getline(cin,palabra);
		cout<<"Digite el nuevo significado: "<<endl;
		fflush(stdin);
		getline(cin,significado);
		fflush(stdin);
		cadena = corchete1+palabra+corchete2+significado;
		cout<<"La nueva cadena es: "<<cadena<<endl;
		carac = cadena[1];		// Toma la primera letra de la cadena del archivo de texto
		Ascii_cod = int(carac);// Obtiene el valor en int de la letra
		hash=hash_(Ascii_cod);	// Obtiene la llave
		T.cadena=cadena;
		T.valor=hash;
		insertar(T.valor,T.cadena);
		ofstream archivo1("diccionario.txt", std::ios::app); //Abrimos el archivo en modo anadir
		archivo1<<cadena;
		archivo1.close();
		ofstream archivo2("modificado.txt", std::ios::app);
		archivo2<<"Se agrego la palabra: "<<cadena<<" \n\n";
		archivo2.close();
	}
	
	if (eleccion==2){
		cout<<"Digite la nueva palabra: "<<endl;
		fflush(stdin);
		getline(cin,palabra);
	
		cout<<"Digite el nuevo significado: "<<endl;
		fflush(stdin);
		getline(cin,significado);
		fflush(stdin);
		cadena = corchete1+palabra+corchete2+significado;
		cout<<"La nueva cadena es: "<<cadena<<endl;
		carac = cadena[1];		// Toma la primera letra de la cadena del archivo de texto
		Ascii_cod = int(carac);// Obtiene el valor en int de la letra
		hash=hash_(Ascii_cod);	// Obtiene la llave
		
		T.cadena=cadena;
		T.valor=hash;
		insertar(T.valor,T.cadena);	
	
	return cadena;	
	}
}

//Elimina una palabra del diccionario
CELDAS Hash_Abierto_Tabla::eliminar(int valor, string cadena){
   	CELDAS *nodo_presente;
	CELDAS salida;
	bool bandera = false;
	nodo_presente = HashTabla[valor];
		
	while(nodo_presente!=NULL){
		if (nodo_presente-> valor == valor){ 
		 	while (nodo_presente-> valor != NULL){
				//buscamos la palabra en cadena de caraces del nuevo nodo
				if(nodo_presente->cadena.find(cadena) != string::npos) {
           			
        			CELDAS* nodo_presente = HashTabla[valor];
        			CELDAS* nodo_anterior = NULL;
        				
        			while(nodo_presente != NULL && nodo_presente->cadena != nodo_presente->cadena){
        				nodo_anterior = nodo_presente;
    					nodo_presente = nodo_presente->sig;			
					}	
        			if (nodo_presente == NULL) {
            			cout << "Ocurrio un error";} 
        				else {
           					if (nodo_anterior == NULL) {
             					HashTabla[valor] = nodo_presente->sig;
           				}
            			else {
             		   	nodo_anterior->sig = nodo_presente->sig;
          				}
        
          				ifstream exit;  					
          				exit.open("diccionario.txt", ios::in);
          				ofstream entrada;
          				entrada.open("temporal.txt", ios::out);
          				ofstream modif;
						modif.open("modificado.txt", std::ios::app);
          				if(exit.fail()){
          					cout<<endl<<"Ocurrio un error al abrir el archivo de diccionario.";
							}
          				string texto;
          				string almacenar;	
          				while(getline(exit,texto)){
							bandera=0;
							if(texto.find(nodo_presente->cadena) != string::npos){
								cout<<endl<<endl<<"Se elimino la palabra..."<<endl<<endl;
								bandera=1;
								}
								if(bandera==0){
								almacenar=almacenar+texto+"\n";}
							}
							entrada<<almacenar;
							modif<<"Se elimino: "<<nodo_presente->cadena<<"\n\n";
							exit.close();
          					entrada.close();
          					modif.close();
          					remove("diccionario.txt");
       						rename("temporal.txt","diccionario.txt");
           					delete nodo_presente;// Borra el nodo ingresado por el usuario
           					bandera = true;			           				 
           				 if (bandera == true){
           				 	return salida;}
       			   		}
					}
        				nodo_presente= nodo_presente->sig;// Pasamos al siguiente nodo en la lista		
				}	
    				return salida; //cerramos el ciclo 
			}
		}
				return salida; // Si no se encuentra la clave, se retorna -1   	
}
		
		
//Modifica las palabras del diccionario
int Hash_Abierto_Tabla::modificar(){
	int eleccion;
	CELDAS nodoEncontrado;
	CELDAS *nodo; CELDAS p;
	int valor;
	string palabra;
	string texto;
	string cadena_new;
	int bandera=0;
		
	cout<<endl<<"Proceso de modificacion: "<<endl;
	cout<<endl<<"Inserte los datos del elemento que va a modificar: "<<endl;
	nodoEncontrado=buscar(2);
	valor= nodoEncontrado.valor;
	palabra=nodoEncontrado.cadena;
	cout<<endl<<endl<<"La cadena obtenida es: "<<nodoEncontrado.cadena<<endl<<endl;
	cadena_new=agregar(2);	
	eliminar (valor, palabra);
	string almacenar;
	ifstream archivo("diccionario.txt"); //Se abre el archivo de diccionario
	
	if(archivo.fail()){
		 cout << "No se pudo abrir el archivo." << endl;}
	while(getline(archivo,texto)){
		bandera=0;
		if(texto.find(palabra) != string::npos){
		    almacenar=almacenar+cadena_new+"\n";	
			bandera=1;
		}
		if(bandera==0){
		almacenar=almacenar+texto+"\n";
	}
}
	archivo.close();
	ofstream archivo2("diccionario.txt"); 
	string linea;
	string tomartexto;
	while(!archivo2.eof()){	
		if(almacenar.find(cadena_new) != string::npos){
			archivo2<<almacenar;
			break; }		
	}
	archivo2.close();
	ofstream archivo3("modificado.txt", std::ios::app);
	string file;
	archivo3<<"Se agrego "<<cadena_new<<"\n Se elimino "<<nodoEncontrado.cadena<<"\n\n";
	archivo3.close();
}

//Crea la Tabla de Hash e inserta los valores de archivo a la Tabla
void Hash_Abierto_Tabla::Crear_tablas(string nombrearchivo,string texto){
	char carac;
	int Ascii_cod;
	int valor;
	CELDAS p;
	
	carac = texto[1];		// Toma la primera letra de la cadena del archivo de texto
	Ascii_cod = int(carac);// Obtiene el valor en int de la letra
	hash=hash_(Ascii_cod);	// Obtiene la llave
	p.cadena=texto;
	p.valor=hash;
	
	insertar(p.valor, p.cadena);	// Se insertan las palabras a la tabla	
}

//Funcion de sub indice para la la funcion de eliminar
int sub_indice(char letra){
	int Ascii_cod;
	Ascii_cod = int(letra);
	return Ascii_cod % HASHCLASES;	
}

//Recorre la Tabla de Hash colocandole sus modulos y la prepara para alfabetizar 
void Hash_Abierto_Tabla::agrupacion_alfab(int valor, char letra){
		CELDAS *nodo_presente;
	   	CELDAS nodo_vacio;
	  	nodo_presente = HashTabla[valor];
	  	cout<<"|" <<letra<< "| " <<"Clave -> "<<"|"<<valor<<"|:"<<endl<<endl;"\n\n";
        	while (nodo_presente != NULL) {
            	if (nodo_presente-> valor == valor) {  
			    	while (nodo_presente != NULL) {	
                		cout <<"	"<< nodo_presente->cadena << "\n";
                		nodo_presente = nodo_presente->sig; }
				cout<<"\n\n";	   
			    break; //cerramos el ciclo  
				}
        	}
}

//Muestra la Tabla de Hash de manera que sus modulos estan organizados alfabeticamente
void Hash_Abierto_Tabla::Imprimir_tabla(){
	  int valor;
	   		cout<<endl<<endl<<"El diccionario ordenado en orden alfabetico"<<endl<<endl;
			// Imprime la letra 'a'
			valor = sub_indice('a'); agrupacion_alfab(valor,'A');
        	valor = sub_indice('b'); agrupacion_alfab(valor,'B');
			valor = sub_indice('c'); agrupacion_alfab(valor,'C');
       		valor = sub_indice('d'); agrupacion_alfab(valor,'D');
       		valor = sub_indice('e'); agrupacion_alfab(valor,'E');
       		valor = sub_indice('f'); agrupacion_alfab(valor,'F');
       		valor = sub_indice('g'); agrupacion_alfab(valor,'G');
       		valor = sub_indice('h'); agrupacion_alfab(valor,'H');
       		valor = sub_indice('i'); agrupacion_alfab(valor,'I');
       		valor = sub_indice('j'); agrupacion_alfab(valor,'J');
       		valor = sub_indice('k'); agrupacion_alfab(valor,'K');
       		valor = sub_indice('l'); agrupacion_alfab(valor,'L');
       		valor = sub_indice('m'); agrupacion_alfab(valor,'M');
       		valor = sub_indice('n'); agrupacion_alfab(valor,'N');
       		valor = sub_indice('o'); agrupacion_alfab(valor,'O');
       		valor = sub_indice('p'); agrupacion_alfab(valor,'P');
      		valor = sub_indice('q'); agrupacion_alfab(valor,'Q');
       		valor = sub_indice('r'); agrupacion_alfab(valor,'R');
       		valor = sub_indice('s'); agrupacion_alfab(valor,'S');
       		valor = sub_indice('t'); agrupacion_alfab(valor,'T');
			valor = sub_indice('u'); agrupacion_alfab(valor,'U');
			valor = sub_indice('v'); agrupacion_alfab(valor,'V');
       		valor = sub_indice('w'); agrupacion_alfab(valor,'W');
       		valor = sub_indice('x'); agrupacion_alfab(valor,'X');
       		valor = sub_indice('y'); agrupacion_alfab(valor,'Y');
       		valor = sub_indice('z'); agrupacion_alfab(valor,'Z');	
}

//Llamamos a todas las demas y que ingrese un archivo de texto que debe abrir
void muestra_archivo(){
	
	int valor, eleccion;
	string cadena;
	int clav;
	string cad, palabra;
	string nombrearchivo;
	string texto;
	string palabraBuscada;
	CELDAS *nodo_presente;	
	char letra;
	int val;
	ifstream archivo;	//Se lee un archivo
	Hash_Abierto_Tabla HASHING= Hash_Abierto_Tabla(HASHCLASES);
	
	do{	//Se busca el archivo y se abre
		cout<<"Escribe el nombre del archivo de texto que desees (que termine en .txt)"<<endl<<">";	
		fflush(stdin);
		getline(cin,nombrearchivo);
		archivo.open(nombrearchivo.c_str(),ios::in);		
		
		if (archivo.fail()){
			cout<<endl<<"No se encontro el archivo,vuelva a insertar el nombre del archivo que desea buscar"<<endl<<endl;	
			system("pause"); }
		system("cls");
	}while (archivo.fail());//Si no encuentra el archivo, pide al usuario que digite el documento otra vez
	int opcion;
	cout << "\t\t\t\t+=+=+=+=+=+DICCIONARIO EN LINEA+=+=+=+=+=+"<<endl<<endl;
    do {
        cout << "Elija una opcion del menu: " <<endl<<endl;
        cout << "1)- Insertar las palabras del documento a la tabla de Hasing Abierto: " << endl;
        cout << "2)- Buscar una palabra: " << endl;
        cout << "3)- Imprimir Tabla de Hashing Abierto: " << endl;
        cout << "4)- Agregar una palabra al diccionario: " << endl;
        cout << "5)- Eliminar una palabra del diccionario: " << endl;
        cout << "6)- Modificar una palabra del diccionario: " << endl;
        cout << "7)- Salir del programa: " << endl;
      	cout << ">";
        cin >> opcion;
        
         cout <<endl<< endl;
        switch(opcion) {
            case 1:
                cout << "Fue seleccionada la Opcion 1" << endl;
                while(!archivo.eof()){	//ciclo que termina cuando llega al final del archivo
					getline(archivo,texto);
					HASHING.Crear_tablas(nombrearchivo,texto);
				}
                cout <<endl<< "Insertado correctamente" << endl<<endl;
                break;
            case 2:
                cout << "Fue seleccionada la Opcion 2" << endl;
            	cout << "Ingrese la opcion que desea buscar"<<endl<<endl<<"(Opcion 1) Buscar todos los elementos contenidos en la clave"
				<<endl<<endl<<"(Opcion 2) Buscar un elemento especifico de la clave"<<endl<<endl<<"opcion: ";
				cin>>eleccion;
				HASHING.buscar(eleccion);
                break;
            case 3:
                cout << "Fue seleccionada la Opcion 3" << endl;
                HASHING.Imprimir_tabla();
                break;
            case 4:
                cout << "Fue seleccionada la Opcion 4" << endl;
                HASHING.agregar(1);
                break;
            case 5:
                cout << "Fue seleccionada la Opcion 5!" << endl;
					fflush(stdin);
					cout<<"Inserte la palabra que desea eliminar: "<<endl;
                	getline(cin,palabra);
                	letra=palabra[0];
                	sub_indice(letra);
                	val=sub_indice(letra);
                	HASHING.eliminar(val,palabra);
                break;
            case 6:
                cout << "Fue seleccionada la Opcion 6!" << endl;
                HASHING.modificar();
                break;     
			case 7:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    } while (opcion != 7);
	archivo.close();	//se cierra el archivo	
}  

//Funcion main
int main(){
	muestra_archivo();
	return 0;
}