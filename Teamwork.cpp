#include <iostream>
#include <cstdlib>

using namespace std; // espacio de trabajo

const int valueRequired = 8995; // valor a superar en el chequeo de bits

extern "C" bool IsValidAssembly(int a, int b, int c); // chequeo de c�digo ensamblador

void InvalidAccess() { // imprime un mensaje de error si el acceso no es correcto

	char errorMessage[] = "El acceso es inv�lido.";
	errorMessage[16] = 0xa0; // almacena la �

	cout << errorMessage; // imprime que el acceso no es correcto

	exit(0); // finaliza la ejecuci�n del programa

}

void CheckBits() { // comprueba valores espec�ficos de los bits de dos n�meros introducidos

	int a;
	int b;
	
	// Entrada de valores.
	char firstNumberMessage[] = "Introduzca el primer n�mero (32 bits m�x): ";
	firstNumberMessage[22] = 0xa3;    // almacena la �
	firstNumberMessage[38] = 0xa0;    // almacena la � 

	cout << firstNumberMessage;
	cin >> a;
	cout << endl;

	char secondNumberMessage[] = "Introduzca el segundo n�mero (32 bits m�x): ";
	secondNumberMessage[23] = 0xa3;   // almacena la �
	secondNumberMessage[39] = 0xa0;   // almacena la �

	cout << secondNumberMessage;
	cin >> b;
	cout << endl;

	// Se comprueba que el bit 9 de la variable a no sea 0.
	int bit9deA = (a & 0x00000200) >> 9;

	if (bit9deA == 0) {
		InvalidAccess(); // si el bit 9 es cero, acceso inv�lido
	}

	// Se comprueba que el bit 17 de la variable a y el bit 22 de la variable b sean iguales.
	int bit17deA = (a & 0x00020000) >> 17;
	int bit22deB = (b & 0x00400000) >> 22;

	if (bit17deA != bit22deB) {
		InvalidAccess(); // si no coinciden los bits, acceso inv�lido
	}

	// Se comprueba que los 12 bits mas significativos de la variable a mas los 20 bits m�s 
	// significativos de la variable b sean mayor o igual a la constante valueRequired.
	int valueToVerificate = (a & 0xfff00000) + (b & 0x000fffff);

	if (valueToVerificate < valueRequired) {
		InvalidAccess(); // si no alcanza el valor requerido, acceso inv�lido
	}

}

void CheckPassword() { // comprueba que la contrase�a de acceso sea correcta

	char originalPassword[] = "znLUveOVX";
	char userPassword[17]; // admite hasta 16 caracteres (sin contar terminador) 

	char message[] = "Introduce la contrase�a: ";
	message[21] = 0xa4; // contiene el c�digo de la �

	cout << message;
	cin >> userPassword; // introducci�n de contrase�a por parte del usuario

	// Se comprueba caracter a caracter que la contrase�a coincida con la correcta
	for (int i = 0; i < sizeof(originalPassword); i++) {
		if (userPassword[i] != originalPassword[i]) {
			InvalidAccess(); // si no coincide, el acceso es inv�lido
		}
	}

}

void CheckAssembly() { // pide tres enteros y llama a IsValidAssembly()

	int a;
	int b;
	int c;

	char numbersMessage[] = "Introduce tres n�meros enteros:";
	numbersMessage[16] = 0xa3; // almacena la �

	cout << numbersMessage << endl;

	cin >> a;
	cin >> b;
	cin >> c;

	if (!IsValidAssembly(a, b, c)) {
		InvalidAccess(); // si devuelve false, el acceso es inv�lido
	}

}

// Pide un entero de 32 bits y comprueba que sus bits 10 y 2 sean iguales
void CheckInlineAssembly() {

	int a;

	char numberMessage[] = "Introduce un n�mero entero: ";
	numberMessage[14] = 0xa3; // almacena la �

	cout << numberMessage;

	cin >> a;

	bool valid; // almacena el resultado de la comparaci�n

	__asm {

		mov ebx, 00000400h       // m�scara de bit 10
		mov eax, [a]             // pasa el valor de "a" a eax
		mov ecx, 00000004h       // m�scara de bit 2

		and ebx, eax
		and ecx, eax

		shr ebx, 10              // desplazamiento a la derecha
		shr ecx, 2               // desplazamiento a la derecha

		cmp ebx, ecx             // se comprueba que sean iguales los bits
		je consecuente

		mov byte ptr [valid], 0  // almacena false en valid
		jmp siguiente

		consecuente:
		mov byte ptr [valid], 1  // almacena true en valid

		siguiente:

	}

	if (!valid) {
		InvalidAccess(); // si valid es false, el acceso es inv�lido
	}

}

int main() { // ejecuci�n del programa principal

	CheckPassword();

	CheckBits();

	CheckAssembly();

	CheckInlineAssembly();

	cout << "Acceso correcto"; // si se cumple todo lo anterior

	return 0; // fin del programa

}