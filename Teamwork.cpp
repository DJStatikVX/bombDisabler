#include <iostream>
#include <cstdlib>

using namespace std; // espacio de trabajo

const int valueRequired = 8995; // valor a superar en el chequeo de bits

extern "C" bool IsValidAssembly(int a, int b, int c); // chequeo de código ensamblador

void InvalidAccess() { // imprime un mensaje de error si el acceso no es correcto

	char errorMessage[] = "El acceso es inválido.";
	errorMessage[16] = 0xa0; // almacena la á

	cout << errorMessage; // imprime que el acceso no es correcto

	exit(0); // finaliza la ejecución del programa

}

void CheckBits() { // comprueba valores específicos de los bits de dos números introducidos

	int a;
	int b;
	
	// Entrada de valores.
	char firstNumberMessage[] = "Introduzca el primer número (32 bits máx): ";
	firstNumberMessage[22] = 0xa3;    // almacena la ú
	firstNumberMessage[38] = 0xa0;    // almacena la á 

	cout << firstNumberMessage;
	cin >> a;
	cout << endl;

	char secondNumberMessage[] = "Introduzca el segundo número (32 bits máx): ";
	secondNumberMessage[23] = 0xa3;   // almacena la ú
	secondNumberMessage[39] = 0xa0;   // almacena la á

	cout << secondNumberMessage;
	cin >> b;
	cout << endl;

	// Se comprueba que el bit 9 de la variable a no sea 0.
	int bit9deA = (a & 0x00000200) >> 9;

	if (bit9deA == 0) {
		InvalidAccess(); // si el bit 9 es cero, acceso inválido
	}

	// Se comprueba que el bit 17 de la variable a y el bit 22 de la variable b sean iguales.
	int bit17deA = (a & 0x00020000) >> 17;
	int bit22deB = (b & 0x00400000) >> 22;

	if (bit17deA != bit22deB) {
		InvalidAccess(); // si no coinciden los bits, acceso inválido
	}

	// Se comprueba que los 12 bits mas significativos de la variable a mas los 20 bits más 
	// significativos de la variable b sean mayor o igual a la constante valueRequired.
	int valueToVerificate = (a & 0xfff00000) + (b & 0x000fffff);

	if (valueToVerificate < valueRequired) {
		InvalidAccess(); // si no alcanza el valor requerido, acceso inválido
	}

}

void CheckPassword() { // comprueba que la contraseña de acceso sea correcta

	char originalPassword[] = "znLUveOVX";
	char userPassword[17]; // admite hasta 16 caracteres (sin contar terminador) 

	char message[] = "Introduce la contraseña: ";
	message[21] = 0xa4; // contiene el código de la ñ

	cout << message;
	cin >> userPassword; // introducción de contraseña por parte del usuario

	// Se comprueba caracter a caracter que la contraseña coincida con la correcta
	for (int i = 0; i < sizeof(originalPassword); i++) {
		if (userPassword[i] != originalPassword[i]) {
			InvalidAccess(); // si no coincide, el acceso es inválido
		}
	}

}

void CheckAssembly() { // pide tres enteros y llama a IsValidAssembly()

	int a;
	int b;
	int c;

	char numbersMessage[] = "Introduce tres números enteros:";
	numbersMessage[16] = 0xa3; // almacena la ú

	cout << numbersMessage << endl;

	cin >> a;
	cin >> b;
	cin >> c;

	if (!IsValidAssembly(a, b, c)) {
		InvalidAccess(); // si devuelve false, el acceso es inválido
	}

}

// Pide un entero de 32 bits y comprueba que sus bits 10 y 2 sean iguales
void CheckInlineAssembly() {

	int a;

	char numberMessage[] = "Introduce un número entero: ";
	numberMessage[14] = 0xa3; // almacena la ú

	cout << numberMessage;

	cin >> a;

	bool valid; // almacena el resultado de la comparación

	__asm {

		mov ebx, 00000400h       // máscara de bit 10
		mov eax, [a]             // pasa el valor de "a" a eax
		mov ecx, 00000004h       // máscara de bit 2

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
		InvalidAccess(); // si valid es false, el acceso es inválido
	}

}

int main() { // ejecución del programa principal

	CheckPassword();

	CheckBits();

	CheckAssembly();

	CheckInlineAssembly();

	cout << "Acceso correcto"; // si se cumple todo lo anterior

	return 0; // fin del programa

}